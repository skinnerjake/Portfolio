CXX = g++
SRCS = Board.cpp Edge.cpp  getInt.cpp Ledge.cpp Player.cpp Space.cpp Tile.cpp main.cpp
HEADERS = Board.hpp Edge.hpp getInt.hpp Ledge.hpp Player.hpp Space.hpp Tile.hpp

CFLAGS = -Wall -Werror -g -std=

make: ${SRCS} ${HEADERS}
	${CXX} ${SRCS} -o main

clean:
	rm -f *.o main