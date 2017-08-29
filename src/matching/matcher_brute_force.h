#ifndef matcher_brute_force_h_
#define matcher_brute_force_h_

#include "keypoint/descriptor.h"
#include "matching/matcher.h"

namespace open3DCV
{
    
    class Matcher_Brute_Force : Match
    {
    public:
        Matcher_Brute_Force() { };
        Matcher_Brute_Force(const Matcher_Param r_matcher_param) : matcher_param_(r_matcher_param) { }
        virtual ~Matcher_Brute_Force() { };
        
        void init_param(Matcher_Param r_matcher_param) : matcher_params_(r_matcher_param) { };
        int match(const vector<Vecf>& desc1, const vector<Vecf>& desc2, vector<Match>& matches);
    };
    
    inline int Match_Brute_Force::match(const vector<Vecf>& desc1, const vector<Vecf>& desc2, vector<Match>& matches)
    {
        float dist = 0, min_dist = 1e8, sec_min_dist = 1e8, rate = 0.8;
        int ind_min_key = 0;
        
        for (int i = 0; i < desc1.size(); ++i)
        {
            min_dist = sec_min_dist = 1e8;
            for (int j = 0; j < desc2.size(); ++j)
            {
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
            if (min_dist < rate * sec_min_dist)
            {
                Match m(i, ind_min_key, min_dist);
                matches.push_back(m);
            }
//        Match m(i, ind_min_key, min_dist);
//        matches.push_back(m);
        }
        
        return 0;
    }
    
} // namespace open3DCV

#endif