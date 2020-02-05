#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <ctime>
#include <_2019_nCoV_infection_prediction/curve_fitting_cost.h>

using namespace std;

int main ( int argc, char* argv[] )
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

    ceres::Problem problem;
    for(int i=0;i<days;i++)
    {
        problem.AddResidualBlock(//add errors
            new ceres::AutoDiffCostFunction<CURVE_FITTING_COST,1,3>(
                new CURVE_FITTING_COST(x_data[i],y_data[i])
            ),
            nullptr,//kernal function
            nig//parameters
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
    std::cout<<"estimated formular: y="<<nig[0]<<"*"<<nig[1]<<"/("<<nig[1]<<"+("<<nig[0]<<"-"<<nig[1]<<")e^(-"<<nig[2]<<"x))"<<std::endl;
    std::cout<<"The estimated peak number is "<<int(nig[0])<<", which is "<<nig[0]/5237.0<<" times the number of SARS."<<std::endl;
    time_t now_seconds{std::time(0)};
    std::tm first_date{0,0,0,17,0,2020-1900,5,16,0};//2020.1.17
    now_seconds=mktime(&first_date);
    now_seconds+=(days-1)*86400;//last data collected day
    std::tm* now_time=std::localtime(&now_seconds);
    int approaching_day=0;
    for(int i=0;nig[0]*nig[1]/(nig[1]+(nig[0]-nig[1])*exp(-nig[2]*(days+i)))<0.99*nig[0];i++)//99% of the peak number
        approaching_day=i-1;
    std::cout<<"The infected number will approach the peak after about "<<approaching_day<<" days."<<std::endl;
    std::cout<<"The last data collected is on "<<1900+now_time->tm_year<<"."<<1+now_time->tm_mon<<"."<<now_time->tm_mday<<std::endl;
    std::cout<<"The predicted number of infected persons in next 3 days are: "<<std::endl;
    for(int i=0;i<3;i++)
    {
        now_seconds+=86400;
        now_time=std::localtime(&now_seconds);
        std::cout<<1900+now_time->tm_year<<"."<<1+now_time->tm_mon<<"."<<now_time->tm_mday<<": "<<int(nig[0]*nig[1]/(nig[1]+(nig[0]-nig[1])*exp(-nig[2]*(days+i)))+0.5)<<std::endl;
    }
    return 0;
}

