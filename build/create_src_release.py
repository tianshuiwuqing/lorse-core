#!/usr/bin/env python

#===========================================================================
#
# Create an LROSE source release
#
#===========================================================================

from __future__ import print_function
import os
import sys
import shutil
import subprocess
from optparse import OptionParser
import time
from datetime import datetime
from datetime import date
from datetime import timedelta
import glob

def main():

    # globals

    global thisScriptName
    thisScriptName = os.path.basename(__file__)

    global options
    global releaseDir
    global tmpDir
    global coreDir
    global codebaseDir
    global versionStr
    global argsStr
    global releaseName
    global tarName
    global tarDir
    global debugStr
    global logPath
    global logFp

    # parse the command line

    usage = "usage: %prog [options]"
    homeDir = os.environ['HOME']
    releaseDirDefault = os.path.join(homeDir, 'releases')
    logDirDefault = '/tmp/create_src_release/logs'
    parser = OptionParser(usage)
    parser.add_option('--debug',
                      dest='debug', default=True,
                      action="store_true",
                      help='Set debugging on')
    parser.add_option('--verbose',
                      dest='verbose', default=False,
                      action="store_true",
                      help='Set verbose debugging on')
    parser.add_option('--osx',
                      dest='osx', default=False,
                      action="store_true",
                      help='Configure for MAC OSX')
    parser.add_option('--package',
                      dest='package', default='lrose-core',
                      help='Package name. Options are: ' + \
                      'lrose-core (default), lrose-blaze, lrose-cyclone, lrose-radx, lrose-cidd')
    parser.add_option('--releaseDir',
                      dest='releaseTopDir', default=releaseDirDefault,
                      help='Top-level release dir')
    parser.add_option('--logDir',
                      dest='logDir', default=logDirDefault,
                      help='Logging dir')
    parser.add_option('--force',
                      dest='force', default=False,
                      action="store_true",
                      help='force, do not request user to check it is OK to proceed')
    parser.add_option('--static',
                      dest='static', default=False,
                      action="store_true",
                      help='produce distribution for static linking, default is dynamic')

    (options, args) = parser.parse_args()
    
    if (options.verbose):
        options.debug = True

    # check package name

    if (options.package != "lrose-core" and
        options.package != "lrose-blaze" and
        options.package != "lrose-cyclone" and
        options.package != "lrose-radx" and
        options.package != "lrose-cidd") :
        print("ERROR: invalid package name: %s:" % options.package, file=sys.stderr)
        print("  options: lrose-core, lrose-blaze, lrose-cyclone, lrose-radx, lrose-cidd", file=sys.stderr)
        sys.exit(1)

    # for CIDD, set to static linkage
    if (options.package == "lrose-cidd"):
        options.static = True
        
    debugStr = " "
    if (options.verbose):
        debugStr = " --verbose "
    elif (options.debug):
        debugStr = " --debug "
    if (options.osx):
        argsStr = debugStr + " --osx "
    else:
        argsStr = debugStr

    # runtime

    now = time.gmtime()
    nowTime = datetime(now.tm_year, now.tm_mon, now.tm_mday,
                       now.tm_hour, now.tm_min, now.tm_sec)
    versionStr = nowTime.strftime("%Y%m%d")

    # set directories

    releaseDir = os.path.join(options.releaseTopDir, options.package)
    if (options.osx):
        releaseDir = os.path.join(releaseDir, "osx")
    tmpDir = os.path.join(releaseDir, "tmp")
    coreDir = os.path.join(tmpDir, "lrose-core")
    codebaseDir = os.path.join(coreDir, "codebase")

    # compute release name and dir name

    if (options.osx):
        releaseName = options.package + "-" + versionStr + ".src.mac_osx"
    else:
        releaseName = options.package + "-" + versionStr + ".src"
    tarName = releaseName + ".tgz"
    tarDir = os.path.join(coreDir, releaseName)

    # initialize logging

    if (os.path.isdir(options.logDir) == False):
        os.makedirs(options.logDir)
    logPath = os.path.join(options.logDir, "master");
    logFp = open(logPath, "w+")

    if (options.debug):
        print("Running %s:" % thisScriptName, file=sys.stderr)
        print("  package: ", options.package, file=sys.stderr)
        print("  osx: ", options.osx, file=sys.stderr)
        print("  releaseTopDir: ", options.releaseTopDir, file=sys.stderr)
        print("  releaseDir: ", releaseDir, file=sys.stderr)
        print("  logDir: ", options.logDir, file=sys.stderr)
        print("  tmpDir: ", tmpDir, file=sys.stderr)
        print("  force: ", options.force, file=sys.stderr)
        print("  static: ", options.static, file=sys.stderr)
        print("  versionStr: ", versionStr, file=sys.stderr)
        print("  releaseName: ", releaseName, file=sys.stderr)
        print("  tarName: ", tarName, file=sys.stderr)
        
    # save previous releases

    savePrevReleases()

    # create tmp dir

    createTmpDir()

    # get repos from git

    logPath = prepareLogFile("git-checkout");
    gitCheckout()

    # install the distribution-specific makefiles

    logPath = prepareLogFile("install-package-makefiles");
    os.chdir(codebaseDir)
    cmd = "./make_bin/installPackageMakefiles.py --package " + \
          options.package + " --codedir . "
    if (options.osx):
        cmd = cmd + " --osx "
    shellCmd(cmd)

    # trim libs and apps to those required by distribution makefiles

    trimToMakefiles("libs")
    trimToMakefiles("apps")

    # set up autoconf

    logPath = prepareLogFile("setup-autoconf");
    setupAutoconf()

    # create the release information file
    
    createReleaseInfoFile()

    # run qmake for QT apps to create moc_ files

    logPath = prepareLogFile("create-qt-moc-files");
    hawkEyeDir = os.path.join(codebaseDir, "apps/radar/src/HawkEye")
    createQtMocFiles(hawkEyeDir)

    # prune any empty directories

    logPath = prepareLogFile("prune-empty_dirs");
    prune(codebaseDir)

    # create the tar file

    logPath = prepareLogFile("create-tar-file");
    createTarFile()

    # create the brew formula for OSX builds

    if (options.osx):
        logPath = prepareLogFile("create-brew-formula");
        createBrewFormula()

    # move the tar file up into release dir

    os.chdir(releaseDir)
    os.rename(os.path.join(coreDir, tarName),
              os.path.join(releaseDir, tarName))
              
    # delete the tmp dir

    shutil.rmtree(tmpDir)

    logFp.close()
    sys.exit(0)

