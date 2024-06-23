# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -municode
LDFLAGS = -lgdi32

# Output binary name (relative to the Makefile location)
TARGET = FileEncryptionTool.exe

# Source files (relative to the Makefile location)
SRCS = ../src/main.c

# Object files directory
OBJDIR = .

# Object files (replace .cpp with .o in SRCS)
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I../include

# Build rule
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

# Clean rule (cross-platform)
clean:
	rm -f $(OBJS) $(TARGET)