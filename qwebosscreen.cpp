/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
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

#include "qwebosscreen.h"
#include "qweboswindow.h"

#include <QtPlatformSupport/private/qeglconvenience_p.h>
#include <QtPlatformSupport/private/qeglplatformcontext_p.h>

QT_BEGIN_NAMESPACE

QWebosScreen::QWebosScreen(EGLNativeDisplayType displayType)
    : mDepth(32)
    , mFormat(QImage::Format_RGB32)
    , mEglDisplay(EGL_NO_DISPLAY)
    , mEglConfig(NULL)
    , mSurfaceFormat()
{
    assert(eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE);
    assert((mEglDisplay = eglGetDisplay(displayType)) != EGL_NO_DISPLAY);
    assert(eglInitialize(mEglDisplay, NULL, NULL) == EGL_TRUE);

    mSurfaceFormat.setRedBufferSize(8);
    mSurfaceFormat.setGreenBufferSize(8);
    mSurfaceFormat.setBlueBufferSize(8);
    mSurfaceFormat.setAlphaBufferSize(8);
    mSurfaceFormat.setDepthBufferSize(24);
    mSurfaceFormat.setStencilBufferSize(8);
    // if (!qEnvirnonmentVariableIsEmpty("QT_QPA_WEBOS_MULTISAMPLE"))
    //    mSurfaceFormat.setSamples(4);
    mEglConfig = q_configFromGLFormat(mEglDisplay, mSurfaceFormat, true);

    int swapInterval = 1;
    QByteArray swapIntervalString = qgetenv("QT_QPA_WEBOS_SWAPINTERVAL");
    if (!swapIntervalString.isEmpty()) {
        bool ok;
        swapInterval = swapIntervalString.toInt(&ok);
        if (!ok)
            swapInterval = 1;
    }
    eglSwapInterval(mEglDisplay, swapInterval);
}

QWebosScreen::~QWebosScreen()
{
}

int QWebosScreen::depth() const
{
    return mDepth;
}

QImage::Format QWebosScreen::format() const
{
    return mFormat;
}

QT_END_NAMESPACE
