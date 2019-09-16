import os,shutil

import proj_updater
import assets_loader
import file_maker

## src
pe_sln_path     = 'C:/dev/Pixel-Engine'
pe_api_path     = 'C:/dev/Pixel-Engine/Pixel-Engine/src/api/'
sfml_path       = 'C:/dev/Pixel-Engine/vender/SFML-2.5.1/include/'
sfml_lib_path   = 'C:/dev/Pixel-Engine/vender/SFML-2.5.1/lib/'
sfml_dll_path   = 'C:/dev/Pixel-Engine/vender/SFML-2.5.1/bin/'
pe_debug_out    = 'C:/dev/Pixel-Engine/bin/Debug-x64/Pixel-Engine/'
pe_release_out  = 'C:/dev/Pixel-Engine/bin/Release-x64/Pixel-Engine/'
#res_path        = "C:/dev/Pixel-Engine/Editor/res/"


def makeDirs(proj_dir):
    os.makedirs(proj_dir)
    os.makedirs(os.path.join(proj_dir, 'include'))
    os.makedirs(os.path.join(proj_dir, 'lib/x64-debug'))
    os.makedirs(os.path.join(proj_dir, 'lib/x64-release'))
    os.makedirs(os.path.join(proj_dir, 'bin/x64-debug'))
    os.makedirs(os.path.join(proj_dir, 'bin/x64-release'))
    os.makedirs(os.path.join(proj_dir, 'src'))
    os.makedirs(os.path.join(proj_dir, 'res'))
    print('project dirs created')

def copyInclude(src, dst):
    copyTree(src, dst)
    for path, dirs, files in os.walk(dst):
        for file in files:
            if file.endswith('.cpp'):
                os.remove( os.path.join(path, file) )
                print("removed file: %s"%file)

def clearLib(dst):
    for path, dirs, files in os.walk(dst):
        for file in files:
            if file.endswith('.pdb'):
                os.remove( os.path.join(path, file) )
                print("removed file: %s"%file)

def copyTree(src, dst, symlinks=False, ignore=None):
    try:
        for item in os.listdir(src):
            s = os.path.join(src, item)
            d = os.path.join(dst, item)
            if os.path.isdir(s):
                shutil.copytree(s, d, symlinks, ignore)
                print("copied dir: %s"%s)
            else:
                shutil.copy2(s, d)
                print("copied file: %s"%s)
    except FileExistsError:
        print("Error : directory already exists!")

def copySfmlLibs(sfml_lib_path, proj_dir):
    for lib in os.listdir(sfml_lib_path):
        if lib.split('.')[0][-1] == 'd':
            shutil.copy(os.path.join(sfml_lib_path, lib),
                        os.path.join(proj_dir, 'lib/x64-debug'))
            print("copied file:",os.path.join(sfml_lib_path, lib))
        else:
            shutil.copy(os.path.join(sfml_lib_path, lib),
                        os.path.join(proj_dir, 'lib/x64-release'))
            print("copied file:",os.path.join(sfml_lib_path, lib))
    clearLib(os.path.join(proj_dir, 'lib'))

def copySfmlDlls(sfml_dll_path, proj_dir):
    for dll in os.listdir(sfml_dll_path):
        if dll == 'openal32.dll':
            shutil.copy(os.path.join(sfml_dll_path, dll),
                        os.path.join(proj_dir, 'bin/x64-debug'))
            shutil.copy(os.path.join(sfml_dll_path, dll),
                        os.path.join(proj_dir, 'bin/x64-release'))
            print("copied file:",os.path.join(sfml_dll_path, dll))
            continue
        if dll.endswith('-d-2.dll'):
            shutil.copy(os.path.join(sfml_dll_path, dll),
                        os.path.join(proj_dir, 'bin/x64-debug'))
            print("copied file:",os.path.join(sfml_dll_path, dll))
        else:
            shutil.copy(os.path.join(sfml_dll_path, dll),
                        os.path.join(proj_dir, 'bin/x64-release'))
            print("copied file:",os.path.join(sfml_dll_path, dll))
            
def copyPEOut(pe_debug_out, proj_dir, spec='debug'):
    assert( spec in ['debug', 'release'] )
    shutil.copy(os.path.join(pe_debug_out, 'Pixel-Engine.dll'),
                        os.path.join(proj_dir, 'bin/x64-%s'%spec))
    print("copied file:",os.path.join(pe_debug_out, 'Pixel-Engine.dll'))
    shutil.copy(os.path.join(pe_debug_out, 'Pixel-Engine.lib'),
                        os.path.join(proj_dir, 'lib/x64-%s'%spec))
    print("copied file:",os.path.join(pe_debug_out, 'Pixel-Engine.lib'))
    

def copyLicenseScons(pe_sln_path, proj_dir):
    shutil.copy(os.path.join(pe_sln_path, 'SConstruct'), proj_dir)
    shutil.copy(os.path.join(pe_sln_path, 'LICENSE'),
                os.path.join(proj_dir, 'include'))

def copyResDir(res_path, dst):
    copyTree(res_path, dst)
    
#####################################################

def init(__proj_name, __dst_path=None):
    proj_name = __proj_name
    dst_path = __dst_path if __dst_path else '.'
    proj_dir = os.path.join(dst_path, proj_name)
    try:
        makeDirs(proj_dir)
    except FileExistsError:
        print('ERROR: file already exists, initialization terminate!')
        return
    copyInclude(pe_api_path, os.path.join(proj_dir, 'include'))
    copyInclude(sfml_path, os.path.join(proj_dir, 'include'))
    copySfmlLibs(sfml_lib_path, proj_dir)
    copySfmlDlls(sfml_dll_path, proj_dir)
    copyPEOut(pe_debug_out, proj_dir, 'debug')
    copyPEOut(pe_release_out, proj_dir, 'release')
    
    #copyResDir(res_path, os.path.join(proj_dir, 'res'))
    copyLicenseScons(pe_sln_path, proj_dir)

    assets_loader.loadAssets(proj_dir)
    proj_updater.updateProj(proj_name, proj_dir)
    file_maker.makeRegister(proj_name, proj_dir)
    file_maker.makeInit( os.path.join( proj_dir, 'bin/x64-debug'), "debug", '../../', 'bin/x64-debug/log.txt' )
    file_maker.makeInit( os.path.join( proj_dir, 'bin/x64-release'), "release", '../../', 'bin/x64-release/log.txt' )

    
    
    
    
    










