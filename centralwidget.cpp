//*****************************************************************************
// Name:      centralwidget.cpp
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

// Qt includes
#include <QBoxLayout>
#include <QInputDialog>
#include <QPixmapCache>

// Local includes
#include "centralwidget.h"
#include "sitelistwidget.h"
#include "global.h"

//******************************************************************************************************
// Constructor
//******************************************************************************************************
CentralWidget::CentralWidget(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    m_Header = new QLabel;

    m_Header->setPixmap(QPixmap(Global::picturePath + "/" + "Header.png").scaledToWidth(320, Qt::SmoothTransformation));

    m_ListWidget = new SiteListWidget;

    QPixmapCache::insert("Add", QPixmap(Global::picturePath + "/" + "Add.png"));
    QPixmapCache::insert("Remove", QPixmap(Global::picturePath + "/" + "Remove.png"));
    QPixmapCache::insert("Now", QPixmap(Global::picturePath + "/" + "Now.png"));

    QPixmap pm;

    QPixmapCache::find("Add", &pm);
    m_AddButton = new QPushButton(QIcon(pm), tr("Add a site"));

    QPixmapCache::find("Remove", &pm);
    m_RemoveButton = new QPushButton(QIcon(pm), tr("Remove a site"));

    QPixmapCache::find("Now", &pm);
    m_CheckNowButton = new QPushButton(QIcon(pm), tr("Check now!"));


    layout->setContentsMargins(5, 5, 5, 5);

    QHBoxLayout* headerLayout = new QHBoxLayout;

    headerLayout->addStretch();
    headerLayout->addWidget(m_Header);
    headerLayout->addStretch();

    layout->addLayout(headerLayout);

    layout->addWidget(m_ListWidget);


    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QVBoxLayout* leftLayout = new QVBoxLayout;
    buttonLayout->addLayout(leftLayout);
    leftLayout->addWidget(m_AddButton);
    leftLayout->addWidget(m_RemoveButton);

    m_CheckNowButton->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));
    buttonLayout->addWidget(m_CheckNowButton);

    layout->addLayout(buttonLayout);

    setLayout(layout);

    setAcceptDrops(true);

    connect(m_AddButton, SIGNAL(clicked()), this, SLOT(addEntry()));
    connect(m_RemoveButton, SIGNAL(clicked()), this, SLOT(removeEntry()));
    connect(m_CheckNowButton, SIGNAL(clicked()), this, SIGNAL(checkNowM()));
};

//******************************************************************************************************
// Destructor
//******************************************************************************************************
CentralWidget::~CentralWidget()
{
};

//******************************************************************************************************
// Open a dialog to add a new site
//******************************************************************************************************
void CentralWidget::addEntry()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Monitor a new site"),
                                         tr("New URL:"), QLineEdit::Normal,
                                         "http://", &ok);
    if (ok && !text.isEmpty())
        emit addSiteM(text, QByteArray(), QDateTime::currentDateTime());

    parentWidget()->adjustSize();
};

//******************************************************************************************************
// Removes a monitored site
//******************************************************************************************************
void CentralWidget::removeEntry()
{
    if(!m_ListWidget->selectedItems().isEmpty())
    {
        for(int i = 0; i < m_ListWidget->selectedItems().size(); ++i)
        {
            emit removeSiteM(m_ListWidget->selectedItems()[i]->row());
        };
    }
};
