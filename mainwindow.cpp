//*****************************************************************************
// Name:      mainwindow.cpp
// Purpose:   Main application window
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

// Qt includes
#include <QCloseEvent>
#include <QBoxLayout>
#include <QStatusBar>

// Local includes
#include "mainwindow.h"
#include "global.h"

#include "monitorreferential.h"

#include "centralwidget.h"
#include "sitelistwidget.h"
#include "settingspanel.h"


//******************************************************************************************************
// Constructor
//******************************************************************************************************
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(Global::picturePath + "/" + "NoUpdate.png"));

    m_CentralWidget = new CentralWidget();
    m_ListWidget = m_CentralWidget->getListWidget();

    connect(this, SIGNAL(showUpdate(const QString&)),
            m_ListWidget, SLOT(showingUpdate(const QString&)));

    connect(this, SIGNAL(addSiteV(const QString&, const QByteArray&, const QDateTime&)),
            m_ListWidget, SLOT(addSite(const QString&, const QByteArray&, const QDateTime&)));

    connect(this, SIGNAL(removeSiteV(int)),
            m_ListWidget, SLOT(removeSite(int)));

    connect(this, SIGNAL(changedV(int, const QString&, const QDateTime&)),
            m_ListWidget, SLOT(changed(int, const QString&, const QDateTime&)));

    connect(this, SIGNAL(unchangedV(int)),
            m_ListWidget, SLOT(unchanged(int)));

    connect(this, SIGNAL(errorV(int)),
            m_ListWidget, SLOT(error(int)));

    connect(this, SIGNAL(setTitleV(int, const QString&)),
            m_ListWidget, SLOT(setTitle(int, const QString&)));

    connect(this, SIGNAL(setFaviconV(int, const QIcon&)),
            m_ListWidget, SLOT(setFavicon(int, const QIcon&)));

    connect(this, SIGNAL(setUrlV(int, const QString&)),
            m_ListWidget, SLOT(setUrl(int, const QString&)));

    connect(m_ListWidget, SIGNAL(showUpdate(const QString&)),
            this, SIGNAL(showUpdate(const QString&)));

    connect(m_ListWidget, SIGNAL(urlChangedM(int, const QString&)),
            this, SIGNAL(urlChangedM(int, const QString&)));

    connect(m_ListWidget, SIGNAL(addSiteM(const QString&, const QByteArray&, const QDateTime&)),
            this, SIGNAL(addSiteM(const QString&, const QByteArray&, const QDateTime&)));

    connect(m_ListWidget, SIGNAL(startMonitoring(int)),
            this, SIGNAL(startMonitoring(int)));

    connect(m_ListWidget, SIGNAL(stopMonitoring(int)),
            this, SIGNAL(stopMonitoring(int)));

    // Add site connection
    connect(m_CentralWidget, SIGNAL(addSiteM(const QString&, const QByteArray&, const QDateTime&)),
            this, SIGNAL(addSiteM(const QString&, const QByteArray&, const QDateTime&)));

    // Remove site connection
    connect(m_CentralWidget, SIGNAL(removeSiteM(int)),
            this, SIGNAL(removeSiteM(int)));

    connect(m_CentralWidget, SIGNAL(checkNowM()),
            this, SIGNAL(checkNowM()));

    setCentralWidget(m_CentralWidget);

    setAcceptDrops(true);

    adjustSize();

    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

//******************************************************************************************************
// Catches tyhe close event to minimize instead
//******************************************************************************************************
void MainWindow::closeEvent(QCloseEvent* event)
{
    hide();
    event->ignore();
};


//******************************************************************************************************
// Actually close the window
//******************************************************************************************************
void MainWindow::doClose()
{
    hide();
};


//******************************************************************************************************
// A drag enters the window, we check it is a URL
//******************************************************************************************************
void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        foreach (QUrl url, event->mimeData()->urls())
        {
            if (url.isValid() && ((url.scheme() == "ftp") || (url.scheme() == "http")) )
            {
                event->acceptProposedAction();
                return;
            }
        };
    }
}

//******************************************************************************************************
// A drop occured, we add the new URL
//******************************************************************************************************
void MainWindow::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        foreach (QUrl url, event->mimeData()->urls())
        {
            emit addSiteM(url.toString(), QByteArray(), QDateTime::currentDateTime());
        };

        event->acceptProposedAction();
    };
};
