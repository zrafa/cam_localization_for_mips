CC = mips-openwrt-linux-gcc 
CXX = mips-openwrt-linux-g++ 

CPPFLAGS = -I..
# CFLAGS = -g -std=gnu99 -Wall -Wno-unused-parameter -Wno-unused-function -O3
CFLAGS = -std=gnu99 -Wall -Wno-unused-parameter -Wno-unused-function -O3
# CXXFLAGS = -g -Wall -O3
CXXFLAGS = -Wall -O3
# LDFLAGS =  -L /home/lechnerm/rafa/mr3020/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib/ -ldl -lpthread -lm

# LDFLAGS = -lpthread -lm



LDFLAGS =  -L /home/lechnerm/rafa/mr3020/OpenWrt-Toolchain-ar71xx-for-mips_r2-gcc-4.6-linaro_uClibc-0.9.33.2/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib/ -ldl -lpthread -lm -lstdc++

# CC=mips-openwrt-linux-gcc
#CFLAGS+=-g
# CFLAGS+=-Wall
# LDFLAGS+=-ljpeg
LDFLAGS+=jpeg-9c/.libs/libjpeg.a
LDFLAGS+=-L/home/lechnerm/rafa/programacion/gv/udp_streaming_jul30_105904_2017/cliente-udp-image-streaming/jpeg-9c
# PROG=v4l2
SRCS=utils
INCS=-I. -I$(SRCS) -I/home/lechnerm/rafa/programacion/gv/udp_streaming_jul30_105904_2017/cliente-udp-image-streaming/jpeg-9c

# OBJS =  $(PROG).o \
#         $(SRCS)/YUYVtoJPEG.o



TARGETS := apriltag_demo 

# TARGETS := apriltag_demo #opencv_demo

.PHONY: all
# all: apriltag_demo opencv_demo
all: apriltag_demo

apriltag_demo: apriltag_demo.o ../libapriltag.a v4l2.o $(SRCS)/YUYVtoJPEG.o $(SRCS)/RAWtoFILE.o foo.o
	@echo "   [$@]"
	@$(CC) -o $@ $^ $(LDFLAGS)

opencv_demo: opencv_demo.o ../libapriltag.a
	@echo "   [$@]"
	@$(CXX) -o $@ $^ $(LDFLAGS) `pkg-config --libs opencv`

%.o: %.c
	@echo "   $@"
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCS) $(CPPFLAGS)

%.o: %.cc
	@echo "   $@"
	@$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

.PHONY: clean
clean:
	@rm -rf *.o $(TARGETS)
