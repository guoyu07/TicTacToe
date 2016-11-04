CXX	= g++
CFLAGS	= -Wall --std=c++11 
CFLAG	= -g -Wall -Weffc++ -Wextra -pedantic
LDFLAGS = -lm

run:	main.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o
	${CXX} ${CFLAGS} -o ttt main.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o -o ttt.cgi

cli:	main_cli.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o
	${CXX} ${CFLAGS} -o ttt main_cli.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o -o ttt.cgi

test:	sampleTest.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o
	${CXX} ${CFLAGS} -o ttt sampleTest.o Board.o BigBoard.o Player.o TTTController.o PlayerDao.o -o test.cgi

main.o:	main.cpp
	${CXX} ${CFLAGS} -c main.cpp

main_cli.o:main_cli.cpp
	${CXX} ${CFLAGS} -c main_cli.cpp

Player.o: ./model/Player.cpp
	${CXX} ${CFLAGS} -c ./model/Player.cpp ./model/Player.h

PlayerDao.o: ./model/PlayerDao.cpp
	${CXX} ${CFLAGS} -c ./model/PlayerDao.cpp ./model/PlayerDao.h

Board.o: ./model/Board.cpp 
	${CXX} ${CFLAGS} -c ./model/Board.cpp ./model/Board.h

BigBoard.o: ./model/BigBoard.cpp
	${CXX} ${CFLAGS} -c ./model/BigBoard.cpp ./model/BigBoard.h

TTTController.o: ./controller/TTTController.cpp
	${CXX} ${CFLAGS} -c ./controller/TTTController.cpp ./controller/TTTController.h

sampleTest.o:	sampleTest.cpp
	${CXX} ${CFLAGS} -c sampleTest.cpp

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf model/*.gch controller/*.gch
	rm -rf run ttt.cgi test.cgi
