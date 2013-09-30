import os
import stat

def force_open(name, mode='r', buffering=-1, encoding=None, errors=None, newline=None, closedfd=True):
    if not 'r' in mode:
        clear_readonly(name)
    return open(name, mode, buffering, encoding, errors, newline, closedfd)

def clear_readonly(name):
    try:
        attributes = os.stat(name)
        if (not attributes.st_mode & stat.S_IWRITE):
            os.chmod(name, stat.S_IWRITE)
    except IOError:
        pass

def matching_unit(f1):
    return True

def iterate_over_files(root, function=lambda s, d: os.path.join(d, s), condition=matching_unit, subpath=''):
    '''
iterates over files in root, and applies function to them if they match condition.
Subpath is used for recursion, you shouldn't need to set it.
'''
    for d in os.listdir(os.path.join(root, subpath)):
        if os.path.isfile(os.path.join(root, subpath, d)):
            if condition(d):
                yield function(os.path.join(subpath, d), root)
        else:
            yield from iterate_over_files(root, function, condition, subpath=os.path.join(subpath, d))

def smart_override(name, data):
    oldData = ''
    try:
        with open(name, 'r') as f:
            oldData = f.read()
    except IOError:
        pass

    if (oldData == data):
        #print('No changes found in {0}, skipping'.format(name))
        return False

    print('A change was detected in {0}, copying'.format(name))

    with force_open(name, 'w+') as f:
        f.truncate()
        f.writelines(data)
    return True

def smart_copy(source, destination):
    with open(source, 'r') as f:
        smart_override(destination, f.read())

def findFilesInDirectory(directory, extension=''):
    return ['{0}/{1}'.format(directory, x) for x in os.listdir(directory) if x.endswith(extension)]

if __name__ == '__main__':
    #put test code here!
    pass
