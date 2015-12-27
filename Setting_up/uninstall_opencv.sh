#!/bin/sh
##
## UNINSTALL_OPENCV
##
# Clean your home folder from previous openCV installation
# Author: Catarina Silva
# Sources:
# ---- http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html 
# ---- http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html
# ---- https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
# ---- http://milq.github.io/install-opencv-ubuntu-debian/
# ---- http://www.ozbotz.org/opencv-installation/



##****************************************************************************************************************************************************************
## 1) openCV: uninstall openCV libraries if they exist and remove openCV folders created
#
# this assumes that openCV repository was fetched to the home folder and build was made using a "release" folder, using the following structure:
# --> opencv
# ------> opencv_contrib (optional)
# ------> opencv_extras (optional)
# ------> release 

cd ~/
if [ -d "opencv" ]; then
    if [ -d "release" ]; then
        cd ~/opencv/release
        sudo make uninstall
        cd ~/opencv
        sudo rm -R release
    fi
    cd ~/
    sudo rm -R opencv
fi

