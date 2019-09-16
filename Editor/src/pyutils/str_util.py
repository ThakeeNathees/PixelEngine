import os


# return 0 if success
def is_valid_proj_name(name):
	if ' ' in name :
		print('ERROR: Project name must not contain spaces!')
		return 1
	if not name[0].isalpha():
		print('ERROR: First character of the project name must be alpahbatic')
		return 2
	return 0
