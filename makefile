all: postfix2infix.x

postfix2infix.x: proj4_driver.o
	g++47 -o postfix2infix.x proj4_driver.o
proj4_driver.o: proj4_driver.cpp
	g++47 -g -c -Wall -Wextra -std=c++11 proj4_driver.cpp
clean:
	rm *.o proj4.x
