client_objects = \
	build/main.o \
	build/sprite.o \
	build/gl_program.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: collapsed

#Client
collapsed: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

build/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

build/sprite.o: src/sprite.cpp
	$(CXX) -c -o $@ src/sprite.cpp

build/gl_program.o: src/gl_program.cpp
	$(CXX) -c -o $@ src/gl_program.cpp

clean:
	rm -rf build/*.o collapsed
