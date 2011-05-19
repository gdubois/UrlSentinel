//*****************************************************************************
// Name:      mainwindow.cpp
// Purpose:   Implements the main window
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
#include <iostream>

// Qt includes
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QSharedMemory>

// Local includes
#include "global.h"

#include "mainwindow.h"
#include "trayicon.h"
#include "monitorreferential.h"

#define APPLICATION_KEY "UrlSentinelKey"

//******************************************************************************************************
// Checks if there is a previous instance running
//******************************************************************************************************
bool alreadyRunning(QSharedMemory& sharedMemory)
{
    sharedMemory.setKey(APPLICATION_KEY);

    // If the memory segment already exists
    if(sharedMemory.attach())
        return true;

    // If the memory segment cannot be created
    if (!sharedMemory.create(1))
        return true;

    // The memory segment has been successfully created
    return false;
};

//******************************************************************************************************
// Launch the application
//******************************************************************************************************
int main(int argc, char *argv[])
{
    // Shared memory created in the main loop so that the object lives throughout the application live.
    // Otherwise it is detach (and deleted as a consequence) in its destructor
    QSharedMemory sharedMemory;
    if (alreadyRunning(sharedMemory))
        return -1;

    QApplication app(argc, argv);

    // Application info
    QCoreApplication::setOrganizationName("Nuku Systems");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("UrlSentinel");

    // Translation management
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator translator;
    translator.load(Global::languagePath + "/" + "urlsentinel_" + QLocale::system().name());
    app.installTranslator(&translator);

    MainWindow* mainWindow = new MainWindow();
    TrayIcon* trayIcon = new TrayIcon(mainWindow);

    new MonitorReferential(0, mainWindow, trayIcon);

    mainWindow->hide();

    postEvent("started");

    return app.exec();
}
