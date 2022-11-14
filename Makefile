# compiler to tuse
CXX = g++
# flags
CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -O3 -DNDEBUG
# source directory
SRC_DIR = src
# object code directory
OBJ_DIR = obj
# source files
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
# object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
# header files
INC = -Iinc
# executable file name
EXE = Simple-SQL
# create object files directory
$(shell mkdir -p $(OBJ_DIR))

.PHONY: all clean run debug

all: $(EXE)

$(OBJS): $(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $(INC) -o $@ $^

$(EXE): $(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -f $(EXE)
	rm -rf $(OBJ_DIR)

run: $(EXE)
	./$(EXE)


