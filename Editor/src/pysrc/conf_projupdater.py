import os

proj_block_name = 'projects:'
proj_key = 'porj='


## include "projects:" and "end" numbers starts at 1
def _projLineRange(lines):
    for ind, line in enumerate(lines):
        if line.strip() == proj_block_name:
            proj_count = 0
            proj_name = lines[ind]
            while proj_name.strip() != 'end':
                proj_name = lines[ind+proj_count]
                proj_count += 1
            return ind,ind+proj_count
    assert(False) ## error in conf file


def _insertProj(proj_name, proj_path, lines):
    line_no = _projLineRange(lines)[1] -1
    ret = lines[:line_no]+[('\t' + proj_key +
                            '"'+proj_name+'"'+','
                            '"'+os.path.abspath(proj_path)+'"'+
                            '\n')] + lines[line_no:]
    return ret

def _getProjects(lines):
    lrange = _projLineRange(lines)
    ret = []
    for i in range(lrange[0]+1, lrange[1]-1):
        pair = lines[i].strip().split('=')[1].split(',')
        proj_name = pair[0].strip().split('"')[1]
        proj_path = pair[1].strip().split('"')[1]
        ret += [(proj_name, proj_path )]
    return ret

def _deleteProj(_proj_name, lines):
    lrange = _projLineRange(lines)
    ret = []
    for i in range(lrange[0]+1, lrange[1]-1):
        pair = lines[i].strip().split('=')[1].split(',')
        proj_name = pair[0].strip().split('"')[1]
        if proj_name == _proj_name: continue
        proj_path = pair[1].strip().split('"')[1]
        ret += [(proj_name, proj_path )]
    return ret
    

def _clearPorj(lines):
    lrange = _projLineRange(lines)
    lines[ lrange[0]+1 : lrange[1]-1 ] = []
    return lines

def getProjects(conf_file_path):
    file = open(conf_file_path, 'r')
    lines = file.readlines()
    file.close()
    return _getProjects(lines)

## search for project in path and insert
def importNewProj(proj_file_path, conf_file_path):
    if os.path.abspath(proj_file_path) in [os.path.abspath(pair[1]) for pair in getProjects(conf_file_path)]:
        return
    for file in os.listdir(proj_file_path) :
        if not os.path.isdir(file):
            if file.endswith('.peproj'):
                proj_name = file[:-len('.peproj')]
                insertNewProj(proj_name, proj_file_path, conf_file_path)

## insert new project
def insertNewProj(proj_name, proj_path, file_path):
    file = open(file_path, 'r')
    lines = file.readlines()
    file.close()

    lines = _insertProj(proj_name, proj_path, lines)
    file = open(file_path, 'w')
    file.write(''.join(lines))
    file.close()
    
## path to conf.init file
def updateProj(path):
    file = open(path, 'r')
    lines = file.readlines()
    file.close()
    projs = _getProjects(lines)
    ## TODO: check proj to be removed or not
    ## call deleteProj() if needed
    lines = _clearPorj(lines)
    for proj in projs:
        lines = _insertProj(proj[0], proj[1], lines)
    file = open(path, 'w')
    file.write( ''.join(lines) )
    file.close()

    

if __name__ == '__main__' and 1:
    ##insertNewProj("newProj", "path/to/proj", "E:\\__test\\test\\test.txt")
    ##updateProj("E:\\__test\\test\\test.txt")
    importNewProj('.','./peconfig.init')
        



