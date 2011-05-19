//*****************************************************************************
// Name:      persistensettings.h
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

#ifndef PERSISTENT_SETTINSG_H
#define PERSISTENT_SETTINSG_H

// Qt includes
#include <QSettings>
#include <QStringList>

// C++ includes

class PersistentSettings : public QSettings
{
    Q_OBJECT

public:
    static PersistentSettings* instance();
    ~PersistentSettings();

    bool aggressiveMode() const
    {
        return m_AggressiveMode;
    };

    bool openMode() const
    {
        return m_OpenMode;
    };

    bool startFlag() const
    {
        return m_StartFlag;
    };

    int defaultFrequency() const
    {
        return m_DefaultFrequency;
    };

    int defaultFrequencyIndex() const;

    static QStringList frequencyList;

signals:
    void updateFrequency(int);

public slots:
    void load();
    void save();

    void setAggressiveMode(const bool);
    void setOpenMode(const bool);
    void setDefaultFrequency(const int);
    void setDefaultFrequencyIndex(const int);
    void setStartFlag(bool);

private:
    PersistentSettings(QWidget* = 0);
    static PersistentSettings* m_Instance;

    QString exePath() const;

    bool loadStartFlag() const;
    void saveStartFlag();

    bool m_AggressiveMode;
    bool m_OpenMode;
    bool m_StartFlag;
    int m_DefaultFrequency;
};

#endif // PERSISTENT_SETTINSG_H
