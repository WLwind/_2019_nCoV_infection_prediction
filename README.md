# _2019_nConV_infection_prediction
This is a cmake project to predict the number of infected persons by 2019-nConV in China.  
I'm trying to use a Susceptible-Infective Model to predict the number. This branch estimates the parameters of the formular using [G2O](https://github.com/RainerKuemmerle/g2o) with the data from [Medsci.cn](http://m.medsci.cn/wh.asp).  
**This is not a rigorous method to predict the number of infected persons, so don't take it seriously.**
## Dependencies
G2O  
For ROS Melodic users, you can simply install it form apt:  
$ sudo apt install ros-melodic-libg2o
## Installation
$ cd _2019_nConV_infection_prediction  
$ mkdir build  
$ cd build   
$ cmake ..  
$ make
## Run
$ ./_2019_nConV_infection_prediction
