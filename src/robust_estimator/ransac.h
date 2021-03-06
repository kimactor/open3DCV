#ifndef ransac_h_
#define ransac_h_

#include "estimator/fundamental.h"
#include "robust_estimator/param_estimator.h"

namespace open3DCV
{
   
// T: type for data; S: type for parameter
template<class T, class S>
class Ransac
{
public:
    // - params:            a vector containing the estimated parameters
    // - param_estimator:   an instance which can estimate the desired parameters by either an exact
    //                      fit or a least squares fit
    // - data:              the input from which the parameters will be estimated
    // - prob_wo_outlieres: the probability that at least one of the selected subsets doens't contain an outlier,
    //                      must be in (0, 1).
    //
    // - number of iterations (k):
    //
    //               log(1 - p)
    //         k = --------------
    //              log(1 - w^n)
    //
    // - p: desired probability without an outlier
    // - w: percentage of inliers in the data
    // - n: minimum number of data for estimation
    //
    static float estimate(Param_Estimator<T, S>* param_estimator,
                          std::vector<T>& data,
                          std::vector<S>& params,
                          float prob_wo_outliers,
                          int* vote_inlier);
    
private:
    
    static unsigned int choose(unsigned int n, unsigned int m);
    
    class Subset_Ind_Cmp
    {
    private:
        int length_;
    public:
        Subset_Ind_Cmp(int length) : length_(length) { }
        bool operator() (const int* arr1, const int* arr2) const
        {
            for (int i = 0; i < length_; ++i)
            {
                if (arr1[i] < arr2[i])
                    return true;
                else if (arr1[i] > arr2[i])
                    return false;
            }
            return false;
        }
    };
    
};
}

#endif
