# bagscolor
A demo program of a retrieval system based on colors

## How to run this program?
### Prerequisites
- OpenCV
- Boost
- CMake

### Data
Bags image/text description used for this demo program can be found at http://www.tamaraberg.com/teaching/Spring_15/hw/hw2/bags.tar.gz

### Compile and run in command line

1. Download the repository

        git clone https://github.com/chunweiliu/bagscolor
2. Compile the source code
        
        cd bagscolor && mkdir build && cd build && cmake .. && make
3. Run the demo program

        ./demo <dataset> <output_html> <kNumQuery>

Here is an expected result for top 5 queries of the five color attributes: black, brown, red, silver, gold, associated with their information of [rank]: score
![results](images/bags_5x5_5cv.png)

## Overview of the program
1. Mining image color tags using text description
2. Based on the tags from the previous step, separating the dataset to training and test set: Each training image would have one and only one tag, each test image would not contain any tag information.
3. Computing HSV color histogram for each image in training set
4. Training SVM (RBF) using the histogram from the training set
5. Indexing the test set using the visual information
6. Printing the result to a HTML page

### Cross-validation for the RBF Kernel
![rbf](images/rbf.png)

The sigma is important to the radial basis function (RBF) kernel.
The sigma can be determined by cross-validation.
Without cross-validation to choose an optimal sigma, the system can still retrieve reasonable result, such as:
![results](images/bags_5x5.png)
But you might see many artifacts here.
For example, the first column for the black attribute has some silver color purses.
Moreover, the fourth column for the silver attribute has a red bag and a brown bag.
Although the "background" of these two bags are silver, but it is unreasonable to say these two are the top 5.