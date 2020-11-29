#!/usr/bin/env python3

import argparse
import sys, os
import shutil

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument(
		"--cleanall", "-c", action='store_true', help="Cleans all the generated files (Warning it includes project files).")
	args = parser.parse_args()

	if args.cleanall:
		cleanall()

## -----------------------

isatty = sys.stdout.isatty()
class Color:
	CYAN   = "\033[96m" if isatty else ""
	PURPLE = "\033[95m" if isatty else ""
	BLUE   = "\033[94m" if isatty else ""
	GREEN  = "\033[92m" if isatty else ""
	YELLOW = "\033[93m" if isatty else ""
	RED	   = "\033[91m" if isatty else ""
	END	   = "\033[0m"  if isatty else ""

REMOVE_DIRS = [
	'debug/',   '.vs/',
	'release/', '.vscode/',
	'x64/',     'bin/',
	'thirdparty/opengl/glad/bin/',
	'thirdparty/opengl/glfw/bin/',
]

REMOVE_FILES = [
	'.pdb', '.idb',
	'.ilk', '.sln',
	'.sconsign.dblite',
        'imgui.ini',
	'.vcxproj',
	'.vcxproj.filters',
	'.vcxproj.user',
]

def cleanall():
	os.system('scons -c')

	print('\nCleaning all files ...'.format())
	for _dir in REMOVE_DIRS:
		try:
			shutil.rmtree(_dir)
			print('{}Removed: {}{}'.format(Color.RED, Color.END, _dir) )
		except Exception as err:
			pass ## file not exists.
	for path, dirs, files in os.walk('.'):
		for file in files:
			for suffix in REMOVE_FILES:
				if file.endswith(suffix):
					os.remove(os.path.join(path, file))
					print('{}Removed: {}{}'.format(Color.RED, Color.END, os.path.join(path, file) ))
	print('Done cleaning targets.'.format())


if __name__ == "__main__":
	main()
