TARGET = Vect.a
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	CC = clang++ -Wall -Werror -Wextra -std=c++17 -lsubunit -lrt -lpthread -lm
	OPEN_CMD = xdg-open
else ifeq ($(OS), Darwin)
	CC = clang++ -Wall -Werror -Wextra -std=c++17
	OPEN_CMD = open
endif

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) -c $() $(SRC)
	ar rc $@ $(OBJ)
	make clean_obj

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean: clean_lib clean_obj
	rm -rf lib_test

.PHONY: all clean
