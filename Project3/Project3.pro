TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    particle.cpp \
    ensemble.cpp \
    vec3.cpp \
    solver.cpp

HEADERS += \
    particle.h \
    ensemble.h \
    vec3.h \
    solver.h

QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
