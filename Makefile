# Define the executable name
TARGET = main

# Define the C source files
CC = g++  # Replace with your preferred C compiler if needed
CFLAGS = -Wall -pthread -std=c++20 -g #-flto# Add additional flags like -g for debugging
INCLUDE_DIRS += include/
CFLAGS += -I$(INCLUDE_DIRS)
LDFLAGS = -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lboost_system #-flto
SRC_FILES_C += $(wildcard src/*.c)# Add additional source files here (separate by space)
SRC_FILES_CPP += $(wildcard src/*.cpp)# Add additional source files here (separate by space)

#SRC_FILES += $(wildcard src/*.c)
# Define object files (automatically generated)
OBJECTS = $(SRC_FILES_C:.c=.o)  # Replace .c with .o for object files
OBJECTS += $(SRC_FILES_CPP:.cpp=.o)  # Replace .c with .o for object files

# Main rule - builds the executable
all: $(TARGET)

# Rule to compile a specific source file
%.o: %.c
	echo "Compiling $< to $@..."
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.cpp
	echo "Compiling $< to $@..."
	$(CC) $(CFLAGS) -c $< -o $@
# Rule to link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET)  

# Rule to clean up object files
clean:
# Remove object files and executable
	rm -f $(OBJECTS) $(TARGET)  

