TARGET=circuitkz-drawer
CXX=g++
LD=g++
OBJS=main.cpp
LIBS=-std=c++17

all:main.cpp
			g++ main.cpp interface.cpp -o circuitkz-drawer $(pkg-config gtkmm-4.0 --cflags --libs)
clean:
	        rm -rf *.o