########################################################################
# move previous releases

def savePrevReleases():

    if (os.path.isdir(releaseDir) == False):
        return
    
    os.chdir(releaseDir)
    prevDirPath = os.path.join(releaseDir, 'previous_releases')

    # remove if file instead of dir

    if (os.path.isfile(prevDirPath)):
        os.remove(prevDirPath)

    # ensure dir exists
    
    if (os.path.isdir(prevDirPath) == False):
        os.makedirs(prevDirPath)

    # get old releases

    pattern = options.package + "-????????*.tgz"
    oldReleases = glob.glob(pattern)

    for name in oldReleases:
        newName = os.path.join(prevDirPath, name)
        if (options.debug):
            print("saving oldRelease: ", name, file=logFp)
            print("to: ", newName, file=logFp)
        os.rename(name, newName)

########################################################################
# create the tmp dir

def createTmpDir():

    # check if exists already

    if (os.path.isdir(tmpDir)):

        if (options.force == False):
            print(("WARNING: you are about to remove all contents in dir: " + tmpDir))
            print("===============================================")
            contents = os.listdir(tmpDir)
            for filename in contents:
                print(("  " + filename))
            print("===============================================")
            answer = "n"
            if (sys.version_info > (3, 0)):
                answer = input("WARNING: do you wish to proceed (y/n)? ")
            else:
                answer = raw_input("WARNING: do you wish to proceed (y/n)? ")
            if (answer != "y"):
                print("  aborting ....")
                sys.exit(1)
                
        # remove it

        shutil.rmtree(tmpDir)

    # make it clean

    os.makedirs(tmpDir)

########################################################################
# check out repos from git

def gitCheckout():

    os.chdir(tmpDir)
    shellCmd("git clone https://github.com/NCAR/lrose-core")
    shellCmd("git clone https://github.com/NCAR/lrose-netcdf")
    shellCmd("git clone https://github.com/NCAR/lrose-displays")

########################################################################
# set up autoconf for configure etc

def setupAutoconf():

    os.chdir(codebaseDir)

    # create files for configure

    shutil.copy("../build/Makefile.top", "Makefile")

    if (options.static):

        if (options.package == "lrose-cidd"):
             shutil.copy("../build/autoconf/configure.base.cidd",
                         "./configure.base")
        else:
             shutil.copy("../build/autoconf/configure.base",
                         "./configure.base")

        shellCmd("./make_bin/createConfigure.am.py --dir ." +
                 " --baseName configure.base" +
                 " --pkg " + options.package + argsStr)
    else:

        if (options.package == "lrose-cidd"):
            shutil.copy("../build/autoconf/configure.base.shared.cidd",
                        "./configure.base.shared")
        elif (options.osx):
            shutil.copy("../build/autoconf/configure.base.shared.osx",
                        "./configure.base.shared")
        else:
            shutil.copy("../build/autoconf/configure.base.shared",
                        "./configure.base.shared")

        shellCmd("./make_bin/createConfigure.am.py --dir ." +
                 " --baseName configure.base.shared --shared" +
                 " --pkg " + options.package + argsStr)

