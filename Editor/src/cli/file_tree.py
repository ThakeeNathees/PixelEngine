import os

class FileTree:
    def __init__(self, path):
        self.path  = path
        self.dirs  = []
        self.files = []
        for p in os.listdir(self.path):
            if not os.path.isdir(os.path.join(self.path, p)):
                self.files.append(p)
            else:
                self.dirs.append(FileTree( os.path.join(self.path, p) ))
        
