#include "matching/matcher.h"
#include "matching/distance.h"

namespace open3DCV
{

int Matcher::match(const vector<Vec>& desc1, const vector<Vec>& desc2, vector<Match>& matches)
{
    float dist = 0, min_dist = 1e8, sec_min_dist = 1e8, rate = 0.6;
    int ind_min_key = 0;
    
    for (int i = 0; i < desc1.size(); ++i)
    {
        for (int j = 0; j < desc2.size(); ++j)
        {
//            std::cout << desc1[i].transpose() << std::endl << desc2[i].transpose() << std::endl;
//            std::cout << desc1[i].norm() << std::endl << desc2[i].norm() << std::endl;
            dist = l2_dist(desc1[i], desc2[j]);
            if (dist < min_dist)
            {
                sec_min_dist = min_dist;
                min_dist = dist;
                ind_min_key = j;
            }
            else if (dist < sec_min_dist)
            {
                sec_min_dist = dist;
            }
        }
//        if (min_dist < rate * sec_min_dist)
//        {
//            Match m(i, ind_min_key, min_dist);
//            matches.push_back(m);
//        }
        Match m(i, ind_min_key, min_dist);
        matches.push_back(m);
    }
    
    return 0;
}

} // namespace open3DCV
