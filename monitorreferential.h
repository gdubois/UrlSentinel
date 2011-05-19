//*****************************************************************************
// Name:      monitorreferential.h
// Purpose:   Manage the supervised website list
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

#ifndef MONITOR_REFERENTIAL_H
#define MONITOR_REFERENTIAL_H

// C++ includes
#include <vector>
#include <memory>

// Qt includes
#include <QSettings>
#include <QString>
#include <QByteArray>
#include <QDateTime>

// Local includes
#include "site.h"

class MainWindow;
class TrayIcon;

class MonitorReferential : public QSettings
{
    Q_OBJECT

public:
    MonitorReferential(QWidget *parent, MainWindow* mainWindow, TrayIcon* trayIcon);
    ~MonitorReferential();

signals:
    void addSiteV(const QString&, const QByteArray&, const QDateTime&);
    void removeSiteV(int);

    void changedV(int, const QString&, const QDateTime&);
    void unchangedV(int);
    void errorV(int);

    void setTitleV(int, const QString&);
    void setFaviconV(int, const QIcon&);
    void setUrlV(int, const QString&);

public slots:
    void addSiteM(const QString&, const QByteArray&, const QDateTime&);
    void removeSiteM(int);
    void updateFrequencyM(const int);
    void updateUrlM(int, const QString&);

    void startMonitoring(int);
    void stopMonitoring(int);

    void start();
    void stop();
    void checkNow();

    void save();
    void load();

private:
    std::vector<std::unique_ptr<Site>> m_SiteList;
    bool m_Started;
};

#endif // MONITOR_REFERENTIAL_H
