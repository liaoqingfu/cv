/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c CvPerfMonitorAdaptor -a CvPerfMonitorAdaptor.h:CvPerfMonitorAdaptor.cpp .\com.dcampus.coolview.performance.monitor.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef CVPERFMONITORADAPTOR_H_1297761395
#define CVPERFMONITORADAPTOR_H_1297761395

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface com.dcampus.coolview.performance.monitor
 */
class CvPerfMonitorAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.dcampus.coolview.performance.monitor")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.dcampus.coolview.performance.monitor\">&#xd;\n"
"	//Register monitored process&#xd;\n"
"	//<method name=\"RegisterProcess\">&#xd;\n"
"	//	<arg direction=\"in\" type=\"ay\" name=\"processInfo\"/>		//MonitoredProcess&#xd;\n"
"	//</method>&#xd;\n"
"	&#xd;\n"
"	//Cancel monitored process&#xd;\n"
"	<method name=\"UnregisterProcess\">\n"
"      <arg direction=\"in\" type=\"i\" name=\"processID\"/>\n"
"    </method>&#xd;\n"
"&#xd;\n"
"	//Hello packet&#xd;\n"
"	//<method name=\"HelloInfo\">&#xd;\n"
"	//	<arg direction=\"in\" type=\"i\" name=\"processID\"/>&#xd;\n"
"	//	<arg direction=\"in\" type=\"ay\" name=\"processImage\"/>	//binary image&#xd;\n"
"	//</method>\n"
"  </interface>\n"
        "")
public:
    CvPerfMonitorAdaptor(QObject *parent);
    virtual ~CvPerfMonitorAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void HelloInfo(int processID, const QByteArray &processImage);
    void RegisterProcess(const QByteArray &processInfo);
    void UnregisterProcess(int processID);
Q_SIGNALS: // SIGNALS
};

#endif
