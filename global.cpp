//*****************************************************************************
// Name:      global.cpp
// Purpose:   Application-wide functions
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
#include "global.h"

#include "Log/log.h"

// Qt includes
#include <QtGlobal>

// C++
#include <cstdlib>

//******************************************************************************************************
// Logs the event
//******************************************************************************************************
#if LOG
void postEvent(const QString& message)
{
    Log::instance()->event(message);
};
#else
void postEvent(const QString&)
{
};
#endif

