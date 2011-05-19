//*****************************************************************************
// Name:      persistentsettings.cpp
// Purpose:   Store and read the settings from the registry
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
#include <QMessageBox>
#include <QDir>

// Local includes
#include "persistentsettings.h"

PersistentSettings* PersistentSettings::m_Instance;

QStringList PersistentSettings::frequencyList;

#define DEFAULT_FREQUENCY 15 * 60 // 15 minutes

//******************************************************************************************************
// Constructor
//******************************************************************************************************
PersistentSettings::PersistentSettings(QWidget*) : QSettings(),
    m_AggressiveMode(value("Aggressive", false).toBool()),
    m_OpenMode(value("Open", false).toBool()),
    m_StartFlag(loadStartFlag()),
    m_DefaultFrequency(value("Frequency", DEFAULT_FREQUENCY).toInt())
{
    if (frequencyList.isEmpty())
        frequencyList <<  tr("1 min") << tr("5 min") << tr("15 min")
                      << tr("30 min") << tr("1 hour") << tr("2 hours") << tr("6 hours")
                      << tr("12 hours") << tr("1 day");
};

//******************************************************************************************************
// Singleton pointer
//******************************************************************************************************
PersistentSettings* PersistentSettings::instance()
{
    if (!m_Instance)
        m_Instance = new PersistentSettings;
    return m_Instance;
};

//******************************************************************************************************
// Destructor
//******************************************************************************************************
PersistentSettings::~PersistentSettings()
{
    save();
    m_Instance = 0;
};

//******************************************************************************************************
// Loads the settings from the registry
//******************************************************************************************************
void PersistentSettings::load()
{
    m_AggressiveMode = value("Aggressive", false).toBool();
    m_OpenMode = value("Open", false).toBool();
    m_StartFlag = loadStartFlag();
    m_DefaultFrequency = value("Frequency", DEFAULT_FREQUENCY).toInt();
};

//******************************************************************************************************
// Saves the settings to the registry
//******************************************************************************************************
void PersistentSettings::save()
{
    setValue("Aggressive", m_AggressiveMode);
    setValue("Open", m_OpenMode);
    saveStartFlag();
    setValue("Frequency", m_DefaultFrequency);
    sync();
};

//******************************************************************************************************
// Enables aggresive check (check the URL and its children)
//******************************************************************************************************
void PersistentSettings::setAggressiveMode(const bool aggressive)
{
    m_AggressiveMode = aggressive;
};

//******************************************************************************************************
// Enables open mode (open a URL as soon as there is a change, without user interaction)
//******************************************************************************************************
void PersistentSettings::setOpenMode(const bool open)
{
    m_OpenMode = open;
};

//******************************************************************************************************
// Enables startup with Windows
//******************************************************************************************************
void PersistentSettings::setStartFlag(const bool start)
{
    m_StartFlag = start;
};

//******************************************************************************************************
// Sets global defaut check frequency
//******************************************************************************************************
void PersistentSettings::setDefaultFrequency(const int frequency)
{
    m_DefaultFrequency = frequency;
    emit updateFrequency(m_DefaultFrequency);
};

//******************************************************************************************************
// Sets the frequency from its index in the available list
//******************************************************************************************************
void PersistentSettings::setDefaultFrequencyIndex(const int frequencyIndex)
{
    //QMessageBox::warning(0, "freq", "start");
    switch (frequencyIndex)
    {
    case 0 :
        m_DefaultFrequency = 60; // 1 min
        break;
    case 1 :
        m_DefaultFrequency = 5 * 60; // 5 min
        break;
    case 2 :
        m_DefaultFrequency = 15 * 60; // 15 min
        break;
    case 3 :
        m_DefaultFrequency = 30 * 60; // 30 min
        break;
    case 4 :
        m_DefaultFrequency = 3600; // 1 hour
        break;
    case 5 :
        m_DefaultFrequency = 2 * 3600; // 2 hours
        break;
    case 6 :
        m_DefaultFrequency = 6 * 3600; // 6 hours
        break;
    case 7 :
        m_DefaultFrequency = 12 * 3600; // 12 hours
        break;
    case 8 :
        m_DefaultFrequency = 24 * 3600; // 1 day
        break;
    }

    emit updateFrequency(m_DefaultFrequency);
};


//******************************************************************************************************
// Gets the frequency index
//******************************************************************************************************
int PersistentSettings::defaultFrequencyIndex() const
{
    switch (m_DefaultFrequency)
    {
    case 60 :
        return 0;
    case 5 * 60 : // 5 min
        return 1;
    case 15 * 60: // 15 min
        return 2;
    case 30 * 60: // 30 min
        return 3;
    case 3600: // 1 hour
        return 4;
    case 2 * 3600: // 2 hours
        return 5;
    case 6 * 3600: // 6 hours
        return 6;
    case 12 * 3600: // 12 hours
        return 7;
    case 24 * 3600: // 1 day
        return 8;
    default:
        return 0;
    }
};

//******************************************************************************************************
// Gets the current path of the executable
//******************************************************************************************************
QString PersistentSettings::exePath() const
{
    QString path = "\"" + QDir::currentPath();
    path.replace("/", "\\");
    path += "\\UrlSentinel.exe\"";

    return path;
}

//******************************************************************************************************
// Gets the status of the "start with windows flag"
//******************************************************************************************************
bool PersistentSettings::loadStartFlag() const
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);

    return (settings.value("UrlSentinel", "").toString() == exePath());
};

//******************************************************************************************************
// Sets the "start with windows" flag
//******************************************************************************************************
void PersistentSettings::saveStartFlag()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);

    //On 64bits HKEY_CURRENT_USER\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run
    //On 64bits HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run
    /*
    QSettings settings("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);
    */

    if (m_StartFlag)
    {
        if (!settings.isWritable())
            QMessageBox::critical(0, "Error", "Could not include in startup");

        settings.setValue("UrlSentinel", exePath());

        if (settings.status() != QSettings::NoError)
        {
            QMessageBox::warning(0, "write error", "registry");
        }
    }
    else
        settings.remove("UrlSentinel");
};
