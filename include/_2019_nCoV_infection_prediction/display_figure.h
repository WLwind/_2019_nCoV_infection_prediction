#pragma once

#include <vector>
#include <list>
#include <array>
#include <opencv2/opencv.hpp>

class DisplayFig
{
public:
    DisplayFig(const double* nig,const std::vector<double>& y_data,const std::string& last_date=std::string("2020.12.31"));
    void display();//display the picture
private:
    void drawDiagnosis();
    void drawPrediction();
    inline double predictionFormula(double x){return m_nig[0]*m_nig[1]/(m_nig[1]+(m_nig[0]-m_nig[1])*std::exp(-m_nig[2]*x));}//returns the prediction value

    int m_height{500};//height of the picture
    int m_width_of_each_data{10};//how many pixels of each data to be displayed
    std::list<int> m_diagnosis;//diagnosis number
    std::array<double,3> m_nig;//parameters of the model
    cv::Mat m_image;//picture to show
    std::string m_last_date;//last date of collected data to display
};
