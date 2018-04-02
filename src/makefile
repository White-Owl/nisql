PRJ=nisql
SRC=main.cpp read_arguments.cpp
OBJ=$(SRC:.cpp=.o)

LIBS=nanodbc/nanodbc.o

ifeq ($(OS),Windows_NT)
	PRJ := $(PRJ).exe
	LIBS += -lodbc32
else
	LIBS += $(shell odbc_config --libs)
endif

all: $(PRJ)

$(PRJ) : $(OBJ)
	g++ -o $@ $^ $(LIBS)

%.o : %.cpp
	g++ -c -std=c++11 -O2 -Werror -o $@ $^

clean:
	rm -f $(OBJ) $(PRJ)
