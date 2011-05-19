//*****************************************************************************
// Name:      log.cpp
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

// Local includes
#include "../global.h"
#include "log.h"

// Qt includes
#include <QMessageBox>

//Statics

Log* Log::m_Instance = 0;

//******************************************************************************************************
// Constructor
//******************************************************************************************************
Log::Log(const QString& logFileName) :
    QTextEdit(0)
{
    setMinimumWidth(600);
    if (logFileName != "")
    {
        logFile = new QFile( logFileName );
        if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text /*| QIODevice::Append*/ | QIODevice::Unbuffered))
        {
            QMessageBox::critical(0, "Can't open file", logFileName);
            return;
        };
        out = new QTextStream (logFile);
        if (out == 0)
        {
            QMessageBox::critical(0, "Can't open stream", logFileName);
            return;
        };
    }
    else
        logFile = 0;

    setWindowTitle(tr("Log"));
    show();
};


//******************************************************************************************************
// Signleton pointer
//******************************************************************************************************
Log* Log::instance()
{
    if (!m_Instance)
    {
        m_Instance = new Log("../log.txt");
    };
    return m_Instance;
};

//******************************************************************************************************
// Closes the log file gracefully
//******************************************************************************************************
Log::~Log()
{
    event("Finishing");

    if (logFile)
    {
        logFile->close();
        delete out;
        delete logFile;
    };
};

//******************************************************************************************************
// Actually logs the message to the screen and to the logfile if it exists
//******************************************************************************************************
void Log::event(QString message)
{
#if MULTICORE
    QMutexLocker locker(&mutex);
#endif

    QString str;
    str = QDateTime::currentDateTime().toString("yy-MM-dd | hh-mm-ss | ") + message;
    append(str);

    if (logFile)
    {
        *out << str << endl;
        out->flush();
    };
};
