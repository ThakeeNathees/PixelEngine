import os

## the name ends with .peproj
def getProjFileName(path='.'):
    for file in os.listdir(path):
        if file.endswith(".peproj"):
            return file
    return ""

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