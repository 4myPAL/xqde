#/bin/bash
echo "/******** XIA Projects 2005 copyright ************" > libkxdocker.h
echo " * libKXDocker.so generic Header auto-generated  *" >> libkxdocker.h
echo " * this is a part of KXDocker GPL project        *" >> libkxdocker.h
echo " * XIA Projects 2005                             *" >> libkxdocker.h
echo " * http://www.xiaprojects.com                    *" >> libkxdocker.h
echo " * Main developer dr. Stefano Zingarini          *" >> libkxdocker.h
echo " * stefano@xiaprojects.com                       *" >> libkxdocker.h
echo " *************************************************/" >> libkxdocker.h
echo "" >> libkxdocker.h
echo "#ifndef LIBKXDOCKERINCLUDES" >> libkxdocker.h
echo "#define LIBKXDOCKERINCLUDES" >> libkxdocker.h
date '+#define KXDOCKERCOMPILETIME "%Y%m%d"' >> libkxdocker.h
echo "" >> libkxdocker.h
cat ../*.h |sed -n '/--HEADERSTART--/,/--HEADERSTOP--/p' >> libkxdocker.h
echo "#endif" >> libkxdocker.h 
