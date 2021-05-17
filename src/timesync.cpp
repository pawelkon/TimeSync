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

#include "timesync.h"
#include "winsystime.h"

#include <qntp/include/qntp/NtpReply.h>

using namespace ts;

TimeSync::TimeSync(QObject *parent) : QObject(parent) {}

TimeSync::TimeSync(int argc, char **argv) { this->argc = argc; this->argv = argv; }

TimeSync::~TimeSync()
{
    delete qapp; delete trayIcon; delete NTPClient; delete menu; delete timeoutTimer;
}

int TimeSync::retMain() { return qapp->exec(); }

void TimeSync::sync(QAction* act)
{
    connect(NTPClient, &NtpClient::replyReceived, this, &TimeSync::NTPReply);
    currentHost = QHostAddress(act->text());
    NTPClient->sendRequest(currentHost, NTP_PORT);
    startTimer(10000);
}

void TimeSync::startTimer(int milis)
{
    timeoutTimer->setSingleShot(true);
    timeoutTimer->setInterval(milis);
    connect(timeoutTimer, &QTimer::timeout, this, &TimeSync::syncProblem);
    timeoutTimer->start();
}

void TimeSync::showConnProblemMsg(const QHostAddress& addr)
{
    trayIcon->showMessage("Time synchronization error",
                          QString("%1: connection problem").arg(addr.toString().remove("::ffff:")),
                          QSystemTrayIcon::Warning);
}

void TimeSync::showSyncDoneMsg(const QHostAddress &addr,
                               const QDateTime &receive,
                               const QDateTime &origin)
{
    QString msg;
    msg.append(QString("%1 result:\n").arg(addr.toString().remove("::ffff:")));
    msg.append(QString("Receive: %1\n").arg(receive.toString()));
    msg.append(QString("Origin: %1").arg(origin.toString()));

    trayIcon->showMessage("Time synchronization done", msg, QSystemTrayIcon::NoIcon);
}

void TimeSync::showNoRootErrorMsg()
{
    trayIcon->showMessage(
                "Time synchronization failed",
                "The system time cannot be changed. Run the program as administrator",
                QSystemTrayIcon::Warning);
}

void TimeSync::NTPReply(const QHostAddress& addr, quint16, const NtpReply &reply)
{
    timeoutTimer->stop();

    WinSysTime time;
    if(time.setDateTime(reply.receiveTime(), true))
        showSyncDoneMsg(addr, reply.receiveTime(), reply.originTime());
    else
        showNoRootErrorMsg();
}

void TimeSync::syncProblem()
{
    showConnProblemMsg(currentHost);
}

void TimeSync::start()
{
    qapp = new QApplication(argc, argv);

    trayIcon = new TrayIcon;
    trayIcon->show();

    NTPClient = new NtpClient;

    menu = new TrayIconMenu(trayIcon);
    connect(menu->serverActions(), &QActionGroup::triggered, this, &TimeSync::sync);

    timeoutTimer = new QTimer;
}


