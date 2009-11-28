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

#ifndef SIMULATION_H
#define SIMULATION_H

class Road;
class Junction;

#include <QList>

/*************************************************************************************/
/*********************** Holds the simulation for QRoadTraffic ***********************/
/*************************************************************************************/

class Simulation
{
public:
  Simulation();                                   // constructor

  void  tick();                                   // simulate 1 time unit step
  float distribute(float, float);                 // distribute 0->1 to new curve 0->1
  float distribute(float, float, float, float);   // distribute 0->1 to new curve min->max

private:
  int                  m_time;            // simulated time
  QList<Road*>         m_roadList;        // list of one-way roads
  QList<Junction*>     m_junctionList;    // list of road junctions
};

#endif // SIMULATION_H
