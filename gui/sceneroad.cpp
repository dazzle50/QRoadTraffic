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
#include <QTabWidget>
#include <QFormLayout>
#include <QTableWidget>

/*************************************************************************************/
/********************** Represents a simulated road on GUI scene *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneRoad::SceneRoad( SceneJunction* sj )
{
  // initialise private variables
  m_start = sj;
  m_end   = 0;
  m_properties = 0;
  m_name       = new QLineEdit();
  m_seLanes    = new QSpinBox();
  m_esLanes    = new QSpinBox();

  // set edit widget values
  m_seLanes->setMaximum( 5 );
  m_seLanes->setMinimum( 0 );
  m_seLanes->setValue( 1 );
  m_esLanes->setMaximum( 5 );
  m_esLanes->setMinimum( 0 );
  m_esLanes->setValue( 1 );

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
  polygon << m_start->pos() << m_bends << m_end->pos();
  for ( int i = m_bends.size(); i > 0; --i )
    polygon << m_bends.at(i-1);
  polygon << m_start->pos();
  setPolygon( polygon );
}

/************************************** addBend **************************************/

void SceneRoad::addBend( QPointF pos )
{
  // need to add bend at correct position in bends list
  int               segment = -1;
  qreal             best    = 9e9;
  QVector<QPointF>  road;
  road << m_start->pos() << m_bends << m_end->pos();

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
  m_sceneBends.insert( segment, sceneBend );
  m_bends.insert( segment, pos );
  adjust();
}

/************************************* bendMoved *************************************/

void SceneRoad::bendMoved( SceneRoadBend* bend )
{
  // receives msg that bend has been moved
  int  i = m_sceneBends.indexOf( bend );
  m_bends[i] = bend->pos();
  adjust();
}

/************************************ deleteBend *************************************/

void SceneRoad::deleteBend( SceneRoadBend* bend )
{
  // remove bend from road and delete scene item
  int  i = m_sceneBends.indexOf( bend );
  m_bends.remove( i );
  m_sceneBends.remove( i );
  delete bend;

  adjust();
}

/************************************* setBends **************************************/

void SceneRoad::setBends( QList<SceneRoadBend*> list )
{
  // set road bends to that in list
  m_bends.clear();
  m_sceneBends.clear();
  foreach( SceneRoadBend* bend, list )
  {
    m_bends.append( bend->pos() );
    m_sceneBends.append( bend );
  }
  adjust();
}

/*********************************** updateNewRoad ***********************************/

void SceneRoad::updateNewRoad( QPointF pos )
{
  // update end of new road to point
  QPolygonF polygon;
  polygon << m_start->pos() << pos;
  setPolygon( polygon );
}

/********************************** completeNewRoad **********************************/

void SceneRoad::completeNewRoad( SceneJunction* ej )
{
  // complete new road
  m_end = ej;
  adjust();

  // register this road with the two scene junctions
  m_end->addRoad( this );
  m_start->addRoad( this );

  // TODO create associated sim road ...
}

/*************************************** angle ***************************************/

float SceneRoad::angle( SceneJunction* junc )
{
  // return angle of road into junction
  QPointF  pos;
  if ( junc == m_start )
  {
    if ( m_bends.isEmpty() ) pos = m_end->pos();
    else                     pos = m_bends.first();
  }
  else
  {
    if ( m_bends.isEmpty() ) pos = m_start->pos();
    else                     pos = m_bends.last();
  }

  QLineF line = QLineF( junc->pos(), pos );
  return 90.0 - line.angle();
}

/********************************* deleteProperties **********************************/

void SceneRoad::deleteProperties()
{
  // delete pre-initialise properties widgets and dialog box
  delete m_name;
  delete m_seLanes;
  delete m_esLanes;
  if ( m_properties ) delete m_properties;
}

/********************************** showProperties ***********************************/

void SceneRoad::showProperties()
{
  // if properties window already exists, bring to front
  if ( m_properties )
  {
     m_properties->show();
     m_properties->raise();
     return;
  }

  // properies window doesn't exist, so create basic properties window widget
  m_properties = new QTabWidget( 0 );
  m_properties->setWindowFlags( Qt::Tool );
  m_properties->setAttribute( Qt::WA_DeleteOnClose, false );
  m_properties->setMinimumSize( 140, 95 );
  m_properties->resize( 140, 95 );
  m_properties->setWindowTitle( "Road properties" );
  m_properties->show();

  // create the two tab widgets
  QWidget*       editWidget     = new QWidget();
  QTableWidget*  sectionsWidget = new QTableWidget( 3, 3 );
  m_properties->addTab( editWidget,     "Edit" );
  m_properties->addTab( sectionsWidget, "Sections" );

  // populate the data widget
  editWidget->setContentsMargins( -5, -5, -5, -5 );
  QFormLayout*  dataLayout  = new QFormLayout( editWidget );
  dataLayout->setVerticalSpacing( 3 );
  dataLayout->addRow( "Name",      m_name );
  dataLayout->addRow( "Lanes S-E", m_seLanes );
  dataLayout->addRow( "Lanes E-S", m_esLanes );

  //=============================================================================================
  // TODO lots more ........ !!!
}
