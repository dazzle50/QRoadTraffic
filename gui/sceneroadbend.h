/***************************************************************************
 *   Copyright (C) 2015 by Richard Crook                                   *
 *   https://github.com/dazzle50/QRoadTraffic                              *
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

#ifndef SCENEROADBEND_H
#define SCENEROADBEND_H

class SceneRoad;

#include <QGraphicsPolygonItem>

/*************************************************************************************/
/************** Represents a bend point on a simulated road on GUI scene *************/
/*************************************************************************************/

class SceneRoadBend : public QGraphicsPolygonItem
{
public:
  SceneRoadBend( SceneRoad*, QPointF );           // constructor

  SceneRoad*  road()                              // returns road associated with this bend
                { return m_road; }

  QVariant	  itemChange( GraphicsItemChange , const QVariant& );  // receive item changes

private:
  SceneRoad*   m_road;                // road associated with this bend
};

#endif // SCENEROADBEND_H
