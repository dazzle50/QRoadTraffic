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

#include "junction.h"
#include "trafficgenerator.h"
//#include "vehicle.h"
//#include "road.h"

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
}

/************************************ associate **************************************/

void Junction::associate( Road* road, int weight )
{
  // register road & traffic weight with start junction
  m_roadList.append( road );
  m_weightList.append( weight );
}

/*************************************** tick ****************************************/

void Junction::tick( int time )
{
  // simulate 1 time unit step
  qDebug("DEBUG Junction::tick");

  if ( m_roadList.empty() ) return;
  Vehicle*  vehicle = m_trafficGenerator->generate( time );
  if ( vehicle == 0 ) return;

  // TODO need to decide on which road to place vehicle!
  if ( m_roadList.count() == 1 )
  {


  }



}
