#include"assets.hpp"

int main(int argc, char* argv[])
{
    PackGLSL("shader.glsl");
    PackDAE("Cube.dae");
    
    return 0;
}