/***************************************************************************
 *   Copyright (C) 2009 by Richard Crook                                   *
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

#include "scene.h"
#include "scenejunction.h"
#include "sceneroad.h"
#include "scenevehicle.h"
#include "../sim/simulation.h"

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

/********************************* addSimulatedItems *********************************/

void Scene::addSimulatedItems()
{
  // add simulated items to the scene

  // add junctions
  foreach( Junction* junction, sim->junctions() )
    new SceneJunction( this, junction );

  // add roads
  foreach( Road* road, sim->roads() )
    new SceneRoad( this, road );

  // add vehicles
  foreach( Vehicle* vehicle, sim->vehicles() )
    new SceneVehicle( this, vehicle );
}
