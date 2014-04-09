CC=gcc
CFLAGS=-lbcm2835 -pthread
DEPS = interface.h list.h dataStructures.h
binaries = seeker
 
all: $(binaries)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

seeker: motor.o datastructures.o interface.o list.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(binaries) *.o
