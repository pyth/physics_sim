HEADERS += vec2.h \
	   object.h \
	   view.h

SOURCES += vec2.cpp \
	   object.cpp \
	   view.cpp \
	   main.cpp

QT += widgets
CONFIG += c++14
QMAKE_CXXFLAGS_RELEASE += -msse2 -msse4.1
