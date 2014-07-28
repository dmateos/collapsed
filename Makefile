client_objects = \
	build/main.o \
	build/sprite.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: collapsed

#Client
collapsed: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

build/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

build/sprite.o: src/sprite.cpp
	$(CXX) -c -o $@ src/sprite.cpp

clean:
	rm -rf build/*.o collapsed
