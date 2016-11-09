cmake_minimum_required(VERSION 3.6)
project(pp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#Original
set(SOURCE_FILES main.cpp model/Player.cpp model/Player.h model/Board.cpp model/Board.h controller/TTTController.cpp controller/TTTController.h model/PlayerDao.h model/PlayerDao.cpp model/BigBoard.cpp model/BigBoard.h)
#Sample test
#set(SOURCE_FILES sampleTest.cpp common.h model/Player.cpp model/Player.h model/Board.cpp model/Board.h controller/TTTController.cpp controller/TTTController.h model/PlayerDao.h model/PlayerDao.cpp model/BigBoard.cpp model/BigBoard.h)
#set(SOURCE_FILES model/Player.cpp model/Player.h model/Board.cpp model/Board.h controller/TTTController.cpp controller/TTTController.h model/PlayerDao.h model/PlayerDao.cpp model/BigBoard.cpp model/BigBoard.h)
add_executable(ttt ${SOURCE_FILES})