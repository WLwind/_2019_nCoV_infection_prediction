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

class CurveFittingCostFunction:public ceres::SizedCostFunction<1, 3>
{
public:
    CurveFittingCostFunction(const double x,const double y):_x(x),_y(y){}
    ~CurveFittingCostFunction()override{}
    bool Evaluate(double const* const* parameters,double* residuals,double** jacobians)const override
    {
        int vertex_index=0,error_index=0;
        const double* nig = parameters[vertex_index];
        residuals[error_index] = _y-nig[0]*nig[1]/(nig[1]+(nig[0]-nig[1])*ceres::exp(-nig[2]*_x));//y-N*I0/(I0+(N-I0)e^(-γβx))
        if(!jacobians)
            return true;
        if(!jacobians[vertex_index])
            return true;
        auto expxx=std::exp(-nig[2]*_x);
        auto denominator=nig[1]+(nig[0]-nig[1])*expxx;
        auto denominator_sq=denominator*denominator;
        auto numerator=(nig[0]/nig[1]-1)*expxx;
        auto denominator2=(numerator+1)*(numerator+1);
        jacobians[vertex_index][error_index*3+0]=-nig[1]*(nig[1]*(1-expxx))/denominator_sq;
        jacobians[vertex_index][error_index*3+1]=-nig[0]*nig[0]*expxx/denominator_sq;
        jacobians[vertex_index][error_index*3+2]=-nig[0]*_x*numerator/denominator2;
        return true;
    }
private:
    const double _x,_y;
};
