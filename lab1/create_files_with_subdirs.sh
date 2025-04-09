#! bin/bash 

# above statement ensures this script runs on bash shell


subDirNoBeginning=101 # variable contains beginning number of subdirectory
fileNoBeginning=501 # variable contains beginning number of file
dirName="$(date)" # name for the file
lans=("Java" "Python" "PHP" "JavaScript" "C" "C++" "SQL" "x86 Assembly" "Go" "Lua") # bash array contains 10 programming language

mkdir "$dirName" # creating main directory
cd "$dirName" # move into the main directory just created

for((i=0; i<10; i++)) # creating sub directories and files
do
    curDirNo=$(($subDirNoBeginning+$i)) # variable curDiNo contains current number of sub directory
    curFileNo=$(($fileNoBeginning+$i)) # variable curFileNo contains current number of file

    mkdir "file$curDirNo" # creating sub directory
    touch "file$curDirNo/tusor$curFileNo.txt" # creating file in each sub directory
    echo "${lans[$i]}" | cat >> "file$curDirNo/tusor$curFileNo.txt" # inserting the name of programming language to each file

done







