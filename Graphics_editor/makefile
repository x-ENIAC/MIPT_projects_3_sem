CUR_PROG = graphical_editor
ARGS = 

CPP = g++
LD = g++

WARNINGS = 
STANDARD = 
OPTIMIZATION = -O1 -Wno-reorder

CFLAGS = $(WARNINGS) $(STANDARD) $(OPTIMIZATION)
LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -L.

.PHONY : all run debug clean

all: app.o tool_manager.o colour.o point.o view_manager.o manager_of_canvas_managers.o animation_manager.o spline.o
	$(CPP) $(CFLAGS) -c ./src/main.cpp -o main.o
	$(LD) -Llib/ app.o tool_manager.o colour.o point.o view_manager.o animation_manager.o manager_of_canvas_managers.o spline.o main.o -ldl -o $(CUR_PROG) $(LDFLAGS)
	
app.o: ./src/app.cpp ./src/app.h
	$(CPP) $(CFLAGS) -c ./src/app.cpp -o app.o
	
tool_manager.o: ./src/tool_manager.cpp ./src/tool_manager.h
	$(CPP) $(CFLAGS) -c ./src/tool_manager.cpp -o tool_manager.o

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
	
spline.o: ./src/spline.cpp ./src/spline.h
	$(CPP) $(CFLAGS) -c ./src/spline.cpp -o spline.o		

run: all
	./$(CUR_PROG) $(ARGS)

callgrind_debug: all
	valgrind --dump-instr=yes --tool=callgrind  ./$(CUR_PROG) $(ARGS)
	
debug: all
	valgrind --track-origins=yes ./$(CUR_PROG) $(ARGS)	

clean:
	rm *.o
