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

#include "sceneroad.h"
#include "scenejunction.h"

#include <QPen>
#include <QLineF>

/*************************************************************************************/
/********************** Represents a simulated road on GUI scene *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneRoad::SceneRoad( SceneJunction* sj )
{
  // initialise private variables
  start = sj;
  end   = 0;

  // create a new road starting from start junction
  qreal  x = sj->x();
  qreal  y = sj->y();

  // road scene item is black line
  setLine( x, y, x+1, y+1 );
  setPen( QPen( Qt::black, 3 ) );
  setZValue( 50 );
}

/************************************** adjust ***************************************/

void SceneRoad::adjust()
{
  // update the road line to the junction positions
  QLineF  road;
  road.setP1( start->pos() );
  road.setP2( end->pos() );
  setLine( road );
}

/*********************************** updateNewRoad ***********************************/

void SceneRoad::updateNewRoad( QPointF pos )
{
  // update end of new road to point
  QLineF  road( line() );
  road.setP2( pos );
  setLine( road );
}

/********************************** completeNewRoad **********************************/

void SceneRoad::completeNewRoad( SceneJunction* ej )
{
  // complete new road
  end = ej;
  adjust();

  // register this road with the two scene junctions
  end->addRoad( this );
  start->addRoad( this );

  // TODO create associated sim road ...
}