########################################################################
# Run qmake for QT apps such as HawkEye to create _moc files

def createQtMocFiles(appDir):
    
    if (os.path.isdir(appDir) == False):
        return
    
    os.chdir(appDir)
    shellCmd("rm -f moc*");
    shellCmd("qmake-qt5 -o Makefile.qmake");
    shellCmd("make -f Makefile.qmake mocables");

########################################################################
# write release information file

def createReleaseInfoFile():

    # go to core dir
    os.chdir(coreDir)

    # open info file

    releaseInfoPath = os.path.join(coreDir, "ReleaseInfo.txt")
    info = open(releaseInfoPath, 'w')

    # write release info

    info.write("package:" + options.package + "\n")
    info.write("version:" + versionStr + "\n")
    info.write("release:" + releaseName + "\n")

    # close

    info.close()

########################################################################
# create the tar file

def createTarFile():

    # go to core dir, make tar dir

    os.chdir(coreDir)
    os.makedirs(tarDir)

    # copy some scripts into tar directory

    shellCmd("rsync -av build/create_bin_release.py " + tarDir)
    shellCmd("rsync -av build/build_src_release.py " + tarDir)

    # move lrose contents into tar dir

    for fileName in [ "LICENSE.txt", "README.md", "ReleaseInfo.txt" ]:
        os.rename(fileName, os.path.join(tarDir, fileName))
        
    for dirName in [ "build", "codebase", "docs", "release_notes" ]:
        os.rename(dirName, os.path.join(tarDir, dirName))

    # move netcdf support into tar dir

    netcdfDir = os.path.join(tmpDir, "lrose-netcdf")
    netcdfSubDir = os.path.join(tarDir, "lrose-netcdf")
    os.makedirs(netcdfSubDir)

    # Copy the color-scales dir from lrose-displays into tar dir (under share)
    
    displaysDir = os.path.join(tmpDir, "lrose-displays/color_scales")
    displaysSubDir = os.path.join(tarDir, "share/")
    os.makedirs(displaysSubDir)
    shellCmd("rsync -av " + displaysDir + " " + displaysSubDir)
    
    if (options.package == "lrose-cidd"):
        name = "build_and_install_netcdf.m32"
        os.rename(os.path.join(netcdfDir, name),
                  os.path.join(netcdfSubDir, name))
    else:
        name = "build_and_install_netcdf"
        os.rename(os.path.join(netcdfDir, name),
                  os.path.join(netcdfSubDir, name))
        name = "build_and_install_netcdf.osx"
        os.rename(os.path.join(netcdfDir, name),
                  os.path.join(netcdfSubDir, name))

    for name in [ "README.md", "tar_files" ]:
        os.rename(os.path.join(netcdfDir, name),
                  os.path.join(netcdfSubDir, name))

    # create the tar file

    shellCmd("tar cvfzh " + tarName + " " + releaseName)
    
########################################################################
# create the brew formula for OSX builds

def createBrewFormula():

    # go to core dir

    os.chdir(coreDir)

    tarUrl = "https://github.com/NCAR/lrose-core/releases/download/" + \
             options.package + "-" + versionStr + "/" + tarName
    formulaName = options.package + ".rb"
    scriptName = "formulas/build_" + options.package + "_formula"
    buildDirPath = os.path.join(tarDir, "build")
    scriptPath = os.path.join(buildDirPath, scriptName)

    # check if script exists

    if (os.path.isfile(scriptPath) == False):
        print("WARNING - ", thisScriptName, file=logFp)
        print("  No script: ", scriptPath, file=logFp)
        print("  Will not build brew formula for package", file=logFp)
        return

    # create the brew formula file

    shellCmd(scriptPath + " " + tarUrl + " " +
             tarName + " " + formulaName)

    # move it up into the release dir

    os.rename(os.path.join(coreDir, formulaName),
              os.path.join(releaseDir, formulaName))

########################################################################
# get string value based on search key
# the string may span multiple lines
#
# Example of keys: SRCS, SUB_DIRS, MODULE_NAME, TARGET_FILE
#
# value is returned

