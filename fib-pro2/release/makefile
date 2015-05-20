CC_FILES := $(wildcard *.cc)
OBJ_FILES := $(patsubst %.cc,%.o,$(CC_FILES))
LD_FLAGS := 
CC_FLAGS := -Werror -D_GLIBCXX_DEBUG

%.o: %.cc
	g++ -c $(CC_FLAGS) -o $@ $<

all: $(OBJ_FILES)
	g++ $(CC_FLAGS) *.o -o taskman

program.exe: all
	mv taskman program.exe

clean:
	rm -f taskman program.exe

.PHONY: build
