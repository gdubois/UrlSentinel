//*****************************************************************************
// Name:      mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes
#include <QMainWindow>
#include <QByteArray>
#include <QDateTime>

// Local includes
class CentralWidget;
class SiteListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;

signals:
    void showUpdate(const QString&);
    void urlChangedM(int, const QString&);
    void addSiteM(const QString&, const QByteArray&, const QDateTime&);
    void removeSiteM(int);

    void startMonitoring(int);
    void stopMonitoring(int);
    void checkNowM();

    void addSiteV(const QString&, const QByteArray&, const QDateTime&);
    void removeSiteV(int);

    void changedV(int, const QString&, const QDateTime&);
    void unchangedV(int);
    void errorV(int);

    void setTitleV(int, const QString&);
    void setFaviconV(int, const QIcon&);
    void setUrlV(int, const QString&);

public slots:
    void doClose();

private:
    void closeEvent(QCloseEvent*);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

    CentralWidget* m_CentralWidget;
    SiteListWidget* m_ListWidget;
};

#endif // MAINWINDOW_H
