//*****************************************************************************
// Name:      monitorreferential.cpp
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

// C++ includes
#include <algorithm>

// Qt includes
#include <QApplication>
#include <QNetworkProxyFactory>

// Local includes
#include "monitorreferential.h"
#include "global.h"
#include "persistentsettings.h"

#include "mainwindow.h"
#include "settingspanel.h"
#include "trayicon.h"

//******************************************************************************************************
// Constructor
//******************************************************************************************************
MonitorReferential::MonitorReferential(QWidget *parent, MainWindow* mainWindow, TrayIcon* trayIcon) : QSettings(parent),
    m_Started(false)
{
    //
    connect(PersistentSettings::instance(), SIGNAL(updateFrequency(const int)),
            this, SLOT(updateFrequencyM(const int)));

    // Loading creates the widgets
    connect(this, SIGNAL(addSiteV(const QString&, const QByteArray&, const QDateTime&)),
            mainWindow, SIGNAL(addSiteV(const QString&, const QByteArray&, const QDateTime&)));

    // Loading creates the widgets
    connect(this, SIGNAL(removeSiteV(int)),
            mainWindow, SIGNAL(removeSiteV(int)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(changedV(int, const QString&, const QDateTime&)),
            mainWindow, SIGNAL(changedV(int, const QString&, const QDateTime&)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(unchangedV(int)),
            mainWindow, SIGNAL(unchangedV(int)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(errorV(int)),
            mainWindow, SIGNAL(errorV(int)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(setTitleV(int, const QString&)),
            mainWindow, SIGNAL(setTitleV(int, const QString&)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(setFaviconV(int, const QIcon&)),
            mainWindow, SIGNAL(setFaviconV(int, const QIcon&)));

    // Changes are notified to the list widget
    connect(this, SIGNAL(setUrlV(int, const QString&)),
            mainWindow, SIGNAL(setUrlV(int, const QString&)));

    // Notifies the tray icon
    connect(this, SIGNAL(changedV(int, const QString&, const QDateTime&)),
            trayIcon, SLOT(changedV(int, const QString&, const QDateTime&)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(urlChangedM(int, const QString&)),
            this, SLOT(updateUrlM(int, const QString&)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(addSiteM(const QString&, const QByteArray&, const QDateTime&)),
            this, SLOT(addSiteM(const QString&, const QByteArray&, const QDateTime&)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(removeSiteM(int)),
            this, SLOT(removeSiteM(int)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(startMonitoring(int)),
            this, SLOT(startMonitoring(int)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(stopMonitoring(int)),
            this, SLOT(stopMonitoring(int)));

    // Notifies of URL change
    connect(mainWindow, SIGNAL(checkNowM()),
            this, SLOT(checkNow()));

    // Notifies the tray icon
    connect(trayIcon, SIGNAL(showUpdate(const QString&)), mainWindow, SIGNAL(showUpdate(const QString&)));

    // Notifies the tray icon
    connect(mainWindow, SIGNAL(showUpdate(const QString&)), trayIcon, SLOT(showingUpdate(const QString&)));

    // Notifies the tray icon
    connect(trayIcon, SIGNAL(closeAll()), mainWindow, SLOT(doClose()));

    // Notifies the tray icon
    connect(trayIcon, SIGNAL(closeAll()), SettingsPanel::instance(), SLOT(doClose()));

    // Notifies the this
    connect(trayIcon, SIGNAL(closeAll()), this, SLOT(save()));
    connect(trayIcon, SIGNAL(closeAll()), this, SLOT(deleteLater()));

    // Notifies the this
    connect(trayIcon, SIGNAL(closeAll()), this, SLOT(deleteLater()));

    // Notifies the tray icon
    connect(trayIcon, SIGNAL(closeAll()), trayIcon, SLOT(hide()));
    connect(trayIcon, SIGNAL(closeAll()), qApp, SLOT(quit()));

    // Use the system proxy for evey request
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    // Load the URL and hash list
    load();
};


//******************************************************************************************************
// Stops the monitoring and save the URL list with their hash
//******************************************************************************************************
MonitorReferential::~MonitorReferential()
{
    stop();
    save();
};

//******************************************************************************************************
// Adds a new site to the model
//******************************************************************************************************
void MonitorReferential::addSiteM(const QString& url, const QByteArray& hash, const QDateTime& time)
{
    postEvent(QString("adding %1").arg(url));

    for (auto it = m_SiteList.cbegin(); it != m_SiteList.cend(); ++it)
        if ((*it)->url() == url)
            return;

    std::unique_ptr<Site> site(new Site(m_SiteList, url, hash, time));

    connect(site.get(), SIGNAL(contentChanged(int, const QString&, const QDateTime&)),
            this, SIGNAL(changedV(int, const QString&, const QDateTime&)));

    connect(site.get(), SIGNAL(unchanged(int)),
            this, SIGNAL(unchangedV(int)));

    connect(site.get(), SIGNAL(error(int)),
            this, SIGNAL(errorV(int)));

    connect(site.get(), SIGNAL(setTitle(int, const QString&)),
            this, SIGNAL(setTitleV(int, const QString&)));

    connect(site.get(), SIGNAL(setFavicon(int, const QIcon&)),
            this, SIGNAL(setFaviconV(int, const QIcon&)));

    connect(site.get(), SIGNAL(urlChanged(int, const QString&)),
            this, SIGNAL(setUrlV(int, const QString&)));

    m_SiteList.push_back(std::move(site));

    emit addSiteV(url, hash, time);
};

//******************************************************************************************************
// Start monitoring a new site
//******************************************************************************************************
void MonitorReferential::startMonitoring(int id)
{
    assert(id >= 0);
    assert(id < (int)m_SiteList.size());
    postEvent(QString("starting monitoring %1").arg(id));
    m_SiteList[id]->start();
};


//******************************************************************************************************
// Stops monitoring a website
//******************************************************************************************************
void MonitorReferential::stopMonitoring(int id)
{
    assert(id >= 0);
    assert(id < (int)m_SiteList.size());
    postEvent(QString("stopping monitoring %1").arg(id));
    m_SiteList[id]->stop();
};


//******************************************************************************************************
// Removes a site from the model
//******************************************************************************************************
void MonitorReferential::removeSiteM(int id)
{
    assert(id >= 0);
    assert(id < (int)m_SiteList.size());
    m_SiteList.erase(m_SiteList.begin() + id);
    emit removeSiteV(id);
};

//******************************************************************************************************
// Starts monitoring all the sites
//******************************************************************************************************
void MonitorReferential::start()
{
    if (m_SiteList.empty())
        load();

    for(auto it = m_SiteList.begin(); it != m_SiteList.end(); ++it)
    {
        (*it)->start();
    };

    m_Started = true;
};

//******************************************************************************************************
// Stop monitoring all the sites
//******************************************************************************************************
void MonitorReferential::stop()
{
    for(auto it = m_SiteList.begin(); it != m_SiteList.end(); ++it)
    {
        (*it)->stop();
    }

    m_Started = false;
};

//******************************************************************************************************
// Changes the frequency check of the model
//******************************************************************************************************
void MonitorReferential::updateFrequencyM(const int frequency)
{
    for(auto it = m_SiteList.begin(); it != m_SiteList.end(); ++it)
    {
        (*it)->setFrequency(frequency);
    }
};

//******************************************************************************************************
// Changes the URL of a site in the model
//******************************************************************************************************
void MonitorReferential::updateUrlM(int id, const QString& url)
{
    assert(id >= 0);
    assert(id < (int)m_SiteList.size());
    postEvent(QString("renaming %1 to %2").arg(id).arg(url));
    m_SiteList[id]->setUrl(url);
};

//******************************************************************************************************
// Check all sites now
//******************************************************************************************************
void MonitorReferential::checkNow()
{
    for(auto it = m_SiteList.begin(), end = m_SiteList.end();  it != end; ++it)
    {
        (*it)->update();
    };
};


//******************************************************************************************************
// Loads the sites from file
//******************************************************************************************************
void MonitorReferential::load()
{
    int size = beginReadArray("Sites");

    postEvent(QString("about to read %1 sites").arg(size));

    for (int i = 0; i < size; ++i)
    {
        setArrayIndex(i);
        QString url = value("url", "").toString();
        QByteArray hash = QByteArray::fromBase64(value("hash").toByteArray());
        QDateTime date = value("date", QDateTime::currentDateTime()).toDateTime();

        if (url != "")
        {
#ifdef QT_NO_OPENSSL
            if (url.startsWith("https") || url.startsWith("ftps"))
            {
                QMessageBox::information(0, tr("HTTPS and FTPS are not supported "), tr("Error in %1").arg(url));
                continue;
            };
#endif
            addSiteM(url, hash, date);
        };
    }
    endArray();
};

//******************************************************************************************************
// Saves the site list to a file
//******************************************************************************************************
void MonitorReferential::save()
{
    beginWriteArray("Sites");
    postEvent(QString("about to write %1 sites").arg(m_SiteList.size()));
    for (unsigned int i = 0, size = m_SiteList.size(); i < size; ++i)
    {
        setArrayIndex(i);
        setValue("url", m_SiteList[i]->url());
        setValue("hash", m_SiteList[i]->hash().toBase64());
        setValue("date", m_SiteList[i]->date());
    }
    endArray();
};
