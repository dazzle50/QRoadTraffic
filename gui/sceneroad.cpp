/***************************************************************************
 *   Copyright (C) 2012 by Richard Crook                                   *
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
#include "sceneroadbend.h"
#include "scenejunction.h"

#include <math.h>
#include <QPen>
#include <QWidget>
#include <QLineF>
#include <QVector2D>
#include <QGraphicsScene>

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
  QPolygonF polygon;
  polygon << QPointF(x,y) << QPointF(x+1,y+1);
  setPolygon( polygon );
  setPen( QPen( Qt::black, 3 ) );
  setZValue( 50 );
}

/************************************** adjust ***************************************/

void SceneRoad::adjust()
{
  // update the road polygon to the junction & bend positions
  QPolygonF polygon;
  polygon << start->pos() << bends << end->pos();
  for ( int i = bends.size(); i > 0; --i )
    polygon << bends.at(i-1);
  polygon << start->pos();
  setPolygon( polygon );
}

/************************************** addBend **************************************/

void SceneRoad::addBend( QPointF pos )
{
  // need to add bend at correct position in bends list
  int               segment = -1;
  qreal             best    = 9e9;
  QVector<QPointF>  road;
  road << start->pos() << bends << end->pos();

  for ( int i = 0; i < road.size()-1; ++i )
  {
    // t =  (linedirection . (point - lineorigin)) / (linedirection . linedirection)
    QVector2D  ld( road.at(i+1) - road.at(i) );
    qreal      t = QVector2D::dotProduct( ld, QVector2D( pos-road.at(i) )) /
                   QVector2D::dotProduct( ld, ld );
    if ( t < 0.0 ) continue;
    if ( t > 1.0 ) continue;

    // calculate distance of pos from road segment
    qreal x0 = pos.x();
    qreal y0 = pos.y();
    qreal x1 = road.at(i).x();
    qreal y1 = road.at(i).y();
    qreal x2 = road.at(i+1).x();
    qreal y2 = road.at(i+1).y();

    qreal d = fabs((x2-x1)*(y1-y0)-(x1-x0)*(y2-y1)) /
              sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

    if ( d < best )
    {
      segment = i;
      best    = d;
    }
  }

  SceneRoadBend*  sceneBend;
  sceneBend = new SceneRoadBend( this, pos );
  sceneBends.insert( segment, sceneBend );
  bends.insert( segment, pos );
  adjust();
}

/************************************* bendMoved *************************************/

void SceneRoad::bendMoved( SceneRoadBend* bend )
{
  // receives msg that bend has been moved
  int  i = sceneBends.indexOf( bend );
  bends[i] = bend->pos();
  adjust();
}

/************************************ deleteBend *************************************/

void SceneRoad::deleteBend( SceneRoadBend* bend )
{
  // remove bend from road and delete scene item
  int  i = sceneBends.indexOf( bend );
  bends.remove( i );
  sceneBends.remove( i );
  delete bend;

  adjust();
}

/************************************* setBends **************************************/

void SceneRoad::setBends( QList<SceneRoadBend*> list )
{
  // set road bends to that in list
  bends.clear();
  sceneBends.clear();
  foreach( SceneRoadBend* bend, list )
  {
    bends.append( bend->pos() );
    sceneBends.append( bend );
  }
  adjust();
}

/*********************************** updateNewRoad ***********************************/

void SceneRoad::updateNewRoad( QPointF pos )
{
  // update end of new road to point
  QPolygonF polygon;
  polygon << start->pos() << pos;
  setPolygon( polygon );
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

/********************************** showProperties ***********************************/

void SceneRoad::showProperties()
{
  qDebug("SceneRoad::showProperties()  %p", this);
  // TODO

  QWidget* prop = new QWidget( 0, Qt::Tool );
  prop->setAttribute( Qt::WA_DeleteOnClose, true );
  prop->resize( 200, 101 );
  prop->setWindowTitle( "Road properties" );
  prop->show();
}
