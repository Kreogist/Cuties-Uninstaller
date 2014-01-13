
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
    kcmessagebox.cpp \
    kcgraphicbuttonuninstall.cpp \
    kcgraphicuninstallbuttonbase.cpp \
    kcgraphicbuttonrepair.cpp \
    kcuninstallerglobal.cpp

HEADERS += \
    Controls/GraphicButtons/kcgraphicbuttonbase.h \
    Controls/GraphicButtons/kcgraphicbuttonok.h \
    Controls/GraphicButtons/kcgraphicbuttoncancel.h \
    mainwindow.h \
    kcmessagebox.h \
    kcgraphicbuttonuninstall.h \
    kcgraphicuninstallbuttonbase.h \
    kcgraphicbuttonrepair.h \
    kcuninstallerglobal.h

RESOURCES += \
    rc.qrc
