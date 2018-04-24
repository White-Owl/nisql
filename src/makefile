PRJ=nisql
SRC=main.cpp read_arguments.cpp decript_format_options.cpp \
    print_result_as_txt.cpp print_result_as_csv.cpp \
    print_result_as_xml.cpp print_result_as_json.cpp

OBJ=$(SRC:.cpp=.o)

ifeq ($(OS),Windows_NT)
	PRJ := $(PRJ).exe
	LIBS += -lodbc32
else
	LIBS += -lodbc

	# use next line if you are on Red Hat
	#LIBS += $(shell odbc_config --libs)
endif

all: $(PRJ)

$(PRJ) : $(OBJ) nanodbc/nanodbc.o
	g++ -o $@ $^ $(LIBS)

%.o : %.cpp
	g++ -c -std=c++11 -O2 -Werror -o $@ $^

clean:
	rm -f $(OBJ) $(PRJ)
