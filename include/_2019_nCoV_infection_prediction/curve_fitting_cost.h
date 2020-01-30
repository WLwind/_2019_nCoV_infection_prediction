#pragma once
#include <ceres/ceres.h>
// cost fuction
struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST(double x,double y):_x(x),_y(y){}
    //residual calcutation
    template <typename T>
    bool operator()(const T* const ka,T* residual)const
    {
        residual[0] = T(_y)-ceres::exp(ka[0]*(T(_x)+ka[1]));// y-exp(k(x+a))
        return true;
    }
    const double _x, _y;//data
};
