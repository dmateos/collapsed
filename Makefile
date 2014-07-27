client_objects = \
	build/main.o \

client_flags = -lglfw3 -lglew -lassimp -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all: collapsed

#Client
collapsed: $(client_objects)
	$(CXX) $(client_flags) -o $@ $(client_objects)

build/main.o: src/main.cpp
	$(CXX) -c -o $@ src/main.cpp

clean:
	rm -rf build/*.o collapsed
