# Root directory of GoogleTest
GTEST_DIR = ./googletest

# Compiler and flags
CXX = c++
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=gnu++11

# Archivos fuente del proyecto (ajusta las rutas si es necesario)
SRC_FILES = ../src/utilidades.cpp  # Agrega aquí otros archivos .cpp necesarios

# Object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Archivo de tests
TEST_FILE = tests.cpp
TEST_OBJ = $(TEST_FILE:.cpp=.o)

# Ejecutable final
TARGET = tests

# Google Test libraries
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Housekeeping build targets
.PHONY : clean all c

all : $(TARGET)

clean :
	rm -f $(TARGET) gtest.a gtest_main.a $(OBJ_FILES) $(TEST_OBJ)

c : clean all

# Rules for Google Test libraries
gtest-all.o : $(GTEST_DIR)/src/gtest-all.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $<

gtest_main.o : $(GTEST_DIR)/src/gtest_main.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $<

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Compile your classes into object files
%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Compile the tests into an object file
$(TEST_OBJ) : $(TEST_FILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Link the tests executable
$(TARGET) : $(TEST_OBJ) $(OBJ_FILES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(TARGET)

# Run the tests
run : $(TARGET)
	./$(TARGET)