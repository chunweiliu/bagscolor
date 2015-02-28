#include "Img2Html.h"

void Img2Html::SetFilename(const std::string& filename) {
  filename_ = filename;
}

void Img2Html::SetList(const RankList& list) { list_ = list; }

void Img2Html::PrintList(int height) {
  std::ofstream file;
  file.open(filename_);

  // Building HTML
  file << "<!DOCTYPE html>" << std::endl;
  file << "<html><body>" << std::endl;
  for (int i = 0; i < list_.size(); ++i) {
    // one row in each loop
    file << "<div>" << std::endl;

    // Print figure
    file << "<img src=\"" << list_[i].first << "\""
         << " height=\"" << height << "\">" << std::endl;

    // Print attributes
    file << "Rank: " << i << std::endl;
    file << "Score: " << list_[i].second << std::endl;

    file << "</div>" << std::endl;
  }
  file << "</body></html>";
  // End of building

  file.close();
}