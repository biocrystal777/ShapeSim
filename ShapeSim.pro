#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T13:40:53
# Shape Sim
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = ShapeSim
TEMPLATE = app
DESTDIR = out
MOC_DIR = moc
OBJECTS_DIR = obj
shalongrodcalculator
#QWTDIR  = /usr/local/qwt-5.2.2
#GSLDIR = /usr/lib

INCLUDEPATH += ./src/Gui \
               ./src/Core
#\
              # $${QWTDIR}/include #\
 #              $${GSLDIR}/include

 #LIBS += #-L$${QWTDIR}/lib -lqwt #\
        #-L$${GSLDIR} -lgsl -lgslcblas -lm


#QMAKE_CXXFLAGS_RELEASE += -Wall -pedantic
#QMAKE_CXXFLAGS_DEBUG += -Wall -pedantic
#QMAKE_LFLAGS_RELEASE += -Wall -pedantic
#QMAKE_LFLAGS_DEBUG += -Wall -pedantic

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE += -O3
#%%%% Add openmp paralelization
QMAKE_CXXFLAGS_DEBUG += -fopenmp
QMAKE_LFLAGS_DEBUG += -fopenmp
QMAKE_CXXFLAGS_RELEASE += -fopenmp
QMAKE_LFLAGS_RELEASE += -fopenmp
QMAKE_CXXFLAGS_PROFILE += -fopenmp
QMAKE_LFLAGS_PROFILE += -fopenmp
#Compile with g++ and C++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += ./src/Core/main.cpp\
           ./src/Core/shacsvparser.cpp \
           ./src/Core/shashapecalculator.cpp \
           ./src/Core/shaprolatecalculator.cpp \           
           ./src/Core/shatwoaxiscalculator.cpp \
           ./src/Core/sharodlikescalculator.cpp \
           ./src/Core/shaoblatecalculator.cpp \
           ./src/Core/shalongrodcalculator.cpp \
           ./src/Core/shacsvwriter.cpp \
           ./src/Gui/shalog_omp.cpp \           
           ./src/Gui/shagnuplotframe.cpp\
           ./src/Gui/shamainwidget.cpp\
           ./src/Gui/shatwoboxwidget.cpp \
           ./src/Gui/shashapeparwidgets.cpp \
           ./src/Gui/shashapereswidgets.cpp \
           ./src/Gui/shaparframe.cpp \

HEADERS += ./src/Core/shacsvparser.h \
           ./src/Core/shadefinitions.h \
           ./src/Core/shashapecalculator.h \
           ./src/Core/shaprolatecalculator.h \
           ./src/Core/shatwoaxiscalculator.h \
           ./src/Core/sharodlikescalculator.h \
           ./src/Core/shaoblatecalculator.h \
           ./src/Core/shalongrodcalculator.h \
           ./src/Core/shacsvwriter.h \
           ./src/Gui/shamainwidget.h \
           ./src/Gui/shatwoboxwidget.h \
           ./src/Gui/shashapeparwidgets.h \
           ./src/Gui/shashapereswidgets.h \           
           ./src/Gui/shaparframe.h \
           ./src/Gui/shalog_omp.h \           
           ./src/Gui/shagnuplotframe.h \
    src/Core/shaparamstructs.h
