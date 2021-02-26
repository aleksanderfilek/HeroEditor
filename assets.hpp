#ifndef HEROEDITOR_ASSETS_HPP
#define HEROEDITOR_ASSETS_HPP

#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>

#include"tinyxml\tinyxml.h"

namespace Hero
{
    namespace Editor
    {
        bool PackGLSL(const std::string& path);
        bool PackDAE(const std::string& path);
    }
}

#endif