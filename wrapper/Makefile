SWIG=swig
PROJECT=fltk_d

# LIBS=`fltk-config --libs --ldstaticflags`
LIBS=-lfltk

all:
	${SWIG} -c++ -d -d2 ${PROJECT}.i
	mv *.d ../source

	g++ -g -fPIC -std=c++17 ${PROJECT}_wrap.cxx ${SOURCES} ${LIBS} -shared -o ../lib${PROJECT}_wrap.so ${INCLUDES}
	ln -frs ../lib${PROJECT}_wrap.so /usr/lib/
