/***************************************************************************
 *   Copyright (C) 2015 by Richard Crook                                   *
 *   https://github.com/dazzle50/QRoadTraffic                              *
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
class QXmlStreamReader;

#include <QGraphicsScene>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

class Scene : public QGraphicsScene
{
public:
  Scene( QWidget* );                  // constructor

  void  removeRoad( SceneRoad* );                         // removes road from scene
  bool  roadExists( SceneJunction*, SceneJunction* );     // returns TRUE if road already exists
  void  readStream( QXmlStreamReader* );                  // read scene data from xml stream
  void  loadBackground( QString );                        // load scene background image from specified file
  void  deletePropertiesDialogs();                        // delete any properties dialog widgets

  QString backgroundFile() { return m_background; }       // return background filename

  void  contextMenuEvent( QGraphicsSceneContextMenuEvent* ); // receive context menu events
  void  mouseMoveEvent( QGraphicsSceneMouseEvent* );         // receive mouse move events
  void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events

private:
  SceneRoad*  m_newRoad;                // null, unless adding a new road
  QWidget*    m_mainWindow;             // pointer to application main window
  QString     m_background;             // name of background image file
};

#endif  // SCENE_H
