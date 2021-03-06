#ifndef detector_h_
#define detector_h_

#include <fstream>
#include "image/image.h"
#include "keypoint/keypoint.h"

namespace open3DCV {
    class Detector {
    public:
        Detector() { };
        virtual ~Detector() { };
        
        virtual int detect_keypoints(const Image& image, vector<Keypoint>& keypoints, int verbose = 0) = 0;
    };
    
} // namespace open3DCV

#endif
