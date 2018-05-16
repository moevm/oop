all: Shape

Shape: main.o Square.o Right_Triangle.o Isosceles_triangle.o Shape.o
	g++ main.o Square.o Right_Triangle.o Isosceles_triangle.o Shape.o -o Shape

main.o: main.cpp
	g++ -c main.cpp
	
Square.o: Square.cpp
	g++ -c Square.cpp
	
Right_Triangle.o: Right_Triangle.cpp
	g++ -c Right_Triangle.cpp
	
Isosceles_triangle.o: Isosceles_triangle.cpp
	g++ -c Isosceles_triangle.cpp
	
Shape.o: Shape.cpp
	g++ -c Shape.cpp

clean:
	rm -rf *.o Shape