# imageProcessingOpenCV
Simple examples for image processing with openCV library

##### Programs
* openCV3 with necessary video encoders/decoders
* C++ and MATLAB
* mexopencv

### Instalation of openCV

##### 1) Installing dependencies, video encoder/decoder libraries, ffmpeg and openCV3

* Copy contents from Setting_up folder in this repository to your home folder
* Change permissions of scripts to 777 - in terminal run: 
	* sudo chmod 777 install_dependencies.sh
	* sudo chmod 777 install_opencv.sh
	* sudo chmod 777 uninstall_dependencies.sh
	* sudo chmod 777 uninstall_opencv.sh
* [OPTIONAL] If you previously tried to install with this script run uninstall_opencv.sh - in terminal run: sudo ./uninstall_opencv.sh
* [OPTIONAL] If you also wish to uninstall libraries run uninstall_dependencies.sh - in terminal run: sudo ./uninstall_dependencies.sh
* Open terminal in home folder and run installation scripts - in terminal run: 
	* sudo ./install_dependencies.sh
	* sudo ./install_opencv.sh


The installation should be done in the home folder and the resulting folder structure should be the following:

##### Folder structure

* home folder 
	* opencv
		* opencv_contrib (optional)
		* opencv_extras (optional)
		* release 
	* ffmpeg
		* sources
		* build

##### Sources:

* http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html 
* http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html
* https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
* http://milq.github.io/install-opencv-ubuntu-debian/
* http://www.ozbotz.org/opencv-installation/

