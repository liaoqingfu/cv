/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp com.dcampus.coolview.im.jabber.xml -c CvMsgAccountAdaptor -a accountadaptor.h:accountadaptor.cpp
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "accountadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class CvMsgAccountAdaptor
 */

CvMsgAccountAdaptor::CvMsgAccountAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

CvMsgAccountAdaptor::~CvMsgAccountAdaptor()
{
    // destructor
}

void CvMsgAccountAdaptor::acceptSubscription(const QString &jid)
{
    // handle method call com.dcampus.coolview.im.jabber.acceptSubscription
    QMetaObject::invokeMethod(parent(), "acceptSubscription", Q_ARG(QString, jid));
}

void CvMsgAccountAdaptor::groupChatChangeNick(const QString &host, const QString &room, const QString &nick, int status)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatChangeNick
    QMetaObject::invokeMethod(parent(), "groupChatChangeNick", Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(int, status));
}

void CvMsgAccountAdaptor::groupChatInvite(const QString &room, const QString &jid, const QString &msg)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatInvite
    QMetaObject::invokeMethod(parent(), "groupChatInvite", Q_ARG(QString, room), Q_ARG(QString, jid), Q_ARG(QString, msg));
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick));
    return out0;
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick, const QString &password)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(QString, password));
    return out0;
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick, const QString &password, int maxchars)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(QString, password), Q_ARG(int, maxchars));
    return out0;
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick, const QString &password, int maxchars, int maxstanzas)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(QString, password), Q_ARG(int, maxchars), Q_ARG(int, maxstanzas));
    return out0;
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick, const QString &password, int maxchars, int maxstanzas, int seconds)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(QString, password), Q_ARG(int, maxchars), Q_ARG(int, maxstanzas), Q_ARG(int, seconds));
    return out0;
}

bool CvMsgAccountAdaptor::groupChatJoin(const QString &host, const QString &room, const QString &nick, const QString &password, int maxchars, int maxstanzas, int seconds, int Status)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatJoin
    bool out0;
    QMetaObject::invokeMethod(parent(), "groupChatJoin", Q_RETURN_ARG(bool, out0), Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(QString, nick), Q_ARG(QString, password), Q_ARG(int, maxchars), Q_ARG(int, maxstanzas), Q_ARG(int, seconds), Q_ARG(int, Status));
    return out0;
}

void CvMsgAccountAdaptor::groupChatLeave(const QString &host, const QString &room)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatLeave
    QMetaObject::invokeMethod(parent(), "groupChatLeave", Q_ARG(QString, host), Q_ARG(QString, room));
}

void CvMsgAccountAdaptor::groupChatSetStatus(const QString &host, const QString &room, int status)
{
    // handle method call com.dcampus.coolview.im.jabber.groupChatSetStatus
    QMetaObject::invokeMethod(parent(), "groupChatSetStatus", Q_ARG(QString, host), Q_ARG(QString, room), Q_ARG(int, status));
}

int CvMsgAccountAdaptor::initAccount(const QString &j, const QString &p)
{
    // handle method call com.dcampus.coolview.im.jabber.initAccount
    int out0;
    QMetaObject::invokeMethod(parent(), "initAccount", Q_RETURN_ARG(int, out0), Q_ARG(QString, j), Q_ARG(QString, p));
    return out0;
}

int CvMsgAccountAdaptor::initAccount(const QString &j, const QString &p, bool overwrite)
{
    // handle method call com.dcampus.coolview.im.jabber.initAccount
    int out0;
    QMetaObject::invokeMethod(parent(), "initAccount", Q_RETURN_ARG(int, out0), Q_ARG(QString, j), Q_ARG(QString, p), Q_ARG(bool, overwrite));
    return out0;
}

int CvMsgAccountAdaptor::login(int status)
{
    // handle method call com.dcampus.coolview.im.jabber.login
    int out0;
    QMetaObject::invokeMethod(parent(), "login", Q_RETURN_ARG(int, out0), Q_ARG(int, status));
    return out0;
}

void CvMsgAccountAdaptor::logout()
{
    // handle method call com.dcampus.coolview.im.jabber.logout
    QMetaObject::invokeMethod(parent(), "logout");
}

void CvMsgAccountAdaptor::sendMessage(const QString &to, const QString &subject, const QString &body)
{
    // handle method call com.dcampus.coolview.im.jabber.sendMessage
    QMetaObject::invokeMethod(parent(), "sendMessage", Q_ARG(QString, to), Q_ARG(QString, subject), Q_ARG(QString, body));
}

int CvMsgAccountAdaptor::setPresence(int status)
{
    // handle method call com.dcampus.coolview.im.jabber.setPresence
    int out0;
    QMetaObject::invokeMethod(parent(), "setPresence", Q_RETURN_ARG(int, out0), Q_ARG(int, status));
    return out0;
}

void CvMsgAccountAdaptor::subscribe(const QString &jid)
{
    // handle method call com.dcampus.coolview.im.jabber.subscribe
    QMetaObject::invokeMethod(parent(), "subscribe", Q_ARG(QString, jid));
}

void CvMsgAccountAdaptor::subscribe(const QString &jid, const QString &nick)
{
    // handle method call com.dcampus.coolview.im.jabber.subscribe
    QMetaObject::invokeMethod(parent(), "subscribe", Q_ARG(QString, jid), Q_ARG(QString, nick));
}

void CvMsgAccountAdaptor::unsubscribe(const QString &jid)
{
    // handle method call com.dcampus.coolview.im.jabber.unsubscribe
    QMetaObject::invokeMethod(parent(), "unsubscribe", Q_ARG(QString, jid));
}
