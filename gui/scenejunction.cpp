/***************************************************************************
 *   Copyright (C) 2011 by Richard Crook                                   *
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

#include "scenejunction.h"
#include "../sim/junction.h"

#include <QPen>

/*************************************************************************************/
/******************** Represents a simulated junction on GUI scene *******************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneJunction::SceneJunction( Junction* junction )
{
  // Junction scene item is a red circle with a black border
  float   radius = 6.0;
  QPointF pos = junction->pos();

  setRect( pos.x()-radius, pos.y()-radius, 2*radius, 2*radius );
  setPen( QPen(Qt::black) );
  setBrush( Qt::red );
  setZValue( 100 );
}
