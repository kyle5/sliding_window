#include <ml_helpers.h>
using namespace std;
using namespace cv;
// f train rand forest
CvRTrees create_random_forest( struct features features_apple_parts ) {
  
  CvRTrees randomForest;
  CvRTParams randomForest_params;
  int randomForest_max_depth;
  int randomForest_min_sample_count;
  float randomForest_regression_accuracy;
  bool randomForest_use_surrogates;
  int randomForest_max_categories;
  float *randomForest_priors;
  bool randomForest_calc_var_importance;
  int randomForest_nactive_vars;
  int randomForest_max_trees;
  int randomForest_forest_accuracy;
  int randomForest_term_criteria;
  //Principal Components Analysis feature reduction members and variables
  int pca_num_components;
  Mat pca_mean;
  PCA pca_structure;

  pca_num_components = 32;
  randomForest_max_depth = 15;
  randomForest_min_sample_count = 50;
  randomForest_regression_accuracy = 0.f;
  randomForest_use_surrogates = false;
  randomForest_max_categories = 2;
  randomForest_priors = 0;
  randomForest_calc_var_importance = false;
  randomForest_nactive_vars = 100;
  randomForest_max_trees = 20;
  randomForest_forest_accuracy = 0;
  randomForest_term_criteria = CV_TERMCRIT_ITER;


  randomForest_params = CvRTParams(
    randomForest_max_depth, // max_depth,
    randomForest_min_sample_count, // min_sample_count,
    randomForest_regression_accuracy, // regression_accuracy,
    randomForest_use_surrogates, // use_surrogates,
    randomForest_max_categories, // max_categories,
    randomForest_priors, // priors,
    randomForest_calc_var_importance, // calc_var_importance,
    randomForest_nactive_vars, // nactive_vars,
    randomForest_max_trees, // max_num_of_trees_in_the_forest,
    randomForest_forest_accuracy, // forest_accuracy,
    randomForest_term_criteria // termcrit_type
  );
  
  Mat training_features;
  features_apple_parts.text_color_features.convertTo( training_features, CV_32F );
  Mat responses = features_apple_parts.all_labels;
  fprintf( stderr, "t1: %s\nt2: %s\n", type2str( training_features.type() ).c_str(), type2str( responses.type() ).c_str() );
  cerr << training_features.size() << endl;
  cerr << responses.size() << endl;
  randomForest.train( training_features.t(), CV_COL_SAMPLE, responses.t());
  return randomForest;
}
