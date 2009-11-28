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

/*************************************** tick ****************************************/

void Junction::tick()
{
  // simulate 1 time unit step
  qDebug("DEBUG Junction::tick");

}