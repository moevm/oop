all: main.o shape.o point.o sqare.o five_pointed_star.o pentagon.o polygon.o
	g++ main.o shape.o point.o sqare.o five_pointed_star.o pentagon.o polygon.o -o main
main.o: main.cpp color.h point.h color.h shape.h
	g++ -c main.cpp
shape.o: shape.cpp color.h point.h shape.h
	g++ -c shape.cpp
sqare.o: sqare.cpp color.h point.h shape.h polygon.h
	g++ -c sqare.cpp
five_pointed_star.o: five_pointed_star.cpp color.h point.h shape.h
	g++ -c five_pointed_star.cpp
pentagon.o: pentagon.cpp color.h point.h shape.h
	g++ -c pentagon.cpp
polygon.o: polygon.cpp color.h point.h shape.h
	g++ -c polygon.cpp
point.o: point.cpp point.h 
	g++ -c point.cpp


