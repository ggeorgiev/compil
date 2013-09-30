import os
import glob
import uuid
import sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
import fileUtils.files as files
import fileUtils.cpp as cpp

def unit(x):
    return x

def log (x):
    print(x)


def gatherFilesHelper(path):
    filesSet = set()
    filesSet |= set(glob.glob('{0}\*.h'.format(path)))
    filesSet |= set(glob.glob('{0}\*.hpp'.format(path)))
    [cpp.fixGuard(x, '', cpp.buildGuard('\\'.join(x.split('\\')[1:]))) for x in filesSet]
        
    filesSet |= set(glob.glob('{0}\*.c'.format(path)))
    filesSet |= set(glob.glob('{0}\*.cc'.format(path)))
    filesSet |= set(glob.glob('{0}\*.cpp'.format(path)))
    filesSet |= set(glob.glob('{0}\*.rc'.format(path)))
    filesSet |= set(glob.glob('{0}\*.compil'.format(path)))
    filesSet |= set(glob.glob('{0}\*.scompil'.format(path)))
    filesSet |= set(glob.glob('{0}\*.compilprj'.format(path)))
    filesSet |= set(glob.glob('{0}\*.scompilprj'.format(path)))
    

    filesSet |= set(glob.glob('{0}\*.bat'.format(path)))

    for root, dirs, files in os.walk(path):
        for d in dirs:
            filesSet |= gatherFilesHelper(os.path.join(root, d))

    return filesSet

def filterStringForGuard(string):
    return string.replace('.', '_').replace('\\', '_').replace('/', '_')

class ProjectData(object):
    def __init__(self, projectName, directory):
        self.name = projectName
        self.directory = directory
        self.jamfile='{0}\\jamfile.jam'.format(self.directory)
        self.files=[]
        self.gatherFiles()
        self.tagsMap = {'.h' : 'ClInclude',
                        '.hpp' : 'ClInclude',
                        '.c' : 'ClCompile',
                        '.cc' : 'ClCompile',
                        '.cpp' : 'ClCompile',
                        '.rc' : 'ResourceCompile',
                        '.proto' : 'None',
                        '.compil' : 'None',
                        '.scompil' : 'None',
                        '.compilprj' : 'None',
                        '.scompilprj' : 'None',
                        '.bat' : 'None',
                        '.jam': 'None'}

    def executableName(self):
        with open(self.jamfile, 'r') as j:
            jamtext = j.read()

            unitTest = jamtext.find('unit-test ')
            if (unitTest > -1):
                print(jamtext[unitTest+len('unit-test '):].split(' ')[0].strip())
                return jamtext[unitTest+len('unit-test '):].split(' ')[0].strip()
            
            gtest = jamtext.find('gtest ')
            if (gtest > -1):
                return jamtext[gtest+len('gtest '):].split(' ')[0].rstrip()+'-unit_test'
            
            parallel = jamtext.find('gtest-parallel ')
            if (parallel > -1):
                return jamtext[parallel+len('gtest-parallel '):].split(' ')[0].rstrip()+'-unit_test'
            
            exe = jamtext.find('exe ')
            if (exe > -1):
                return jamtext[exe+len('exe '):].split(' ')[0].rstrip()

            lib = jamtext.find('lib ')
            if (lib > -1):
                return 'lib'+jamtext[lib+len('lib '):].split(' ')[0].rstrip()
            
            return self.name
        
    def gatherFiles(self):
        for x in gatherFilesHelper(self.directory):
            self.files.append(x)
        self.files.sort()

    def findMissing(self, collection):
        missingCollection = []
        for x in collection:
            missing = True
            if(x[0] == '#'):
               continue
            for y in self.files:
                if x.replace('/', '\\') in y:
                    missing = False
            if missing:
                missingCollection.append(x)
        return missingCollection
            
    def buildHeaderPair(self, file):
        base, ext = os.path.splitext(file)
        header = base + '.h'
        cppfile = base + '.cpp'

        headerInclude = self.name + "/" + header
        guard = cpp.buildGuard(headerInclude)
        log("guard: " + guard)
        with open(self.directory + "\\" + header, 'w+') as h:
            h.write('#ifndef __{0}__\n'.format(guard))
            h.write('#define __{0}__\n'.format(guard))
            h.write('#pragma once\n\n')
            h.write('#endif //__{0}__'.format(guard))

        with open(self.directory + "\\" + cppfile, 'w+') as c:
            c.write('#include "{0}"'.format(headerInclude))

        return (header, cpp)

    def allFiles(self):
        return [self.jamfile] + self.files
    
    def __str__(self):
        return '{0}\n'.format(self.name)
    def __repr__(self):
        return self.__str__()
        

def makeProjectData(path, jamfile):
    projectName = os.path.basename(os.path.normpath(path))
    newProject = ProjectData(projectName, path)
    return newProject

def projectDataFromPath(path):
    subdirs=[]
    for f in os.listdir(path):
        full='{0}\\{1}'.format(path, f)
        if os.path.isdir(full):
            subdirs.append(full)
        elif f.endswith('file.jam'):
            project = makeProjectData(path, f)
            return [makeProjectData(path, f)]
    retval = []
    for x in subdirs:
        retval += projectDataFromPath(x)
    return retval

