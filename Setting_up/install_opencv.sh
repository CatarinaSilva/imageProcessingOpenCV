#!/bin/sh
##
## INSTALL_OPENCV
##
# openCV3 installation for use with C++ and MATLAB R2014b with mexopencv in Linux Mint Raffaela (17.2)
# Author: Catarina Silva
# Sources:
# ---- http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html 
# ---- http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html
# ---- https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
# ---- http://milq.github.io/install-opencv-ubuntu-debian/
# ---- http://www.ozbotz.org/opencv-installation/
# ---- 


##****************************************************************************************************************************************************************
##
## (1 - 6) dependencies: run install_dependencies.sh
##
##****************************************************************************************************************************************************************


##****************************************************************************************************************************************************************
## 7) OpenCV3 installation with contrib modules
cd ~/  
sudo git clone https://github.com/Itseez/opencv.git
cd opencv
sudo git clone https://github.com/Itseez/opencv_contrib.git
sudo mkdir release
cd release
sudo cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -D WITH_4VL=ON .. 
sudo make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
cd ~/
