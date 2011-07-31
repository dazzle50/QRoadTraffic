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

#include "sceneroadbend.h"
#include "sceneroad.h"

#include <QPen>

/*************************************************************************************/
/************** Represents a bend point on a simulated road on GUI scene *************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneRoadBend::SceneRoadBend( SceneRoad* sceneRoad, QPointF pos )
{
  // road-bend scene item is a green diamond with a black border
  road = sceneRoad;
  QPolygonF  polygon;
  polygon << QPointF(0,5) << QPointF(5,0) << QPointF(0,-5) << QPointF(-5,0);
  setPolygon( polygon );
  setPos( pos );
  setPen( QPen(Qt::black) );
  setBrush( Qt::green );
  setZValue( 50 );
  setFlags( QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIgnoresTransformations |
            QGraphicsItem::ItemSendsGeometryChanges );
  setParentItem( sceneRoad );
}

/************************************ itemChange *************************************/

QVariant	SceneRoadBend::itemChange( GraphicsItemChange change, const QVariant& value )
{
  // if the scene bend moved then adjust associated road
  if ( change == QGraphicsItem::ItemPositionHasChanged )
    road->bendMoved( this );

  return QGraphicsItem::itemChange(change, value);
}
