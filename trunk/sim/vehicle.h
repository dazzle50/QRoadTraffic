/***************************************************************************
 *   Copyright (C) 2013 by Richard Crook                                   *
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

#ifndef VEHICLE_H
#define VEHICLE_H

/*************************************************************************************/
/************************* Vehicle that travels along a road *************************/
/*************************************************************************************/

class Vehicle
{
public:
  Vehicle();                                           // constructor

  int   id() const { return m_id; }                    // return vehicle id
  float length() const { return m_length; }            // return vehicle length
  float gapDistance() const { return m_gapDistance; }  // return vehicle gap distance
  float gapTime() const { return m_gapTime; }          // return vehicle gap time
  float speedFactor() const { return m_speedFactor; }  // return vehicle speed factor

private:
  static int m_idCount;             // unique vehicle count
  int    m_id;                      // unqiue vehicle number
  float  m_length;                  // length of vehicle
  float  m_gapDistance;             // minimum gap in queueing traffic
  float  m_gapTime;                 // minimum gap in time units in moving traffic
  float  m_speedFactor;             // vehicle speed factor vs road speed
};

#endif // VEHICLE_H
