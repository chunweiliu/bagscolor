#include "Image.h"

Image::Image(std::string name) {
  if (name.find("img") > 0 && name.compare(name.size() - 3, 3, "jpg") == 0) {
    img_name_ = name;
    Replace(name, "img", "descr");
    Replace(name, "jpg", "txt");
    descr_name_ = name;
  } else if (name.find("descr") > 0 &&
             name.compare(name.size() - 3, 3, "txt") == 0) {
    descr_name_ = name;
    Replace(name, "descr", "img");
    Replace(name, "txt", "jpg");
    img_name_ = name;
  } else {
    std::cout << "Unsupported format" << std::endl;
    return;
  }
  // retrieve feature and meta data
  MiningTag();
  ComputeFeature();
}

bool Image::Replace(std::string& str, const std::string& from,
                    const std::string& to) {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos) return false;
  str.replace(start_pos, from.length(), to);
  return true;
}

Color Image::HasColor(std::string word) {
  std::transform(word.begin(), word.end(), word.begin(),
                 ::tolower);  // to lower case
  if (word == "black") return kBlack;
  if (word == "brown") return kBrown;
  if (word == "gold") return kGold;
  if (word == "red") return kRed;
  if (word == "silver") return kSilver;
  return kUnknown;
}

void Image::MiningTag() {
  std::ifstream infile(descr_name_);
  std::string word;
  while (infile >> word) {
    tag_ = HasColor(word);
    if (tag_ != kUnknown) break;
  }
  infile.close();
}

void Image::ComputeFeature() {
  cv::Mat image =
      cv::imread(img_name_, 1);  // flag>0 Return a 3-channel color image
  cv::Mat hsv_image;
  cv::cvtColor(image, hsv_image, CV_BGR2HSV);

  const int hist_size[] = {10, 10, 10};
  const int channels[] = {0, 1};
  const float h_ranges[] = {0, 180};
  const float s_ranges[] = {0, 256};
  const float v_ranges[] = {0, 256};
  const float* ranges[] = {h_ranges, s_ranges, v_ranges};
  cv::calcHist(&hsv_image, sizeof(hsv_image) / sizeof(cv::Mat), channels,
               cv::Mat(), feature_, sizeof(hist_size) / sizeof(int), hist_size,
               ranges, true, false);
}

// void Image::ComputeFeature() { st }