g++ -c -Ilibs -Iinclude *.cpp
g++ -c -Ilibs libs/tinyxml/*.cpp
g++ -c -Iinclude -Ilibs source/*.cpp
g++ *.o
rm *.o