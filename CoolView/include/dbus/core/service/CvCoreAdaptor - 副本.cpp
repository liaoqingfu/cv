/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c CvCoreAdaptor -a CvCoreAdaptor.h:CvCoreAdaptor.cpp .\com.dcampus.coolview.core.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "CvCoreAdaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class CvCoreAdaptor
 */

CvCoreAdaptor::CvCoreAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

CvCoreAdaptor::~CvCoreAdaptor()
{
    // destructor
}

void CvCoreAdaptor::TeleCommand(int command_index, const QByteArray &intput_array)
{
    // handle method call com.dcampus.coolview.core.TeleCommand
    QMetaObject::invokeMethod(parent(), "TeleCommand", Q_ARG(int, command_index), Q_ARG(QByteArray, intput_array));
}

