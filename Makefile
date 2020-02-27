FILAMENT_LIBS=-lfilament -lbackend -lbluegl -lbluevk -lfilabridge -lfilaflat -lutils -lgeometry -lsmol-v -libl
FRAMEWORKS=-framework Cocoa -framework Metal -framework CoreVideo
CC=clang++

demo: demo.o
	$(CC) -Lfilament/lib/x86_64/ demo.o $(FILAMENT_LIBS) $(FRAMEWORKS) -o demo

demo.o: demo.cc
	$(CC) -Ifilament/include/ -std=c++14 -c demo.cc

clean:
	rm -f demo demo.o

.PHONY: clean
