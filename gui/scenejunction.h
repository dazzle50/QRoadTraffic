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

#ifndef SCENEJUNCTION_H
#define SCENEJUNCTION_H

class Junction;
class SceneRoad;

class QTabWidget;
class QDoubleSpinBox;

#include <QGraphicsEllipseItem>
#include <QLineEdit>
#include <QComboBox>

typedef struct
{
  float angle;
  int   inLanes;
  int   outLanes;
} RoadSummary;

/*************************************************************************************/
/******************** Represents a simulated junction on GUI scene *******************/
/*************************************************************************************/

class SceneJunction : public QGraphicsEllipseItem
{
public:
  SceneJunction( Junction* );                          // constructor

  void     addRoad( SceneRoad* road )                  // add road to roads list
             { m_roads << road; }
  void     removeRoad( SceneRoad* road )               // remove road from roads list
             { m_roads.removeAll( road ); }
  bool     hasRoads()                                  // return TRUE if has associated roads
             { return !m_roads.isEmpty(); }
  void     showProperties();                           // show properties dialog
  void     deleteProperties();                         // delete properties dialog
  QString  name()                                      // return junction name
             { return m_name->text(); }
  void     setName( QString name )                     // set junction name
             { m_name->setText( name ); }
  QString  generator()                                 // return junction traffic generator name
             { return m_generator->currentText(); }
  void     setGenerator( QString gen )                 // set junction traffic generator
             { m_generator->setItemText( 0, gen ); }
  QList<RoadSummary>  getRoadSummaries();              // return junction's road summaries

  QVariant	itemChange( GraphicsItemChange , const QVariant& );  // receive item changes

private:
  QList<SceneRoad*>   m_roads;                      // list of roads connected to junction

  QTabWidget*         m_properties;                 // window for junction properties
  QLineEdit*          m_name;                       // widget for name
  QDoubleSpinBox*     m_x;                          // widget for x coordinates
  QDoubleSpinBox*     m_y;                          // widget for y coordinates
  QComboBox*          m_generator;                  // widget for traffic generator
};

#endif // SCENEJUNCTION_H
