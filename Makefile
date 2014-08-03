client_objects = \
	build/main.o \
	build/sprite.o \
	build/gl_program.o \
	build/camera.o \
	build/texture.o \

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

build/camera.o: src/camera.cpp
	$(CXX) -c -o $@ src/camera.cpp

build/texture.o: src/texture.cpp
	$(CXX) -c -o $@ src/texture.cpp

clean:
	rm -rf build/*.o collapsed
