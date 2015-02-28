#ifndef IMG_2_HTML_
#define IMG_2_HTML_

#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, float> > RankList;

class Img2Html {
 private:
  std::string filename_;
  RankList list_;

 public:
  void SetFilename(const std::string& filename);
  void SetList(const RankList& list);

  void PrintList(int);
  void PrintLists(int);
};

#endif  // IMG_2_HTML_