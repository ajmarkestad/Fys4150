£TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

#INCLUDEPATH += /Users/VidveiLarsen/arma/armadillo-7.400.2/include


INCLUDEPATH += /usr/local/include


LIBS += -L/usr/local/lib -larmadillo -lblas -llapack

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

#LIBS +=  -larmadillo -lblas -llapack
