
def isValidName(name):
    if not name[0].isalpha(): return False
    for c in ['\\','/',':','*','?','<','>','|','"', ' ', '\n', '\t']:
        if c in name: 
            return False
    return True

def endswith(string, ends):
    return string.endswith(ends)

## for python interpriter window
def getString(obj):
    if obj.__class__ == ''.__class__ :
        return obj
    else :
        return str(obj)
