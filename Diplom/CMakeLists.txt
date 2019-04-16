cmake_minimum_required(VERSION 3.12)
project(Diplom)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
add_executable(Diplom source.h main.cpp EA/Basic/abstract_opl.cpp EA/Basic/abstract_opl.h EA/Basic/opl/opl.cpp EA/Basic/opl/opl.h EA/Basic/opl_separating/opl_separating.cpp EA/Basic/opl_separating/opl_separating.h EA/Basic/opl_Ab/opl_Ab.cpp EA/Basic/opl_Ab/opl_Ab.h "EA/Q-learning/abstract_oplQ.cpp" "EA/Q-learning/abstract_oplQ.h" "EA/Q-learning/oplQ/oplQ.cpp" "EA/Q-learning/oplQ/oplQ.h" name_getter.h)