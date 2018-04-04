_ignore:=$(shell mkdir -p obj)

CC_FILES := $(wildcard src/*.cc)
OBJ_FILES := $(patsubst src/%.cc,obj/%.o,$(CC_FILES))
LD_FLAGS := 
CC_FLAGS := -Werror -D_GLIBCXX_DEBUG

obj/%.o: src/%.cc
	@mkdir -p obj
	g++ -c $(CC_FLAGS) -o $@ $<

all: $(OBJ_FILES)
	g++ $(CC_FLAGS) obj/*.o -o taskman


clean:
	rm -rf obj src/*~ doc taskman release/out


doc:
	doxygen

release: all doc
	release/build.sh

jutge: all doc
	release/build.sh jutge

.PHONY: build release jutge doc
