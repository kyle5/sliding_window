//////////////////////////////////////////////////////////           INCLUDE              /////////////////////////////////////////////////////////////////

#include <main.h>
#include <get_features.h>
#include <calculate_directory_paths.h>
#include <utilities_kyle.h>
#include <ml_helpers.h>

using namespace std;
using namespace cv;

// function prototypes

int main( int argc, char *argv[] ) {
  int recomp = atoi(argv[1]);
  CvRTrees randomForest;
  string file( "/home/kyle/rand_forest_temp.xml" );
  string root_directory = "/home/kyle/sliding_window_apple_detection/";
  // setup the pos and neg paths
  struct directory_paths directory_paths_apple_parts = calculate_paths( root_directory );
  struct filepaths filepaths_apple_parts = calculate_filepaths( directory_paths_apple_parts );
  struct features features_apple_parts;
  if ( recomp ) {
    if ( recomp ) {
	    //////////////////////////////////////////////////////////           TRAINING              /////////////////////////////////////////////////////////////////	
	    // open the directory of images
	    // get the image paths
	    // for each of the neg and pos features
		    // extract the features of the pos and neg images
	    features_apple_parts = get_all_features( filepaths_apple_parts );
      // save the features and the responses
      FileStorage fs("test.yml", FileStorage::WRITE);
      fs << "features" << features_apple_parts.text_color_features;
      fs << "labels_saved" << features_apple_parts.all_labels;
      fs.release();
    }
  } else {
    FileStorage fs( "test.yml", FileStorage::READ );
    struct features features_apple_parts;
    fs["features"] >> features_apple_parts.text_color_features;
    fs["labels_saved"] >> features_apple_parts.all_labels;
	  // train rand forest using the extracted features
    fs.release();
	  // randomForest = create_random_forest( features_apple_parts );
  }
  
	//////////////////////////////////////////////////////////           TESTING              /////////////////////////////////////////////////////////////////
  
	// 1/8 - 1/4 of the image that is being utilized
	// 3:1, 2:1, and 1:1 aspect ratios
	// setup the (high/low) scale and the (steps)
	// setup every scale to extract features at 
	// setup the aspect ratios that should be searched
  float scales[3] = {0.125, 0.1875, 0.25};
	float aspect_ratios[3] = {3, 2, 1};
	// find the image paths of the images that have already been classified
  for ( int i = 0; i < filepaths_apple_parts.filepaths_testing.size(); i++ ) {
	// for each image that has a classification of pixels that are apple
		// load the image

    string test_img_path = filepaths_apple_parts.filepaths_testing[i];
    int idx0 = test_img_path.rfind("/");
    int idx1 = test_img_path.rfind(".");
    string path = test_img_path.substr(0,idx0+1);
    string name = test_img_path.substr(idx0+1,idx1-idx0-1);
    string end = test_img_path.substr(idx1);
    cerr << end << endl;
    if ( strcmp( end.c_str(), ".png" ) == 0 ) {
      continue;
    }
    string full_testing_image_mask_path = path + name + string( "_mask.png" );
    // open both of the images
    
    Mat mask_img = imread( full_testing_image_mask_path );
    fprintf( stderr,  "%s: is the type in question.\n", type2str( mask_img.type() ).c_str() );
    Mat mask_img_gray, mask_img_binary;
    cvtColor( mask_img, mask_img_gray, CV_BGR2GRAY );
    threshold( mask_img_gray, mask_img_binary, 240, 255, THRESH_BINARY );
    vector<KeyPoint> grid_kps = get_grid_over_valid_pixels( mask_img_binary );
    
    Mat raw_img = imread( test_img_path );
    Mat gray_img;
    cvtColor( raw_img, gray_img, CV_BGR2GRAY );
    Mat descriptorsA;
    fprintf( stderr, "rows: %d\ncols: %d\n", gray_img.rows, gray_img.cols );
    string str = type2str( gray_img.type() );
    SiftDescriptorExtractor extractor;
    extractor.compute( gray_img, grid_kps, descriptorsA );
    descriptorsA.convertTo( descriptorsA, CV_32F );
    fprintf( stderr, "computed descriptors: gray img type: %s\n", str.c_str() );
    
    BFMatcher matcher;
    vector<vector<DMatch> > matches;
    // matcher.match( features_apple_parts.text_color_features, descriptorsA, matches );
    int k = 3;
    matcher.knnMatch( descriptorsA, features_apple_parts.text_color_features, matches, k );
    vector<apple_part> classifications( ( int ) matches.size(), APPLE_SMOOTH );
    for ( int m = 0; m < (int) matches.size(); m++ ) {
      int count_rough = 0, count_smooth = 0;
      for ( int n = 0; n < k; n++ ) {
        if ( features_apple_parts.all_labels.at<float>( matches[m][n].trainIdx ) == 1 ) {
          count_rough++;
        } else {
          count_smooth++;
        }
      }
      if ( count_rough > count_smooth ) {
        classifications[m] = APPLE_ROUGH;
      }
    }
    // write out the classifications to the original bgr image
    for(int m = 0; m < (int) classifications.size(); m++) {
      uchar arr[3] = {0, 0, 0};
      if ( classifications[m] == APPLE_SMOOTH ) arr[0] = 255;
      else if ( classifications[m] == APPLE_ROUGH ) arr[2] = 255;
      int y = grid_kps[m].pt.y, x = grid_kps[m].pt.x;
      for ( int a = -1; a <= 1; a++ )
      for ( int b = -1; b <= 1; b++ )
      {
        raw_img.at<Vec3b>( a+y, b+x )[0] = arr[0];
        raw_img.at<Vec3b>( a+y, b+x )[1] = arr[1];
        raw_img.at<Vec3b>( a+y, b+x )[2] = arr[2];
      }
    }
    imwrite( "test_img_result.ppm", raw_img );
		// for loop through aspect ratios
			// for loop through scales
				// for loop through the x and y directions
					// run classifier over the section that the classifier is currently over
  }
	return 0;
}
