//*****************************************************************************
// Name:      trayicon.cpp
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

// C++ includes
#include <algorithm>

// Qt includes
#include <QDesktopServices>
#include <QUrl>

// Local includes
#include "trayicon.h"
#include "global.h"

#include "traymenu.h"
#include "persistentsettings.h"

//******************************************************************************************************
// Constructor
//******************************************************************************************************
TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(parent),
    m_Parent(parent)
{
    assert(parent != 0);
    setIcon(QIcon(Global::picturePath + "/" + "NoUpdate.png"));

    connect(this, SIGNAL(showUpdate(const QString&)), this, SLOT(showingUpdate(const QString&)));
    connect(this, SIGNAL(messageClicked()), this, SLOT(notificationClicked()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(doubleClicked(QSystemTrayIcon::ActivationReason)));

    TrayMenu* menu = new TrayMenu(m_Parent);

    // This is the real closing message
    connect(menu, SIGNAL(closeAll()), this, SIGNAL(closeAll()));
    setContextMenu(menu);

    show();
}

//******************************************************************************************************
// Destructor
//******************************************************************************************************
TrayIcon::~TrayIcon()
{
    //hide();
}

//******************************************************************************************************
// Notifies the user of site updates with a ballon tip
//******************************************************************************************************
void TrayIcon::changedV(int, const QString& url, const QDateTime&)
{
    if (std::find(m_UpdatedList.cbegin(), m_UpdatedList.cend(), url) != m_UpdatedList.cend())
        return;

    m_UpdatedList.push_back(url);

    if (m_UpdatedList.size() == 1)
    {
        showMessage(tr("Updated Site"), url);
    }
    else
    {
        showMessage(tr("Multiple updates"), QString(tr("%1 updated websites")).arg(m_UpdatedList.size()));
    };

    setIcon(QIcon(Global::picturePath + "/" + "UpdateWaiting.png"));

    if (PersistentSettings::instance()->aggressiveMode())
        showUpdate("");
};

//******************************************************************************************************
// Opens the modified URL to show their content
//******************************************************************************************************
void TrayIcon::showingUpdate(const QString& str)
{
    if (str.isEmpty())
    {
        for(auto it = m_UpdatedList.begin(); it != m_UpdatedList.end(); ++it)
        {
            QDesktopServices::openUrl(QUrl(*it));
        }
        m_UpdatedList.clear();
    }
    else
    {
        // Always open the url
        QDesktopServices::openUrl(QUrl(str));
        m_UpdatedList.remove_if([&str](const QString& current)
        {
            return current == str;
        });
    };

    if (m_UpdatedList.empty())
        setIcon(QIcon(Global::picturePath + "/" + "NoUpdate.png"));
};


//******************************************************************************************************
// Single click on the icon : we show all the modified content
//******************************************************************************************************
void TrayIcon::notificationClicked()
{
    emit showUpdate("");
};


//******************************************************************************************************
// Double-click on the icon : toggle visibility (or show the awaiting content)
//******************************************************************************************************
void TrayIcon::doubleClicked(QSystemTrayIcon::ActivationReason reason)
{
    //if ((reason == QSystemTrayIcon::Trigger) || (reason == QSystemTrayIcon::DoubleClick))
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        if (m_UpdatedList.empty())
        {
            // No update, we open the main window
            if (m_Parent->isVisible())
                m_Parent->hide();
            else
            {
                m_Parent->show();
                m_Parent->raise();
                m_Parent->activateWindow();
            };
        }
        else
        {
            // Updates waiting, we show them
            emit showUpdate("");
        }
    };
};


