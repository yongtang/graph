FILAMENT_LIBS=-lfilament -lbackend -lbluegl -lbluevk -lfilabridge -lfilaflat -lutils -lgeometry -lsmol-v -libl
FRAMEWORKS=-framework Cocoa -framework Metal -framework CoreVideo
CC=clang++

demo: demo.o
	$(CC) -Lfilament/lib/x86_64/ demo.o $(FILAMENT_LIBS) $(FRAMEWORKS) -o demo

bakedColor.inc: bakedColor.mat
	filament/bin/matc -a opengl -a metal -o bakedColor.inc -f header bakedColor.mat

demo.o: demo.cc bakedColor.inc
	$(CC) -Ifilament/include/ -std=c++14 -c demo.cc

clean:
	rm -f demo demo.o

.PHONY: clean
