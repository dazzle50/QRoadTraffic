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
#include "../sim/simulation.h"

#include <QGraphicsEllipseItem>

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
  float radius = 5.0;
  foreach( QPointF pos, sim->junctionPoints() )
    addEllipse( pos.x()-radius, pos.y()-radius, 2*radius, 2*radius,
                QPen(Qt::black), QBrush(Qt::red) )->setZValue( 100 );

  // add roads
  QPointF start;
  foreach( QPointF pos, sim->roadPoints() )
  {
    if ( start.isNull() )
      start = pos;
    else
    {
      QLineF  lane   = QLineF( start,pos ).normalVector().unitVector();
      QPointF offset = QPointF( lane.dx(), lane.dy() );
      addLine( QLineF(start+offset,pos+offset), QPen() );
      start.rx() = 0.0;
      start.ry() = 0.0;
    }
  }

  // add vehicles
  foreach( QPointF pos, sim->vehiclePoints() )
    qDebug("VEHICLE xxxxxx");


}
