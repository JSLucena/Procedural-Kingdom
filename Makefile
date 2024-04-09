# Define the executable name
TARGET = main

# Define the C source files
CC = g++  # Replace with your preferred C compiler if needed
CFLAGS = -Wall -pthread -std=c++20 -fdata-sections -ffunction-sections -flto -g ## Add additional flags like -g for debugging
INCLUDE_DIRS += include/
CFLAGS += -I$(INCLUDE_DIRS)
LDFLAGS =  -lglfw -lvulkan -lpthread -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXrandr  -lboost_system -Wl,--gc-sections -flto
SRC_FILES_C += $(wildcard src/*.c)# Add additional source files here (separate by space)
SRC_FILES_CPP += $(wildcard src/*.cpp)# Add additional source files here (separate by space)

#SRC_FILES += $(wildcard src/*.c)
# Define object files (automatically generated)
OBJECTS = $(SRC_FILES_C:.c=.o)  # Replace .c with .o for object files
OBJECTS += $(SRC_FILES_CPP:.cpp=.o)  # Replace .c with .o for object files



# Main rule - builds the executable
all: $(TARGET) shaders

# Rule to compile a specific source file echo "Compiling $< to $@..." echo "Compiling $< to $@..."
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
# Rule to link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET)  

shaders: shaders/vert.spv shaders/frag.spv

shaders/vert.spv: shaders/shader.vert
	glslc shaders/shader.vert -o shaders/vert.spv

shaders/frag.spv: shaders/shader.frag
	glslc shaders/shader.frag -o shaders/frag.spv

clean: cleanobj cleanshader
# Rule to clean up object files
cleanobj:
# Remove object files and executable
	rm -f $(OBJECTS) $(TARGET)

cleanshader:
	rm -f shaders/*.spv

