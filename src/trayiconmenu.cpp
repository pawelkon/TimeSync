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

#include "trayiconmenu.h"

#include "timesync.h"

using namespace ts;

TrayIconMenu::TrayIconMenu(QObject *parent) : QObject(parent) {}

TrayIconMenu::TrayIconMenu(TrayIcon *icon)
{
    trayIcon = icon;
    layout();
}

TrayIconMenu::~TrayIconMenu()
{
    qDeleteAll(addressActions.begin(), addressActions.end());
    delete quitAction; delete _addressGroup;
}

const QActionGroup *TrayIconMenu::serverActions() { return _addressGroup; }

void TrayIconMenu::quit()
{
    quitAction = new QAction("quit");
    connect(quitAction, &QAction::triggered, &QApplication::quit);
    trayIcon->menu()->addAction(quitAction);
}

void TrayIconMenu::separator() { trayIcon->menu()->addSeparator(); }

void TrayIconMenu::serverList()
{
    _addressGroup = new QActionGroup(this);

    foreach(auto serv, NTPServerList()) {
        auto action = new QAction(serv.toString());
        addressActions.append(action);
        //action->setCheckable(true);
        _addressGroup->addAction(action);
        trayIcon->menu()->addActions(_addressGroup->actions());
    }
}

void TrayIconMenu::layout()
{
    serverList();
    separator();
    quit();
}
