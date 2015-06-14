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

#include "road.h"
#include "vehicle.h"
#include "junction.h"

#include <QDebug>
#include <QVector2D>

/*************************************************************************************/
/************************ Road along which vehicles can travel ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Road::Road( Junction* start, Junction* end, int weight )
{
  // set private variables
  m_startJunction = start;
  m_endJunction   = end;
  m_trafficWeight = weight;
  m_startSpeed    = 30.0;
  m_endSpeed      = 40.0;
  m_roadLength    = QVector2D(start->pos() - end->pos()).length();

  // register road with start junction with weight
  start->associate( this, weight );
}

/*************************************** tick ****************************************/

void Road::tick()
{
  // simulate 1 time unit step
  //qDebug("DEBUG Road::tick");

  for( int v=0 ; v<m_vehicleList.size() ; v++ )
  {
    Vehicle*  vehicle = m_vehicleList.at(v);
    float     pos     = m_vehiclePosList.at(v);
    qDebug("DEBUG Road::tick - road %p vehicle %p @ %f", this, vehicle, pos);

    float     speed   = roadSpeed( pos ) * vehicle->speedFactor();
    m_vehiclePosList[v] += speed / m_roadLength;
    qDebug("DEBUG Road::tick - roadS %f vehSF %f len %f => %f",
           roadSpeed( pos ), vehicle->speedFactor(), m_roadLength, m_vehiclePosList[v]);
  }
}

/*************************************** add *****************************************/

void Road::add( Vehicle* vehicle )
{
  // add vehicle to the road
  qDebug("DEBUG Road::add");

  m_vehicleList.append( vehicle );
  m_vehiclePosList.append( float(0.0) );
}

/************************************ roadSpeed **************************************/

float Road::roadSpeed( float pos )
{
  // return speed of road at position 'pos'

  return m_startSpeed + pos*( m_endSpeed - m_startSpeed );
}
