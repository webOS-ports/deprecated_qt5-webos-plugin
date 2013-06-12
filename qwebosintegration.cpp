/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** Modified by the webOS ports project
** Copyright (C) 2013 Simon Busch <morphis@gravedo.de>
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qwebosintegration.h"
#include "qweboswindow.h"
#include "qwebosbackingstore.h"
#include "qweboscontext.h"
#include "qwebosscreen.h"

#include <QtPlatformSupport/private/qgenericunixfontdatabase_p.h>
#include <QtPlatformSupport/private/qgenericunixeventdispatcher_p.h>
#include <QtGui/private/qguiapplication_p.h>

#include <qpa/qplatformwindow.h>
#include <QtGui/QSurfaceFormat>
#include <QtGui/QOpenGLContext>
#include <QtGui/QScreen>

#include <EGL/egl.h>

QT_BEGIN_NAMESPACE

QWebosIntegration::QWebosIntegration()
    : mFontDb(new QGenericUnixFontDatabase()),
      mScreen(new QWebosScreen(EGL_DEFAULT_DISPLAY)),
      mEventDispatcher(createUnixEventDispatcher())
{
    screenAdded(mScreen);
    QGuiApplicationPrivate::instance()->setEventDispatcher(mEventDispatcher);

#ifdef QEGL_EXTRA_DEBUG
    qWarning("QWebosIntegration\n");
#endif

    mContext = g_main_context_default();
    mMainLoop = g_main_loop_new(mContext, TRUE);
    mClient = new QWebosWindowManagerClient(mMainLoop);
}

QWebosIntegration::~QWebosIntegration()
{
    delete mScreen;
    delete mFontDb;
    delete mEventDispatcher;
}

bool QWebosIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case OpenGL: return true;
    case ThreadedOpenGL: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformWindow *QWebosIntegration::createPlatformWindow(QWindow *window) const
{
    QPlatformWindow *platformWindow = new QWebosWindow(mClient, window, mScreen);
    platformWindow->requestActivateWindow();
    return platformWindow;
}

QPlatformBackingStore *QWebosIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new QWebosBackingStore(window);
}

QPlatformOpenGLContext *QWebosIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    return new QWebosContext(static_cast<QWebosScreen*>(context->screen()->handle()));
}

QPlatformFontDatabase *QWebosIntegration::fontDatabase() const
{
    return mFontDb;
}

QAbstractEventDispatcher *QWebosIntegration::guiThreadEventDispatcher() const
{
    return mEventDispatcher;
}

QT_END_NAMESPACE
