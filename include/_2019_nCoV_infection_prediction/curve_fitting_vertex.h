#pragma once
#include <iostream>
#include <Eigen/Core>
#include <g2o/core/base_vertex.h>
class CurveFittingVertex: public g2o::BaseVertex<2, Eigen::Vector2d>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    virtual void setToOriginImpl()
    {
        _estimate << 0,0;
    }
    
    virtual void oplusImpl( const double* update ) 
    {
        _estimate += Eigen::Vector2d(update);
    }
    virtual bool read( std::istream& in ) {}
    virtual bool write( std::ostream& out ) const {}
};
