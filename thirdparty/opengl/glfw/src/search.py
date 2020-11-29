import re, os, sys

## help : > python search.py regex [path="."] [output='result.txt']
## usage: > python search.py "func .*?\(\)"
## override skip_search() for ignore file/dirs

VALID_FORMAT = ['.h', '.cpp']

def skip_search(_dir):
    if os.path.isdir(_dir):
        return False
    for f in VALID_FORMAT:
        if _dir.endswith(f):
            return False
    return True


def search(regex, path, out):
    assert(os.path.isdir(path))
    for _dir in map(lambda _dir: os.path.join(path, _dir), os.listdir(path)):
        if skip_search(_dir):
                continue
        if (os.path.isdir(_dir)):
            search(regex, _dir, out)
        elif os.path.isfile(_dir):
            if os.path.abspath(_dir) in (__file__, os.path.abspath(out)) :
                continue
            print(f'searching : {_dir}')
            with open(out, 'a', encoding='utf8') as o:
                try:
                    with open(_dir, 'r', encoding='utf8') as f:
                        for line_i, line in enumerate(f, 1):
                            if re.findall(regex, line):
                                o.write(f'{_dir} : {line_i}:\n\t{line}\n')
                except Exception as err:
                    print(f'\tError: {err}\n\t\t{_dir}')


if __name__ == '__main__':
    search_str, path, out = (sys.argv[1:] + ['', '', ''])[:3]
    if path == '': path = '.'
    if out == '': out = 'result.log'
    with open(out, 'w', encoding='utf8'):
        pass # clear last results
    if search_str[0] == '"' and search_str[-1] == '"':
        search_str = search_str[1:-1]
    if search_str == '-h':
        print('''\
help : > python search.py regex [path='.'] [output='result.log']
usage: > python search.py func .*?\(\)
override skip_search() for ignore file/dirs'''
        )
        exit(0)
    search(search_str, path, out)
    print('DONE-SEARCHING')
