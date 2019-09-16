import os, shutil


def _cleanPycache(dst):
    for path, dirs, files in os.walk(dst):
        for d in dirs:
            if d == '__pycache__':
                shutil.rmtree( os.path.join(path, d) )
                print('removed dir:',os.path.join(path, d))
def _cleanObj(dst):
    for path, dirs, files in os.walk(dst):
        for f in files:
            if f.endswith('.obj'):
                os.remove( os.path.join(path, f) )
                print('removed dir:',os.path.join(path, f))

def clean(dst='.'):
	_cleanPycache(dst)
	_cleanObj(dst)

if __name__ == "__main__" and 0:
    _cleanPycache('.')
    _cleanObj('.')
    
