# # Makefile for Mac

# CXX = g++
# CXXFLAGS = -std=c++17 -O2
# TARGET = ecc_demo
# SRCS = ecc.cpp polar.cpp

# all:
# 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# # clean 규칙 (선택사항) - 만들어진 파일 삭제
# clean:
# 	rm -f $(TARGET)

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows (MSYS2, MinGW 등)
    TARGET_EXT = .exe
    RM = del /f
else
    # Mac or Linux
    TARGET_EXT =
    RM = rm -f
endif

# Compiler and flagsif
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Files
TARGET = ecc_final
SRCS = rs.cpp

# Default target
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(TARGET_EXT) $(SRCS)

# Run target
run: all
ifeq ($(OS),Windows_NT)
	./$(TARGET)$(TARGET_EXT)
else
	./$(TARGET)
endif

# Clean target
clean:
	$(RM) $(TARGET)$(TARGET_EXT)
