# _2019_nCoV_infection_prediction
This is a cmake project to predict the number of infected persons by 2019-nCoV in China.  
I'm trying to use a Susceptible-Infective Model to predict the number. This branch estimates the parameters of the formular using [G2O](https://github.com/RainerKuemmerle/g2o) with the data from [Medsci.cn](http://m.medsci.cn/wh.asp).  
**This is not a rigorous method to predict the number of infected persons, so don't take it seriously. As the evaluation criterion of definite diagnosis had changed since 2020 February 13th, I stopped updating new data for prediction.**  
**I restarted updating at 2020 March 13th, and stopped updating at the end of March since the curve was approximately flat at that time.**  

## Dependencies
G2O  
For ROS Melodic or Noetic users, you can simply install it from apt:  
`$ sudo apt install ros-melodic-libg2o` or  
`$ sudo apt install ros-noetic-libg2o`  
OpenCV  
I have tested it with OpenCV 2.4.9, 3.2.0 and 4.2.0:  
`$ sudo apt install libopencv-dev`  
## Installation
`$ cd _2019_nCoV_infection_prediction`  
`$ mkdir build`  
`$ cd build`   
`$ cmake ..`  
`$ make`  
## Run
`$ ./_2019_nCoV_infection_prediction`  
