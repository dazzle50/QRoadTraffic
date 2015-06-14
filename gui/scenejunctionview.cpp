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

#include "scenejunctionview.h"
#include "scenejunction.h"

#include <QPainter>

#include <math.h>

/*************************************************************************************/
/********************** Displays a scene junction showing lanes **********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

SceneJunctionView::SceneJunctionView( SceneJunction* junc )
{
  // initialise private variables
  m_junction = junc;
}

/************************************ paintEvent *************************************/

void SceneJunctionView::paintEvent( QPaintEvent* event )
{
  Q_UNUSED( event )
  // get summary of roads to be displayed in this view
  QList<RoadSummary>  roads = m_junction->getRoadSummaries();

  // general drawing parameters
  float  roadWidth  = 10.0;
  float  roadGap    =  5.0;
  float  juncRadius = 75.0;

  // setup basic painter parameters
  int side = qMin( width(), height() );
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.translate( width() / 2, height() / 2 );
  painter.scale( side / 200.0, side / 200.0 );

  // draw the roads on view
  QPen pen;
  pen.setWidth( roadWidth );
  pen.setCapStyle( Qt::FlatCap );
  painter.setPen( pen );
  foreach( RoadSummary road, roads )
  {
    int   lanes = road.inLanes + road.outLanes;
    float x     = ( 1 - lanes ) * ( roadWidth + roadGap ) / 2.0;

    painter.save();
    painter.rotate( road.angle );
    for( int lane = 1; lane<=lanes; lane++ )
    {
      painter.drawLine( QPointF(x, 0.0), QPointF(x, -999.9) );
      x += roadWidth + roadGap;
    }
    painter.restore();
  }

  // draw the junction circle
  pen.setWidth( roadWidth / 5.0 );
  painter.setPen( pen );
  painter.setBrush( QBrush( Qt::red ) );
  painter.drawEllipse( QPointF(0.0,0.0), juncRadius, juncRadius );

  // draw the road connections
  pen.setWidth( roadWidth );
  pen.setBrush( QColor(0,255,0,200) );
  painter.setPen( pen );
  foreach( RoadSummary road1, roads )
  {
    int     lanes1 = road1.inLanes + road1.outLanes;
    float   x1     = ( 1 - lanes1 ) * ( roadWidth + roadGap ) / 2.0;
    QMatrix matrix1;
    matrix1.rotate( 180.0 + road1.angle );

    for( int in = 1; in<=road1.inLanes; in++ )
    {
      float   y1 = sqrt( juncRadius*juncRadius - x1*x1 );
      QPointF p1 = QPointF( x1, y1 ) * matrix1;
      x1 += roadWidth + roadGap;

      foreach( RoadSummary road2, roads )
      {
        // avoid connecting outs and ins from same road
        if ( road2.angle == road1.angle ) continue;

        int     lanes2 = road2.inLanes + road2.outLanes;
        float   x2     = ( 1 - lanes2 ) * ( roadWidth + roadGap ) / 2.0;
        QMatrix matrix2;
        matrix2.rotate( 180.0 + road2.angle );

        // avoid connecting in-lanes to in-lanes
        for( int out = 1; out<=road2.inLanes; out++ )
          x2 += roadWidth + roadGap;

        for( int out = 1; out<=road2.outLanes; out++ )
        {
          float   y2 = sqrt( juncRadius*juncRadius - x2*x2 );
          QPointF p2 = QPointF( x2, y2 ) * matrix2;
          x2 += roadWidth + roadGap;

          painter.drawLine( p1, p2 );

          //painter.drawArc( x, y, w, h, start, span );
        }
      }
    }
  }

}
