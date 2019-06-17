# cam_localization_for_mips
Camera localization using apriltags port for mips with image adquisition

This repository has a modified example application for apriltags 3.0, which takes a picture from linux webcam driver (/dev/video*), converts to jpeg, and then gets the camera localization using apriltags and few extra source code lines.

THe makefiles has hardcoded compiler mips instructions, for building the source code for MIPS architecture (big endian, openwrt Linux distribution).

The are several components:
- apriltags 3.0
- the example apriltags_demo modified
- the lib jpeg9 library
- a module (v4l2) to use the linux uvc driver for getting pictures from webcam
- eigen library with Makefiles for MIPS

How to build
------------

```
cd eigen-libreria-c++-portada-a-MIPS-usada-por-pose-c++/eigen-eigen-323c052e1731/demos/mix_eigen_and_c/
# Instructions for eigen and mips : cat README.mips 
# Set the PATH var to your mips-openwrt gcc compiler folder: 
export PATH=/home/....etc...../OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin:$PATH
mips-openwrt-linux-g++ -c foo.cpp -O2  -I ../..
cp foo.o foo.cpp foo.h ../../../../apriltags_mips/example/
cd ../../../../apriltags_mips/
cd example/jpeg-9c/
make
cd ..
make
cp ../../eigen-libreria-c++-portada-a-MIPS-usada-por-pose-c++/eigen-eigen-323c052e1731/demos/mix_eigen_and_c/foo.o example/
make
```

How to use
----------

- Copy the apriltag_demo to your MIPS computer 
- (You will need the uvc Linux driver installed),
- ssh to that computer,
- plug a webcam to that computer,
- and run with : ```./apriltag_demo```.

