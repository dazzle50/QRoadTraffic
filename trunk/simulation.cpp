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

#include "simulation.h"
#include "junction.h"
#include "road.h"
#include "trafficgenerator.h"

#include <QDebug>

/*************************************************************************************/
/*********************** Holds the simulation for QRoadTraffic ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Simulation::Simulation()
{
  // initialise private variables
  m_time = 0;

  // DUMMY test code ###########################################
  // create traffic generator
  TrafficGenerator*  gen = new TrafficGenerator();

  // create 3 junctions
  //                j2
  //       j1                j3
  Junction*  j1 = new Junction( 200, 400, gen );
  Junction*  j2 = new Junction( 400, 200, gen );
  Junction*  j3 = new Junction( 600, 400, gen );
  m_junctionList.append( j1 );
  m_junctionList.append( j2 );
  m_junctionList.append( j3 );

  // create roads connecting the junctions
  Road*  r12 = new Road( j1, 100, j2 );
  Road*  r21 = new Road( j2, 100, j1 );
  Road*  r23 = new Road( j2, 100, j3 );
  Road*  r31 = new Road( j3, 100, j1 );
  m_roadList.append( r12 );
  m_roadList.append( r21 );
  m_roadList.append( r23 );
  m_roadList.append( r31 );

  for( int count=0 ; count<15 ; count++ )
    tick();
}

/************************************ distribute *************************************/

float Simulation::distribute(float in, float shape)
{
  // returns float between 0 and 1 by distributing 'in' parameter to curve defined by 'shape' parameter
  // =IF(A<0.5;(2*bb*bb+bb)*((1/2/bb)-1/(2*A+2*bb));1-(2*bb*bb+bb)*((1/2/bb)-1/(2*(1-A)+2*bb)))

  if ( in<0.0 || in>1.0 )
  {
    qDebug("WARNING Simulation::distribute in=%f - must be between 0.0 and 1.0", in);
    return 0.0;
  }

  if ( shape <= 0.0 )
  {
    qDebug("WARNING Simulation::distribute shape=%f - must be greater than zero, typically 0.1", shape);
    return 0.0;
  }

  float out;
  if (in < 0.5)
    out = (2.0*shape*shape+shape)*((0.5/shape)-0.5/(in+shape));
  else
    out = 1.0-(2.0*shape*shape+shape)*((0.5/shape)-0.5/(1.0-in+shape));

  // qDebug("DEBUG Simulation::distribute %f %f => %f", in, shape, out);
  return out;
}

/************************************ distribute *************************************/

float Simulation::distribute(float in, float shape, float min, float max)
{
  // returns float between 'min' and 'max' by distributing 'in' parameter to curve defined by 'shape' parameter
  float out = distribute( in, shape );

  // qDebug("DEBUG Simulation::distribute %f %f %f %f => %f", in, shape, min, max, min+out*(max-min));
  return min + out*(max-min);
}

/*************************************** rand ****************************************/

float Simulation::rand()
{
  // returns a random number between 0.0 and 1.0
  return float(qrand()) / RAND_MAX;
}

/*************************************** tick ****************************************/

void Simulation::tick()
{
  // simulate 1 time unit step
  qDebug("DEBUG Simulation::tick - time=%i", m_time);

  foreach( Road* road, m_roadList )
    road->tick();
  foreach( Junction* junction, m_junctionList )
    junction->tick( m_time );

  m_time++;
}
