#include <fstream>
#include "io/sfm_io.h"

using std::endl;
namespace open3DCV
{
    int write_sfm(const std::string dir, const Graph& graph)
    {
        std::ofstream ofstr;
        char oname[100];
        for (int i = 0; i < graph.ncams_; ++i)
        {
            if ((false))
            {
                sprintf(oname, "%s/%08d.txt", dir.c_str(), i);
                ofstr.open(&oname[0], std::ofstream::out);
                if (!ofstr.is_open())
                {
                    std::cerr << "Cannot open file." << std::endl;
                    return 1;
                }
                const Mat3f& K = graph.intrinsics_mat_[i];
                const Mat34f& Rt = graph.extrinsics_mat_[i];
                ofstr << K(0, 0) << " " << K(0, 1) << " " << K(0, 2) << endl
                      << K(1, 0) << " " << K(1, 1) << " " << K(1, 2) << endl
                      << K(2, 0) << " " << K(2, 1) << " " << K(2, 2) << endl
                      << Rt(0, 0) << " " << Rt(0, 1) << " " << Rt(0, 2) << " " << Rt(0, 3) << endl
                      << Rt(1, 0) << " " << Rt(1, 1) << " " << Rt(1, 2) << " " << Rt(1, 3) << endl
                      << Rt(2, 0) << " " << Rt(2, 1) << " " << Rt(2, 2) << " " << Rt(2, 3);
                ofstr.close();
            }
            
            sprintf(oname, "%s/txt/%08d.txt", dir.c_str(), i);
            ofstr.open(&oname[0], std::ofstream::out);
            if (!ofstr.is_open())
            {
                std::cerr << "Cannot open file." << std::endl;
                return 1;
            }
            const Mat34f& pose = graph.intrinsics_mat_[i] * graph.extrinsics_mat_[i];
            ofstr << "CONTOUR" << endl
                  << pose(0, 0) << " " << pose(0, 1) << " " << pose(0, 2) << " " << pose(0, 3) << endl
                  << pose(1, 0) << " " << pose(1, 1) << " " << pose(1, 2) << " " << pose(1, 3) << endl
                  << pose(2, 0) << " " << pose(2, 1) << " " << pose(2, 2) << " " << pose(2, 3);
            ofstr.close();
        }
        
        return 0;
    }
}
