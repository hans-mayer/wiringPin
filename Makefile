

# Wed Jan 11 21:07:38 CET 2017 - mayer 


CC=gcc
DEPS = wiringPi.h 
OBJ = wiringPin.o
LIBS = -lwiringPi -lpthread

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wiringPin: $(OBJ) 
	$(CC) -o $@ $^ $(LIBS) 

clean: 
	rm -f wiringPin.o wiringPin

install:
	cp wiringPin /usr/local/bin 


