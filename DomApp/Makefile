OS = $(shell uname -s)
CC = g++
MV = mv
CP = cp
RM = rm
MESSAGE =

#specify dependency list
OBJECTS ?= src/main.o src/ImmersiveKidz.o src/Model.o src/DrawableObject.o src/Billboard.o src/Illustration.o src/Camera.o src/SceneLoader.o
OUTPUT ?= Program
FLAGS ?= 
INCPATH ?= -I"sgct_0_9_5/include"

OPENGL=1

# check if argument OPENGL=1 is set, reguires glfw to be properly installed
ifdef OPENGL
	MESSAGE += OpenGL,
	ifeq ($(OS),Linux)
		FLAGS += -lsgct -lGL -lGLU -lX11 -lXrandr -static-libgcc -static-libstdc++ -L"sgct_0_9_5/linux_lib"
	else ifeq ($(OS),Darwin)
		FLAGS += -framework Cocoa -framework OpenGL -lglfw -lsgct -L"sgct_0_9_5/mac_lib"
	else ifeq ($(OS),MINGW32_NT-6.1)
		OUTPUT = Program.exe
		FLAGS += -L"sgct_0_9_5/win_mingw32_lib" -lsgct32 -lopengl32 -lglu32 -lws2_32 -static-libgcc -static-libstdc++
	endif
endif




all: $(OBJECTS)
	-@echo "Linking for $(OS)"
	-@echo "Including $(MESSAGE)"
	-@echo " "
	$(CC) -o $(OUTPUT) $(OBJECTS) $(INCPATH) $(FLAGS) 

clean:
	-@echo "Cleaning"
	-$(RM) src/*.o

# pattern that compiles all .o files
%.o: %.cpp
	$(CC) $(INCPATH) -c $< -o $@


