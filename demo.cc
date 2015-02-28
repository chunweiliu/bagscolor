#include "BagsColor.h"
#include "Image.h"
#include "Img2Html.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "Usage: ./demo <dataset> <output_file> <num_query>"
              << std::endl;
  }

  std::string dataset(argv[1]);
  std::string output_file(argv[2]);
  const int kNumQuery = atoi(argv[3]);

  BagsColor bags(dataset);

  Color color[5] = {kBlack, kBrown, kRed, kSilver, kGold};
  std::vector<RankList> ranks;
  for (int i = 0; i < 5; ++i) {
    ranks.push_back(bags.Rank(color[i], kNumQuery));
  }

  Img2Html html;
  const int kHeight = 100;
  html.SetFilename(output_file);
  html.SetLists(ranks);
  html.PrintLists(kHeight);
}