SRC_PATH := ./src
DFILE_PATH := ./dFiles
OBJ_PATH := ./obj
BIN_PATH := .

SOURCES := $(wildcard $(SRC_PATH)/*.cpp)
DFILES := $(patsubst %.cpp, $(DFILE_PATH)/%.d, $(notdir $(SOURCES)))
OBJECTS := $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(notdir $(SOURCES)))
EXE := $(BIN_PATH)/test.exe

CXX = clang++
CPPFLAGS = -I./include -std=c++14
CXXFLAGS = -c -Wall -O3 -pedantic

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $^ -o $@

$(OBJECTS): | $(OBJ_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(DFILES): | $(DFILE_PATH)

$(DFILE_PATH):
	mkdir -p $(DFILE_PATH)

include $(DFILES)

$(DFILE_PATH)/%.d: $(SRC_PATH)/%.cpp
	set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($(*F)\)\.o[ :]*,$(OBJ_PATH)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.h:;
#	prevent make from stopping when a header file is renamed, moved or deleted

clean:
	rm -f $(OBJ_PATH)/*.o $(DFILE_PATH)/*.d*