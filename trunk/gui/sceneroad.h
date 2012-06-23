/***************************************************************************
 *   Copyright (C) 2012 by Richard Crook                                   *
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

class QTabWidget;

#include <QGraphicsPolygonItem>
#include <QLineEdit>
#include <QSpinBox>

/*************************************************************************************/
/********************** Represents a simulated road on GUI scene *********************/
/*************************************************************************************/

class SceneRoad : public QGraphicsPolygonItem
{
public:
  SceneRoad( SceneJunction* );                           // constructor

  void  updateNewRoad( QPointF );                        // update end of new road
  void  completeNewRoad( SceneJunction* );               // complete new road
  void  adjust();                                        // update road path
  void  addBend( QPointF );                              // adds bend at point
  void  bendMoved( SceneRoadBend* );                     // receives msg that bend has been moved
  void  showProperties();                                // show properties dialog
  void  deleteProperties();                              // delete properties dialog
  void  deleteBend( SceneRoadBend* );                    // delete bend from road
  void  setBends( QList<SceneRoadBend*> );               // set bends to list
  float angle( SceneJunction* );                         // return angle of road into junction

  SceneJunction*           startJunction()               // return start SceneJunction
                             { return m_start; }
  SceneJunction*           endJunction()                 // return end SceneJunction
                             { return m_end; }
  QVector<SceneRoadBend*>  roadBends()                   // return vector of bends
                             { return m_sceneBends; }
  QString                  name()                        // return junction name
                             { return m_name->text(); }
  void                     setName( QString name )       // set junction name
                             { m_name->setText( name ); }
  int                      esLanes()                     // return number of lanes from end to start
                             { return m_esLanes->value(); }
  int                      seLanes()                     // return number of lanes from start to end
                             { return m_seLanes->value(); }
  void                     setLanes( int se, int es )    // set number of lanes
                             { m_seLanes->setValue( se );
                               m_esLanes->setValue( es ); }

private:
  SceneJunction*           m_start;        // SceneJunction at road start
  SceneJunction*           m_end;          // SceneJunction at road end
  QVector<QPointF>         m_bends;        // bends between the road start & end
  QVector<SceneRoadBend*>  m_sceneBends;   // SceneRoadBends associated with bends

  QTabWidget*   m_properties;              // window for junction properties
  QLineEdit*    m_name;                    // widget for name
  QSpinBox*     m_seLanes;                 // widget for number of start->end lanes
  QSpinBox*     m_esLanes;                 // widget for number of end->start lanes
};

#endif // SCENEROAD_H
