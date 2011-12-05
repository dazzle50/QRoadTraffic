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

#ifndef SCENE_H
#define SCENE_H

class SceneRoad;
class SceneJunction;

#include <QGraphicsScene>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

class Scene : public QGraphicsScene
{
private:
  SceneRoad*  newRoad;                // null, unless adding a new road
  QWidget*    mainWindow;             // pointer to application main window

public:
  Scene( QWidget* );                  // constructor

  void  addSimulatedItems();                              // create QGraphicsItems for simulated items
  void  removeRoad( SceneRoad* );                         // removes road from scene
  bool  roadExists( SceneJunction*, SceneJunction* );     // returns TRUE if road already exists

  void  contextMenuEvent( QGraphicsSceneContextMenuEvent* ); // receive context menu events
  void  mouseMoveEvent( QGraphicsSceneMouseEvent* );         // receive mouse move events
  void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events
};

#endif  // SCENE_H