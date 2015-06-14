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

#include "scene.h"
#include "scenejunction.h"
#include "sceneroad.h"
#include "sceneroadbend.h"
#include "scenevehicle.h"
#include "../sim/simulation.h"
#include "../sim/junction.h"
#include "../sim/trafficgenerator.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QXmlStreamReader>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Scene::Scene( QWidget* mainWindow ) : QGraphicsScene()
{
  Q_UNUSED( mainWindow )
  // create invisible item to provide default top-left anchor to scene
  addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );

  // initialise private variables
  m_newRoad = 0;
}

/********************************* contextMenuEvent **********************************/

void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  // depending on what the user clicked we want to show different context menus
  QMenu  menu;
  qreal  x   = event->scenePos().x();
  qreal  y   = event->scenePos().y();

  // if user in process of adding new road, show cancel new road context menu
  if ( m_newRoad )
  {
    QAction*  cancelNewRoad = menu.addAction("Cancel new road");
    if ( menu.exec( event->screenPos() ) == cancelNewRoad )
    {
      removeItem( m_newRoad );
      delete m_newRoad;
      m_newRoad = 0;
    }
    return;
  }

  // if user clicked a road, display road context menu
  SceneRoad*  road = dynamic_cast<SceneRoad*>( itemAt( x, y, QTransform() ) );
  if ( road )
  {
    QAction*  roadProp = menu.addAction("Road properties");
    QAction*  addBend  = menu.addAction("Add bend");
    QAction*  delRoad  = menu.addAction("Delete road");
    QAction*  action   = menu.exec( event->screenPos() );

    if ( action == roadProp )
    {
      road->showProperties();
      return;
    }

    if ( action == addBend )
    {
      road->addBend( event->scenePos() );
      return;
    }

    if ( action == delRoad )
    {
      removeRoad( road );
      return;
    }

    return;
  }

  // if user clicked a junction, display junction context menu
  SceneJunction*  junction = dynamic_cast<SceneJunction*>( itemAt( x, y, QTransform() ) );
  if ( junction )
  {
    QAction*  junctionProp = menu.addAction("Junction properties");
    QAction*  addRoad      = menu.addAction("Add road");
    QAction*  delJunction  = menu.addAction("Delete junction");
    QAction*  action       = menu.exec( event->screenPos() );

    if ( action == addRoad )
    {
      m_newRoad = new SceneRoad( junction );
      addItem( m_newRoad );

      // move mouse cursor by one pixel to trigger a mouseMoveEvent
      QCursor::setPos( QCursor::pos() + QPoint(1,0) );
      return;
    }

    if ( action == junctionProp )
    {
      junction->showProperties();
      return;
    }

    if ( action == delJunction )
    {
      if ( junction->hasRoads() )
        QMessageBox::information( m_mainWindow, "Delete Junction",
                                  "Remove all associated roads before deleting junction.");
      else
      {
        removeItem( junction );
        delete junction;
      }
      return;
    }

    return;
  }

  // if user clicked a road bend, display road bend context menu
  SceneRoadBend*  roadBend = dynamic_cast<SceneRoadBend*>( itemAt( x, y, QTransform() ) );
  if ( roadBend )
  {
    QAction*  roadProp = menu.addAction("Road properties");
    QAction*  delBend  = menu.addAction("Delete bend");
    QAction*  action   = menu.exec( event->screenPos() );

    if ( action == roadProp )
    {
      roadBend->road()->showProperties();
      return;
    }

    if ( action == delBend )
    {
      roadBend->road()->deleteBend( roadBend );
      return;
    }

    return;
  }

  // user didn't click on item, therefore display landscape context menu
  QAction*  addJunction = menu.addAction("Add Junction");
  if ( menu.exec( event->screenPos() ) == addJunction )
  {
    Junction* newJunc = new Junction( x, y, new TrafficGenerator() );
    addItem( new SceneJunction( newJunc ) );
  }
}

/********************************* mousePressEvent ***********************************/

void  Scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  // if not adding new road, just call base mousePressEvent to handle
  if ( m_newRoad == 0 )
  {
    QGraphicsScene::mousePressEvent( event );
    return;
  }

  // check if user clicked a juntion to end new road
  qreal  x   = event->scenePos().x();
  qreal  y   = event->scenePos().y();
  SceneJunction*  junction = dynamic_cast<SceneJunction*>( itemAt( x, y, QTransform() ) );
  if ( junction )
  {
    // don't complete road if clicked junction is new road start junction
    if ( junction == m_newRoad->startJunction() ) return;

    // don't complete road if road already exists between the two junctions
    if ( roadExists( junction, m_newRoad->startJunction() )) return;

    // complete new road
    m_newRoad->completeNewRoad( junction );
    m_newRoad = 0;
  }
}

/********************************** mouseMoveEvent ***********************************/

