SWIG=swig
PROJECT=fltk_d
EXTRAWIDGETS=/Shine/Libs/FLTKExtraWidgets/src/Widgets.cpp -I/Shine/Libs/FLTKExtraWidgets/include/

# LIBS=`fltk-config --libs --ldstaticflags`
LIBS=-lfltk

all:
	${SWIG} -c++ -d -d2 ${PROJECT}.i
	mv *.d ../source
# 	python generate.py
	g++ -g -fPIC -std=c++17 ${EXTRAWIDGETS} ${PROJECT}_wrap.cxx ${SOURCES} ${LIBS} -shared -o ../lib${PROJECT}_wrap.so ${INCLUDES}
	ln -frs ../lib${PROJECT}_wrap.so /usr/lib/

build:
	g++ -g -fPIC -std=c++17 ${EXTRAWIDGETS} ${PROJECT}_wrap.cxx ${SOURCES} ${LIBS} -shared -o ../lib${PROJECT}_wrap.so ${INCLUDES}
	ln -frs ../lib${PROJECT}_wrap.so /usr/lib/
