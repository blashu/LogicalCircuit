#-------------------------------------------------
#
# Project created by QtCreator 2012-03-25T17:32:24
#
#-------------------------------------------------

GTEST_LOCATION = "D:\\Program Files (x86)\\gtest\\1.6.0"

#QT       += core
#QT       -= gui
QT       += core gui


DEFINES += GTEST_LINKED_AS_SHARED_LIBRARY=1

TARGET = TestLogicalCircuit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEPENDPATH += . ../
INCLUDEPATH += . ../

include(../CoreLogicalCircuit.pri)

SOURCES += main.cpp \
    TestONode.cpp \
    TestINode.cpp

INCLUDEPATH += $${GTEST_LOCATION}/include
LIBS += -L$${GTEST_LOCATION}/lib -lgtest_dll

GTEST_DLL_LOCATION = $$join(GTEST_LOCATION, "", "if not exist debug\\gtest.dll copy /Y \"", "\\bin\\gtest.dll\" debug\\")

win32{
   QMAKE_POST_LINK=$${GTEST_DLL_LOCATION}
}

HEADERS += \
    TestONode.h \
    TestINode.h
