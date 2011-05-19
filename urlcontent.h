//*****************************************************************************
// Name:      urlcontent.h
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

#ifndef URL_CONTENT_H
#define URL_CONTENT_H

// Qt includes
#include <QNetworkAccessManager>
#include <QUrl>

class Site;

// C++ includes

class UrlContent : public QNetworkAccessManager
{
    Q_OBJECT

public:
    UrlContent(const QString&);
    ~UrlContent();

    void update();
    void abort();

    void setUrl(const QString&);
    QString url() const
    {
        return m_Url.toString();
    };

signals:
    void redirectedTo(const QString&);
    void tryFaviconUrl(const QString&);
    void statusError();
    void contentDownloaded(const QByteArray&);
    void newTitle(const QString&);

private slots:
    void replyFinished(QNetworkReply*);

private:
    QUrl m_Url;
    QString m_Title;
    QNetworkReply* m_Reply;
};

#endif // URL_CONTENT_H
