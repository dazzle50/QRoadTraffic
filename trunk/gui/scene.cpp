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

  addSimulatedItems();
}

/********************************* contextMenuEvent **********************************/

void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  // we only want to display a menu if user clicked a station
  qreal      x        = event->scenePos().x();
  qreal      y        = event->scenePos().y();
  // SceneJunction*  junction = dynamic_cast<SceneJunction*>( itemAt( x, y ) );

  // display context menu and action accordingly
  QMenu     menu;
  QAction*  addJunctionAction = menu.addAction("Add Junction");
  if ( menu.exec( event->screenPos() ) == addJunctionAction )
  {
    Junction* j = new Junction( x, y, new TrafficGenerator() );
    addItem( new SceneJunction( j ) );
    qDebug( qPrintable( QString("Junction added at %1,%2").arg(x).arg(y) ) );
  }
}

/********************************* addSimulatedItems *********************************/

void Scene::addSimulatedItems()
{
  // add simulated items to the scene

  // add junctions
  foreach( Junction* junction, sim->junctions() )
    new SceneJunction( junction );

  // add roads
  foreach( Road* road, sim->roads() )
    new SceneRoad( this, road );

  // add vehicles
  foreach( Vehicle* vehicle, sim->vehicles() )
    new SceneVehicle( this, vehicle );
}
