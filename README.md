# cam_localization_for_mips
Camera localization using latest apriltags port for mips with image adquisition

2019. Alejandro Mora, Candelaria Alvarez, Rafael Zurita.

This repository has a modified example application for apriltags 3.0, which takes a picture from linux webcam driver (/dev/video*), converts to jpeg, and then gets the camera localization using apriltags.

There are no external dependencies, and the code is almost 100% in C language. It lets to test this prototype in embedded systems (no opencv, neither other huge libraries dependences).

**Goal**: After prototype is ready (hardware and software) it should be demostrated
that the module consumes low power and it fits the 
the response time requirements for robots navigation like Frankestito. It means,
the correctness depends not only on the logical result but also the time it was delivered - failure to respond is as bad as the wrong response.

The makefiles has hardcoded compiler mips instructions, for building the source code for MIPS architecture (big endian, openwrt Linux distribution).

There are several components:
- apriltags 3.0
- the example apriltags_demo modified, which reports camera localization in a 2d world
- the lib jpeg9 library
- a module (v4l2) for using the linux uvc driver for getting pictures from webcam
- eigen library with Makefiles for MIPS

How to build
------------

It is a little mess yet, but you will get the idea:

```
# the global config is at config.h. For example: camera intrinsic parameters
# edit example/config.h if you need to change them
cd eigen-libreria-c++-portada-a-MIPS-usada-por-pose-c++/eigen-eigen-323c052e1731/demos/mix_eigen_and_c/
# Instructions for eigen and mips : cat README.mips 
# Set the PATH var to your mips-openwrt gcc compiler folder: 
export PATH=/home/....etc...../OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/bin:$PATH
mips-openwrt-linux-g++ -c foo.cpp -O2  -I ../..
cp foo.o foo.cpp foo.h ../../../../apriltags_mips/example/
cd ../../../../apriltags_mips/
cd example/jpeg-9c/
make
cd ../../../
cd apriltags_mips/example/
cp ../../eigen-libreria-c++-portada-a-MIPS-usada-por-pose-c++/eigen-eigen-323c052e1731/demos/mix_eigen_and_c/foo.o .   # it must be copied under example/ folder
make
```

How to use
----------

- Copy the apriltag_demo to your MIPS computer 
- (You will need the uvc Linux driver installed),
- ssh to that computer,
- plug a webcam to that computer,
- and run with : ```./apriltag_demo```.

