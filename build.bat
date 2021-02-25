@echo off
g++ -c -Ilibs\ *.cpp
g++ -c libs\tinyxml\*.cpp
g++ *.o
del *.o