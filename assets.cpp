#include"assets.hpp"

bool PackGLSL(const std::string path)
{
    std::string shaderData[3];
    int shaderType = -1;

    std::ifstream readFile;
    readFile.open(path);

    if(!readFile.is_open())
    {
        std::cout<<"Could not open the file: "<<path<<std::endl;
        return false;
    }

    std::string line;
    while(std::getline(readFile, line))
    {
        if(line.compare("#shader vertex") == 0)
        {
            shaderType = 0;
            continue;
        }
        else if(line.compare("#shader fragment") == 0)
        {
            shaderType = 1;
            continue;
        }
        else if(line.compare("#shader geometry") == 0)
        {
            shaderType = 2;
            continue;  
        }

        if(shaderType < 0)
        {
            continue;
        }

        if(line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        {
            continue;
        }

        std::size_t commentPosition = line.find("//");
        if(commentPosition != std::string::npos){
            line.erase(commentPosition);
        }

        shaderData[shaderType] += line;
        shaderData[shaderType] += "\n";
    }

    readFile.close();

    std::string newPath = path;
    newPath += "bin";

    std::ofstream writeFile;
    writeFile.open(newPath, std::ios::out | std::ios::binary);

    if(!writeFile.is_open())
    {
        std::cout<<"Could not create the file: "<<newPath<<std::endl;
        return false;
    }

    for(int i = 0; i < 3; i++){
        const std::string& str = shaderData[i];
        size_t size = str.size();

        writeFile.write((const char*)&size, sizeof(size));
        writeFile.write(str.c_str(), size);
    }

    writeFile.close();

    return true;
}

bool PackDAE(const std::string path)
{
    
    return true;
}