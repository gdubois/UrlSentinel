//*****************************************************************************
// Name:      site.h
// Purpose:   Monitors a specific web site
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

#ifndef SITE_H
#define SITE_H

// C++ includes
#include <memory>
#include <cassert>

// Qt includes
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QTimer>
#include <QIcon>
#include <QUrl>

// Local includesm_List.

#include "urlcontent.h"
#include "favicon.h"

class Site : public QObject
{
    Q_OBJECT

public:
    Site(const std::vector<std::unique_ptr<Site>>&, const QString&, const QByteArray& = QByteArray(), const QDateTime& = QDateTime::currentDateTime(), const long frequency = 60 * 10);
    ~Site();

    void start();
    void stop();

    void setFrequency(const int);


    QString url() const
    {
        return m_Url.toString();
    };

    QByteArray hash() const
    {
        return m_LastHash;
    };

    QDateTime date() const
    {
        return m_LastDate;
    };

signals:
    void contentChanged(int, const QString&, const QDateTime&);
    void unchanged(int);
    void error(int);
    void urlChanged(int, const QString&);
    void setTitle(int, const QString&);
    void setFavicon(int, const QIcon&);

public slots:
    void setUrl(const QString&);
    void update();

private slots:
    void statusError();
    void contentDownloaded(const QByteArray&);
    void newTitle(const QString&);
    void newIcon(const QIcon&);

private:

    int id() const
    {
        for(int i = 0, size = m_List.size(); i < size; ++i)
        {
            if (m_List[i].get() == this)
                return i;
        };
        assert(false);
        return 0;
    };

    const std::vector<std::unique_ptr<Site>>& m_List;
    QUrl m_Url;
    UrlContent m_Content;
    Favicon m_Favicon;

    QString m_Title;
    QByteArray m_LastHash;
    QDateTime m_LastDate;
    long m_Frequency;

    QTimer m_Timer;
};

#endif // SITE_H
