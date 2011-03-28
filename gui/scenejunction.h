/***************************************************************************
 *   Copyright (C) 2011 by Richard Crook                                   *
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

#ifndef SCENEJUNCTION_H
#define SCENEJUNCTION_H

class Junction;
class SceneRoad;

#include <QGraphicsEllipseItem>

/*************************************************************************************/
/******************** Represents a simulated junction on GUI scene *******************/
/*************************************************************************************/

class SceneJunction : public QGraphicsEllipseItem
{
private:
  QList<SceneRoad*>  roads;               // list of roads connected to junction

public:
  SceneJunction( Junction* );                                    // constructor

  void addRoad( SceneRoad* road )  { roads << road; }            // add road to roads list

  QVariant	itemChange( GraphicsItemChange , const QVariant& );  // receive item changes
};

#endif // SCENEJUNCTION_H
