
run: build
	./prog

build:
	g++ -o prog -Wall -pedantic -std=c++11 `find src -name '*.cpp'`

debug:
	g++ -o prog -Wall -pedantic -std=c++11 -g `find src -name '*.cpp'`
	gdb prog