void  Scene::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
  // if adding new road, update new road position
  if ( m_newRoad ) m_newRoad->updateNewRoad( event->scenePos() );

  QGraphicsScene::mouseMoveEvent( event );
}

/****************************** deletePropertiesDialogs ******************************/

void  Scene::deletePropertiesDialogs()
{
  // delete all properties dialog widgets, typically just before deleting scene
    foreach( QGraphicsItem* item, items() )
    {
      // delete each junction properties dialog
      SceneJunction*  junction = dynamic_cast<SceneJunction*>( item );
      if ( junction ) junction->deleteProperties();

      // delete each road properties dialog
      SceneRoad*  road = dynamic_cast<SceneRoad*>( item );
      if ( road ) road->deleteProperties();
    }
}

/************************************ removeRoad *************************************/

void  Scene::removeRoad( SceneRoad* road )
{
  // removes road from scene including junction associations
  foreach( QGraphicsItem* item, items() )
  {
    SceneJunction*  junction = dynamic_cast<SceneJunction*>( item );
    if ( junction ) junction->removeRoad( road );
  }

  removeItem( road );
  delete road;
}

/************************************ roadExists *************************************/

bool  Scene::roadExists( SceneJunction* j1, SceneJunction* j2 )
{
  // returns TRUE if road already exists between these two scene junctions
  foreach( QGraphicsItem* item, items() )
  {
    SceneRoad*  road = dynamic_cast<SceneRoad*>( item );
    if ( road )
    {
      if ( j1 == road->startJunction() && j2 == road->endJunction() ) return true;
      if ( j2 == road->startJunction() && j1 == road->endJunction() ) return true;
    }
  }

  return false;
}

/************************************ readStream *************************************/

void  Scene::readStream( QXmlStreamReader* stream )
{
  // prepare working variables
  QList<SceneJunction*>  junc_lookup;   // lookup of junctions against id in stream
  QList<SceneRoadBend*>  bends;         // list of bends for road
  SceneRoad*             sRoad = 0;     // current road

  // read station data from xml stream
  while ( !stream->atEnd() )
  {
    stream->readNext();

    // create junctions also building lookup list against id
    if ( stream->isStartElement() && stream->name() == "junction" )
    {
      int id = -1;
      qreal x = 0.0, y = 0.0;
      QString name, gen = "None";
      foreach( QXmlStreamAttribute attribute, stream->attributes() )
      {
        if ( attribute.name() == "id"        ) id   = attribute.value().toString().toInt();
        if ( attribute.name() == "x"         ) x    = attribute.value().toString().toDouble();
        if ( attribute.name() == "y"         ) y    = attribute.value().toString().toDouble();
        if ( attribute.name() == "name"      ) name = attribute.value().toString();
        if ( attribute.name() == "generator" ) gen  = attribute.value().toString();
      }

      Junction*       newJunc = new Junction( x, y, new TrafficGenerator() );
      SceneJunction*  sJunc   = new SceneJunction( newJunc );
      sJunc->setName( name );
      sJunc->setGenerator( gen );
      addItem( sJunc );
      junc_lookup.append( sJunc );
      Q_UNUSED( id )
    }

    // create roads
    if ( stream->isStartElement() && stream->name() == "road" )
    {
      int s = -1, e = -1;
      int seL = 1, esL = 1;
      QString name;
      foreach( QXmlStreamAttribute attribute, stream->attributes() )
      {
        if ( attribute.name() == "start"    ) s    = attribute.value().toString().toInt();
        if ( attribute.name() == "end"      ) e    = attribute.value().toString().toInt();
        if ( attribute.name() == "name"     ) name = attribute.value().toString();
        if ( attribute.name() == "se-lanes" ) seL  = attribute.value().toString().toInt();
        if ( attribute.name() == "es-lanes" ) esL  = attribute.value().toString().toInt();
      }

      sRoad = new SceneRoad( junc_lookup.at(s) );
      sRoad->completeNewRoad( junc_lookup.at(e) );
      sRoad->setName( name );
      sRoad->setLanes( seL, esL );
      addItem( sRoad );
    }

    // collect bends for the current road
    if ( stream->isStartElement() && stream->name() == "bend" )
    {
      qreal x = 0.0, y = 0.0;
      foreach( QXmlStreamAttribute attribute, stream->attributes() )
      {
        if ( attribute.name() == "x"  ) x  = attribute.value().toString().toDouble();
        if ( attribute.name() == "y"  ) y  = attribute.value().toString().toDouble();
      }

      bends.append( new SceneRoadBend( sRoad, QPointF(x,y) ) );
    }

    // when at end of current road element set the collected bends
    if ( stream->isEndElement() && stream->name() == "road" )
    {
      if ( sRoad )
      {
        sRoad->setBends( bends );
        sRoad = 0;
        bends.clear();
      }
    }
  }
}
