CUR_PROG = vector
ARGS = 

CPP = g++
LD = g++

WARNINGS = -Wall -Wextra
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image

.PHONY : all run debug clean

all: colour.o my_vector.o main.o canvas.o 
	$(LD) colour.o main.o my_vector.o canvas.o  -o $(CUR_PROG) $(LDFLAGS)
	
colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o

canvas.o: ./src/canvas.cpp ./src/canvas.h
	$(CPP) $(CFLAGS) -c ./src/canvas.cpp -o canvas.o

my_vector.o: ./src/my_vector.cpp ./src/my_vector.h
	$(CPP) $(CFLAGS) -c ./src/my_vector.cpp -o my_vector.o

main.o: ./src/main.cpp ./src/main.h
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o		

run: all
	./$(CUR_PROG) $(ARGS)

debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)

clean:
	rm *.o
