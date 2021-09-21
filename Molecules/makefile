CUR_PROG = molecules
ARGS = 

CPP = g++
LD = g++

WARNINGS = -Wall -Wextra
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image

.PHONY : all run debug clean

all: colour.o my_vector.o molecule_manager.o molecule.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) colour.o main.o my_vector.o molecule_manager.o molecule.o -o $(CUR_PROG) $(LDFLAGS)
	

	
colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o

my_vector.o: ./src/my_vector.cpp ./src/my_vector.h
	$(CPP) $(CFLAGS) -c ./src/my_vector.cpp -o my_vector.o

		
molecule_manager.o: ./src/molecule_manager.cpp ./src/molecule_manager.h
	$(CPP) $(CFLAGS) -c ./src/molecule_manager.cpp -o molecule_manager.o
	
molecule.o: ./src/molecule.cpp ./src/molecule.h
	$(CPP) $(CFLAGS) -c ./src/molecule.cpp -o molecule.o	

run: all
	./$(CUR_PROG) $(ARGS)

debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)

clean:
	rm *.o
