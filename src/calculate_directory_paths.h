#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include <vector>
#include <stdexcept>
#include <string>

struct directory_paths calculate_paths( string root_directory );
vector<string> get_files_from_directory( string directory_given );
struct filepaths calculate_filepaths( directory_paths directory_paths_apple_parts );

// calculate directory paths

struct directory_paths {
	std::string root_training_directory;
	std::string positives_training_directory;
	std::string positives_training_directory_raw;
	std::string positives_training_directory_mask;
	std::string negatives_training_directory;
	std::string negatives_training_directory_raw;
	std::string negatives_training_directory_mask;
	std::string root_testing_directory;
};

struct filepaths {
  std::vector<std::string> filepaths_positive_raw;
  std::vector<std::string> filepaths_positive_mask;
  std::vector<std::string> filepaths_negative_raw;
  std::vector<std::string> filepaths_negative_mask;
  std::vector<std::string> filepaths_testing;
};




