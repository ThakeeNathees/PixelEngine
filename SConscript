Import('env')
import os
	
env.PROJECT_NAME = "PixelEngine"

def target_path(name):
	return os.path.join('bin/', name)
	
## ide debug run target
env.RUN_TARGET = target_path('tests/opengl')

## include directories
env.Append(CPPPATH=[
	#Dir('#include/'),
	Dir('#thirdparty/glad/include/'),
	Dir('#thirdparty/glfw/include/'),
])

## lib sources
env.SOURCES = [
	'src/main.c',
]

## test sources
env.TESTS = {
	#"sandbox" : [ Glob("tests/sandbox/*.c"), ],
	#"unit_tests" : [ Glob("tests/unit_tests/*.c"), ],
	"opengl" : [ Glob('tests/opengl/*.c'), ],
}

## link libs
if env['platform'] == 'windows':
	env.Append(LIBS=[
		'opengl32.lib', 'gdi32.lib', 'shell32.lib', 'User32.lib',
	])
elif env['platform'] == 'linux':
	env.Append(LIBS=['GL', 'X11', 'pthread', 'Xrandr', 'Xi'])
elif env['platform'] == 'osx':
	env.Append(LIBS=['GL'])
	
## only for ide
env.ALL_SOURCES = []
SConscript('thirdparty/SConscript')

## compile the lib. TODO:
if False:
	env.Append(CPPDEFINES=['TARGET_SHARED_LIB'])
	dll = env.SharedLibrary(
		target = target_path('shared/' + env.PROJECT_NAME),
		source = env.SOURCES)
	env.Append(LIBS=[dll[1]]) ## TODO: add lib name to env
else:
	lib = env.Library(
		target = target_path('static/' + env.PROJECT_NAME),
		source = env.SOURCES)
	env.Prepend(LIBS=[lib])


## tests
for test in env.TESTS:
	env.Program(
	target = target_path('tests/' + test),
	source = env.TESTS[test])
	
## add ide sources
for test in env.TESTS:
	env.ALL_SOURCES += env.TESTS[test]
env.ALL_SOURCES += env.SOURCES
