//*****************************************************************************
// Name:      trayicon.h
// Purpose:   Icon in the taskbar, updated when monitored site change
// Author:    Gabriel Dubois (gabygabygaby@gmail.com)
// Created:   2011-04-08
// License:   GPL v3
//*****************************************************************************
// This file is part of UrlSentinel.
//
//     UrlSentinel is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     UrlSentinel is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with UrlSentinel.  If not, see <http://www.gnu.org/licenses/>.
//*****************************************************************************

#ifndef TRAYICON_H
#define TRAYICON_H

// C++ includes
#include <list>

// Qt includes
#include <QSystemTrayIcon>
#include <QString>
#include <QDateTime>

// Local includes

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon(QWidget *parent);
    ~TrayIcon();

signals:
    void showUpdate(const QString&);
    void closeAll();

public slots:
    void changedV(int, const QString&, const QDateTime&);
    void showingUpdate(const QString&);

private slots:
    void doubleClicked(QSystemTrayIcon::ActivationReason);
    void notificationClicked();

private:
    QWidget* m_Parent;
    std::list<QString> m_UpdatedList;
};

#endif // TRAYICON_H
