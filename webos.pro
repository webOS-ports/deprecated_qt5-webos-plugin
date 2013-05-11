load(configure)
load(qt_parts)

TARGET = qwebos
TEMPLATE = lib

QT += core-private gui-private platformsupport-private
CONFIG += plugin link_prl
CONFIG += egl qpa/genericunixfontdatabase

#DEFINES += QEGL_EXTRA_DEBUG
DEFINES += MESA_EGL_NO_X11_HEADERS

QMAKE_CXXFLAGS += -fPIC


SOURCES =   main.cpp \
            qwebosintegration.cpp \
            qweboswindow.cpp \
            qwebosbackingstore.cpp \
            qwebosscreen.cpp

HEADERS =   qwebosintegration.h \
            qweboswindow.h \
            qwebosbackingstore.h \
            qwebosscreen.h

OTHER_FILES += webos.json
