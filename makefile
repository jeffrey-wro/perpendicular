OBJS	= main.o
SOURCE	= main.cpp
HEADER	= 
OUT		= perpendicular.out
CC		= /usr/local/oecore-x86_64/sysroots/x86_64-nilrtsdk-linux/usr/bin/arm-nilrt-linux-gnueabi/arm-nilrt-linux-gnueabi-g++ 
CFLAGS	= --sysroot=/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi -std=c++11 -pthread
INCLUDE = -I../ultrasonic/ultrasonic -I../myrio/myrio -I../myrio/myrio/csupport -I"/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi/usr/include" -I"/usr/local/oecore-x86_64/sysroots/cortexa9-vfpv3-nilrt-linux-gnueabi/usr/include/c++/4.9.2/arm-nilrt-linux-gnueabi" 
FLAGS	= -g -c -Wall -DMyRio_1900 -O0 -g3 -Wall -std=gnu++11 -fmessage-length=0 -mfpu=vfpv3 -mfloat-abi=softfp
LFLAGS 	= -L../ultrasonic/ultrasonic -L../myrio/myrio -L../myrio/myrio/csupport -lultrasonic -lcsupport -lmyrio -ldl

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -g $(OBJS) -o $(OUT)  $(LFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) main.cpp

clean:
	rm -f $(OBJS) $(OUT)



