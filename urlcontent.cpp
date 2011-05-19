//*****************************************************************************
// Name:      urlcontent.cpp
// Purpose:   Recovery of the url content to be monitored
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
#include <cassert>

// Qt includes
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QRegExp>
#include <QTextCodec>
#include <QTextDocumentFragment>

// Local includes
#include "urlcontent.h"
#include "site.h"

#include "global.h"

const QString FaviconName("favicon.ico");

//******************************************************************************************************
// Constructor
//******************************************************************************************************
UrlContent::UrlContent(const QString& url) : QNetworkAccessManager(),
    m_Url(url),
    m_Title(""),
    m_Reply(0)
{
    assert(!url.isEmpty());
    connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
};

//******************************************************************************************************
// Abort download
//******************************************************************************************************
UrlContent::~UrlContent()
{
    abort();
    //delete m_Reply;
    m_Reply->deleteLater();
    m_Reply = 0;
};

//******************************************************************************************************
// Download the URL content
//******************************************************************************************************
void UrlContent::update()
{
    abort();
    setNetworkAccessible(QNetworkAccessManager::Accessible);
    m_Reply = get(QNetworkRequest(m_Url));
};

//******************************************************************************************************
// Abort download of the URL
//******************************************************************************************************
void UrlContent::abort()
{
    if (m_Reply)
        m_Reply->abort();
};

//******************************************************************************************************
// Changes the URL and download the content
//******************************************************************************************************
void UrlContent::setUrl(const QString& url)
{
    assert(!url.isEmpty());
    m_Url = url;
    update();
};

//******************************************************************************************************
// Manages the download status and content
//******************************************************************************************************
void UrlContent::replyFinished(QNetworkReply* reply)
{
    // Deal with HTTP 302 redirections
    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirect.isEmpty())
    {
        m_Url = redirect;
        postEvent(QString("redirected to %1").arg(m_Url.toString()));
        emit redirectedTo(m_Url.toString());
        return;
    };

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data(reply->readAll());

        QRegExp refreshRx("<head[^>]*>.*<meta http-equiv=\"Refresh\"\\s+content=\"[^\"]*URL=([^>]*)\"[^>]*/?>.*</head>", Qt::CaseInsensitive);
        if (refreshRx.indexIn(data) != -1)
        {
            m_Url = refreshRx.cap(1);
            postEvent(QString("redirected to %1").arg(m_Url.toString()));
            emit redirectedTo(m_Url.toString());
            return;
        };

        QString favUrl(QString("%1://%2/%3").arg(m_Url.scheme()).arg(m_Url.host()).arg(FaviconName));

        QRegExp faviconRx("<head[^>]*>.*<link rel=\"[^>]*icon[^>]*\"\\s+href=\"([^>]*\\.ico|[^>]*\\.png)\"[^>]*/?>.*</head>", Qt::CaseInsensitive);
        if (faviconRx.indexIn(data) != -1)
        {
            favUrl = faviconRx.cap(1);
            if (!favUrl.contains("://"))
                favUrl = m_Url.resolved(favUrl).toString();

            postEvent(QString("got favicon url %1").arg(favUrl));
        };

        emit tryFaviconUrl(favUrl);

        QRegExp titleRx("<title[^>]*>(.+)</title>.*</head>", Qt::CaseInsensitive);
        if (titleRx.indexIn(data) != -1)
        {
            QRegExp encodingRx("(?:charset|encoding)=\"?([^\"]+)\"", Qt::CaseInsensitive);

            QString title = (encodingRx.indexIn(data) != -1) ?
                            QTextCodec::codecForName(encodingRx.cap(1).toAscii())->toUnicode(titleRx.cap(1).toAscii()) :
                            QString::fromUtf8(titleRx.cap(1).toAscii());

            postEvent(QString("encoding : %1").arg(encodingRx.cap(1)));

            title = QTextDocumentFragment::fromHtml(title).toPlainText().simplified();

            if (title != m_Title)
            {
                postEvent(QString("got title %1").arg(title));
                m_Title = title;
                emit newTitle(title);
            };
        }
        else
            postEvent(QString("no title for %1").arg(reply->url().toString()));

        emit contentDownloaded(data);
    }
    else if (reply->error() != QNetworkReply::OperationCanceledError)
    {
        postEvent(QString("error %1 with %2").arg(reply->error()).arg(reply->url().toString()));
        emit statusError();
    };
};
