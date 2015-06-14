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

#include "scenejunction.h"
#include "sceneroad.h"
#include "scenejunctionview.h"
#include "../sim/junction.h"

#include <QPen>
#include <QTabWidget>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QTableWidget>

/*************************************************************************************/
/******************** Represents a simulated junction on GUI scene *******************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneJunction::SceneJunction( Junction* junction )
{
  // initialise variables
  m_properties = 0;
  m_name       = new QLineEdit();
  m_generator  = new QComboBox();
  m_generator->addItem( "None" );

  // junction scene item is a red circle with a black border
  float   radius = 6.0;

  setToolTip( name() );
  setRect( -radius, -radius, 2*radius, 2*radius );
  setPos( junction->pos() );
  setPen( QPen(Qt::black) );
  setBrush( Qt::red );
  setZValue( 100 );
  setFlags( QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemSendsGeometryChanges );
}

/************************************ itemChange *************************************/

QVariant	SceneJunction::itemChange( GraphicsItemChange change, const QVariant& value )
{
  // if the junction moved then adjust each road connected to the junction
  if ( change == QGraphicsItem::ItemPositionHasChanged )
  {
    foreach( SceneRoad* road, m_roads )
      road->adjust();
  }

  return QGraphicsItem::itemChange( change, value );
}

/********************************* getRoadSummaries **********************************/

QList<RoadSummary>  SceneJunction::getRoadSummaries()
{
  // collect summary info for each road connected to this junction
  QList<RoadSummary>  roads;
  foreach( SceneRoad* road, m_roads )
  {
    RoadSummary  summary;
    summary.angle = road->angle( this );

    if ( road->startJunction() == this )
    {
      summary.inLanes  = road->esLanes();
      summary.outLanes = road->seLanes();
    }
    else
    {
      summary.inLanes  = road->seLanes();
      summary.outLanes = road->esLanes();
    }

    roads.append( summary );
  }

  return roads;
}

/********************************* deleteProperties **********************************/

void SceneJunction::deleteProperties()
{
  // delete pre-initialise properties widgets and dialog box
  delete m_name;
  delete m_generator;
  if ( m_properties ) delete m_properties;
}

/********************************** showProperties ***********************************/

void SceneJunction::showProperties()
{
  // if properties window already exists, bring to front
  if ( m_properties )
  {
     m_properties->show();
     m_properties->raise();
     return;
  }

  // properies window doesn't exist, so create basic properties window widget
  m_properties = new QTabWidget( 0 );
  m_properties->setWindowFlags( Qt::Tool );
  m_properties->setAttribute( Qt::WA_DeleteOnClose, false );
  m_properties->setMinimumSize( 150, 110 );
  m_properties->resize( 150, 110 );
  m_properties->setWindowTitle( "Junction properties" );
  m_properties->show();

  // create the three tab widgets
  QWidget*       editWidget  = new QWidget();
  QTableWidget*  roadsWidget = new QTableWidget( 3, 3 );
  QWidget*       viewWidget  = new SceneJunctionView( this );
  m_properties->addTab( editWidget,  "Edit" );
  m_properties->addTab( roadsWidget, "Roads" );
  m_properties->addTab( viewWidget,  "View" );

  // populate the edit widget
  editWidget->setContentsMargins( -5, -5, -5, -5 );
  QFormLayout*  dataLayout  = new QFormLayout( editWidget );
  m_x         = new QDoubleSpinBox();
  m_y         = new QDoubleSpinBox();
  dataLayout->setVerticalSpacing( 3 );
  dataLayout->addRow( "Name",       m_name );
  dataLayout->addRow( "X",          m_x );
  dataLayout->addRow( "Y",          m_y );
  dataLayout->addRow( "Generator",  m_generator );

  // set edit widget values
  m_x->setMaximum( 99999 );
  m_x->setValue( x() );
  m_y->setMaximum( 99999 );
  m_y->setValue( y() );

  //=============================================================================================
  // TODO lots more ........ !!!
}
