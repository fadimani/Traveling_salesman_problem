cmake_minimum_required(VERSION 3.24)
project(miniProjet2)

set(CMAKE_CXX_STANDARD 17)


add_executable(recuit_Simule recuit_Simule.cpp shared_Functionalities.h shared_Functionalities.cpp)
add_executable(genetique genetique.cpp shared_Functionalities.h shared_Functionalities.cpp)
add_executable(escalade_Simple escalade_Simple.cpp shared_Functionalities.h shared_Functionalities.cpp)
add_executable(escalade_Complet escalade_Complet.cpp shared_Functionalities.h shared_Functionalities.cpp)