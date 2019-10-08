import os

class FileTree:
    def __init__(self, path):
        self.path  = path
        self.dirs  = []
        self.files = []
        for p in os.listdir(self.path):
            if not os.path.isdir(os.path.join(self.path, p)):
                self.files.append(os.path.join(self.path, p))
            else:
                self.dirs.append(FileTree( os.path.join(self.path, p) ))

    @staticmethod
    def getFileFormat(path):
        if "." not in path: return ""
        return path.split('.')[-1].lower()

    @staticmethod
    def makeStr(ft, tab=1, ret="" ):
        for file in ft.files:
            ret += '\t'*tab + os.path.basename(file) + '\n'
        for _ft in ft.dirs:
            ret += '\t'*tab + os.path.basename(_ft.path) + '\n'
            ret = FileTree.makeStr(_ft, tab+1, ret)
        return ret
        
    def __str__(self):
        ret = self.path+'\n'
        ret += FileTree.makeStr(self)
        return ret

    def isAssetFile(self, ind):
        return os.path.basename(self.files[ind]) == "assets.xml"