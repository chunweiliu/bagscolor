#include "BagsColor.h"
#include "Image.h"
#include "Img2Html.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::string dataset("/Users/chunwei/Data/shopping/bags/");
  BagsColor bags(dataset);
  const int num_query = 10;

  Img2Html html;

  RankList rank_red = bags.Rank(kRed, num_query);
  html.SetFilename("/Users/chunwei/Downloads/kRed.html");
  html.SetList(rank_red);
  html.PrintList(100);

  // cv::Mat tmp(5, 1, CV_32F), idx;
  // tmp.at<float>(0, 0) = 1.0;
  // tmp.at<float>(1, 0) = 6.0;
  // tmp.at<float>(2, 0) = 3.0;
  // tmp.at<float>(3, 0) = 4.0;
  // tmp.at<float>(4, 0) = 5.0;
  // cv::sortIdx(tmp, idx, CV_SORT_EVERY_COLUMN + CV_SORT_DESCENDING);
  // std::cout << tmp << std::endl;
  // std::cout << idx << std::endl;

  // cv::Mat A = cv::Mat::eye(3, 3, CV_32F), B;
  // sortIdx(A, B, CV_SORT_EVERY_COLUMN + CV_SORT_ASCENDING);
  // std::cout << A << std::endl;
  // std::cout << B << std::endl;

  // SVM setup
  // SVM training data
  // int n_data = 10;
  // int n_feature = 2;
  // cv::Mat X(n_data, n_feature, CV_32F);
  // cv::Mat y(n_data, 1, CV_32S);  // CV_32S categorical
  // for (int i = 0; i < n_data; ++i) {
  //   float temp = 0.0;
  //   if (i > 5) {
  //     y.at<int>(i) = 0;
  //     temp += i + 0.1;
  //   } else {
  //     y.at<int>(i) = 1;
  //     temp -= i + 0.1;
  //   }
  //   for (int j = 0; j < n_feature; ++j) {
  //     X.at<float>(i, j) = temp;
  //   }
  // }

  // std::cout << "Labels = " << std::endl << y << std::endl << std::endl;
  // std::cout << "Data = " << std::endl << X << std::endl << std::endl;

  // cv::ml::SVM::Params params;
  // params.svmType = cv::ml::SVM::C_SVC;
  // params.kernelType = cv::ml::SVM::LINEAR;
  // // params.gamma = 3;
  // // params.termCrit = cv::TermCriteria(cv::TermCriteria::COUNT, 1000, 0.01);

  // cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create(params);

  // cv::Ptr<cv::ml::TrainData> traindata;  // Pointer need to point to an
  // instance
  // // traindata = cv::ml::TrainData::create(X, cv::ml::ROW_SAMPLE, y);
  // traindata = cv::ml::TrainData::create(X, cv::ml::ROW_SAMPLE, y);

  // std::cout << "getTrainResponses" << traindata->getTrainResponses()
  //           << std::endl;
  // std::cout << "getTrainNormCatResponses"
  //           << traindata->getTrainNormCatResponses() << std::endl;
  // svm->train(traindata);

  // cv::Mat y_(n_data, 1, CV_32S);
  // svm->predict(X, y_);
  // std::cout << "predict" << y_ << std::endl;
  // // svm->train(X, cv::ml::ROW_SAMPLE, y);
}