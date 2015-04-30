_ignore:=$(shell mkdir -p obj)

CPP_FILES := $(wildcard src/*.cc)
OBJ_FILES := $(patsubst src/%.cc,obj/%.o,$(CPP_FILES))
LD_FLAGS := 
CC_FLAGS := -Werror
obj/%.o: src/%.cc
	g++ -c $(CC_FLAGS) -o $@ $<

all: $(OBJ_FILES)
	g++ $(CC_FLAGS) obj/*.o -o taskman

clean:
	rm -f obj/*.o
	rm -f src/*~
	rm taskman
