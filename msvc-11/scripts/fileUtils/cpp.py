import os
import re
import fileUtils.files as files

def buildGuard(file):
    return '__{0}__'.format(file.replace('\\', '_').replace('/', '_').replace('.', '_').replace('-', '_').upper())

def isHeader(file):
    return file.endswith('.h') or file.endswith('.hpp')

pragmaSearch = re.compile(r'^\s*#ifndef .*?\n\s*#define .*?\n(\s*(// no )?#pragma once\n\s*)?([\s\S]*?)(\s*#endif(\n| //.*?)?)$')

def fixGuard(file, root, guardString):
    filepath = os.path.join(root, file)
    data = ''
    with open(filepath, mode='r') as f:
        data = f.read()

    s = pragmaSearch.split(data)

    if len(s) < 4:
        return

    if (s[2] is not None) and ("// no " in s[2]):
        return

    newData = "#ifndef " + guardString +"\n#define " + guardString + "\n#pragma once\n\n" + s[3] + "\n\n#endif // " + guardString
    if (newData == data):
        return
    
    with files.force_open(filepath, mode='w') as f:
        f.write(newData)
