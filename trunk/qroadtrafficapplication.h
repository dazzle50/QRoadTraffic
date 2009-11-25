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

#ifndef QROADTRAFFICAPPLICATION_H
#define QROADTRAFFICAPPLICATION_H

class Road;
class Junction;

#include <QApplication>

/*************************************************************************************/
/************************ Main QRoadTraffic application class ************************/
/*************************************************************************************/

class QRoadTrafficApplication : public QApplication
{
public:
  QRoadTrafficApplication( int argc, char *argv[] );            // constructor

  float distribute( float, float );
  float distribute( float, float, float, float );

  QList<Road*>         roadList;        // list of one-way roads
  QList<Junction*>     junctionList;    // list of road junctions
  int                  time;            // simulated time
};

#endif // QROADTRAFFICAPPLICATION_H
