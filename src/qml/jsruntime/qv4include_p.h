/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
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

#ifndef QV4INCLUDE_P_H
#define QV4INCLUDE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>

#include <private/qqmlcontext_p.h>

#include <private/qv4value_inl_p.h>
#include <private/qv4context_p.h>

QT_BEGIN_NAMESPACE

class QQmlEngine;
class QNetworkAccessManager;
class QNetworkReply;
class QV8Engine;
class QV4Include : public QObject
{
    Q_OBJECT
public:
    enum Status {
        Ok = 0,
        Loading = 1,
        NetworkError = 2,
        Exception = 3
    };

    static QV4::ReturnedValue method_include(QV4::CallContext *ctx);

private Q_SLOTS:
    void finished();

private:
    QV4Include(const QUrl &url, QV8Engine *engine, QQmlContextData *context,
               const QV4::ValueRef qmlglobal, const QV4::ValueRef callback);
    ~QV4Include();

    QV4::ReturnedValue result();

    static QV4::ReturnedValue resultValue(QV4::ExecutionEngine *v4, Status status = Loading);
    static void callback(const QV4::ValueRef callback, const QV4::ValueRef status);

    QV4::ExecutionEngine *v4;
    QNetworkAccessManager *m_network;
    QPointer<QNetworkReply> m_reply;

    QUrl m_url;
    int m_redirectCount;

    QV4::PersistentValue m_callbackFunction;
    QV4::PersistentValue m_resultObject;

    QQmlGuardedContextData m_context;
    QV4::PersistentValue m_qmlglobal;
};

QT_END_NAMESPACE

#endif

