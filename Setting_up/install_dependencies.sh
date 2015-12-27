#!/bin/sh
##
## INSTALL_DEPENDENCIES
##
# Ffmpeg and other openCV3 dependencies installation for use with C++ and MATLAB R2014b with mexopencv in Linux Mint Raffaela (17.2)
# Author: Catarina Silva
# Sources:
# ---- http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html 
# ---- http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html
# ---- https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu
# ---- http://milq.github.io/install-opencv-ubuntu-debian/
# ---- http://www.ozbotz.org/opencv-installation/
# ---- 



##****************************************************************************************************************************************************************
## 1) Update repositories and upgrade
sudo apt-get update 
sudo apt-get upgrade  



##****************************************************************************************************************************************************************
## 2) GCC, G++, GFORTRAN
# install necessary compilers for C++ use and Matlab use: G++ is the important one, but this way we compile mex such that gcc and fortran are already set
# gcc 4.7, g++ 4.7 and gfortran 4.7 are compatible with matlab R2014b, change if Matlab version is different, but make sure it is still compatible both with openCV, mexopencv and Matlab
sudo apt-get install gcc -y 
sudo apt-get install g++ -y 
sudo apt-get install gfortran -y 
sudo apt-get install gcc-4.7 -y 
sudo apt-get install g++-4.7 -y 
sudo apt-get install gfortran-4.7 -y 

# specify gcc, g++ and fortran compilers to be used by the system (linking each to the 4.7 version)
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.7 --slave /usr/bin/gfortran gfortran /usr/bin/gfortran-4.7




##****************************************************************************************************************************************************************
## 3) Some ffmpeg/openCV general dependencies:
# Build tools
sudo apt-get install build-essential cmake mercurial checkinstall git pkg-config autoconf automake libtool -y 

#TBB:
sudo apt-get install libtbb2 libtbb-dev -y 

# GUI:
sudo apt-get install libgtk2.0-dev qt5-default libvtk6-dev libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev -y 

# Media I/O:
sudo apt-get install zlib1g-dev libjpeg-dev libwebp-dev libpng-dev libtiff-dev libtiff5-dev libjasper-dev libopenexr-dev libgdal-dev libsdl1.2-dev libfreetype6-dev -y 

# Video I/O:
sudo apt-get install libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev v4l-utils libvdpau-dev libva-dev libass-dev -y 

# Parallelism and linear algebra libraries:
sudo apt-get install libtbb-dev libeigen3-dev -y 

# Python:
sudo apt-get install python-dev python-tk python-numpy python3-dev python3-tk python3-numpy -y 

# Java
sudo apt-get install ant default-jdk -y 

# Documentation:
sudo apt-get install doxygen texinfo -y 


##*************************************
# others
sudo apt-get install libfaac-dev libjack-jackd2-dev libx11-dev libxfixes-dev texi2html -y 



##****************************************************************************************************************************************************************
## 4) Ffmpeg dependencies
# make sure that if an error occurs, the script stops and doesn't proceed to the next step
set -o errexit

# Preparing ffmpeg directories
cd ~/
sudo mkdir ffmpeg
cd ffmpeg
sudo mkdir sources
sudo mkdir build
cd sources

# YASM
sudo apt-get install yasm -y 

# H.264 video encoder
sudo apt-get install libx264-dev -y 

# H.265/HEVC video encoder (not used later on in ffmpeg configuration)
cd ~/ffmpeg/sources
sudo hg clone https://bitbucket.org/multicoreware/x265
cd ~/ffmpeg/sources/x265/build/linux
PATH="$HOME/bin:$PATH" sudo cmake -G "Unix Makefiles" -D CMAKE_INSTALL_PREFIX="$HOME/ffmpeg/build" -D ENABLE_SHARED:bool=off ../../source
sudo make
sudo make install
sudo make clean
cd ~/ffmpeg/sources

# AAC audio encoder
cd ~/ffmpeg/sources
sudo wget -O fdk-aac.tar.gz https://github.com/mstorsjo/fdk-aac/tarball/master
sudo tar xzvf fdk-aac.tar.gz
cd mstorsjo-fdk-aac*
sudo autoreconf -fiv
sudo ./configure --prefix="$HOME/ffmpeg/build" --disable-shared
sudo make
sudo make install
sudo make distclean
cd ~/ffmpeg/sources

# MP3 audio encoder
sudo apt-get install libmp3lame-dev -y 

# Opus audio decoder and encoder
sudo apt-get install libopus-dev -y 

# VP8/VP9 video encoder and decoder
cd ~/ffmpeg/sources
sudo wget http://storage.googleapis.com/downloads.webmproject.org/releases/webm/libvpx-1.4.0.tar.bz2
sudo tar xjvf libvpx-1.4.0.tar.bz2
cd libvpx-1.4.0
PATH="$HOME/bin:$PATH" sudo ./configure --prefix="$HOME/ffmpeg/build" --disable-examples --disable-unit-tests
PATH="$HOME/bin:$PATH" sudo make
sudo make install
sudo make clean
cd ~/ffmpeg/sources



##****************************************************************************************************************************************************************
## 5) FFMPEG installation
cd ~/ffmpeg/sources
sudo wget http://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2
sudo tar xjvf ffmpeg-snapshot.tar.bz2
cd ffmpeg
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg/build/lib/pkgconfig" sudo ./configure \
  --prefix="$HOME/ffmpeg/build" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I $HOME/ffmpeg/build/include" \
  --extra-ldflags="-L $HOME/ffmpeg/build/lib" \
  --bindir="$HOME/bin" \
  --enable-gpl \
  --enable-libass \
  --enable-libfdk-aac \
  --enable-libfreetype \
  --enable-libmp3lame \
  --enable-libopus \
  --enable-libtheora \
  --enable-libvorbis \
  --enable-libvpx \
  --enable-libx264 \
  --enable-nonfree
PATH="$HOME/bin:$PATH" sudo make
sudo make install
sudo make distclean
hash -r
cd ~/ffmpeg/sources

# Documentation: man pages
echo "MANPATH_MAP $HOME/bin $HOME/ffmpeg_build/share/man" >> ~/.manpath
. ~/.profile



##****************************************************************************************************************************************************************
## 6) gstreamer installation - breaks OS installation for Linux Mint 17.2
##sudo apt-get install gstreamer-tools gstreamer0.10-alsa gstreamer0.10-buzztard gstreamer0.10-buzztard-doc gstreamer0.10-doc gstreamer0.10-ffmpeg gstreamer0.10-fluendo-mp3 gstreamer0.10-gconf gstreamer0.10-gnomevfs gstreamer0.10-gnonlin gstreamer0.10-gnonlin-dbg gstreamer0.10-gnonlin-doc gstreamer0.10-hplugins gstreamer0.10-nice gstreamer0.10-packagekit gstreamer0.10-plugins-bad gstreamer0.10-plugins-bad-doc gstreamer0.10-plugins-bad-multiverse gstreamer0.10-plugins-base gstreamer0.10-plugins-base-apps gstreamer0.10-plugins-base-dbg gstreamer0.10-plugins-base-doc gstreamer0.10-plugins-cutter gstreamer0.10-plugins-good gstreamer0.10-plugins-good-doc gstreamer0.10-plugins-ugly gstreamer0.10-plugins-ugly-doc gstreamer0.10-pocketsphinx gstreamer0.10-pulseaudio gstreamer0.10-qapt gstreamer0.10-tools gstreamer0.10-x libgstreamer0.10-dev libgstreamer0.10-0-dbg libgstreamer0.10-0 


