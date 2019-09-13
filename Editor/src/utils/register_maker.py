text_format = '''\

// engine
#define PE_PROJECT %s
#include "Pixel-Engine.h"

// classes for register
%s

void register_classes()
{
%s}
'''
include_format = "#include \"%s\""
register_format =  "REGISTER_CLASS(%s);"

def makeRegister( proj_title, classes ):
    include_str = ""
    register_str = ""
    for i in classes.items():
        include_str += include_format%(i[1])+"\n"
        register_str += "\t"+register_format%(i[0])+"\n"

    register_text = text_format%(proj_title, include_str, register_str)
    file = open("register.cpp", 'w')
    file.write(register_text)
    file.close()


if __name__ == "__main__" and False:
    makeRegister( "SandBox",{ "Player":"src/Player.h", "Npc":"src/Npc"})
