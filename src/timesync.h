/*******************************************************************************
MIT License
Copyright (c) 2021 pawelkon
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
********************************************************************************/

#ifndef TIMESYNC_H
#define TIMESYNC_H

#include "trayicon.h"
#include "trayiconmenu.h"

#include <qntp/include/qntp/NtpClient.h>

#include <QApplication>
#include <QTimer>
#include <QHostAddress>

namespace ts {
class TimeSync : public QObject
{
    Q_OBJECT

public:
    static const int NTP_PORT = 123;

private:
    int argc; char** argv;
    QApplication *qapp;

    TrayIcon *trayIcon;
    TrayIconMenu *menu;

    NtpClient *NTPClient;
    QTimer *timeoutTimer;
    QHostAddress currentHost;

public:
    explicit TimeSync(QObject *parent = nullptr);
    TimeSync(int, char**);
    ~TimeSync();

    void start();
    int retMain();

private:
    void sync(QAction*);

    void startTimer(int);

private slots:
    void showConnProblemMsg(const QHostAddress&);
    void showSyncDoneMsg(const QHostAddress&, const QDateTime&, const QDateTime&);
    void showNoRootErrorMsg();
    void NTPReply(const QHostAddress&, quint16, const NtpReply&);
    void syncProblem();

signals:

};

inline const QList<QHostAddress> NTPServerList()
{
    QList<QHostAddress> list;
    list.append(QHostAddress("194.29.130.252"));
    list.append(QHostAddress("195.187.245.55"));

    return list;
};

}

#endif // TIMESYNC_H


