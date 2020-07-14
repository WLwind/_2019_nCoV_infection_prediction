#pragma once
#include <iostream>
#include <Eigen/Core>
#include <g2o/core/base_vertex.h>
class CurveFittingVertex: public g2o::BaseVertex<3, Eigen::Vector3d>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    virtual void setToOriginImpl()
    {
        _estimate << 0,0,0;
    }
    
    virtual void oplusImpl( const double* update ) 
    {
        _estimate += Eigen::Vector3d(update);
    }
    virtual bool read(std::istream& in){return true;}
    virtual bool write(std::ostream& out)const {return out.good();}
};
