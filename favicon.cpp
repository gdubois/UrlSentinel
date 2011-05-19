//*****************************************************************************
// Name:      favicon.cpp
// Purpose:   Recover the website favicon
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
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>

#include <QFile>

// Local includes
#include "favicon.h"
#include "global.h"

//******************************************************************************************************
// Constructor
//******************************************************************************************************
Favicon::Favicon() : QNetworkAccessManager(),
    m_Reply(0)
{
    connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
};

//******************************************************************************************************
// Destructor : abort the download to close gracefully
//******************************************************************************************************
Favicon::~Favicon()
{
    abort();
};

//******************************************************************************************************
// Reset the icon
//******************************************************************************************************
void Favicon::reset()
{
    abort();
    m_Url = "";
    m_Icon = QIcon();
};


//******************************************************************************************************
// Download the favicon content
//******************************************************************************************************
void Favicon::update()
{
    if (!m_Url.isEmpty() && m_Icon.isNull())
    {
        abort();
        postEvent(QString("grabbing %1").arg(m_Url.toString()));
        m_Reply = get(QNetworkRequest(m_Url));
    };
};

//******************************************************************************************************
// Aborts the download
//******************************************************************************************************
void Favicon::abort()
{
    if (m_Reply)
        m_Reply->abort();

    //delete m_Reply;
    m_Reply->deleteLater();
    m_Reply = 0;
};

//******************************************************************************************************
// Sets the favicon URL
//******************************************************************************************************
void Favicon::setUrl(const QString& url)
{
    if (m_Url != url)
    {
        m_Url = url;
        m_Icon = QIcon();
        update();
    };
};


//******************************************************************************************************
// Content has been downloaded
//******************************************************************************************************
void Favicon::replyFinished(QNetworkReply* reply)
{
    postEvent(QString("icon grabbing %1 answered").arg(reply->url().toString()));

    // Deal with HTTP 302 redirections
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirect.isEmpty())
    {
        postEvent(QString("icon grabbing %1 redirected to %2").arg(reply->url().toString()).arg(redirect.toString()));

        setUrl(redirect.toString());
        return;
    };

    if (reply->error() == QNetworkReply::NoError)
    {
        // Download successful
        QByteArray data(reply->readAll());

        postEvent(QString("icon %1 grabbed and written").arg(reply->url().toString()));

        QPixmap pixmap;
        pixmap.loadFromData(data);

        if (m_Icon.isNull() && !pixmap.isNull())
        {
            m_Icon = QIcon(pixmap);
            emit newIcon(m_Icon);
        };
    }
    else
    {
        postEvent(QString("icon grabbing %1 error %2").arg(reply->url().toString()).arg(reply->error()));
    };
};
