#!/bin/bash
if [[ -f traducteur.html ]];
then
rm traducteur.html
fi
read -p "Choisissez votre compilateur (\"gcc\"/\"clang\"): " Comp
{
gcc="gcc"
clang="clang"
if [[ "$Comp" == "$clang" ]];
then
cd CLANG
make clean traducteurHTML
cd ../
fi
} &> /dev/null
{
if [[ "$Comp" == "$gcc" ]];
then
cd GCC
make clean traducteurHTML
cd ../
fi
} &> /dev/null
if [[ "$Comp" == "$clang" ]];
then
./CLANG/traducteurHTML $1
fi
if [[ "$Comp" == "$gcc" ]];
then
./GCC/traducteurHTML $1
fi