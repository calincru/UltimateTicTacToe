INCLUDE_DIRS = ./include ./src ./src/strategies
NAME = ab_bot

HEADERS = $(wildcard src/*.h)
SRC = $(wildcard src/*.cpp) $(wildcard ./src/strategies/*.cpp)
OBJ = $(subst src/,obj/,$(patsubst %.cpp,%.o,$(SRC)))

CXXFLAGS = $(foreach idir, $(INCLUDE_DIRS), -I$(idir)) \
           -std=c++14 \
           -g -DDEBUG

.PHONY: build run clean

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $(NAME)

obj/%.o: src/%.cpp $(HEADERS)
	@mkdir -p obj
	@mkdir -p obj/strategies
	$(CXX) -c $(CXXFLAGS) $< -o $@

run: build
	./$(NAME)

clean:
	rm -rf obj $(NAME)
