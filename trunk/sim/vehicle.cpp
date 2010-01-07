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

#include "vehicle.h"
#include "simulation.h"

#include <QDebug>

/*************************************************************************************/
/************************* Vehicle that travels along a road *************************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Vehicle::Vehicle()
{
  // construct random vehicle
  float rand = sim->rand();
  m_length      = sim->distribute( rand, 0.1, 1.0, 5.0 );
  m_gapDistance = sim->distribute( rand, 0.1, 0.5, 2.0 );
  m_gapTime     = sim->distribute( 1-rand, 0.1, 1.0, 3.0 );
  m_speedFactor = sim->distribute( 1-rand, 0.1, 0.5, 1.5 );
  //qDebug("DEBUG Vehicle constructor len=%f gapD=%f gapT=%f speed=%f",
  //       m_length, m_gapDistance, m_gapTime, m_speedFactor);
}
