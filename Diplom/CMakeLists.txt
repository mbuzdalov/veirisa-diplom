cmake_minimum_required(VERSION 3.12)
project(Diplom)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
add_executable(Diplom source.h main.cpp EA/Basic/abstract_opl.cpp EA/Basic/abstract_opl.h EA/Basic/opl/opl.cpp EA/Basic/opl/opl.h EA/Basic/opl_separating/opl_separating.cpp EA/Basic/opl_separating/opl_separating.h EA/Basic/opl_Ab/opl_Ab.cpp EA/Basic/opl_Ab/opl_Ab.h "EA/Default Q-learning/abstract_oplQ.cpp" "EA/Default Q-learning/abstract_oplQ.h" "EA/Default Q-learning/oplQ/oplQ.cpp" "EA/Default Q-learning/oplQ/oplQ.h" "EA/Default Q-learning/oplQ_separating/oplQ_separating.cpp" "EA/Default Q-learning/oplQ_separating/oplQ_separating.h" name_getter.h "EA/Normalized Q-learning/abstract_oplNQ.cpp" "EA/Normalized Q-learning/abstract_oplNQ.h" "EA/Normalized Q-learning/oplNQ/oplNQ.cpp" "EA/Normalized Q-learning/oplNQ/oplNQ.h" )