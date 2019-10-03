import os

## TODO: create list for listDir and update when needed

class Explorer:

    @staticmethod
    def listDir(path):
        items = os.listdir(path)
        dirs, files = [], []
        for item in items:
            if os.path.isdir(os.path.join(path, item)):
                dirs.append(item)
            else: files.append(item)
        return dirs + files
    
    def __init__(self, path):
        self.path = os.path.abspath(path)
        self.listdir = Explorer.listDir(self.path)

    def pathUp(self):
        self.path = os.path.abspath( os.path.join(self.path, "..") )
        self.listdir = Explorer.listDir(self.path)
        
    def pathIn(self, ind):
        self.path = os.path.join(self.path, Explorer.listDir(self.path)[ind])
        self.listdir = Explorer.listDir(self.path)

    def getItemCount(self):
        return len(self.listdir)

    def isItemDir(self, ind):
        return os.path.isdir( os.path.join( self.path, self.listdir[ind] ) )

    def getItemPath(self, ind):
        return os.path.join( self.path, self.listdir[ind] )

    def getItemName(self, ind):
        return self.listdir[ind]

    def getPath(self):
        return self.path

    def setPath(self, path):
        if os.path.isdir(path):
            self.path = os.path.abspath(path)

    def reload(self):
        self.listdir = Explorer.listDir(self.path)

    
        
        
