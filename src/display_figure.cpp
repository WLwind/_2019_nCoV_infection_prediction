#include <cmath>
#include <_2019_nCoV_infection_prediction/display_figure.h>

DisplayFig::DisplayFig(const double* nig,const std::vector<double>& y_data):m_diagnosis(y_data.begin(),y_data.end()),m_image(m_height,(y_data.size()+2)*m_width_of_each_data,CV_8UC3,cv::Scalar(255,255,255))
{
    m_nig={nig[0],nig[1],nig[2]};
}

void DisplayFig::display()
{
    drawDiagnosis();
    drawPrediction();
    cv::imshow("2019-nCoV prediction curve and diagnosis data in China",m_image);
    cv::waitKey(0);
    return;
}

void DisplayFig::drawDiagnosis()
{
    int num{0};
    for(auto diag:m_diagnosis)
    {
        cv::Rect diag_rect((num+1)*m_width_of_each_data,int(m_height-diag*0.005+0.5),m_width_of_each_data,int(diag*0.005+0.5));
        cv::rectangle(m_image,diag_rect,cv::Scalar(255,0,0),1,8,0);
        num++;
    }
    return;
}

void DisplayFig::drawPrediction()
{
    for(int i=0;i<m_image.cols;i++)
    {
        cv::Point pred(i,int(m_height-predictionFormula((i-(1.5*m_width_of_each_data))/m_width_of_each_data)*0.005+0.5));
        cv::circle(m_image,pred,1,cv::Scalar(0,0,255),-1);
    }
    return;
}
