#include"project.hpp"

// wymaga mocnej optymalizacji, szczególnie budowanie komendy
// dostosować do c++
static bool ExecuteSystemCommand(const char* str, ...)
{
    va_list valist;
    char _command[FILENAME_MAX] = {0};
    int i = 0, j = 0;

    va_start(valist, str);
    while(str && str[i]){
        if(str[i] == '%'){
            i++;
            if(str[i] == 's'){
                char* string = (char*)va_arg(valist, char*);
                size_t string_size = strlen(string);
                int k;
                for(k = 0; k < string_size; k++){
                    _command[j] = string[k];
                    j++;
                }
            }
        }
        else{
            _command[j] = str[i];
            j++;
        }
        i++;
    }
    va_end(valist);

    std::cout<<_command<<std::endl;

    system(_command);

    return true;
}

namespace Hero { namespace Editor {

bool CreateProject()
{

    ExecuteSystemCommand("mkdir %s\\build\\release", "test");

    return true;
}

}}
