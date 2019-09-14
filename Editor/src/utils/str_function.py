
def str_split(string, delimeter=" "):
	return string.split(delimeter)

def simple_hash(string):
	shift = 0; hash = 0
	for char in string:
		hash += ord(char) << shift * 8
		shift += 1
	return hash

def reverse_hash(hash):
	assert(type(hash) is int)
	ret = ""
	while hash > 0:
		ret += chr(hash & 0xff)
		hash >>= 8
	return ret

def to_hex_string(number, upper=True):
	assert(type(number) is int)
	ret = hex(number)[2:]
	if upper: ret = ret.upper()
	return ret

