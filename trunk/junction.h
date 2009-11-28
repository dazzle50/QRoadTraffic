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

#ifndef JUNCTION_H
#define JUNCTION_H

class TrafficGenerator;

/*************************************************************************************/
/**************************** Junction at each end of road ***************************/
/*************************************************************************************/

class Junction
{
public:
  Junction( float, float, TrafficGenerator* );                 // constructor

  void  tick();                               // simulate 1 time unit step

private:
  float               m_x;                    // junction location x coordinate
  float               m_y;                    // junction location y coordinate
  TrafficGenerator*   m_trafficGenerator;     // traffic generator
};

#endif // JUNCTION_H
