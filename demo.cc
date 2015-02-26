#include "BagsColor.h"
#include "Image.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::string dataset("/Users/chunwei/Data/shopping/bags/");
  BagsColor bags(dataset);
  std::vector<Image> training_images = bags.GetTrainingImages();
  std::cout << training_images.size() << std::endl;
  std::vector<Image> test_images = bags.GetTestImages();
  std::cout << test_images.size() << std::endl;
}