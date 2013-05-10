TARGET = qwebos

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = QWebosIntegrationPlugin
load(qt_plugin)

QT += core-private gui-private platformsupport-private

#DEFINES += QEGL_EXTRA_DEBUG

#Avoid X11 header collision
DEFINES += MESA_EGL_NO_X11_HEADERS

SOURCES =   main.cpp \
            qwebosintegration.cpp \
            qweboswindow.cpp \
            qwebosbackingstore.cpp \
            qwebosscreen.cpp

HEADERS =   qwebosintegration.h \
            qweboswindow.h \
            qwebosbackingstore.h \
            qwebosscreen.h

QMAKE_CXXFLAGS += -fPIC

CONFIG += egl qpa/genericunixfontdatabase

OTHER_FILES += \
    webos.json
