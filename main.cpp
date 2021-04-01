#include<iostream>

#include"assets.hpp"

int main(int argc, char* argv[])
{
    Hero::Editor::PackGLSL("uiShader.glsl");
    Hero::Editor::PackGLSL("lineShader.glsl");
    Hero::Editor::PackGLSL("standardShader.glsl");
    Hero::Editor::PackDAE("plane.dae");
    Hero::Editor::PackDAE("ground.dae");
    Hero::Editor::PackDAE("player.dae");
    system("pause");

    return 0;
}