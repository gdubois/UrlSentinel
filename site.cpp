//*****************************************************************************
// Name:      site.cpp
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

// Qt includes

// Local includes
#include "site.h"
#include "global.h"

#include "sha1.h"

//******************************************************************************************************
// Constructor
//******************************************************************************************************
Site::Site(const std::vector<std::unique_ptr<Site>>& list, const QString& urlString, const QByteArray& lastHash, const QDateTime& lastDate,  const long frequency) : QObject(0),
    m_List(list),
    m_Url(urlString),
    m_Content(urlString),
    m_Favicon(),
    m_Title(""),
    m_LastHash(lastHash),
    m_LastDate(lastDate),
    m_Frequency(frequency),
    m_Timer(this)
{
    assert(!urlString.isEmpty());

    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(&m_Content, SIGNAL(contentDownloaded(const QByteArray&)), this, SLOT(contentDownloaded(const QByteArray&)));
    connect(&m_Content, SIGNAL(statusError()), this, SLOT(statusError()));
    connect(&m_Content, SIGNAL(newTitle(const QString&)), this, SLOT(newTitle(const QString&)));

    connect(&m_Content, SIGNAL(redirectedTo(const QString&)), this, SLOT(setUrl(const QString&)));
    connect(&m_Content, SIGNAL(tryFaviconUrl(const QString&)), &m_Favicon, SLOT(setUrl(const QString&)));

    connect(&m_Favicon, SIGNAL(newIcon(const QIcon&)), this, SLOT(newIcon(const QIcon&)));

};

//******************************************************************************************************
// Stop the checking
//******************************************************************************************************
Site::~Site()
{
    stop();
};

//******************************************************************************************************
// Start monitoring a site
//******************************************************************************************************
void Site::start()
{
    m_Timer.start(m_Frequency * 1000); // in milliseconds
    m_Content.update();
    m_Favicon.update();
};

//******************************************************************************************************
// Stops the monitoring
//******************************************************************************************************
void Site::stop()
{
    m_Timer.stop();
    m_Content.abort();
    m_Favicon.abort();
};

//******************************************************************************************************
// Sets the monitoring frequency
//******************************************************************************************************
void Site::setFrequency(const int frequency)
{
    assert(frequency > 0);
    m_Frequency = frequency;
    stop();
    start();
};

//******************************************************************************************************
// Sets the URL
//******************************************************************************************************
void Site::setUrl(const QString& url)
{
    assert(!url.isEmpty());
    postEvent(QString("setting %1 to %2").arg(id()).arg(url));
    QString newUrl(url);

    if (!newUrl.contains("://"))
        newUrl.prepend("http://");

    emit urlChanged(id(), newUrl);

    m_Url = newUrl;
    stop();
    m_Favicon.reset();
    m_Content.setUrl(newUrl);
    start();
};

//******************************************************************************************************
// Sets the title
//******************************************************************************************************
void Site::newTitle(const QString& title)
{
    assert(!title.isEmpty());
    m_Title = title;
    emit setTitle(id(), title);
};

//******************************************************************************************************
// Actually checks the content
//******************************************************************************************************
void Site::update()
{
    m_Content.update();
    // No need to update the favicon here
};

//******************************************************************************************************
// The site cannot be checked
//******************************************************************************************************
void Site::statusError()
{
    postEvent("error");
    emit error(id());
};

//******************************************************************************************************
// Web site content has been downloaded
//******************************************************************************************************
void Site::contentDownloaded(const QByteArray& content)
{
    QString urlString(url());
    QString str(urlString);

    if (m_LastHash.isEmpty())
    {
        // This is the first check of the site
        m_LastHash = Sha1::hash(content);
        m_LastDate = QDateTime::currentDateTime();
        str += " new hash " + QString(m_LastHash);

        emit contentChanged(id(), urlString, m_LastDate);
    }
    else
    {
        QByteArray currentHash = Sha1::hash(content);
        if (m_LastHash != currentHash)
        {
            // The content has changed
            str += " changed ";
            m_LastHash = currentHash;
            m_LastDate = QDateTime::currentDateTime();

            emit contentChanged(id(), urlString, m_LastDate);
        }
        else
        {
            // The content is the same
            str += " unchanged ";
            emit unchanged(id());
        }

        // New hash to log
        str += "  " + QString(m_LastHash);
    }

    postEvent(str);
};

//******************************************************************************************************
// The site has a new favicon
//******************************************************************************************************
void Site::newIcon(const QIcon& icon)
{
    assert(!icon.isNull());
    emit setFavicon(id(), icon);
};
