QT += core
QT -= gui

CONFIG += c++14

TARGET = Deque
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    constants.hpp \
    vector_decl.inc \
    testing.hpp \
    vector.hpp \
    dequelistimpl.hpp \
    doublelinkedlist_decl.inc \
    doublelinkedlist.hpp \
    dequelistimpl_decl.inc \
    dequearrayimpl_decl.inc \
    dequearrayimpl.hpp
