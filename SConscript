Import('env')
import os
	
env.PROJECT_NAME = "PixelEngine"

def target_path(name, include_bin=True):
	## run target path should be relative to bin
	if include_bin: return os.path.join('bin/', env['TARGET_ARCH'], name)
	else: return os.path.join(env['TARGET_ARCH'], name)
	
## ide debug run target
env.RUN_TARGET = target_path('tests/opengl', False)

## include directories
env.Append(CPPPATH=[
	#Dir('#include/'),
	Dir('#thirdparty/glad/include/'),
	Dir('#thirdparty/glfw/include/'),
])

## core sources
env.SOURCES = [
	'core/main.c',
]

## test sources
env.TESTS = {
	#"sandbox" : [ Glob("tests/sandbox/*.c"), ],
	#"unit_tests" : [ Glob("tests/unit_tests/*.c"), ],
	"opengl" : [ Glob('tests/opengl/*.c'), ],
}

## link libs
if env['platform'] == 'windows':
	env.Append(LIBS=['gdi32.lib', 'shell32.lib'])
elif env['platform'] == 'linux':
	env.Append(LIBS=['GL'])
elif env['platform'] == 'osx':
	env.Append(LIBS=['GL'])
	
## only for ide
env.ALL_SOURCES = []
SConscript('thirdparty/SConscript')
	
## compile the lib.
dll_env = env.Clone()
dll = dll_env .SharedLibrary(
	target = target_path('shared/' + env.PROJECT_NAME),
	source = env.SOURCES)
lib = env.Library(
	target = target_path('static/' + env.PROJECT_NAME),
	source = env.SOURCES)

env.Append(LIBS=[dll[1]])

## tests
for test in env.TESTS:
	env.Program(
	target = target_path('tests/' + test),
	source = env.TESTS[test])
	
## add ide sources
for test in env.TESTS:
	env.ALL_SOURCES += env.TESTS[test]
env.ALL_SOURCES += env.SOURCES
