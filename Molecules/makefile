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

all: colour.o point.o my_vector.o object_manager.o circle.o object.o collision_detection.o collision_response.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) colour.o point.o main.o my_vector.o object_manager.o circle.o object.o collision_detection.o collision_response.o -o $(CUR_PROG) $(LDFLAGS)
	

	
colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o
	
point.o: ./src/point.cpp ./src/point.h
	$(CPP) $(CFLAGS) -c ./src/point.cpp -o point.o	

my_vector.o: ./src/my_vector.cpp ./src/my_vector.h
	$(CPP) $(CFLAGS) -c ./src/my_vector.cpp -o my_vector.o

		
object_manager.o: ./src/object_manager.cpp ./src/object_manager.h
	$(CPP) $(CFLAGS) -c ./src/object_manager.cpp -o object_manager.o
	
circle.o: ./src/circle.cpp ./src/circle.h
	$(CPP) $(CFLAGS) -c ./src/circle.cpp -o circle.o	
	
object.o: ./src/object.cpp ./src/object.h
	$(CPP) $(CFLAGS) -c ./src/object.cpp -o object.o
	
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
