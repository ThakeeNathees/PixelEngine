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


