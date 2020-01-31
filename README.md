# _2019_nConV_infection_prediction
This is a cmake project to predict the number of infected persons by 2019-nConV in China.  
I'm trying to use Susceptible-Infective Model to predict the number. This branch estimates the parameters of the formular using [Ceres Solver](http://www.ceres-solver.org/) with the data from [Medsci.cn](http://m.medsci.cn/wh.asp).  
**This is not a rigorous method to predict the number of infected persons, so don't take it seriously.**
## Dependencies
Ceres Solver
## Installation
$ cd _2019_nConV_infection_prediction  
$ mkdir build  
$ cd build  
$ cmake ..  
$ make
## Run
$ ./_2019_nConV_infection_prediction
