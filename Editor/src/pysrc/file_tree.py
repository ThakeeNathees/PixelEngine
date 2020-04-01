import os

class FileTree:

    ## static fileds
    object_paths = []
    scene_paths = []

    def __init__(self, path):
        self.path  = path   ## abs path 
        self.dirs  = []     ## rel paths
        self.files = []
        for p in os.listdir(self.path):
            if not os.path.isdir(os.path.join(self.path, p)):
                if p.endswith('.obj.xml'): 
                    if p not in FileTree.object_paths: FileTree.object_paths.append(
                        os.path.relpath(os.path.join(self.path, p))
                    )
                if p.endswith('.scn.xml'): 
                    if p not in FileTree.scene_paths: FileTree.scene_paths.append(
                        os.path.relpath(os.path.join(self.path, p))
                    )
                self.files.append(
                    os.path.relpath(os.path.join(self.path, p))
                )
            else:
                self.dirs.append(FileTree( os.path.join(self.path, p) ))

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

    ## special files
    def isAssetFile(self, ind):
        return os.path.basename(self.files[ind]) == "assets.xml"

    def isObjectFile(self, ind):
        return os.path.basename(self.files[ind]).endswith(".obj.xml")
    
    def isSceneFile(self, ind):
        return os.path.basename(self.files[ind]).endswith(".scn.xml")
