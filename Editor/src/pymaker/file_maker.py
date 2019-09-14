import os

init_format = '''\
%s
%s

this file change the working dir to the path in the first line
and out put the logs to the path in the second line
'''

register_format = '''\

// engine
#define PE_PROJECT %s
#include "Pixel-Engine.h"

// include classes
%s

void register_classes()
{
    // register cpp objects
%s
    // add python object path
%s}
'''
include_format = "#include \"%s\""
register_class_format =  "REGISTER_CLASS(%s);"
pyobjpath_format = "ADD_PYOBJECT_PATH(\"%s\");"

def makeRegister( proj_title, proj_dir,  classes={}, pyobj_paths=[] ):
    include_str = ""
    register_str = ""
    pyobjpath_str = ""
    for i in classes.items():
        include_str += include_format%(i[1])+"\n"
        register_str += "\t"+register_class_format%(i[0])+"\n"
    for path in pyobj_paths:
        pyobjpath_str+= "\t"+pyobjpath_format%(path)+"\n"

    register_text = register_format%(proj_title, include_str, register_str, pyobjpath_str)
    file = open(os.path.join(proj_dir,"register.cpp"), 'w')
    file.write(register_text)
    file.close()

def makeInit(dst, cwd, log):
    file = open(os.path.join(dst, 'init'), 'w')
    file.write( init_format%(cwd, log) )
    file.close()

if __name__ == "__main__" and 0:
    makeRegister( "SandBox",'.',{ "Player":"src/Player.h", "Npc":"src/Npc"}, ["src"])
