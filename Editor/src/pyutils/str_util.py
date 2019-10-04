
def isValidName(name):
    if not name[0].isalpha(): return False
    for c in ['\\','/',':','*','?','<','>','|','"', ' ', '\n', '\t']:
        if c in name: 
            return False
    return True

def endswith(string, ends):
    return string.endswith(ends)