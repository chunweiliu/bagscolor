#ifndef BAGS_COLOR_H_
#define BAGS_COLOR_H_

#include "Image.h"

#include <string>
#include <vector>

#include "boost/filesystem.hpp"
// #include <opencv2/ml/ml.hpp>

typedef boost::filesystem::directory_iterator FileIterator;
typedef std::vector<std::pair<std::string, float> > RankList;

class BagsColor {
 private:
  std::string data_folder_;
  std::vector<Image> test_images_;
  std::vector<Image> training_images_;

  cv::Ptr<cv::ml::TrainData> training_data_;
  cv::Ptr<cv::ml::SVM> svm_;

 public:
  BagsColor(std::string);

  std::vector<Image> GetTestImages() const { return test_images_; }
  std::vector<Image> GetTrainingImages() const { return training_images_; }
  cv::Ptr<cv::ml::TrainData> GetTrainData() const { return training_data_; }
  cv::Ptr<cv::ml::SVM> GetSVM() const { return svm_; }

  cv::Mat Image2X(const std::vector<Image>&) const;
  cv::Mat Image2y(const std::vector<Image>&, const Color&) const;

  void PrepareTrainData(const Color&);
  RankList Rank(const Color&, int);
  int SeparateSet();
  void Train(const Color&);

  float CrossValidation(int, const cv::ml::SVM::Params&, const Color&);
  float Error(const cv::Mat&, const cv::Mat&);
};

#endif  // BAGS_COLOR_H_
