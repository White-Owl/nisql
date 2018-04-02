PRJ=nisql
SRC=main.cpp read_arguments.cpp
OBJ=$(SRC:.cpp=.o)

ifeq ($(OS),Windows_NT)
	PRJ := $(PRJ).exe
endif

all: $(PRJ)

$(PRJ) : $(OBJ)
	g++ -o $@ $^

%.o : %.cpp
	g++ -c -std=c++11 -O2 -Werror -o $@ $^

clean:
	rm -f $(OBJ) $(PRJ)
