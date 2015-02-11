#include <calculate_directory_paths.h>

using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////           HELPER FS              /////////////////////////////////////////////////////////////////
// f calculate paths
struct directory_paths calculate_paths( string root_directory ) {
	struct directory_paths ret;
	root_directory = root_directory + string("/");
	ret.root_training_directory = root_directory + string( "training/" );
	ret.positives_training_directory = ret.root_training_directory + string( "positives/" );
	ret.positives_training_directory_raw = ret.positives_training_directory + string("raw/");
	ret.positives_training_directory_mask = ret.positives_training_directory + string("mask/");
	ret.negatives_training_directory = ret.root_training_directory + string( "negatives/" );
	ret.negatives_training_directory_raw = ret.negatives_training_directory + string( "raw/" );
	ret.negatives_training_directory_mask = ret.negatives_training_directory + string( "mask/" );
	ret.root_testing_directory = root_directory + string( "testing/" );;
	return ret;
}

vector<string> get_files_from_directory( string directory_given ) {
  DIR *dir;
  struct dirent *ent;
  vector<string> filepaths;
  if ( ( dir = opendir ( directory_given.c_str() ) ) != NULL ) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      char cur[64];
      sprintf( cur, "%s", ent->d_name );
      if( strcmp( cur, "." ) != 0 && strcmp( cur, ".." ) != 0 ) {
        printf ( "%s\n", cur );
        string cur_str( cur );
        filepaths.push_back( cur_str );
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    throw runtime_error( "get_files_from_directory( ) : Could not open the directory!?" );
  }
  return filepaths;
}

struct filepaths calculate_filepaths( directory_paths directory_paths_apple_parts ) {
  struct filepaths ret;
  // for each positive image : save filepath : label set to 0
  cerr << "b : positives_training_directory_raw " << endl;
  vector<string> positive_filepaths_raw = get_files_from_directory( directory_paths_apple_parts.positives_training_directory_raw );
  for ( int i = 0; i < (int) positive_filepaths_raw.size(); i++ ) {
    string cur = directory_paths_apple_parts.positives_training_directory_raw + positive_filepaths_raw[i];
    ret.filepaths_positive_raw.push_back( cur );
  }
  cerr << "b : positives_training_directory_mask " << endl;
  vector<string> positive_filepaths_mask = get_files_from_directory( directory_paths_apple_parts.positives_training_directory_mask );
  for ( int i = 0; i < (int) positive_filepaths_mask.size(); i++ ) {
    string cur = directory_paths_apple_parts.positives_training_directory_mask + positive_filepaths_mask[i];
    ret.filepaths_positive_mask.push_back( cur );
  }
  cerr << "b : negatives_training_directory_raw " << endl;
  vector<string> negatives_filepaths_raw = get_files_from_directory( directory_paths_apple_parts.negatives_training_directory_raw );
  for ( int i = 0; i < (int) negatives_filepaths_raw.size(); i++ ) {
    string cur = directory_paths_apple_parts.negatives_training_directory_raw + negatives_filepaths_raw[i];
    ret.filepaths_negative_raw.push_back( cur );
  }
  cerr << "b : negatives_training_directory_mask " << endl;
  vector<string> negatives_filepaths_mask = get_files_from_directory( directory_paths_apple_parts.negatives_training_directory_mask );
  for ( int i = 0; i < (int) negatives_filepaths_mask.size(); i++ ) {
    string cur = directory_paths_apple_parts.negatives_training_directory_mask + negatives_filepaths_mask[i];
    ret.filepaths_negative_mask.push_back( cur );
  }
  cerr << "b : testing_directory " << endl;
  vector<string> testing_filepaths = get_files_from_directory( directory_paths_apple_parts.root_testing_directory );
  for ( int i = 0; i < (int) testing_filepaths.size(); i++ ) {
    string cur = directory_paths_apple_parts.root_testing_directory + testing_filepaths[i];
    ret.filepaths_testing.push_back( cur );
  }
  return ret;
}

