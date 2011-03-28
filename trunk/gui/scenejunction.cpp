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

#include "scenejunction.h"
#include "sceneroad.h"
#include "../sim/junction.h"

#include <QPen>

/*************************************************************************************/
/******************** Represents a simulated junction on GUI scene *******************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneJunction::SceneJunction( Junction* junction )
{
  // junction scene item is a red circle with a black border
  float   radius = 6.0;

  setRect( -radius, -radius, 2*radius, 2*radius );
  setPos( junction->pos() );
  setPen( QPen(Qt::black) );
  setBrush( Qt::red );
  setZValue( 100 );
  setFlags( QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIgnoresTransformations |
            QGraphicsItem::ItemSendsGeometryChanges );
}

/************************************ itemChange *************************************/

QVariant	SceneJunction::itemChange( GraphicsItemChange change, const QVariant& value )
{
  // if the junction moved then adjust each road connected to the junction
  if ( change == QGraphicsItem::ItemPositionChange )
  {
    foreach( SceneRoad* road, roads )
      road->adjust();
  }

  return QGraphicsItem::itemChange(change, value);
}