def loadTemplateVcproj(path):
    with files.force_open('{0}\\template.vcxproj.xml'.format(path), 'r') as t:
        projectText = t.read()
    return projectText

def makeFileXML(project):
    files = '  <ItemGroup>\n'
    for x in project.allFiles():
        filePath, fileExtension = os.path.splitext(x)
        files +='     <{0} Include="..\compil\{1}" />\n'.format(project.tagsMap[fileExtension], x)
    files += '  </ItemGroup>'
    return files

def writeProject(projectData, projectPath, templatePath):
    project = loadTemplateVcproj(templatePath)

    #project globals
    project = project.replace('@PROJECT_NAME@', projectData.name)
    project = project.replace('@PROJECT_GUID@', str(generateGUID(projectData.name)))
                                                                                           

    #build scripts
    runstring = os.path.dirname(projectData.jamfile)
    project = project.replace('@RUN_NAME@', '..\compil\{0}'.format(runstring))
                    
    #intermediate directories
    outDir = '\\'.join(projectData.directory.split('\\')[1:])
    project = project.replace('@OUT_PATH@', outDir)

    #executable
    executable = projectData.executableName()
    project = project.replace('@EXE_NAME@', executable)

    #source files
    project = project.replace('@CODE_FILES@',makeFileXML(projectData))

    filename = '{0}\\{1}.vcxproj'.format(projectPath, projectData.name)

    if files.smart_override(filename, project):
        print('writing {0}'.format(filename))
        writeFilters(projectData, projectPath)

def generateGUID(key):
    ''' filters require a MS GUID. To build one, we use a pre-computed UUID as a base and
then we add to it the MD5 of the code path. This makes the keys 100% deterministic and
repeatable on any system '''
    return uuid.uuid3(uuid.UUID('B76C417A-51B7-49E1-A8A8-77395F8A0D9F'), key)

def mapFilters(projectData):
    filters = {}
    for x in projectData.allFiles():
        key = '\\'.join(x.split('\\')[0:-1])
        key = key.replace(projectData.directory, '')[1:]
        if key == '':
            continue
        if key in filters:
            filters[key].append('..\compil\{0}'.format(x))
        else:
            filters[key] = ['..\compil\{0}'.format(x)]

    return filters

def writeFilters(projectData, projectPath):
    filtersDict = mapFilters(projectData)

    fileStrings = []
    existingFilters=set()

    keys = sorted(filtersDict.keys())

    for k in keys:
        folders = k.split('\\')
        currentFolder=''
        for folder in folders:
            currentFolder = os.path.join(currentFolder, folder)
            if currentFolder in existingFilters:
                continue
            existingFilters.add(currentFolder)

        includes = sorted(filtersDict[k])
        for i in includes:
            filePath, fileExtension = os.path.splitext(i)
            fileStrings.append('    <{0} Include="{1}">\n'.format(projectData.tagsMap[fileExtension], i))
            fileStrings.append('      <Filter>{0}</Filter>\n'.format(k))
            fileStrings.append('    </{0}>\n'.format(projectData.tagsMap[fileExtension]))

    filterStrings = []

    folders = sorted(existingFilters)
    for folder in folders:
        filterStrings.append('    <Filter Include="{0}">\n'.format(folder))
        filterStrings.append('      <UniqueIdentifier>{'+str(generateGUID(folder))+'}</UniqueIdentifier>\n')
        filterStrings.append('    </Filter>\n')

    filename = '{0}\\{1}.vcxproj.filters'.format(projectPath, projectData.name)
    print('writing {0}'.format(filename))
    with files.force_open(filename, 'w+') as f:
        f.truncate()
        f.write('<?xml version="1.0" encoding="utf-8"?>\n')
        f.write('<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">\n')
        f.write('  <ItemGroup>\n')
        [f.write(x) for x in filterStrings]
        f.write('  </ItemGroup>\n  <ItemGroup>\n')
        [f.write(x) for x in fileStrings]
        f.write('  </ItemGroup>\n</Project>')
    
    
if __name__ == '__main__':
    import optparse as op
    
    usage = 'build_vcproj.py [options] directory_to_scan_for_projects directory_to_write_projects_to\nType -h for a list of options'
    parser = op.OptionParser(usage)
    parser.add_option('-t', '--template', dest='template', help='directory to find the template vcxproj')
    parser.add_option('-v', '--verbose', dest='verbose', help='sets verbose mode, with more logging')

    options, args = parser.parse_args(sys.argv)
    if len(args) < 2:
        parser.error('Not enough args')
    else:
        if (not options.verbose):
            log = unit
            print ("quiet!")
        templatePath = ''
        if(options.template):
            templatePath = options.template
        else:
            templatePath = os.path.dirname(os.path.realpath(__file__))
        scanDir = args[1]
        os.chdir(os.path.dirname(scanDir))
        projects = projectDataFromPath(os.path.basename(scanDir))
        [writeProject(p, args[2], templatePath) for p in projects]
