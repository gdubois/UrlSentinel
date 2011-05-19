//*****************************************************************************
// Name:      sitelistwidget.cpp
// Purpose:   Display the list of the monitored sites in the main window
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
#include <cassert>

// Qt includes
#include <QDateTime>
#include <QMessageBox>

#include <QDropEvent>
#include <QUrl>
#include <QDesktopServices>

#include <QPixmapCache>

// Local includes
#include "sitelistwidget.h"
#include "global.h"

#define COLUMNS 5

//******************************************************************************************************
// Constructor
//******************************************************************************************************
SiteListWidget::SiteListWidget(QWidget* parent) : QTableWidget(0, COLUMNS, parent)
{
    setColumnWidth(Column::Title, 200);
    setColumnWidth(Column::Status, 120);
    setColumnWidth(Column::Url, 300);
    setColumnWidth(Column::DateChanged, 120);
    setColumnWidth(Column::DateChecked, 120);

    QStringList headerList;
    headerList << tr("Site") << tr("Status") << tr("Url") << tr("Last update") << tr("Last check");
    setHorizontalHeaderLabels(headerList);

    assert(COLUMNS == headerList.size());

    connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SLOT(launchItem(QTableWidgetItem*)));

    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(itemModified(QTableWidgetItem*)));

    connect(this, SIGNAL(showUpdate(const QString&)),
            this, SLOT(showingUpdate(const QString&)));

    QPixmapCache::insert("Default", QPixmap(Global::picturePath + "/" + "AppIcon.ico"));
    QPixmapCache::insert("Monitoring", QPixmap(Global::picturePath + "/" + "Monitoring.png"));
    QPixmapCache::insert("Warning", QPixmap(Global::picturePath + "/" + "Warning.png"));
    QPixmapCache::insert("Error", QPixmap(Global::picturePath + "/" + "Error.png"));

};

//******************************************************************************************************
// Destructor
//******************************************************************************************************
SiteListWidget::~SiteListWidget()
{
};

//******************************************************************************************************
// Add a site to the monitoring referential
//******************************************************************************************************
void SiteListWidget::addSite(const QString& url, const QByteArray&, const QDateTime& time)
{
    QPixmap pm;
    QPixmapCache::find("Default", &pm);

    QTableWidgetItem* titleWidget = new QTableWidgetItem(QIcon(pm), "");
    titleWidget->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    QPixmapCache::find("Monitoring", &pm);
    QTableWidgetItem* statusWidget = new QTableWidgetItem(QIcon(pm), tr("Monitoring"));
    statusWidget->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    QTableWidgetItem* urlWidget = new QTableWidgetItem(url);
    urlWidget->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

    QTableWidgetItem* dateChangedWidget = new QTableWidgetItem(time.toString(Qt::LocaleDate));
    dateChangedWidget->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    QTableWidgetItem* dateCheckedWidget = new QTableWidgetItem(time.toString(Qt::LocaleDate));
    dateCheckedWidget->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    int index = rowCount();
    insertRow(index);

    setItem(index, Column::Title, titleWidget);
    setItem(index, Column::Status, statusWidget);
    setItem(index, Column::Url, urlWidget);
    setItem(index, Column::DateChanged, dateChangedWidget);
    setItem(index, Column::DateChecked, dateCheckedWidget);

    parentWidget()->adjustSize();

    emit startMonitoring(index);
};

//******************************************************************************************************
// Removes a site from the monitoring referential
//******************************************************************************************************
void SiteListWidget::removeSite(int row)
{
    assert((row >= 0) && (row < rowCount()));
    removeRow(row);
};


//******************************************************************************************************
// Sets a name for a monitored site
//******************************************************************************************************
void SiteListWidget::setTitle(int id, const QString& title)
{
    item(id, Column::Title)->setText(title);
};


//******************************************************************************************************
// Sets a favicon for a monitored site
//******************************************************************************************************
void SiteListWidget::setFavicon(int id, const QIcon& icon)
{
    item(id, Column::Title)->setIcon(icon);
};

//******************************************************************************************************
// Sets a URL for a monitored site
//******************************************************************************************************
void SiteListWidget::setUrl(int id, const QString& url)
{
    item(id, Column::Url)->setText(url);
};

//******************************************************************************************************
// A site has changed, we update its status
//******************************************************************************************************
void SiteListWidget::changed(int id, const QString&, const QDateTime& time)
{
    QPixmap pm;
    QPixmapCache::find("Warning", &pm);

    item(id, Column::Status)->setText(tr("Updated"));
    item(id, Column::Status)->setIcon(QIcon(pm));
    item(id, Column::DateChanged)->setText(time.toString(Qt::LocaleDate));
};

//******************************************************************************************************
// A site is still the same after a check (we only update the last check date)
//******************************************************************************************************
void SiteListWidget::unchanged(int id)
{
    QPixmap pm;
    QPixmapCache::find("Monitoring", &pm);
    item(id, Column::Status)->setText(tr("Monitoring"));
    item(id, Column::Status)->setIcon(QIcon(pm));
    item(id, Column::DateChecked)->setText(QDateTime::currentDateTime().toString(Qt::LocaleDate));
};

//******************************************************************************************************
// A site cannot be checked, we display the error status
//******************************************************************************************************
void SiteListWidget::error(int id)
{
    QPixmap pm;
    QPixmapCache::find("Error", &pm);

    item(id, Column::Status)->setText(tr("Error"));
    item(id, Column::Status)->setIcon(QIcon(pm));
};

//******************************************************************************************************
// Minimum acceptable size for the widget
//******************************************************************************************************
QSize SiteListWidget::minimumSizeHint() const
{
    return QSize(320, 200);
};

//******************************************************************************************************
// Best size for the widget
//******************************************************************************************************
QSize SiteListWidget::sizeHint() const
{
    return QSize(320, 200);
}

//******************************************************************************************************
// Double-click on a site "line", we display the current site
//******************************************************************************************************
void SiteListWidget::launchItem(QTableWidgetItem* current)
{
    if (current->column() != Column::Url)
    {
        QString urlStr(item(current->row(), Column::Url)->text());
        postEvent(QString("doubleclicked %1").arg(urlStr));
        emit showUpdate(urlStr);
    };
}

//******************************************************************************************************
// The site URL has been modified by the user
//******************************************************************************************************
void SiteListWidget::itemModified(QTableWidgetItem* item)
{
    if ((item->column() == Column::Url) && (!item->text().isEmpty()))
        emit urlChangedM(item->row(), item->text());
};

//******************************************************************************************************
// The modifications are being shown, we reset the status of the sites
//******************************************************************************************************
void SiteListWidget::showingUpdate(const QString& urlStr)
{
    QPixmap pm;
    QPixmapCache::find("Monitoring", &pm);

    if (urlStr == "")
    {
        // Deal with all the monitored sites
        for(int i = 0; i < rowCount(); ++i)
        {
            item(i, Column::Status)->setText(tr("Monitoring"));
            item(i, Column::Status)->setIcon(QIcon(pm));
        };
    }
    else
        // Only deal with one site
        for(int i = 0; i < rowCount(); ++i)
        {
            if (item(i, Column::Url)->text() == urlStr)
            {
                item(i, Column::Status)->setText(tr("Monitoring"));
                item(i, Column::Status)->setIcon(QIcon(pm));
            };
        };
};
