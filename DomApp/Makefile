OS = $(shell uname -s)
CC = g++
MV = mv
CP = cp
RM = rm
MESSAGE =

#specify dependency list
OBJECTS ?= src/main.o src/ImmersiveKidz.o src/Model.o src/DrawableObject.o src/Billboard.o src/BatchBillboard.o src/Illustration.o src/Camera.o src/SceneLoader.o src/Skybox.o src/HUD.o src/Plane.o src/AudioHandler.o src/SoundObject.o src/Animation.o
OUTPUT ?= Program
FLAGS ?=
CXXFLAGS ?= 
INCPATH ?= -I"sgct_0_9_5/include"

OPENGL=1
#SOUND=1
TEST=1

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

# check if argument OPENGL=1 is set, reguires glfw to be properly installed
ifdef TEST
	MESSAGE += OpenGL,
	OBJECTS += unit_test/UnitTests.o
	INCPATH += -I"unit_test" -D"_RUN_TESTS_AT_STARTUP_" -D"_RUN_TESTS_"
	ifeq ($(OS),Linux)
		FLAGS += -lgtest -L"unit_test/lib/linux_lib"
	else ifeq ($(OS),Darwin)
		FLAGS += -lgtest -L"unit_test/lib/mac_lib"
	else ifeq ($(OS),MINGW32_NT-6.1)
		FLAGS += 
	endif
endif

# check if argument OPENGL=1 is set, reguires glfw to be properly installed
ifdef SOUND
	MESSAGE += OpenAL,
	ifeq ($(OS),Linux)
		FLAGS += -lalut
	else ifeq ($(OS),Darwin)
		FLAGS += -framework ALUT -framework OpenAL
	else ifeq ($(OS),MINGW32_NT-6.1)
		FLAGS += 
	endif
else
	INCPATH += -D"NO_SOUND"
endif



all: $(OBJECTS)
	-@echo "Linking for $(OS)"
	-@echo "Including $(MESSAGE)"
	-@echo " "
	$(CC) -o $(OUTPUT) $(OBJECTS) $(INCPATH) $(CXXFLAGS) $(FLAGS) 

clean:
	-@echo "Cleaning"
	-$(RM) src/*.o
	-$(RM) unit_test/*.o

# pattern that compiles all .o files
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCPATH) -c $< -o $@


