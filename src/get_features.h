#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include <vector>
#include <stdexcept>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

struct features {
  // needs to have : features, labels
  cv::Mat text_color_features;
  cv::Mat all_labels;
  int length_features;
};

std::vector<cv::KeyPoint> get_grid_over_valid_pixels( cv::Mat mask_img );
cv::Mat get_features( cv::SIFT &extractor, std::string raw_img_path, std::string mask_img_path );
struct features get_all_features( struct filepaths filepaths_apple_parts );
