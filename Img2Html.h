#ifndef IMG_2_HTML_
#define IMG_2_HTML_

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, float> > RankList;

class Img2Html {
 private:
  std::string filename_;
  std::vector<RankList> lists_;

 public:
  void SetFilename(const std::string&);
  void SetLists(const std::vector<RankList>&);

  void PrintLists(int);
};

#endif  // IMG_2_HTML_