#include "BagsColor.h"

BagsColor::BagsColor(std::string name) : data_folder_(name) { SeparateSet(); }

cv::Mat BagsColor::Image2X(const std::vector<Image>& images) const {
  int n_data = images.size();
  int n_feature = images[0].GetFeature().reshape(0, 1).cols;
  cv::Mat X(n_data, n_feature, CV_32F);
  for (int i = 0; i < images.size(); ++i) {
    cv::Mat row = images[i].GetFeature().reshape(0, 1);  // channel, row
    for (int j = 0; j < row.cols; ++j) {
      X.at<float>(i, j) = row.at<float>(j);
    }
  }
  return X;
}

cv::Mat BagsColor::Image2y(const std::vector<Image>& images,
                           const Color& color) const {
  int n_data = images.size();
  int n_feature = images[0].GetFeature().reshape(0, 1).cols;
  cv::Mat y(n_data, 1, CV_32S);  // use int type for categorical
  for (int i = 0; i < images.size(); ++i) {
    if (images[i].GetTag() == color) {
      y.at<int>(i) = 0;
    } else {
      y.at<int>(i) = 1;
    }
  }
  return y;
}

void BagsColor::PrepareTrainData(const Color& color) {
  cv::Mat X = Image2X(training_images_);
  cv::Mat y = Image2y(training_images_, color);
  // Pointer need to point to an instance
  training_data_ = cv::ml::TrainData::create(X, cv::ml::ROW_SAMPLE, y);
}

RankList BagsColor::Rank(const Color& color, int top) {
  Train(color);

  cv::Mat X = Image2X(test_images_);
  cv::Mat y(test_images_.size(), 1, CV_32S);
  svm_->predict(X, y, cv::ml::StatModel::RAW_OUTPUT);  // y for predicted score,
                                                       // the heightest score
                                                       // cooresponding to the
                                                       // label 0
  cv::Mat idx;
  cv::sortIdx(y, idx, CV_SORT_EVERY_COLUMN + CV_SORT_DESCENDING);

  RankList rank;
  for (int i = 0; i < top; ++i) {
    std::pair<std::string, float> element;
    element.first = test_images_[idx.at<int>(i)].GetImgName();
    element.second = y.at<float>(idx.at<int>(i));
    rank.push_back(element);
  }
  return rank;
}

int BagsColor::SeparateSet() {
  FileIterator end_itr;
  for (FileIterator itr(data_folder_); itr != end_itr; ++itr) {
    if (boost::filesystem::is_regular_file(itr->path())) {  // if not folder
      std::string name = itr->path().string();
      if (name.find("img") > 0 &&
          name.compare(name.size() - 3, 3, "jpg") == 0) {
        Image image(name);
        if (image.GetTag() == kUnknown)
          test_images_.push_back(image);
        else
          training_images_.push_back(image);
      }
    }
  }
  return training_images_.size();
}

void BagsColor::Train(const Color& color) {
  std::cout << "Train " << color << std::endl;
  PrepareTrainData(color);

  // SVM setup
  cv::ml::SVM::Params params;
  params.svmType = cv::ml::SVM::C_SVC;
  params.kernelType = cv::ml::SVM::RBF;
  // params.gamma = 3;

  float gammas[20] = {1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3, 1e4,
                      1e5,  2,    4,    8,    16,   32,  64,  128, 256, 512};
  // float gammas[2] = {1, 3};
  float best_gamma = gammas[0], best_error = 100.0;
  const int kFold = 5;
  for (int i = 0; i < 20; ++i) {
    params.gamma = gammas[i];
    float error = CrossValidation(
        kFold, params,
        color);  // Very high error, but with good visualization results?
    if (error < best_error) {
      best_error = error;
      best_gamma = gammas[i];
    }
    std::cout << ".. Gamma: " << gammas[i] << " (" << error << "%)"
              << std::endl;
  }
  std::cout << ">> Best Gamma: " << best_gamma << " (" << best_error << "%)"
            << std::endl;
  params.gamma = best_gamma;
  svm_ = cv::ml::SVM::create(params);
  svm_->train(training_data_);
}

float BagsColor::CrossValidation(int fold, const cv::ml::SVM::Params& params,
                                 const Color& color) {
  float error = 0.0;

  for (int i = 0; i < fold; ++i) {
    // take a partion out of training_images
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create(params);

    std::vector<Image> train, test;
    for (int j = 0; j < training_images_.size(); ++j) {
      if (j % fold == i) {
        test.push_back(training_images_[j]);
      } else {
        train.push_back(training_images_[j]);
      }
    }

    // Train on the training portion
    cv::Mat train_X = Image2X(train);
    cv::Mat train_y = Image2y(train, color);
    cv::Ptr<cv::ml::TrainData> train_data;
    train_data =
        cv::ml::TrainData::create(train_X, cv::ml::ROW_SAMPLE, train_y);
    svm->train(train_data);

    // Test on the test protion
    cv::Mat test_X = Image2X(test);
    cv::Mat test_y = Image2y(test, color);
    cv::Ptr<cv::ml::TrainData> test_data;
    test_data = cv::ml::TrainData::create(test_X, cv::ml::ROW_SAMPLE, test_y);

    cv::Mat predict_y(test.size(), 1, CV_32S);  // predict_y not correct

    // error += svm->calcError(test_data, false, predict_y);  // 0%-100%

    svm->predict(test_X, predict_y);
    error += (float)Error(test_y, predict_y);

    // std::cout << test_y << predict_y << std::endl;
    // std::cout << error << std::endl;
    // cv::waitKey(0);
    // std::cout << "fold " << i + 1 << ": " << error << std::endl;
  }
  return error / (float)fold;
}

float BagsColor::Error(const cv::Mat& y1, const cv::Mat& y2) {
  float error = 0;
  for (int i = 0; i < y1.rows; ++i) {
    if (abs(y1.at<float>(i) - y2.at<float>(i)) > 0.1) {
      // std::cout << y1.at<float>(i) << " " << y2.at<float>(i) << std::endl;
      error++;
    }
  }
  return error;
}