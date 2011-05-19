//*****************************************************************************
// Name:      log.h
// Purpose:   Log events (DEBUG purpose only)
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

#ifndef LOG_H
#define LOG_H

// Local includes

// QT includes
#include <QString>
#include <QFile>
#include <QTextEdit>
#include <QTextStream>
#include <QDateTime>

#include <QMutex>

class Log : public QTextEdit
{
    Q_OBJECT
public:
    static Log* instance();
    ~Log();

public slots:
    void event(QString);

private:
    // Singleton
    Log(const QString& fileName = "");
    static Log* m_Instance;

    QFile* logFile;
    QTextStream* out;

#ifdef MULTICORE
    QMutex mutex;
#endif
};

#endif //LOG_H
