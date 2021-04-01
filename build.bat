@echo off
g++ -c -Iinclude -Ilibs source\*.cpp
g++ -c -Ilibs libs\tinyxml\*.cpp
g++ -c -Ilibs -Iinclude main.cpp
g++ *.o
del *.o