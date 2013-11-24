#!/bin/bash
##
# Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)
#
# build.sh - Script to build several Arduino .ino files at the same time
#   1. Build the source
#   2. Static code analysis using cppcheck
#   3. Fix indentation using bcpp
#

START=$(date +%s)
START2=$(date)

##################################################################  
# SCRIPT SETTINGS                                               #
##################################################################

SCRIPTPATH="`pwd`"
RESOURCESPATH=$SCRIPTPATH"/resources/"
CPPCHECKOPTIONS="--enable=all --error-exitcode=1 --std=c99 --std=posix  --std=c++11 -v"

BUILDSUCCESCOUNTER=0
BUILDFAILURECOUNTER=0
CODECHECKFAILURECOUNTER=0
CODECHECKSUCCESCOUNTER=0

MAXDEPTH=1

##################################################################  
# SELECT FILES TO BUILD                                          #
##################################################################

cd examples

# create the FILES[] array, filled with all the folder names in the examples folder
FILES=( $(find . -maxdepth 1 -type d -printf '%P\n') )

# select the range of file you want to build (from FIRSTFILE up to LASTFILE)
FIRSTFILE=0
LASTFILE=${#FILES[@]}-1  #equals last element of the FILES[] array

##################################################################  
# FUNCTIONS                                                      #
##################################################################  

function buildFile 
{
  scons > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Build OK in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Build OK in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $RESOURCESPATH/succes.log
        let BUILDSUCCESCOUNTER++ 

    else
      echo "Build errors in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Build errors in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $RESOURCESPATH/errors.log
      let BUILDFAILURECOUNTER++
  fi
}

function CreateLogfiles 
{
  if [ -f $RESOURCESPATH/succes.log ];
  then
    echo -ne ""
  else
    echo "File succes.log does not exist, creating it now"
    touch $RESOURCESPATH/succes.log
  fi

  if [ -f $RESOURCESPATH/errors.log ];
  then
    echo -ne ""
  else
    echo "File errors.log does not exist, creating it now"
    touch $RESOURCESPATH/errors.log
  fi
}

function PrintStats
{
  echo "------------------------------"
  echo "| Succesfull builds : $BUILDSUCCESCOUNTER      |"
  echo "| Failed builds     : $BUILDFAILURECOUNTER      |"
  echo "|----------------------------|"
  echo "| Succesfull code checks : $CODECHECKSUCCESCOUNTER |"
  echo "| Failed code checks     : $CODECHECKFAILURECOUNTER |"
  echo "------------------------------"
}

function logStats
{
  echo "--------------------------------" > $RESOURCESPATH/lastbuild.log
  echo "| `date` |" >> $RESOURCESPATH/lastbuild.log
  echo "--------------------------------" >> $RESOURCESPATH/lastbuild.log
  echo "| Succesfull builds : $BUILDSUCCESCOUNTER        |" >> $RESOURCESPATH/lastbuild.log
  echo "| Failed builds     : $BUILDFAILURECOUNTER        |" >> $RESOURCESPATH/lastbuild.log
  echo "|------------------------------|" >> $RESOURCESPATH/lastbuild.log
  echo "| Succesfull code checks : $CODECHECKSUCCESCOUNTER   |" >> $RESOURCESPATH/lastbuild.log
  echo "| Failed code checks     : $CODECHECKFAILURECOUNTER   |" >> $RESOURCESPATH/lastbuild.log
  echo "--------------------------------" >> $RESOURCESPATH/lastbuild.log

  END=$(date +%s)
  DIFF=$(( $END - $START ))
  echo "Build took $DIFF seconds." >> $RESOURCESPATH/lastbuild.log
  echo "Build took $DIFF seconds."
}

function buildFiles
{
  for ((i=FIRSTFILE;i<=LASTFILE;i++)); do
    cd ${FILES[i]}
    buildFile
    cd ..
  done
}

function staticCodeCheck
{
if [ $BUILDFAILURECOUNTER -eq 0 ]
    then
      staticCodeCheckRun
    else
      echo "Build errors -> skipping static code analysis"
fi
}

function staticCodeCheckRun
{
  for ((i=FIRSTFILE;i<=LASTFILE;i++)); do
    cd ${FILES[i]}
    staticCodeCheckFile
    cd ..
  done

  cd $SCRIPTPATH
  cppcheck $CPPCHECKOPTIONS *.h > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in header file(s)"
      echo "`date`: Cppcheck OK in header file(s)" >> $RESOURCESPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in header file(s)"
      echo "`date`: Cppcheck errors in header file(s)" >> $RESOURCESPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi

  cppcheck $CPPCHECKOPTIONS *.cpp > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in cpp file(s)"
      echo "`date`: Cppcheck OK in cpp file(s)" >> $RESOURCESPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in cpp file(s)"
      echo "`date`: Cppcheck errors in cpp file(s)" >> $RESOURCESPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi
}

function staticCodeCheckFile
{
  cppcheck $CPPCHECKOPTIONS build/*.cpp > /dev/null
  if [ $? -eq 0 ] 
    then
      echo "Cppcheck OK in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Cppcheck OK in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $RESOURCESPATH/succes.log
        let CODECHECKSUCCESCOUNTER++ 

    else
      echo "Cppcheck errors in folder: '`pwd | awk -F/ '{print $NF}'`' "
      echo "`date`: Cppcheck errors in folder: '`pwd | awk -F/ '{print $NF}'`' " >> $RESOURCESPATH/errors.log
      let CODECHECKFAILURECOUNTER++
  fi
}

function indentFiles
{
if [ $BUILDFAILURECOUNTER -eq 0 ]
    then
      indentFilesRun
    else
      echo "Build errors -> skipping code indenter"
fi  
}

function indentFilesRun
{
  filesuffix="h"
  indentFilesType
  filesuffix="cpp"
  indentFilesType
  filesuffix="ino"
  MAXDEPTH=3
  indentFilesType
}

function indentFilesType
{
  file_list=`find -maxdepth $MAXDEPTH ${1} -name "*.${filesuffix}" -type f`
  for file2indent in $file_list
    do
      echo "Indenting file $file2indent"
      bcpp -fi "$file2indent" -fnc $RESOURCESPATH/"bcpp_indenter.cfg" -fo indentoutput.tmp
      mv indentoutput.tmp "$file2indent"
  done
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

  ls | grep build> /dev/null
  if [ $? -eq 0 ] 
    then 
      rm -rf build
  fi

  ls -a | grep .sconsign.dblite> /dev/null
  if [ $? -eq 0 ] 
    then 
      rm -rf .sconsign.dblite
  fi
}

function cleanFiles
{
  for ((i=FIRSTFILE;i<=LASTFILE;i++)); do
    cd ${FILES[i]}
    echo "Cleaning: ${FILES[i]}"
    cleanPreviousBuilds
    cd ..
  done
}

##################################################################  
# MAIN CODE STARTS HERE                                          #
##################################################################

if [ "$1" = "clean" ] 
  then
    cleanFiles
  else
    CreateLogfiles
    buildFiles
    staticCodeCheck
    indentFiles
    PrintStats
    logStats
fi