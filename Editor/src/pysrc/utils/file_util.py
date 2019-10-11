import os

## the name ends with .peproj
def getProjFileName(path='.'):
    for file in os.listdir(path):
        if file.endswith(".peproj"):
            return file
    return ""

def getFileFormat(path):
        if "." not in path: return ""
        return path.split('.')[-1].lower()

## return paths of python files to update sys.path
import xml.etree.ElementTree as ET
def getPyPaths(working_dir='.', proj_file_name=""):
    if proj_file_name == "":
        for file in os.listdir(working_dir):
            if file.endswith(".peproj"):
                proj_file_name = file
                break
    doc = ET.parse(os.path.join(working_dir, proj_file_name))
    root = doc.getroot()
    pypaths = root.find('pypaths')
    if pypaths is None : return []
    ret = []
    for pypath in pypaths:
        ret.append(pypath.text)
    return ret
        
    

## return true if path ends with .py, .h, .hpp else false
def isPathScript(path):
    if (not os.path.exists(path)) : return False
    if (os.path.isdir(path)): return False
    for extention in ['.py', '.h', '.hpp']:
        if path.endswith(extention): return True
    return False


import ast, _ast
def getClasses(module_path):
    if not os.path.exists(module_path) : return []
    if not module_path.endswith(".py") : return []
    with open(module_path) as mf:
        tree = ast.parse(mf.read())
    module_classes = [_ for _ in tree.body if isinstance(_, _ast.ClassDef)]
    module_classes = [(c.name, [_.name for _ in c.body if isinstance(_, _ast.FunctionDef)]) for c in module_classes]
    return [ cls[0] for cls in module_classes]

def getPyFileName(path):
    name = os.path.basename(path).split(".")
    if len(name) < 2: return "<UNKNOWN>"
    if name[1] != "py" : return "<UNKNOWN>"
    return name[0]

def relPath(path):
    return os.path.relpath(path)

## convert "C:/dev/proj/src/pyobj1.py" -> "src/"
def relPyObjDirPath(py_obj_path):
    return os.path.dirname( os.path.relpath(py_obj_path) )

## ========================================================================================= pyfile create
default_template_py = '''\
import pixel_engine as pe

## called when the object enters a new scene
def sceneEntered(self, scene):
    pass

## called every frame. 'dt' is the elapsed time since the previous frame
def process(self, dt):
    pass
'''

default_template_cpp = '''\
#pragma once

#include "Pixel-Engine.h"

class %s : public pe::Object
{
public:
	// called when the object enters a new scene
	inline void sceneEntered(pe::Scene* scene) override {
	}

	// called every frame. 'dt' is the elapsed time since the previous frame
	inline void process(double dt) override {
	}

};
'''

no_comment_template_py = '''\
import pixel_engine as pe

def sceneEntered(self, scene):
    pass

def process(self, dt):
    pass
'''
no_comment_template_cpp = '''\
#pragma once

#include "Pixel-Engine.h"

class %s : public pe::Object
{
public:
	inline void sceneEntered(pe::Scene* scene) override {
	}

	inline void process(double dt) override {
	}

};
'''

empty_template_py = '''\
import pixel_engine as pe
'''

empty_template_cpp = '''\
#pragma once

#include "Pixel-Engine.h"
'''

## script type == 0:python, 1:cpp
## template == 0:default, 1:no_comment, 2:empty
def createScript(dir_path, file_name, script_type =0, template=0): 
    file_path = os.path.join(dir_path, file_name) + ('.py' if script_type == 0 else '.h')
    if os.path.exists(file_path) :
        print(file_path, 'already exist')
        return ""
    file = open( file_path, 'w' )
    if template == 0: 
        if script_type == 0: file.write(default_template_py)
        else : file.write(default_template_cpp%file_name)
    elif template == 1: 
        if script_type == 0: file.write(no_comment_template_py)
        else : file.write(no_comment_template_cpp%file_name)
    else : 
        if script_type == 0: file.write(empty_template_py)
        else: file.write(empty_template_cpp)
    file.close()
    return  os.path.relpath(file_path)

## =========================================================================================
