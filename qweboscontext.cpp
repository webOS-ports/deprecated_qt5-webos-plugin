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

#include <assert.h>
#include <QtDebug>
#include <QtPlatformSupport/private/qeglconvenience_p.h>
#include "qwebosscreen.h"
#include "qweboscontext.h"
#include "qweboswindow.h"

QT_BEGIN_NAMESPACE

QWebosContext::QWebosContext(QWebosScreen *screen)
    : mScreen(screen)
{
    assert(mScreen != NULL);

    QVector<EGLint> attribs;
    attribs.append(EGL_CONTEXT_CLIENT_VERSION);
    attribs.append(2);
    attribs.append(EGL_NONE);
    assert(eglBindAPI(EGL_OPENGL_ES_API) == EGL_TRUE);
    assert((mEglContext = eglCreateContext(screen->eglDisplay(), screen->eglConfig(), EGL_NO_CONTEXT, attribs.constData())) != EGL_NO_CONTEXT);
}

QWebosContext::~QWebosContext()
{
    assert(eglDestroyContext(mScreen->eglDisplay(), mEglContext) == EGL_TRUE);
}

bool QWebosContext::makeCurrent(QPlatformSurface *surface)
{
    assert(surface->surface()->surfaceType() == QSurface::OpenGLSurface);

    EGLSurface eglSurface = static_cast<QWebosWindow*>(surface)->eglSurface();
    eglBindAPI(EGL_OPENGL_ES_API);
    eglMakeCurrent(mScreen->eglDisplay(), eglSurface, eglSurface, mEglContext);
}

void QWebosContext::doneCurrent()
{
    eglBindAPI(EGL_OPENGL_ES_API);
    eglMakeCurrent(mScreen->eglDisplay(), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

void QWebosContext::swapBuffers(QPlatformSurface *surface)
{
    EGLSurface eglSurface = static_cast<QWebosWindow*>(surface)->eglSurface();
    eglBindAPI(EGL_OPENGL_ES_API);
    eglSwapBuffers(mScreen->eglDisplay(), eglSurface);
}

void (*QWebosContext::getProcAddress(const QByteArray& procName))()
{
    eglBindAPI(EGL_OPENGL_ES_API);
    return eglGetProcAddress(procName.constData());
}
QT_END_NAMESPACE

