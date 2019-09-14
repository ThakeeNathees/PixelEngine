import os

text_files = [".c",".cpp",".h", ".hpp", ".txt", ".ini" ];
image_files = [ ".jpg",".png",".jpeg" ];
binary_files = [".exe", ".lib", ".dll", ]

def isPathText(path):
	for text_format in text_files:
		if path.endswith(text_format):
			return True
	return False

def isPathImage(path):
	for img_format in image_files:
		if path.endswith(img_format):
			return True
	return False

def isPathBinary(path):
	for bin_format in binary_files:
		if path.endswith(bin_format):
			return True
	return False