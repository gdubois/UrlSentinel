//*****************************************************************************
// Name:      settingspanel.h
// Purpose:   Display the application settings
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

#ifndef SETTINGS_PANEL_H
#define SETTINGS_PANEL_H

// Qt includes
#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QCheckBox>

// C++ includes

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:
    static SettingsPanel* instance();
    ~SettingsPanel();

public slots:
    void doClose();

private:
    SettingsPanel(QWidget* = 0);
    static SettingsPanel* m_Instance;

    void closeEvent(QCloseEvent* event);

    void save();

    QGroupBox* actionGroup();
    QGroupBox* aggressiveGroup();
    QGroupBox* frequencyGroup();
    QGroupBox* startGroup();

    QRadioButton* notifyRadio;
    QRadioButton* notifyAndOpenRadio;

    QRadioButton* contentRadio;
    QRadioButton* contentAndLinksRadio;

    QComboBox* frequencyCombo;

    QCheckBox* startBox;

};

#endif // SETTINGS_PANEL_H
