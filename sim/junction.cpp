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

#include "junction.h"
#include "trafficgenerator.h"
#include "road.h"

#include <QDebug>

/*************************************************************************************/
/**************************** Junction at each end of road ***************************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Junction::Junction( float x, float y, TrafficGenerator* gen )
{
  // set private variables
  m_x                = x;
  m_y                = y;
  m_trafficGenerator = gen;
  m_weightSum        = 0;
}

/************************************ associate **************************************/

void Junction::associate( Road* road, int weight )
{
  // register road & traffic weight with start junction
  m_roadList.append( road );
  m_weightSum += weight;
}

/*************************************** tick ****************************************/

void Junction::tick( int time )
{
  // simulate 1 time unit step
  //qDebug("DEBUG Junction::tick");

  // if no roads associated then no point in generating traffic
  if ( m_roadList.empty() ) return;

  // run traffic generator, if no vehicle then return immediately
  Vehicle*  vehicle = m_trafficGenerator->generate( time );
  if ( vehicle == 0 ) return;

  // if only one road associated, then add vehicle to that road
  if ( m_roadList.count() == 1 )
  {
    m_roadList[0]->add( vehicle );
    return;
  }

  // multiple road starts associated with junction
  int rand = qrand() % m_weightSum;
  foreach( Road* road, m_roadList )
  {
    if ( rand < road->weight() )
    {
      road->add( vehicle );
      return;
    }
    rand -= road->weight();
  }

  qDebug("WARNING Junction::tick - vehicle not allocated to a road!");
}
