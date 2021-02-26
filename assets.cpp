#include"assets.hpp"
namespace Hero
{
namespace Editor
{
bool PackGLSL(const std::string& path)
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

bool PackDAE(const std::string& path)
{
    TiXmlDocument doc(path.c_str());
    if(!doc.LoadFile())
    {
        std::cout<<"Could not open file: "<<path<<std::endl;
        return false;
    }

    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElement;
    TiXmlHandle hRoot(0);

    pElement = hDoc.FirstChildElement().Element();
    if(!pElement)
    {
        return false;
    }
    hRoot = TiXmlHandle(pElement);

    TiXmlElement* meshNode = hRoot.FirstChild("library_geometries").FirstChild().FirstChild().Element();

    //load position array
    pElement = meshNode->FirstChild()->FirstChild()->ToElement();

    int positionCount = 0;
    pElement->QueryIntAttribute("count", &positionCount);
    std::string positionArrayText = pElement->GetText();

    std::istringstream inPosition(positionArrayText);

    std::vector<float> positionVector;
      
    std::copy(std::istream_iterator<float>(inPosition),
        std::istream_iterator<float>(),
        std::back_inserter(positionVector));

    //load normal array
    pElement = meshNode->FirstChild()->NextSibling()->FirstChild()->ToElement();

    int normalCount = 0;
    pElement->QueryIntAttribute("count", &normalCount);
    std::string normalArrayText = pElement->GetText();

    std::istringstream inNormal(normalArrayText);

    std::vector<float> normalVector;
      
    std::copy(std::istream_iterator<float>(inNormal),
        std::istream_iterator<float>(),
        std::back_inserter(normalVector));

    //load uv array
    pElement = meshNode->FirstChild()->NextSibling()->NextSibling()->FirstChild()->ToElement();

    int uvCount = 0;
    pElement->QueryIntAttribute("count", &uvCount);
    std::string uvArrayText = pElement->GetText();

    std::istringstream inUv(uvArrayText);

    std::vector<float> uvVector;
      
    std::copy(std::istream_iterator<float>(inUv),
        std::istream_iterator<float>(),
        std::back_inserter(uvVector));

    //load face array
    pElement = meshNode->FirstChild()->NextSibling()->NextSibling()->NextSibling()->NextSibling()->ToElement();
    
    int faceCount = 0;
    pElement->QueryIntAttribute("count", &faceCount);
    
    pElement = pElement->FirstChildElement("p");

    std::string faceArrayText = pElement->GetText();

    std::istringstream inFace(faceArrayText);

    std::vector<unsigned int> faceVector;
      
    std::copy(std::istream_iterator<int>(inFace),
        std::istream_iterator<int>(),
        std::back_inserter(faceVector));

    
    
    
    std::string newPath = path;
    newPath += "bin";

    std::ofstream writeFile;
    writeFile.open(newPath, std::ios::out | std::ios::binary);

    if(!writeFile.is_open())
    {
        std::cout<<"Could not create the file: "<<newPath<<std::endl;
        return false;
    }

    writeFile.write((const char*)&positionCount, sizeof(int));
    writeFile.write((const char*)positionVector.data(), positionCount*sizeof(float));
    
    writeFile.write((const char*)&normalCount, sizeof(int));
    writeFile.write((const char*)normalVector.data(), normalCount*sizeof(float));

    writeFile.write((const char*)&uvCount, sizeof(int));
    writeFile.write((const char*)uvVector.data(), uvCount*sizeof(float));

    writeFile.write((const char*)&faceCount, sizeof(int));
    writeFile.write((const char*)faceVector.data(), faceCount*3*sizeof(int));

    writeFile.close();

    return true;
}
}
}