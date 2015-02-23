CPP_FILES := $(wildcard src/*.cc)
OBJ_FILES := $(patsubst src/%.cc,obj/%.o,$(CPP_FILES))
LD_FLAGS := 
CC_FLAGS := -ansi -O2 -DNDEBUG -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -Wshadow

obj/%.o: src/%.cc
	g++ $(CC_FLAGS) -o $@ $<
	#g++  -o $@ $<

all: $(OBJ_FILES)


clean:
	rm obj/*.o
	rm src/*~
