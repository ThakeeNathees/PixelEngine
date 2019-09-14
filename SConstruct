#!python
import os, subprocess

## in cmd > scons platfrom=windows generate_bindings=yes
out_path='bin/SandBox'
include_paths = ['./include']
lib_files = ["Pixel-Engine", "sfml-audio-d","sfml-graphics-d","sfml-main-d",
"sfml-network-d","sfml-system-d", "sfml-window-d"]

target = ARGUMENTS.get("target", "debug")

# platform= makes it in line with Godots scons file, keeping p for backwards compatibility
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
    for lib in lib_files:
        lib += '.windows.64'

if platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
    for lib in lib_files:
        lib += '.windows.64'

if platform == "windows":
    env.Append(CCFLAGS = ['-DWIN32', '-D_WIN32', '-D_WINDOWS', '-W3', '-GR', '-D_CRT_SECURE_NO_WARNINGS'])
    if target == "debug":
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])
    for lib in lib_files:
        lib += '.windows.64'

# , 'include', 'include/core'
env.Append(CPPPATH=include_paths)
env.Append(LIBPATH=['lib/'])
env.Append(LIBS=lib_files)


sources = ['register.cpp']
add_sources(sources, "src")
env.Program(out_path, sources)

