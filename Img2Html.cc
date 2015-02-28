#include "Img2Html.h"

void Img2Html::SetFilename(const std::string& filename) {
  filename_ = filename;
}

void Img2Html::SetLists(const std::vector<RankList>& lists) { lists_ = lists; }

void Img2Html::PrintLists(int height) {
  std::ofstream file;
  file.open(filename_);

  // Building HTML
  file << "<!DOCTYPE html>" << std::endl;
  file << "<html><body>" << std::endl;
  for (int i = 0; i < lists_[0].size(); ++i) {
    // one row in each loop
    file << "<div>" << std::endl;

    for (int j = 0; j < lists_.size(); ++j) {
      // Print figure
      file << "<img src=\"" << lists_[j][i].first << "\""
           << " height=\"" << height << "\">" << std::endl;

      // Print attributes
      file << "[" << i + 1 << "]:" << std::endl;  // rank
      file << std::setprecision(3) << lists_[j][i].second
           << std::endl;  // score
    }

    file << "</div>" << std::endl;
  }
  file << "</body></html>";
  // End of building

  file.close();
}