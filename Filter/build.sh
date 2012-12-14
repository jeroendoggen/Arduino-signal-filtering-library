#!/bin/bash
##
# build.sh - Script to build several Arduino .ino files at the same time
# Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

##################################################################  
# SELECT FILES TO BUILD                                          #
##################################################################

FILES[0]='examples/Bessel/'
FILES[1]='examples/Chebychev/'
FILES[1]='examples/Median/'
FILES[1]='examples/Testing/'

# select the range of file you want to build (from FIRSTFILE up to LASTFILE)
FIRSTFILE=0
LASTFILE=1

##################################################################  
# SCRIPT SETTINGS                                               #
##################################################################

SCRIPTPATH="`pwd`"
CPPCHECKOPTIONS="--enable=all --error-exitcode=1 --std=c99 --std=posix  --std=c++11 -v"

SUCCESCOUNTER=0
FAILURECOUNTER=0
CODECHECKFAILURECOUNTER=0
CODECHECKSUCCESCOUNTER=0

##################################################################  
# FUNCTIONS                                                      #
##################################################################  

function buildFile 
{
  cleanPreviousBuilds
  scons > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Build OK in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Build OK in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $SCRIPTPATH/succes.log
        let SUCCESCOUNTER++ 

    else
      echo "Build errors in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Build errors in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $SCRIPTPATH/errors.log
      let FAILURECOUNTER++
  fi
}

function cleanPreviousBuilds
{
  ls | grep .elf > /dev/null
  if [ $? -eq 0 ] 
    then 
      rm *.elf
  fi

  ls | grep .hex> /dev/null
  if [ $? -eq 0 ] 
    then 
      rm *.hex
  fi

# Comment these 5 lines to ignore warnings from the first build (e.g. warnings from Arduino core libraries)
#   ls | grep build> /dev/null
#   if [ $? -eq 0 ] 
#     then 
#       rm -rf build
#   fi
}

function CreateLogfiles 
{
  if [ -f $SCRIPTPATH/succes.log ];
  then
    echo -ne ""
  else
    echo "File succes.log does not exist, creating it now"
    touch $SCRIPTPATH/succes.log
  fi

  if [ -f $SCRIPTPATH/errors.log ];
  then
    echo -ne ""
  else
    echo "File errors.log does not exist, creating it now"
    touch $SCRIPTPATH/errors.log
  fi
}

function PrintStats
{
  echo "------------------------------"
  echo "| Succesfull builds : $SUCCESCOUNTER      |"
  echo "| Failed builds     : $FAILURECOUNTER      |"
  echo "|----------------------------|"
  echo "| Succesfull code checks : $CODECHECKSUCCESCOUNTER |"
  echo "| Failed code checks     : $CODECHECKFAILURECOUNTER |"
  echo "------------------------------"
}

function logStats
{
  echo "--------------------------------" > $SCRIPTPATH/lastbuild.log
  echo "| `date` |" >> $SCRIPTPATH/lastbuild.log
  echo "--------------------------------" >> $SCRIPTPATH/lastbuild.log
  echo "| Succesfull builds : $SUCCESCOUNTER        |" >> $SCRIPTPATH/lastbuild.log
  echo "| Failed builds     : $FAILURECOUNTER        |" >> $SCRIPTPATH/lastbuild.log
  echo "|------------------------------|" >> lastbuild.log
  echo "| Succesfull code checks : $CODECHECKSUCCESCOUNTER   |" >> $SCRIPTPATH/lastbuild.log
  echo "| Failed code checks     : $CODECHECKFAILURECOUNTER   |" >> $SCRIPTPATH/lastbuild.log
  echo "--------------------------------" >> $SCRIPTPATH/lastbuild.log
}

function buildFiles
{
  for ((i=FIRSTFILE;i<=LASTFILE;i++)); do
    cd ${FILES[i]}
    buildFile
    cd $SCRIPTPATH
  done
}

function staticCodeCheck
{
  for ((i=FIRSTFILE;i<=LASTFILE;i++)); do
    cd ${FILES[i]}
    staticCodeCheckFile
    cd $SCRIPTPATH
  done

  cppcheck $CPPCHECKOPTIONS *.h > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in header file(s)"
      echo "`date`: Cppcheck OK in header file(s)" >> $SCRIPTPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in header file(s)"
      echo "`date`: Cppcheck errors in header file(s)" >> $SCRIPTPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi

  cppcheck $CPPCHECKOPTIONS *.cpp > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in cpp file(s)"
      echo "`date`: Cppcheck OK in cpp file(s)" >> $SCRIPTPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in cpp file(s)"
      echo "`date`: Cppcheck errors in cpp file(s)" >> $SCRIPTPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi
}

function staticCodeCheckFile
{
  cppcheck $CPPCHECKOPTIONS build/*.cpp > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Cppcheck OK in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $SCRIPTPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Cppcheck errors in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $SCRIPTPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi
}


##################################################################  
# MAIN CODE STARTS HERE                                          #
##################################################################

CreateLogfiles
buildFiles
staticCodeCheck
PrintStats
logStats
