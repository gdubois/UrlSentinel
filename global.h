//*****************************************************************************
// Name:      global.h
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

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

//#undef DEBUG

#include <cassert>

// Qt includes
#include <QString>
#include <QMessageBox>
#include <QWidget>

// C++ includes

#include <memory>


namespace Global
{
void init();
const QString languagePath("Language");
const QString picturePath("Pictures");
};

void postEvent(const QString& message);

#endif // GLOBAL_H_INCLUDED

