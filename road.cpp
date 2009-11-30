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

#include "road.h"
#include "vehicle.h"
#include "junction.h"

#include <QDebug>

/*************************************************************************************/
/************************ Road along which vehicles can travel ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Road::Road( Junction* start, int weight, Junction* end )
{
  // set private variables
  m_startJunction = start;
  m_endJunction   = end;

  // register road with start junction with weight
  start->associate( this, weight );
}

/*************************************** tick ****************************************/

void Road::tick()
{
  // simulate 1 time unit step
  //qDebug("DEBUG Road::tick");

  foreach( Vehicle* vehicle, m_vehicleList )
    vehicle->tick();
}

/*************************************** add *****************************************/

void Road::add( Vehicle* vehicle )
{
  // // add vehicle to the road
  qDebug("DEBUG Road::add");

  m_vehicleList.append( vehicle );
}
