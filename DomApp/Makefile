OS = $(shell uname -s)
CC = g++
MV = mv
CP = cp
RM = rm
MESSAGE =

#specify dependency list
OBJECTS ?= src/main.o
OUTPUT ?= Program
FLAGS ?= 
INCPATH ?= -I"sgct_0_9_5/include"

OPENGL=1

# check if argument OPENGL=1 is set, reguires glfw to be properly installed
ifdef OPENGL
	MESSAGE += OpenGL,
	ifeq ($(OS),Linux)
		FLAGS += -lsgct -lGL -lGLU -lX11 -lXrandr -static-libgcc -static-libstdc++
	else ifeq ($(OS),Darwin)
		FLAGS += -framework Cocoa -framework OpenGL -lglfw -lsgct -L"sgct_0_9_5/mac_lib"
	endif
endif




all: $(OBJECTS)
	-@echo "Linking for $(OS)"
	-@echo "Including $(MESSAGE)"
	-@echo " "
	$(CC) -o $(OUTPUT) $(OBJECTS) $(FLAGS) $(INCPATH)

clean:
	-@echo "Cleaning"
	-$(RM) src/*.o

# pattern that compiles all .o files, both .cpp and .c works (tested on linux)
%.o: %.cpp
	$(CC) $(INCPATH) -c $< -o $@


