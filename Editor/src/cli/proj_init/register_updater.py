import xml.etree.ElementTree as ET
import xml.dom.minidom as mdom
import os
import proj_updater as proj

register_format = '''\

// engine
#define PE_PROJECT %s
#include "Pixel-Engine.h"

// include classes
%s

void register_classes()
{
    // register cpp objects
\t%s

    // add python object path
\t%s
}
'''
include_format = "#include \"%s\""
register_class_format =  "REGISTER_CLASS(%s);"
pyobjpath_format = "ADD_PYOBJECT_PATH(\"%s\");"
file_name = "register.h"

def updateRegister(proj_name, working_dir = '.'):
    include_lists=[]
    cpp_register_list = []
    python_path_list = []
    #working_dir = working_dir+'/' if working_dir[-1] not in ['/', '\\'] else working_dir
    file_path = os.path.join(working_dir, file_name)

    for path, folders, files in os.walk(working_dir):
        for file in files:
            obj_path = os.path.join(path, file)
            if proj.isPathObject(obj_path):
                doc = ET.parse(obj_path)
                root = doc.getroot()
                class_tag = root.find('class')
                if class_tag.attrib['type'] == 'CPP_OBJECT':
                    include_lists.append(class_tag.text)
                    cpp_register_list.append(class_tag.attrib['name'])
                elif class_tag.attrib['type'] == 'PYTHON_OBJECT':
                    python_path_list.append(class_tag.text)
    file = open(file_path, 'w')
    file.write( register_format %(
        proj_name,
        '\n'.join( list(map(lambda path: include_format%path,include_lists))),
        '\n\t'.join(list(map(lambda path: register_class_format%path,cpp_register_list))),
        '\n\t'.join(list(map(lambda path: pyobjpath_format%path,python_path_list)))
        ) )
    file.close()
                
                
