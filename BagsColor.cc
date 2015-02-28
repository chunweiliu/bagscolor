#include "BagsColor.h"

BagsColor::BagsColor(std::string name) : data_folder_(name) { SeparateSet(); }

cv::Mat BagsColor::Image2Mat(const std::vector<Image>& images) const {
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

void BagsColor::PrepareTrainData(Color color) {
  cv::Mat X = Image2Mat(training_images_);
  cv::Mat y(training_images_.size(), 1,
            CV_32S);  // use int type for categorical

  for (int i = 0; i < training_images_.size(); ++i) {
    if (training_images_[i].GetTag() == color) {
      y.at<int>(i) = 0;
    } else {
      y.at<int>(i) = 1;
    }
  }
  // Pointer need to point to an instance
  training_data_ = cv::ml::TrainData::create(X, cv::ml::ROW_SAMPLE, y);
}

RankList BagsColor::Rank(Color color, int top) {
  Train(color);

  cv::Mat X = Image2Mat(test_images_);
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

void BagsColor::Train(Color color) {
  PrepareTrainData(color);

  // SVM setup
  cv::ml::SVM::Params params;
  params.svmType = cv::ml::SVM::C_SVC;
  params.kernelType = cv::ml::SVM::RBF;
  params.gamma = 3;

  svm_ = cv::ml::SVM::create(params);
  svm_->train(training_data_);
}
