CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))
LD_FLAGS := 
CC_FLAGS := -ansi -O2 -DNDEBUG -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -Wshadow

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -o $@ $<

all: $(OBJ_FILES)


clean:
	rm obj/*.o
