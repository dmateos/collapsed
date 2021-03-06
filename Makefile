client_objects = \
	build/main.o \
	build/sprite.o \
	build/gl_program.o \
	build/gl_window.o \
	build/camera.o \
	build/texture.o \
	build/util.o \

client_flags = -lglfw3 -lglew -lassimp -lil -lilu -lilut -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

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

build/gl_window.o: src/gl_window.cpp
	$(CXX) -c -o $@ src/gl_window.cpp

build/camera.o: src/camera.cpp
	$(CXX) -c -o $@ src/camera.cpp

build/texture.o: src/texture.cpp
	$(CXX) -c -o $@ src/texture.cpp
	
build/util.o: src/util.cpp
	$(CXX) -c -o $@ src/util.cpp

clean:
	rm -rf build/*.o collapsed
