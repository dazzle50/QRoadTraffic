/***************************************************************************
 *   Copyright (C) 2013 by Richard Crook                                   *
 *   http://code.google.com/p/qroadtraffic/                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef SCENEJUNCTIONVIEW_H
#define SCENEJUNCTIONVIEW_H

class SceneJunction;

#include <QWidget>

/*************************************************************************************/
/********************** Displays a scene junction showing lanes **********************/
/*************************************************************************************/

class SceneJunctionView : public QWidget
{
public:
  SceneJunctionView( SceneJunction* );              // constructor

protected:
  void   paintEvent( QPaintEvent *event );          // receives paint events

private:
  SceneJunction*   m_junction;                      // pointer to scene junction
};

#endif // SCENEJUNCTIONVIEW_H
