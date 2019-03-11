CC = g++ -std=c++11
OBJ = main.o triangle.o righttriangle.o ellipse.o shape.o
	
all: $(OBJ)
	$(CC) $(OBJ) -o lr2
$(OBJ): %.o: %.cpp triangle.h righttriangle.h ellipse.h shape.h
	$(CC) -c $< -o $@ 
clean:
	rm *.o
	rm lr2

