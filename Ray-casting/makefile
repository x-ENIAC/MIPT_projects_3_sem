CUR_PROG = ray_casting
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image

.PHONY : all run debug clean

all: colour.o my_vector.o  screen_info.o sphere.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) colour.o main.o my_vector.o screen_info.o sphere.o -o $(CUR_PROG) $(LDFLAGS)
	

	
colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o

my_vector.o: ./src/my_vector.cpp ./src/my_vector.h
	$(CPP) $(CFLAGS) -c ./src/my_vector.cpp -o my_vector.o

		
screen_info.o: ./src/screen_info.cpp ./src/screen_info.h
	$(CPP) $(CFLAGS) -c ./src/screen_info.cpp -o screen_info.o
	
sphere.o: ./src/sphere.cpp ./src/sphere.h
	$(CPP) $(CFLAGS) -c ./src/sphere.cpp -o sphere.o	

run: all
	./$(CUR_PROG) $(ARGS)

debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)

clean:
	rm *.o
