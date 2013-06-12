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

#ifndef QWEBOSWINDOW_H
#define QWEBOSWINDOW_H

#include "qwebosintegration.h"
#include "qwebosscreen.h"
#include "qweboswindowmanagerclient.h"

#include <qpa/qplatformwindow.h>
#include <QSystemSemaphore>

#include <SysMgrEvent.h>
#include <SysMgrDefs.h>
#include <SysMgrKeyEventTraits.h>
#include <SysMgrTouchEventTraits.h>

#include <OffscreenNativeWindow.h>

class PIpcChannel;

QT_BEGIN_NAMESPACE

class QWebosWindow : public QPlatformWindow,
                     public OffscreenNativeWindow
{
public:
    QWebosWindow(QWebosWindowManagerClient *client, QWindow *w, QWebosScreen *screen);

    void setGeometry(const QRect &);
    virtual void setVisible(bool visible);

    WId winId() const { return mWinid; }
    EGLSurface eglSurface() const { return mEglSurface; }

    void resizeSurface();

public:
    void handleFocus(bool focused);
    void handleResize(int width, int height, bool resizeBuffer);
    void handleFullScreenEnabled();
    void handleFullScreenDisabled();
    void handlePause();
    void handleResume();
    void handleInputEvent(const SysMgrEventWrapper& wrapper);
    void handleTouchEvent(const SysMgrTouchEvent& touchEvent);
    void handleKeyEvent(const SysMgrKeyEvent& keyEvent);
    void handleBufferConsumed(int key);
    PIpcChannel* channel() const; // Required by IPC_MESSAGE_FORWARD

private:
    WId mWinid;
    QWebosWindowManagerClient *mClient;
    QWebosScreen *mScreen;
    EGLSurface mEglSurface;
    QTouchDevice *mTouchDevice;

private:
    void createSurface();
};
QT_END_NAMESPACE
#endif // QWEBOSWINDOW_H
