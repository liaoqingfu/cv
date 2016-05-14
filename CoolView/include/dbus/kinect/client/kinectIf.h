/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -v -c KinectIf -p KinectIf.h:KinectIf.cpp .\com.dcampus.coolview.kinect.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef KINECTIF_H_1313637307
#define KINECTIF_H_1313637307

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.dcampus.coolview.kinect
 */
class KinectIf: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.dcampus.coolview.kinect"; }

public:
    KinectIf(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~KinectIf();

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void GestureOccur(const QString &to, int type);
    void KinectMessage(int type, const QString &message);
};

namespace com {
  namespace dcampus {
    namespace coolview {
      typedef ::KinectIf kinect;
    }
  }
}
#endif
