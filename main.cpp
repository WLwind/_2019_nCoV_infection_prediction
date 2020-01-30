#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <ctime>
#include <_2019_nCoV_infection_prediction/curve_fitting_cost.h>

using namespace std;

int main ( int argc, char* argv[] )
{
    double ka[2] = {0.3,14.0};//parameters
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

    ceres::Problem problem;
    for(int i=0;i<days;i++)
    {
        problem.AddResidualBlock(//add errors
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST,1,2>(
                new CURVE_FITTING_COST(x_data[i],y_data[i])
            ),
            nullptr,//kernal function
            ka//parameters
        );
    }

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;//print progress with std::cout

    ceres::Solver::Summary summary;// info
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    ceres::Solve ( options, &problem, &summary );  // optimization
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
    cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
    cout<<summary.BriefReport() <<endl;
    std::cout<<"estimated formular: y="<<"e^("<<ka[0]<<"(x+"<<ka[1]<<"))"<<std::endl;
    time_t now_seconds{std::time(0)};
//    std::tm first_date{0,0,0,17,0,2020-1900,5,16,0};//2020.1.17
//    now_seconds=mktime(&first_date);
//    now_seconds+=(days-1)*86400;
    std::tm* now_time=std::localtime(&now_seconds);
    std::cout<<"Today is "<<1900+now_time->tm_year<<"."<<1+now_time->tm_mon<<"."<<now_time->tm_mday<<std::endl;
    std::cout<<"The predicted number of infected persons in comming 3 days are: "<<std::endl;
    for(int i=0;i<3;i++)
    {
        now_seconds+=86400;
        now_time=std::localtime(&now_seconds);
        std::cout<<1900+now_time->tm_year<<"."<<1+now_time->tm_mon<<"."<<now_time->tm_mday<<": "<<int(exp(ka[0]*(days+i+ka[1]))+0.5)<<std::endl;
    }
    return 0;
}

