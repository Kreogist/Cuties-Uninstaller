
QT += core\
      gui\
      widgets\
      multimedia

#Enabled C++ 11
CONFIG += c++11

SOURCES += \
    main.cpp \
    Controls/GraphicButtons/kcgraphicbuttonbase.cpp \
    Controls/GraphicButtons/kcgraphicbuttonok.cpp \
    Controls/GraphicButtons/kcgraphicbuttoncancel.cpp \
    mainwindow.cpp \
    kcmessagebox.cpp

HEADERS += \
    Controls/GraphicButtons/kcgraphicbuttonbase.h \
    Controls/GraphicButtons/kcgraphicbuttonok.h \
    Controls/GraphicButtons/kcgraphicbuttoncancel.h \
    mainwindow.h \
    kcmessagebox.h

RESOURCES += \
    rc.qrc
