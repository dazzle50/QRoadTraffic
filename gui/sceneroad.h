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

#ifndef SCENEROAD_H
#define SCENEROAD_H

class SceneJunction;
class SceneRoadBend;

#include <QGraphicsPolygonItem>

/*************************************************************************************/
/********************** Represents a simulated road on GUI scene *********************/
/*************************************************************************************/

class SceneRoad : public QGraphicsPolygonItem
{
private:
  SceneJunction*           start;        // SceneJunction at road start
  SceneJunction*           end;          // SceneJunction at road end
  QVector<QPointF>         bends;        // bends between the road start & end
  QVector<SceneRoadBend*>  sceneBends;   // SceneRoadBends associated with bends

public:
  SceneRoad( SceneJunction* );                           // constructor

  void  updateNewRoad( QPointF );                        // update end of new road
  void  completeNewRoad( SceneJunction* );               // complete new road
  void  adjust();                                        // update road path
  void  addBend( QPointF );                              // adds bend at point
  void  bendMoved( SceneRoadBend* );                     // receives msg that bend has been moved
  void  showProperties();                                // show properties dialog
  void  deleteBend( SceneRoadBend* );                    // delete bend from road
  void  setBends( QList<SceneRoadBend*> );               // set bends to list

  SceneJunction*           startJunction() { return start; }      // return start SceneJunction
  SceneJunction*           endJunction() { return end; }          // return end SceneJunction
  QVector<SceneRoadBend*>  roadBends() { return sceneBends; }     // return vector of bends
};

#endif // SCENEROAD_H
