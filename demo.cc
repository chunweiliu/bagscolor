#include "BagsColor.h"
#include "Image.h"
#include "Img2Html.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Usage: ./demo <dataset> <output_html> <num_query>"
              << std::endl;
  }

  std::string dataset(argv[1]);
  std::string output_html(argv[2]);
  const int kNumQuery = atoi(argv[3]);

  BagsColor bags(dataset);

  const int kLabel = 5;
  Color color[kLabel] = {kBlack, kBrown, kRed, kSilver, kGold};
  std::vector<RankList> ranks;
  for (int i = 0; i < kLabel; ++i) {
    ranks.push_back(bags.Rank(color[i], kNumQuery));
  }

  Img2Html html;
  const int kHeight = 100;
  html.SetFilename(output_html);
  html.SetLists(ranks);
  html.PrintLists(kHeight);
}