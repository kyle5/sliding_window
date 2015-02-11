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

enum apple_part { APPLE_SMOOTH, APPLE_ROUGH };


