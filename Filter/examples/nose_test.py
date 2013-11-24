#!/usr/bin/env python
#
# nose_test.py is copyright 2013 Jeroen Doggen.

import os
import subprocess
import shutil


def test_build_examples():
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


def test_upload_examples():
    failures = 0
    path = os.getcwd()
    for example in os.listdir(path):
        if(os.path.isdir(example)):
            os.chdir(example)
            state = subprocess.call(["scons", "upload"])
            if (state != 0):
                failures += 1
            cleanup(example)
            os.chdir("../")
    assert (failures == 0)


def cleanup(example):
    if (os.path.exists("build")):
        shutil.rmtree("build")

    hexfile = example + ".hex"
    if (os.path.exists(hexfile)):
        os.remove(hexfile)

    elffile = example + ".elf"
    if (os.path.exists(elffile)):
        os.remove(elffile)
