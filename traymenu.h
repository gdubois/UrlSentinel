//*****************************************************************************
// Name:      traymenu.h
// Purpose:   Menu open with a right click on the tray icon
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

#ifndef TRAYMENU_H
#define TRAYMENU_H

// Qt includes
#include <QMenu>

// C++ includes

class TrayMenu : public QMenu
{
    Q_OBJECT

public:
    TrayMenu(QWidget* = 0);
    ~TrayMenu();

signals:
    void closeAll();

private:
    void createActions(QWidget*);

    QAction* m_TestNowAct;
    QAction* m_ShowAct;
    QAction* m_OptionAct;
    QAction* m_ExitAct;

};

#endif // TRAYMENU_H
