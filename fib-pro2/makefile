_ignore:=$(shell mkdir -p obj)

CC_FILES := $(wildcard src/*.cc)
OBJ_FILES := $(patsubst src/%.cc,obj/%.o,$(CC_FILES))
LD_FLAGS := 
CC_FLAGS := -Werror -D_GLIBCXX_DEBUG
obj/%.o: src/%.cc
	g++ -c $(CC_FLAGS) -o $@ $<

all: $(OBJ_FILES)
	g++ $(CC_FLAGS) obj/*.o -o taskman


clean:
	rm -rf obj src/*~ doc taskman jutge/out

jutge:release

doc:
	doxygen

release: all doc
	jutge/build.sh

.PHONY: build release jutge doc
