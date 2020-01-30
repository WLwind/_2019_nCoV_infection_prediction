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
    void computeError()
    {
        const CurveFittingVertex* v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector2d ka = v->estimate();
        _error[0]= _measurement - std::exp(ka[0]*(_x+ka[1]));// y-exp(k(x+a))
    }
    virtual bool read( std::istream& in ) {}
    virtual bool write( std::ostream& out ) const {}
public:
    double _x;
};

