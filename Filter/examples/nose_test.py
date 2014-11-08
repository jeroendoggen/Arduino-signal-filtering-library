""" 
    Nose test: build all example by running one command: 'nosetests'
        nose_test.py is copyright 2013 Jeroen Doggen.
"""


#!/usr/bin/env python
#
# nose_test.py is copyright 2013 Jeroen Doggen.

import os
import subprocess
import shutil


def test_build_examples():
    """ Build all the .ino files in the Examples folder """
    failures = 0
    path = os.getcwd()
    for example in os.listdir(path):
        if(os.path.isdir(example)):
            os.chdir(example)
            state = subprocess.call("scons")
            if (state != 0):
                failures += 1
            cleanup(example)
            os.chdir("../")
    assert (failures == 0)


#def test_upload_examples():
    #""" Upload all the .ino files in the Examples folder to Arduino board """
    #failures = 0
    #path = os.getcwd()
    #for example in os.listdir(path):
        #if(os.path.isdir(example)):
            #os.chdir(example)
            #state = subprocess.call(["scons", "upload"])
            #if (state != 0):
                #failures += 1
            #cleanup(example)
            #os.chdir("../")
    #assert (failures == 0)


def cleanup(example):
    """ Clean up all scons files (hex, build,...) """
    if (os.path.exists("build")):
        shutil.rmtree("build")

    hexfile = example + ".hex"
    safe_remove(hexfile)

    elffile = example + ".elf"
    safe_remove(elffile)

    sconsfile = ".sconsign.dblite"
    safe_remove(sconsfile)


def safe_remove(inputfile):
    """ Remove 'inputfile' safely """
    if (os.path.exists(inputfile)):
        os.remove(inputfile)
