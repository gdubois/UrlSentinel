//*****************************************************************************
// Name:      traymenu.cpp
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

// Qt includes
#include <QAction>
#include <QApplication>

// Local includes
#include "traymenu.h"
#include "settingspanel.h"


//******************************************************************************************************
// Constructor
//******************************************************************************************************
TrayMenu::TrayMenu(QWidget* parent) : QMenu(parent)
{
    createActions(parent);
};

//******************************************************************************************************
// Destructor
//******************************************************************************************************
TrayMenu::~TrayMenu()
{
};

//******************************************************************************************************
// Creates the menu actions
//******************************************************************************************************
void TrayMenu::createActions(QWidget* parent)
{
    m_TestNowAct = new QAction(tr("&Check now"), this);
    connect(m_TestNowAct, SIGNAL(triggered()), parent, SIGNAL(checkNowM()));
    addAction(m_TestNowAct);

    addSeparator();

    m_ShowAct = new QAction(tr("&Show"), this);
    connect(m_ShowAct, SIGNAL(triggered()), parent, SLOT(show()));
    addAction(m_ShowAct);

    m_OptionAct = new QAction(tr("&Options"), this);
    connect(m_OptionAct, SIGNAL(triggered()), SettingsPanel::instance(), SLOT(show()));
    addAction(m_OptionAct);

    addSeparator();

    m_ExitAct = new QAction(tr("&Exit"), this);
    connect(m_ExitAct, SIGNAL(triggered()), this, SIGNAL(closeAll()));
    addAction(m_ExitAct);
};
