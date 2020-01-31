#pragma once
#include <ceres/ceres.h>
// cost fuction
struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST(double x,double y):_x(x),_y(y){}
    //residual calcutation
    template <typename T>
    bool operator()(const T* const nig,T* residual)const
    {
        residual[0] = T(_y)-nig[0]*nig[1]/(nig[1]+(nig[0]-nig[1])*ceres::exp(-nig[2]*T(_x)));//y-N*I0/(I0+(N-I0)e^(-γβx))
        return true;
    }
    const double _x, _y;//data
};
