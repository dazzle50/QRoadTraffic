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

#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QAction>

#include "scene.h"
#include "scenejunction.h"
#include "sceneroad.h"
#include "scenevehicle.h"
#include "../sim/simulation.h"
#include "../sim/junction.h"
#include "../sim/trafficgenerator.h"

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Scene::Scene() : QGraphicsScene()
{
  // create invisible item to provide default top-left anchor to scene
  addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );

  // initialise private variables
  newRoad = 0;

  addSimulatedItems();
}

/********************************* contextMenuEvent **********************************/

void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  // depending on what the user clicked we want to show different context menus
  QMenu  menu;
  qreal  x   = event->scenePos().x();
  qreal  y   = event->scenePos().y();

  // if user in process of adding new road, show cancel new road context menu
  if ( newRoad )
  {
    QAction*  cancelNewRoad = menu.addAction("Cancel new road");
    if ( menu.exec( event->screenPos() ) == cancelNewRoad )
    {
      removeItem( newRoad );
      delete newRoad;
      newRoad = 0;
    }
    return;
  }

  // if user clicked a junction, display junction context menu
  SceneJunction*  junction = dynamic_cast<SceneJunction*>( itemAt( x, y ) );
  if ( junction )
  {
    QAction*  junctionProp = menu.addAction("Junction properties");
    QAction*  addRoad      = menu.addAction("Add Road");
    QAction*  delJunction  = menu.addAction("Delete Junction");
    QAction*  action       = menu.exec( event->screenPos() );

    if ( action == addRoad )
    {
      // qDebug("Scene::contextMenuEvent Junction - Add Road");
      newRoad = new SceneRoad( junction );
      addItem( newRoad );
      // move mouse cursor by one pixel to trigger a mouseMoveEvent
      QCursor::setPos( QCursor::pos() + QPoint(1,0) );
      return;
    }

    if ( action == junctionProp )
    {
      qDebug("Scene::contextMenuEvent Junction - Properties");
      return;
    }

    if ( action == delJunction )
    {
      qDebug("Scene::contextMenuEvent Junction - Delete");
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
    qDebug( qPrintable( QString("Junction added at %1,%2").arg(x).arg(y) ) );
  }
}

/********************************* mousePressEvent ***********************************/

void  Scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  // if not adding new road, just call base mousePressEvent to handle
  if (newRoad == 0)
  {
    QGraphicsScene::mousePressEvent( event );
    return;
  }

  // check if user clicked a juntion to end new road
  qreal  x   = event->scenePos().x();
  qreal  y   = event->scenePos().y();
  SceneJunction*  junction = dynamic_cast<SceneJunction*>( itemAt( x, y ) );
  if ( junction )
  {
    // check clicked junction is not the road start junction
    if ( junction != newRoad->startJunction() )
    {
      newRoad->completeNewRoad( junction );
      newRoad = 0;
    }
  }
}

/********************************** mouseMoveEvent ***********************************/

void  Scene::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
  // if not adding new road, just call base mouseMoveEvent to handle
  if (newRoad == 0)
  {
    QGraphicsScene::mouseMoveEvent( event );
    return;
  }

  // update new road
  newRoad->updateNewRoad( event->scenePos() );
}

/********************************* addSimulatedItems *********************************/

void Scene::addSimulatedItems()
{
  // add simulated items to the scene (NO LONGER NEEDED??? TODO)

  // add junctions
  foreach( Junction* junction, sim->junctions() )
    new SceneJunction( junction );

  // add roads
  //foreach( Road* road, sim->roads() )
    //new SceneRoad( this, road );

  // add vehicles
  foreach( Vehicle* vehicle, sim->vehicles() )
    new SceneVehicle( this, vehicle );
}
