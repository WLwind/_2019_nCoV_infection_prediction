#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <ctime>
#include <Eigen/Core>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_dogleg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <_2019_nCoV_infection_prediction/curve_fitting_edge.h>
#include <_2019_nCoV_infection_prediction/curve_fitting_vertex.h>

using namespace std; 

int main( int argc, char** argv )
{
    double nig[3] = {50000.0,58.0,0.02123106};//parameters
    vector<double> y_data;
    double load_data;
    std::ifstream ifs("../infected_numbers.txt");
    if(!ifs.is_open())
    {
        ifs.open("infected_numbers.txt");
        assert(ifs.is_open());
    }
    std::cout<<"Loading data"<<std::endl;
    while(ifs>>load_data)//data source: http://m.medsci.cn/wh.asp
    {
        y_data.push_back(load_data);
    }
    int days=y_data.size();
    vector<double> x_data;//data,date
    for(int i=0;i<days;i++)//from 2020.1.17 when number increased rapidly
        x_data.push_back(int(i));
    
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<Eigen::Dynamic,Eigen::Dynamic>> Block;//block solver
    std::unique_ptr<Block::LinearSolverType> linear_solver(new g2o::LinearSolverDense<Block::PoseMatrixType>());//linear solver
    std::unique_ptr<Block> solver_ptr(new Block(std::move(linear_solver)));
    //GN, LM, DogLeg
    g2o::OptimizationAlgorithm* solver(new g2o::OptimizationAlgorithmLevenberg(std::move(solver_ptr)));//solver
    g2o::SparseOptimizer optimizer;//optimizer
    optimizer.setAlgorithm(solver);
    optimizer.setVerbose(true);//print process
    
    //add vertecis
    CurveFittingVertex* v = new CurveFittingVertex();
    v->setEstimate(Eigen::Vector3d(nig[0],nig[1],nig[2]));
    v->setId(0);
    optimizer.addVertex(v);
    
    //add edges
    for ( int i=0; i<days; i++ )
    {
        CurveFittingEdge* edge = new CurveFittingEdge( x_data[i] );
        edge->setId(i);
        edge->setVertex( 0, v );
        edge->setMeasurement( y_data[i] );
        edge->setInformation(Eigen::Matrix<double,1,1>::Identity());
        optimizer.addEdge(edge);
    }
    
    cout<<"start optimization"<<endl;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(100);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
    cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
    
    auto nig_estimate = v->estimate();
    std::cout<<"estimated formular: y="<<nig_estimate[0]<<"*"<<nig_estimate[1]<<"/("<<nig_estimate[1]<<"+("<<nig_estimate[0]<<"-"<<nig_estimate[1]<<")e^(-"<<nig_estimate[2]<<"x))"<<std::endl;
    std::cout<<"The estimated peak number is "<<int(nig_estimate[0])<<", which is "<<nig_estimate[0]/5237.0<<" times the number of SARS."<<std::endl;
    time_t now_seconds{std::time(0)},approaching_seconds{std::time(0)};
    std::tm first_date{0,0,0,17,0,2020-1900,5,16,0};//2020.1.17
    approaching_seconds=now_seconds=mktime(&first_date);
    int approaching_days{0};
    for(;nig_estimate[0]*nig_estimate[1]/(nig_estimate[1]+(nig_estimate[0]-nig_estimate[1])*exp(-nig_estimate[2]*(days+approaching_days)))<0.99*nig_estimate[0];approaching_days++){}//99% of the peak number
    approaching_seconds+=(days+approaching_days)*86400;
    now_seconds+=(days-1)*86400;//last data collected day
    std::tm* time_ptr=std::localtime(&now_seconds);
    std::cout<<"The data is collected from 2020.01.17 to "<<1900+time_ptr->tm_year<<"."<<1+time_ptr->tm_mon<<"."<<time_ptr->tm_mday<<std::endl;
    time_ptr=std::localtime(&approaching_seconds);    
    std::cout<<"The infected number will approach the peak after about "<<approaching_days<<" days: "<<1900+time_ptr->tm_year<<"."<<1+time_ptr->tm_mon<<"."<<time_ptr->tm_mday<<std::endl;
    std::cout<<"The predicted number of infected persons in next 3 days are: "<<std::endl;
    for(int i=0;i<3;i++)
    {
        now_seconds+=86400;
        time_ptr=std::localtime(&now_seconds);
        std::cout<<1900+time_ptr->tm_year<<"."<<1+time_ptr->tm_mon<<"."<<time_ptr->tm_mday<<": "<<int(nig_estimate[0]*nig_estimate[1]/(nig_estimate[1]+(nig_estimate[0]-nig_estimate[1])*exp(-nig_estimate[2]*(days+i)))+0.5)<<std::endl;
    }
    return 0;
}
