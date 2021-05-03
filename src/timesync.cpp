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

using namespace ts;

TimeSync::TimeSync(QObject *parent) : QObject(parent) {}

TimeSync::TimeSync(int argc, char **argv) { this->argc = argc; this->argv = argv; }

TimeSync::~TimeSync()
{
    delete qapp; delete trayIcon;
}

int TimeSync::retMain() { return qapp->exec(); }

void TimeSync::start()
{
    qapp = new QApplication(argc, argv);

    trayIcon = new TrayIcon;
    trayIcon->show();

    quitAction = new QAction("quit");
    connect(quitAction, &QAction::triggered, &QApplication::quit);
    trayIcon->menu()->addAction(quitAction);
}
