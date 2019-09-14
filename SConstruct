#!python
import os, subprocess

## in cmd > scons conf=release
include_paths = ['./include']
lib_files_debug = ["Pixel-Engine", "sfml-audio-d","sfml-graphics-d","sfml-main-d",
"sfml-network-d","sfml-system-d", "sfml-window-d"]

lib_files_release = ["Pixel-Engine", "sfml-audio","sfml-graphics","sfml-main",
"sfml-network","sfml-system", "sfml-window"]

proj_name = ARGUMENTS.get("proj", "SandBox")
conf = ARGUMENTS.get("conf", "debug")

lib_files = lib_files_debug
lib_path = 'lib/x64-debug/'
out_path='bin/x64-debug/%s'%proj_name
if conf == "release":
    lib_files = lib_files_release
    lib_path = 'lib/x64-release/'
    out_path='bin/x64-release/%s'%proj_name


# platform
platform = ARGUMENTS.get("p", "windows")
platform = ARGUMENTS.get("platform", platform)

# This makes sure to keep the session environment variables on windows, 
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()
if platform == "windows":
    env = Environment(ENV = os.environ)

if ARGUMENTS.get("use_llvm", "no") == "yes":
    env["CXX"] = "clang++"

def add_sources(sources, directory):
    for file in os.listdir(directory):
        if file.endswith('.cpp'):
            sources.append(directory + '/' + file)

if platform == "osx":
    env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64'])
    env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    for lib in lib_files_debug:
        lib += '.windows.64'

if platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
    for lib in lib_files_debug:
        lib += '.windows.64'

if platform == "windows":
    env.Append(CCFLAGS = ['-DWIN32', '-D_WIN32', '-D_WINDOWS', '-W3', '-GR', '-D_CRT_SECURE_NO_WARNINGS'])
    if conf == "debug":
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])
    for lib in lib_files_debug:
        lib += '.windows.64'


env.Append(CPPPATH=include_paths)
env.Append(LIBPATH=[lib_path])
env.Append(LIBS=lib_files)


sources = ['register.cpp']
add_sources(sources, "src")
env.Program(out_path, sources)

