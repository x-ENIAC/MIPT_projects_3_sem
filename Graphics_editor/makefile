CUR_PROG = graphical_editor
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

.PHONY : all run debug clean

all: colour.o point.o view_manager.o manager_of_canvas_managers.o animation_manager.o interpolator.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) colour.o point.o view_manager.o animation_manager.o manager_of_canvas_managers.o interpolator.o main.o -o $(CUR_PROG) $(LDFLAGS)
	

colour.o: ./src/colour.cpp ./src/colour.h
	$(CPP) $(CFLAGS) -c ./src/colour.cpp -o colour.o
	
point.o: ./src/point.cpp ./src/point.h
	$(CPP) $(CFLAGS) -c ./src/point.cpp -o point.o
	
view_manager.o: ./src/view_manager.cpp ./src/view_manager.h
	$(CPP) $(CFLAGS) -c ./src/view_manager.cpp -o view_manager.o	
	
manager_of_canvas_managers.o: ./src/manager_of_canvas_managers.cpp ./src/manager_of_canvas_managers.h
	$(CPP) $(CFLAGS) -c ./src/manager_of_canvas_managers.cpp -o manager_of_canvas_managers.o
	
animation_manager.o: ./src/animation_manager.cpp ./src/animation_manager.h
	$(CPP) $(CFLAGS) -c ./src/animation_manager.cpp -o animation_manager.o
	
interpolator.o: ./src/interpolator.cpp ./src/interpolator.h
	$(CPP) $(CFLAGS) -c ./src/interpolator.cpp -o interpolator.o		

run: all
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o
