#!python
import os, subprocess, sys

class Target:
	SHARED_LIB = 0
	LIBRARY    = 1
	EXECUTABLE = 2

###### USER DATA #############################################################################
def USER_DATA(env):
	env.PROJECT_NAME = "PixelEngine"
	env.BUILD = Target.EXECUTABLE
	
	env.SOURCES  = [ 
		Glob("./main/*.cpp") 
	]
	env.SCONSCRIPTS = [
		'thirdparty/SConstruct',
		'os/SConstruct',
	]

	if env['platform'] == 'windows':
		env.Append(LIBS=[
		'opengl32.lib', 
		'kernel32.lib', 'user32.lib', 'gdi32.lib', 'shell32.lib',
		])
	elif env['platform'] == 'linux':
		env.Append(LIBS=['GL'])
	elif env['platform'] == 'osx':
		env.Append(LIBS=['GL'])


#################################################################################################

## Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

opts = Variables([], ARGUMENTS)
## Define our options
opts.Add(EnumVariable('platform', "Compilation platform", '', ['', 'windows', 'linux', 'osx']))
opts.Add(EnumVariable('target', "Compilation target", 'debug', ['debug', 'release']))
opts.Add(EnumVariable('bits', 'output program bits', '64', ['32', '64']))
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", False))

opts.Add(BoolVariable('vsproj', "make a visual studio project", False))
opts.Add(PathVariable('target_path', 'The path to the output library.', 'bin/', PathVariable.PathAccept))
opts.Add(BoolVariable('build_verbose', "use verbose build command", False))

## Updates the environment with the option variables.
opts.Update(env)

if env['platform'] == '':
	if sys.platform == 'win32':
		env['platform'] = 'windows'
	elif sys.platform in ('linux', 'linux2'):
		env['platform'] = 'linux'
	elif sys.platform == 'darwin':
		env['platform'] = 'osx'
	else:
		print("platform(%s) not supported." % sys.platform)
		quit()

## Process some arguments
if env['use_llvm']:
	env['CC'] = 'clang'
	env['CXX'] = 'clang++'

## For the reference:
## - CCFLAGS are compilation flags shared between C and C++
## - CFLAGS are for C-specific compilation flags
## - CXXFLAGS are for C++-specific compilation flags
## - CPPFLAGS are for pre-processor flags
## - CPPDEFINES are for pre-processor defines
## - LINKFLAGS are for linking flags

## Check our platform specifics
if env['platform'] == "osx":
	if env['target'] == 'debug':
		env.Append(CCFLAGS=['-g', '-O2', '-arch', 'x86_64'])
		env.Append(LINKFLAGS=['-arch', 'x86_64'])
	else:
		env.Append(CCFLAGS=['-g', '-O3', '-arch', 'x86_64'])
		env.Append(LINKFLAGS=['-arch', 'x86_64'])

elif env['platform'] == 'linux':
	env.Append(LIBS=['GL', 'GLU', 'dl', 'X11', 'pthread']) 
	if env['target'] == 'debug':
		env.Append(CCFLAGS=['-fPIC', '-g3', '-Og'])
		env.Append(CXXFLAGS=['-std=c++17'])
	else:
		env.Append(CCFLAGS=['-fPIC', '-g', '-O3'])
		env.Append(CXXFLAGS=['-std=c++17'])

