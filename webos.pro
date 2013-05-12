load(configure)
load(qt_parts)

TARGET = qwebos
TEMPLATE = lib

QT += core-private gui-private platformsupport-private
CONFIG += plugin link_prl
CONFIG += egl qpa/genericunixfontdatabase

CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0 LunaSysMgrIpc webos-gui

#DEFINES += QEGL_EXTRA_DEBUG
DEFINES += MESA_EGL_NO_X11_HEADERS

QMAKE_CXXFLAGS += -fPIC -fno-rtti -fno-exceptions

SOURCES =   main.cpp \
            qwebosintegration.cpp \
            qweboswindow.cpp \
            qwebosbackingstore.cpp \
            qwebosscreen.cpp \
            qweboswindowmanagerclient.cpp

HEADERS =   qwebosintegration.h \
            qweboswindow.h \
            qwebosbackingstore.h \
            qwebosscreen.h \
            qweboswindowmanagerclient.h

OTHER_FILES += webos.json

target.path += $$[QT_INSTALL_PLUGINS]/platforms
INSTALLS += target
