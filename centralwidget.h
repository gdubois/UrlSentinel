//*****************************************************************************
// Name:      centralwidget.h
// Purpose:   Central widget of the main window
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

#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

// Qt includes
#include <QWidget>
#include <QPushButton>
#include <QDateTime>
#include <QLabel>

// C++ includes

class SiteListWidget;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget* parent = 0);
    ~CentralWidget();

    SiteListWidget* getListWidget() const
    {
        return m_ListWidget;
    };

signals:
    void addSiteM(const QString&, const QByteArray&, const QDateTime&);
    void removeSiteM(int);
    void checkNowM();

private slots:
    void addEntry();
    void removeEntry();

private:
    QLabel* m_Header;
    SiteListWidget* m_ListWidget;
    QPushButton* m_CheckNowButton;
    QPushButton* m_AddButton;
    QPushButton* m_RemoveButton;
};

#endif // CENTRAL_WIDGET_H
