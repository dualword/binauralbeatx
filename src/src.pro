include("binauralbeatx.version.pri")

TARGET = binauralbeatx
TEMPLATE = app
message(Building: = $${TARGET} - $${VERSION})

DEPENDPATH += .
INCLUDEPATH += .

QT += widgets multimedia
CONFIG += c++11 thread release
LIBS += 

HEADERS += \
        app/DualwordApp.h \
	gui/MainWindow.h \
	app/global.h \
	gui/ScreenSaver.h \
	gui/Generator.h

SOURCES += \
	app/main.cpp \
	app/DualwordApp.cpp \
	gui/MainWindow.cpp \
	gui/ScreenSaver.cpp

FORMS += \
	gui/MainWindow.ui

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