def getValueListForKey(path, key):

    valueList = []

    try:
        fp = open(path, 'r')
    except IOError as e:
        print("ERROR - ", thisScriptName, file=logFp)
        print("  Cannot open file:", path, file=logFp)
        return valueList

    lines = fp.readlines()
    fp.close()

    foundKey = False
    multiLine = ""
    for line in lines:
        if (foundKey == False):
            if (line[0] == '#'):
                continue
        if (line.find(key) >= 0):
            foundKey = True
            multiLine = multiLine + line
            if (line.find("\\") < 0):
                break;
        elif (foundKey):
            if (line[0] == '#'):
                break
            if (len(line) < 2):
                break
            multiLine = multiLine + line;
            if (line.find("\\") < 0):
                break;

    if (foundKey == False):
        return valueList

    multiLine = multiLine.replace(key, " ")
    multiLine = multiLine.replace("=", " ")
    multiLine = multiLine.replace("\t", " ")
    multiLine = multiLine.replace("\\", " ")
    multiLine = multiLine.replace("\r", " ")
    multiLine = multiLine.replace("\n", " ")

    toks = multiLine.split(' ')
    for tok in toks:
        if (len(tok) > 0):
            valueList.append(tok)

    return valueList

########################################################################
# Trim libs and apps to those required by distribution

def trimToMakefiles(subDir):

    print("Trimming unneeded dirs, subDir: " + subDir, file=logFp)

    # get list of subdirs in makefile

    dirPath = os.path.join(codebaseDir, subDir)
    os.chdir(dirPath)

    # need to allow upper and lower case Makefile (makefile or Makefile)
    subNameList = getValueListForKey("makefile", "SUB_DIRS")
    if not subNameList:
        print("Trying uppercase Makefile ... ", file=logFp)
        subNameList = getValueListForKey("Makefile", "SUB_DIRS")
    
    for subName in subNameList:
        if (os.path.isdir(subName)):
            print("  need sub dir: " + subName, file=logFp)
            
    # get list of files in subDir

    entries = os.listdir(dirPath)
    for entry in entries:
        theName = os.path.join(dirPath, entry)
        print("considering: " + theName, file=logFp)
        if (entry == "scripts") or (entry == "include") or (entry == "images") or (entry == "resources"):
            # always keep scripts directories
            continue
        if (os.path.isdir(theName)):
            if (entry not in subNameList):
                print("discarding it", file=logFp)
                shutil.rmtree(theName)
            else:
                print("keeping it and recurring", file=logFp)
                # check this child's required subdirectories (recurse)
                trimToMakefiles(os.path.join(subDir, entry))

########################################################################
# prune empty dirs

def prune(tree):

    # walk the tree
    if (os.path.isdir(tree)):
        contents = os.listdir(tree)

        if (len(contents) == 0):
            print("pruning empty dir: " + tree, file=logFp)
            shutil.rmtree(tree)
        else:
            for l in contents:
                # remove CVS directories
                if (l == "CVS") or (l == ".git"): 
                    thepath = os.path.join(tree,l)
                    print("pruning dir: " + thepath, file=logFp)
                    shutil.rmtree(thepath)
                else:
                    thepath = os.path.join(tree,l)
                    if (os.path.isdir(thepath)):
                        prune(thepath)
            # check if this tree is now empty
            newcontents = os.listdir(tree)
            if (len(newcontents) == 0):
                print("pruning empty dir: " + tree, file=logFp)
                shutil.rmtree(tree)


########################################################################
# prepare log file

def prepareLogFile(logFileName):

    global logFp

    logFp.close()
    logPath = os.path.join(options.logDir, logFileName + ".log");
    if (logPath.find('no-logging') >= 0):
        return logPath
    print("========================= " + logFileName + " =========================", file=sys.stderr)
    if (options.verbose):
        print("====>> Creating log file: " + logPath + " <<==", file=sys.stderr)
    logFp = open(logPath, "w+")
    logFp.write("===========================================\n")
    logFp.write("Log file from script: " + thisScriptName + "\n")

    return logPath

########################################################################
# Run a command in a shell, wait for it to complete

def shellCmd(cmd):

    print("Running cmd:", cmd, file=sys.stderr)
    
    if (logPath.find('no-logging') >= 0):
        cmdToRun = cmd
    else:
        print("Log file is:", logPath, file=sys.stderr)
        print("    ....", file=sys.stderr)
        cmdToRun = cmd + " 1>> " + logPath + " 2>&1"

    try:
        retcode = subprocess.check_call(cmdToRun, shell=True)
        if retcode != 0:
            print("Child exited with code: ", retcode, file=sys.stderr)
            sys.exit(1)
        else:
            if (options.verbose):
                print("Child returned code: ", retcode, file=sys.stderr)
    except OSError as e:
        print("Execution failed:", e, file=sys.stderr)
        sys.exit(1)

    print("    done", file=sys.stderr)
    
########################################################################
# Run - entry point

if __name__ == "__main__":
   main()
