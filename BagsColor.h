#ifndef BAGS_COLOR_H_
#define BAGS_COLOR_H_

#include "Image.h"

#include <string>
#include <vector>

#include "boost/filesystem.hpp"

typedef boost::filesystem::directory_iterator FileIterator;

class BagsColor {
 private:
  std::string data_folder_;
  std::vector<Image> training_images_;
  std::vector<Image> test_images_;

 public:
  BagsColor(std::string);

  std::vector<Image> GetTrainingImages() { return training_images_; }
  std::vector<Image> GetTestImages() { return test_images_; }

  int SeparateSet();
};

#endif
