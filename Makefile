CXX	= g++
CFLAGS	= -Wall 
CFLAG	= -g -Wall -Weffc++ -Wextra -pedantic
LDFLAGS = -lm

run:	main.o Board.o Player.o ttt_controller.o
	${CXX} ${CFLAGS} -o ttt main.o Board.o Player.o ttt_controller.o

main.o:	main.cpp
	${CXX} ${CFLAGS} -c main.cpp

Player.o: ./model/Player.cpp
	${CXX} ${CFLAGS} -c ./model/Player.cpp ./model/Player.h

Board.o: ./model/Board.cpp 
	${CXX} ${CFLAGS} -c ./model/Board.cpp ./model/Board.h

ttt_controller.o: ./controller/ttt_controller.cpp
	${CXX} ${CFLAGS} -c ./controller/ttt_controller.cpp ./controller/ttt_controller.h

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf run a.out
