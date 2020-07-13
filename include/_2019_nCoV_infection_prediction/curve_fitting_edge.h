#pragma once
#include <iostream>
#include <Eigen/Core>
#include <g2o/core/base_unary_edge.h>
#include <_2019_nCoV_infection_prediction/curve_fitting_vertex.h>
class CurveFittingEdge: public g2o::BaseUnaryEdge<1,double,CurveFittingVertex>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CurveFittingEdge(double x):BaseUnaryEdge(),_x(x){}
    void computeError()override
    {
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d nig = v->estimate();
        _error[0]= _measurement - nig[0]*nig[1]/(nig[1]+(nig[0]-nig[1])*std::exp(-nig[2]*_x));//y-N*I0/(I0+(N-I0)e^(-γβx))
        return;
    }
    void linearizeOplus()override
    {
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d nig = v->estimate();
        auto expxx=std::exp(-nig[2]*_x);
        auto denominator=nig[1]+(nig[0]-nig[1])*expxx;
        auto denominator_sq=denominator*denominator;
        auto numerator=(nig[0]/nig[1]-1)*expxx;
        auto denominator2=(numerator+1)*(numerator+1);
        _jacobianOplusXi(0,0)=-nig[1]*(nig[1]*(1-expxx))/denominator_sq;
        _jacobianOplusXi(0,1)=-nig[0]*nig[0]*expxx/denominator_sq;
        _jacobianOplusXi(0,2)=-nig[0]*_x*numerator/denominator2;
        return;
    }
    virtual bool read( std::istream& in ) {return true;}
    virtual bool write( std::ostream& out )const {return out.good();}
public:
    double _x;
};

