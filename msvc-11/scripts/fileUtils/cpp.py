import os
import re
import fileUtils.files as files

def buildGuard(file):
    return '__{0}__'.format(file.replace('\\', '_').replace('/', '_').replace('.', '_').replace('-', '_').replace('+', 'P').upper())

def isHeader(file):
    return file.endswith('.h') or file.endswith('.hpp')

pragmaSearch = re.compile(r'^([\s\S]*)#ifndef .*?\n\s*#define .*?\n(\s*(// no )?#pragma once\n\s*)?([\s\S]*?)(\s*#endif(\n| //.*?)?)$')

def fixGuard(file, root, guardString):
    filepath = os.path.join(root, file)
    data = ''
    with open(filepath, mode='r') as f:
        data = f.read()

    s = pragmaSearch.split(data)

    if len(s) < 4:
        return

    if (s[3] is not None) and ("// no " in s[3]):
        return

    newData = s[1] + "#ifndef " + guardString +"\n#define " + guardString + "\n#pragma once\n\n" + s[4] + "\n\n#endif // " + guardString
    if (newData == data):
        return
    
    with files.force_open(filepath, mode='w') as f:
        f.write(newData)
