name=$1

where=$2

headerPath=./$where/src/include/$name.h


sourcePath=./$where/src/$name.cpp

touch $headerPath

touch $sourcePath

guardName=${name^^}_GUARD

echo "#ifndef $guardName" >> $headerPath
echo "#define $guardName" >> $headerPath
echo "" >> $headerPath
echo "" >> $headerPath
echo "#endif" >> $headerPath


echo "#include \"include/$name.h\"" >> $sourcePath