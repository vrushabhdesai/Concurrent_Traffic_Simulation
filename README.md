# Concurrent Traffic Simulation

A multithreaded traffic simulator using a real urban map. Run each vehicle on a septate thread, and manage intersections to facilitate traffic flow and avoid collisions. 

Refer the following:
<img src="data/Idel_Results.gif"/>

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros `sudo apt install libopencv-dev`
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Project Program Schematic

The structure and logic of the program is explained in the following image

<img src="data/flow.jpg"/>


## Basic Build Instructions

1. Clone the project repository: `git clone https://github.com/vrushabhdesai/Concurrent_Traffic_Simulation.git`
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.
