CUR_PROG = molecules
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

.PHONY : all run debug clean

all: colour.o my_vector.o shape_manager.o molecule.o shape.o collision_detection.o collision_response.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) colour.o main.o my_vector.o shape_manager.o molecule.o shape.o collision_detection.o collision_response.o -o $(CUR_PROG) $(LDFLAGS)
	

	
colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o

my_vector.o: ./src/my_vector.cpp ./src/my_vector.h
	$(CPP) $(CFLAGS) -c ./src/my_vector.cpp -o my_vector.o

		
shape_manager.o: ./src/shape_manager.cpp ./src/shape_manager.h
	$(CPP) $(CFLAGS) -c ./src/shape_manager.cpp -o shape_manager.o
	
molecule.o: ./src/molecule.cpp ./src/molecule.h
	$(CPP) $(CFLAGS) -c ./src/molecule.cpp -o molecule.o	
	
shape.o: ./src/shape.cpp ./src/shape.h
	$(CPP) $(CFLAGS) -c ./src/shape.cpp -o shape.o
	
collision_detection.o: ./src/collision_detection.cpp ./src/collision_detection.h
	$(CPP) $(CFLAGS) -c ./src/collision_detection.cpp -o collision_detection.o	
	
collision_response.o: ./src/collision_response.cpp ./src/collision_response.h
	$(CPP) $(CFLAGS) -c ./src/collision_response.cpp -o collision_response.o			

run: all
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o
