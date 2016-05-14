/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c ConferenceRoomAdaptor -a ConferenceRoomAdaptor.h:ConferenceRoomAdaptor.cpp .\com.coolview.ui.conferenceroom.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "ConferenceRoomAdaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class ConferenceRoomAdaptor
 */

ConferenceRoomAdaptor::ConferenceRoomAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

ConferenceRoomAdaptor::~ConferenceRoomAdaptor()
{
    // destructor
}

void ConferenceRoomAdaptor::AddMediaWindow(bool send, const QByteArray &input_garray, int screenIndex, int seet)
{
    // handle method call com.coolview.ui.conferenceroom.AddMediaWindow
    QMetaObject::invokeMethod(parent(), "AddMediaWindow", Q_ARG(bool, send), Q_ARG(QByteArray, input_garray), Q_ARG(int, screenIndex), Q_ARG(int, seet));
}

void ConferenceRoomAdaptor::ChangeLayout(int screenIndex, int displayModel)
{
    // handle method call com.coolview.ui.conferenceroom.ChangeLayout
    QMetaObject::invokeMethod(parent(), "ChangeLayout", Q_ARG(int, screenIndex), Q_ARG(int, displayModel));
}

void ConferenceRoomAdaptor::CloseMediaWindow(const QString &user_id)
{
    // handle method call com.coolview.ui.conferenceroom.CloseMediaWindow
    QMetaObject::invokeMethod(parent(), "CloseMediaWindow", Q_ARG(QString, user_id));
}

void ConferenceRoomAdaptor::CloseWindow()
{
    // handle method call com.coolview.ui.conferenceroom.CloseWindow
    QMetaObject::invokeMethod(parent(), "CloseWindow");
}

void ConferenceRoomAdaptor::ExitConference()
{
    // handle method call com.coolview.ui.conferenceroom.ExitConference
    QMetaObject::invokeMethod(parent(), "ExitConference");
}

void ConferenceRoomAdaptor::ModifyMediaWindow(const QString &user_id, int actionIdex, const QByteArray &arguments)
{
    // handle method call com.coolview.ui.conferenceroom.ModifyMediaWindow
    QMetaObject::invokeMethod(parent(), "ModifyMediaWindow", Q_ARG(QString, user_id), Q_ARG(int, actionIdex), Q_ARG(QByteArray, arguments));
}

void ConferenceRoomAdaptor::OpenScreenShareFile(const QString &filePath, int screenIndex)
{
    // handle method call com.coolview.ui.conferenceroom.OpenScreenShareFile
    QMetaObject::invokeMethod(parent(), "OpenScreenShareFile", Q_ARG(QString, filePath), Q_ARG(int, screenIndex));
}

void ConferenceRoomAdaptor::RecoveryRecvMediaProcess(const QByteArray &input_garray, int screenIndex, int seet)
{
    // handle method call com.coolview.ui.conferenceroom.RecoveryRecvMediaProcess
    QMetaObject::invokeMethod(parent(), "RecoveryRecvMediaProcess", Q_ARG(QByteArray, input_garray), Q_ARG(int, screenIndex), Q_ARG(int, seet));
}

void ConferenceRoomAdaptor::ShowRtcpMsg(int screenIndex, bool show)
{
    // handle method call com.coolview.ui.conferenceroom.ShowRtcpMsg
    QMetaObject::invokeMethod(parent(), "ShowRtcpMsg", Q_ARG(int, screenIndex), Q_ARG(bool, show));
}

void ConferenceRoomAdaptor::UpdateRtcpMsg(const QByteArray &input_garray)
{
    // handle method call com.coolview.ui.conferenceroom.UpdateRtcpMsg
    QMetaObject::invokeMethod(parent(), "UpdateRtcpMsg", Q_ARG(QByteArray, input_garray));
}

