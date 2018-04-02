PRJ=nanodbc.o
SRC=nanodbc.cpp
INCLUDE=..

all: $(PRJ)

%.o : %.cpp
	g++ -c -std=c++11 -O2 -Werror -o $@ -I$(INCLUDE) $^

clean:
	rm -f $(PRJ)
