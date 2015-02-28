#ifndef IMAGE_H_
#define IMAGE_H_

// #include <algorithm>
#include <string>
#include <fstream>

#include "opencv/cv.hpp"
#include "opencv2/opencv.hpp"

enum Color { kBlack, kBrown, kGold, kRed, kSilver, kUnknown, kNull };

class Image {
 private:
  std::string descr_name_;
  std::string img_name_;
  Color tag_ = kNull;

  cv::MatND feature_;
  // cv::Mat image_;

 public:
  Image(std::string);

  std::string GetDescrName() const { return descr_name_; }
  std::string GetImgName() const { return img_name_; }
  Color GetTag() const { return tag_; }
  cv::MatND GetFeature() const { return feature_; }
  // cv::Mat GetImage() { return image_; }

  Color HasColor(std::string);
  bool Replace(std::string&, const std::string&, const std::string&);
  void MiningTag();

  void ComputeFeature();
};

#endif  // IMAGE_H_