elif env['platform'] == "windows":
	## This makes sure to keep the session environment variables on windows,
	## that way you can run scons in a vs 2017 prompt and it will find all the required tools
	env.Append(ENV=os.environ)

	env.Append(CPPDEFINES=['WIN32', '_WIN32', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS'])
	env.Append(CCFLAGS=['-W3', '-GR'])
	env.Append(LINKFLAGS='/SUBSYSTEM:CONSOLE')
	env.Append(LIBS=[])

	if env['target'] == 'debug':
		env.Append(CPPDEFINES=['_DEBUG'])
		env.Append(CCFLAGS=['/EHsc', '/MDd', '/ZI'])
		env.Append(LINKFLAGS=['/DEBUG'])
	else:
		env.Append(CPPDEFINES=['NDEBUG'])
		env.Append(CCFLAGS=['/O2', '/EHsc', '/MD'])

## debug macro for all platforms
if env['target'] == 'debug':
    env.Append(CPPDEFINES=['DEBUG_BUILD'])
else:
    env.Append(CPPDEFINES=['RELEASE_BUILD'])

## --------------------------------------------------------------------------------

## no_verbose function is from : https://github.com/godotengine/godot/blob/master/methods.py
def no_verbose(sys, env):
	colors = {}
	# Colors are disabled in non-TTY environments such as pipes. This means
	# that if output is redirected to a file, it will not contain color codes
	if sys.stdout.isatty():
		colors["cyan"] = "\033[96m"
		colors["purple"] = "\033[95m"
		colors["blue"] = "\033[94m"
		colors["green"] = "\033[92m"
		colors["yellow"] = "\033[93m"
		colors["red"] = "\033[91m"
		colors["end"] = "\033[0m"
	else:
		colors["cyan"] = ""
		colors["purple"] = ""
		colors["blue"] = ""
		colors["green"] = ""
		colors["yellow"] = ""
		colors["red"] = ""
		colors["end"] = ""
	compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
		colors["blue"], colors["purple"], colors["yellow"], colors["end"]
	)
	java_compile_source_message = "{}Compiling {}==> {}$SOURCE{}".format(
		colors["blue"], colors["purple"], colors["yellow"], colors["end"]
	)
	compile_shared_source_message = "{}Compiling shared {}==> {}$SOURCE{}".format(
		colors["blue"], colors["purple"], colors["yellow"], colors["end"]
	)
	link_program_message = "{}Linking Program        {}==> {}$TARGET{}".format(
		colors["red"], colors["purple"], colors["yellow"], colors["end"]
	)
	link_library_message = "{}Linking Static Library {}==> {}$TARGET{}".format(
		colors["red"], colors["purple"], colors["yellow"], colors["end"]
	)
	ranlib_library_message = "{}Ranlib Library         {}==> {}$TARGET{}".format(
		colors["red"], colors["purple"], colors["yellow"], colors["end"]
	)
	link_shared_library_message = "{}Linking Shared Library {}==> {}$TARGET{}".format(
		colors["red"], colors["purple"], colors["yellow"], colors["end"]
	)
	java_library_message = "{}Creating Java Archive  {}==> {}$TARGET{}".format(
		colors["red"], colors["purple"], colors["yellow"], colors["end"]
	)
	env.Append(CXXCOMSTR=[compile_source_message])
	env.Append(CCCOMSTR=[compile_source_message])
	env.Append(SHCCCOMSTR=[compile_shared_source_message])
	env.Append(SHCXXCOMSTR=[compile_shared_source_message])
	env.Append(ARCOMSTR=[link_library_message])
	env.Append(RANLIBCOMSTR=[ranlib_library_message])
	env.Append(SHLINKCOMSTR=[link_shared_library_message])
	env.Append(LINKCOMSTR=[link_program_message])
	env.Append(JARCOMSTR=[java_library_message])
	env.Append(JAVACCOMSTR=[java_compile_source_message])
if not env['build_verbose']:
	no_verbose(sys, env)

## update user data
USER_DATA(env)

Export('env')
for script in env.SCONSCRIPTS:
	SConscript(script)

build_command = None
if   env.BUILD == Target.EXECUTABLE:   build_command = env.Program
elif env.BUILD == Target.SHARED_LIB: build_command = env.SharedLibrary
elif env.BUILD == Target.LIBRARY:    build_command = env.Library

target = build_command(
	target = os.path.join(env['target_path'], env.PROJECT_NAME),
	source = env.SOURCES)

## --------------------------------------------------------------------------------

## visual studio targets
def get_vsproj_context():
	vsproj_targets = []
	variants = [] ## ["debug|Win32", "debug|x64", "release|Win32", "release|x64"]
	for target in 'debug', 'release':
		for bits in '32', '64':
			vsproj_targets.append(
				os.path.join(env['target_path'], env.PROJECT_NAME + '.exe'))
			variants.append(
				target+'|'+('Win32' if bits=='32' else 'x64'))
	return vsproj_targets, variants

def msvs_collect_header():

	def recursive_collect(dir):
		ret = []
		for file in os.listdir(dir):
			file = os.path.join(dir, file)
			if os.path.isfile(file):
				if (file.endswith('.h') or file.endswith('.hpp')):
					ret.append('$(ProjectDir)' + os.path.relpath(file))
			elif os.path.isdir(file):
				ret += recursive_collect(file)
		return ret

	ret = []
	for dir in env['CPPPATH']:
		ret += recursive_collect(str(dir))
	return ret

def msvc_collect_sources():
	ret = []
	for src in env.SOURCES:
		if (str(src).endswith('.c')  or str(src).endswith('.cpp') or 
			str(src).endswith('.cc') or str(src).endswith('.cxx')):
			ret.append(str(src))
		else: ## Glob
			for _src in src:
				assert(str(_src).endswith('.c')  or str(_src).endswith('.cpp') or 
					   str(_src).endswith('.cc') or str(_src).endswith('.cxx'))
				ret.append(str(_src))
	return ret

def msvc_build_commandline(commands):
	common_build_prefix = [
		'cmd /V /C set "bits=64"',
		'(if "$(PlatformTarget)"=="x86" (set "bits=32"))',
	]
	return " ^& ".join(common_build_prefix + [commands])


if env['vsproj']:
	env["MSVSBUILDCOM"] = msvc_build_commandline(
		"scons --directory=\"$(ProjectDir.TrimEnd('\\'))\" platform=windows target=$(Configuration) bits=!bits!"
	)
	env["MSVSREBUILDCOM"] = msvc_build_commandline(
		"scons --directory=\"$(ProjectDir.TrimEnd('\\'))\" platform=windows target=$(Configuration) bits=!bits! vsproj=yes"
	)
	env["MSVSCLEANCOM"] = msvc_build_commandline(
		"scons --directory=\"$(ProjectDir.TrimEnd('\\'))\" --clean platform=windows bits=!bits! target=$(Configuration)"
	)
	targets, variants = get_vsproj_context()
	env.MSVSProject(target = env.PROJECT_NAME + env['MSVSPROJECTSUFFIX'],
		srcs = msvc_collect_sources(),
		incs = msvs_collect_header(),
		variant = variants,
		runfile = targets,
		buildtarget = targets,
	)


## Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))