#include "BagsColor.h"

BagsColor::BagsColor(std::string name) : data_folder_(name) { SeparateSet(); }

int BagsColor::SeparateSet() {
  FileIterator end_itr;
  for (FileIterator itr(data_folder_); itr != end_itr; ++itr) {
    if (boost::filesystem::is_regular_file(itr->path())) {  // not folder
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