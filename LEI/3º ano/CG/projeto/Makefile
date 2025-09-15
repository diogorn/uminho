COMPILER = g++
FLAGS = -Wall -g -std=c++11
INCLUDES = -Iinclude

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)  # macOS
    LIBS = -framework OpenGL -framework GLUT -lGLEW -lIL -lILU -lILUT
else  # Linux
    LIBS = -lGL -lGLU -lglut -lGLEW -lIL -lILU -lILUT
endif

SRC_DIR = src
OBJ_DIR = bin

# Cria pasta bin
$(shell mkdir -p $(OBJ_DIR))

SRC_ENGINE_GENERATOR = \
	$(SRC_DIR)/figuras/Triangles.cpp \
	$(SRC_DIR)/ficheiro3d/Ficheiro.cpp \
	$(SRC_DIR)/engine/groups.cpp

SRC_ENGINE = \
	$(SRC_DIR)/tinyxml/tinyxml.cpp \
	$(SRC_DIR)/tinyxml/tinyxmlparser.cpp \
	$(SRC_DIR)/tinyxml/tinyxmlerror.cpp \
	$(SRC_DIR)/tinyxml/tinystr.cpp \
	$(SRC_DIR)/engine/World.cpp \
	$(SRC_DIR)/engine/processaXML.cpp \
	$(SRC_DIR)/engine/engine.cpp

SRC_GENERATOR = \
	$(SRC_DIR)/gerador/gerador.cpp

OBJS_ENGINE_GENERATOR = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_ENGINE_GENERATOR:.cpp=.o))
OBJS_ENGINE = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_ENGINE:.cpp=.o))
OBJS_GENERATOR = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_GENERATOR:.cpp=.o))

all: generator engine

generator: $(OBJS_ENGINE_GENERATOR) $(OBJS_GENERATOR)
	$(COMPILER) $(FLAGS) -o files/generator $^ $(LIBS)

engine: $(OBJS_ENGINE_GENERATOR) $(OBJS_ENGINE)
	$(COMPILER) $(FLAGS) -o files/engine $^ $(LIBS)

#Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o generator engine