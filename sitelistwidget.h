//*****************************************************************************
// Name:      sitelistwidget.h
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

#ifndef SITELIST_WIDGET_H
#define SITELIST_WIDGET_H

// Qt includes
#include <QTableWidget>


// C++ includes

class SiteListWidget : public QTableWidget
{
    Q_OBJECT

public:
    SiteListWidget(QWidget* parent = 0);
    ~SiteListWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    void urlChangedM(int, const QString&);
    void addSiteM(const QString&, const QByteArray&, const QDateTime&);
    void startMonitoring(int);
    void stopMonitoring(int);
    void showUpdate(const QString&);

public slots:
    void addSite(const QString&, const QByteArray&, const QDateTime&);
    void removeSite(int);

    void changed(int, const QString&, const QDateTime&);
    void unchanged(int);
    void error(int);

    void setTitle(int, const QString&);
    void setFavicon(int, const QIcon&);
    void setUrl(int, const QString&);

    void showingUpdate(const QString&);

private slots:
    void launchItem(QTableWidgetItem* item);
    void itemModified(QTableWidgetItem* item);

private:
    //void wheelEvent(QWheelEvent* event);

    enum Column
    {
        Title = 0,
        Status,
        Url,
        DateChanged,
        DateChecked
    };
};

#endif // SITELIST_WIDGET_H
