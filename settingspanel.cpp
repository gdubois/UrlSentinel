//*****************************************************************************
// Name:      settings.cpp
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

// Qt includes
#include <QGridLayout>
#include <QCloseEvent>

#include <QMessageBox>

// Local includes
#include "settingspanel.h"
#include "persistentsettings.h"

SettingsPanel* SettingsPanel::m_Instance;

//******************************************************************************************************
// Constructor
//******************************************************************************************************
SettingsPanel::SettingsPanel(QWidget* parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;

    grid->addWidget(aggressiveGroup(), 0, 0);
    grid->addWidget(actionGroup(), 0, 1);
    grid->addWidget(frequencyGroup(), 1, 0);
    grid->addWidget(startGroup(), 1, 1);

    setLayout(grid);

    setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon("ICON1"));
};

//******************************************************************************************************
// Singleton pointer
//******************************************************************************************************
SettingsPanel* SettingsPanel::instance()
{
    if (!m_Instance)
        m_Instance = new SettingsPanel;
    return m_Instance;
};

//******************************************************************************************************
// Destructor
//******************************************************************************************************
SettingsPanel::~SettingsPanel()
{
    m_Instance = 0;
};


//******************************************************************************************************
// Group display of the available actions following a modification
//******************************************************************************************************
QGroupBox* SettingsPanel::actionGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Update action"));

    notifyRadio = new QRadioButton(tr("&Notify only"));
    notifyAndOpenRadio = new QRadioButton(tr("Notify and &Open"));

    if (PersistentSettings::instance()->aggressiveMode())
        notifyAndOpenRadio->setChecked(true);
    else
        notifyRadio->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(notifyRadio);
    vbox->addWidget(notifyAndOpenRadio);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}


//******************************************************************************************************
// Groups display of the change detection method
//******************************************************************************************************
QGroupBox* SettingsPanel::aggressiveGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Update detection"));

    contentRadio = new QRadioButton(tr("&Content only"));
    contentAndLinksRadio = new QRadioButton(tr("Content and &Links"));

    if (PersistentSettings::instance()->aggressiveMode())
        contentAndLinksRadio->setChecked(true);
    else
        contentRadio->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(contentRadio);
    vbox->addWidget(contentAndLinksRadio);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    // TODO implement
    contentRadio->setEnabled(false);
    contentAndLinksRadio->setEnabled(false);

    return groupBox;
}


//******************************************************************************************************
// Group display of the check frequency
//******************************************************************************************************
QGroupBox* SettingsPanel::frequencyGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Check frequency"));

    frequencyCombo = new QComboBox;

    frequencyCombo->addItems(PersistentSettings::frequencyList);

    frequencyCombo->setCurrentIndex(PersistentSettings::instance()->defaultFrequencyIndex());

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(frequencyCombo);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

//******************************************************************************************************
// Group display of the "start with windows option"
//******************************************************************************************************
QGroupBox* SettingsPanel::startGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Starting option"));

    startBox = new QCheckBox(tr("&Start with Windows"));

    startBox->setChecked(PersistentSettings::instance()->startFlag());

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(startBox);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

//******************************************************************************************************
// Catches the close event to hide instead
//******************************************************************************************************
void SettingsPanel::closeEvent(QCloseEvent* event)
{
    hide();
    save();
    event->ignore();
};

//******************************************************************************************************
// Really close the settings panel when the application is closing
//******************************************************************************************************
void SettingsPanel::doClose()
{
    hide();
    save();
    m_Instance = 0;
};

//******************************************************************************************************
// Saves the settings to the registry
//******************************************************************************************************
void SettingsPanel::save()
{
    PersistentSettings::instance()->setAggressiveMode(contentAndLinksRadio->isChecked());
    PersistentSettings::instance()->setOpenMode(notifyAndOpenRadio->isChecked());
    PersistentSettings::instance()->setDefaultFrequencyIndex(frequencyCombo->currentIndex());
    PersistentSettings::instance()->setStartFlag(startBox->isChecked());
    PersistentSettings::instance()->save();
};
