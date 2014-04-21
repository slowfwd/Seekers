CFLAGS=-lbcm2835 -pthread
CFLAGS_OPENCV = -I/usr/include/opencv
LDFLAGS2_OPENCV = -lopencv_highgui -lopencv_core -lopencv_legacy -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc

DEPS = interface.h list.h dataStructures.h init.h

USERLAND_ROOT = /opt/vc/userland-master
CFLAGS_PI = \
	-I$(USERLAND_ROOT)/host_applications/linux/libs/bcm_host/include \
	-I$(USERLAND_ROOT)/host_applications/linux/apps/raspicam \
	-I$(USERLAND_ROOT) \
	-I$(USERLAND_ROOT)/interface/vcos/pthreads \
	-I$(USERLAND_ROOT)/interface/vmcs_host/linux \
	-I$(USERLAND_ROOT)/interface/mmal \
	-I/usr/local/include/opencv \

LDFLAGS_PI = -L$(USERLAND_ROOT)/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host

BUILD_TYPE=debug
#BUILD_TYPE=release

CFLAGS_COMMON = -Wno-multichar -g $(CFLAGS_OPENCV) $(CFLAGS_PI) -MD

ifeq ($(BUILD_TYPE), debug)
	CFLAGS = $(CFLAGS_COMMON)
endif
ifeq ($(BUILD_TYPE), release)
	CFLAGS = $(CFLAGS_COMMON) -O3
endif

LDFLAGS = 
LDFLAGS2 = $(LDFLAGS2_OPENCV) $(LDFLAGS_PI) -lX11 -lXext -lrt -lstdc++


all: seeker

%.o: %.c $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)


RaspiCamTest.o: 
	g++ -c $(CFLAGS) RaspiCamTest.cpp -o RaspiCamTest.o

seeker: RaspiCamTest.o motor.o datastructures.o interface.o list.o seeker.o
	g++ $(LDFLAGS) $+ $(LDFLAGS2) $(CFLAGS) -L. -lraspicamcv -lbcm2835 -o $@


clean:
	rm -f seeker RaspiCamTest.o




