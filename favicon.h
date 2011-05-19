//*****************************************************************************
// Name:      favicon.h
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

#ifndef FAVICON_H
#define FAVICON_H

// Qt includes
#include <QNetworkAccessManager>
#include <QUrl>
#include <QIcon>

class UrlMonitor;

// C++ includes

class Favicon : public QNetworkAccessManager
{
    Q_OBJECT

public:
    Favicon();
    ~Favicon();

    void update();
    void abort();
    void reset();

    QString url() const
    {
        return m_Url.toString();
    };

    QIcon getIcon() const
    {
        return m_Icon;
    };

signals:
    void newIcon(const QIcon&);

public slots:
    void setUrl(const QString& url);

private slots:
    void replyFinished(QNetworkReply*);

private:
    QUrl m_Url;
    QNetworkReply* m_Reply;
    QIcon m_Icon;
};

#endif // FAVICON_H
