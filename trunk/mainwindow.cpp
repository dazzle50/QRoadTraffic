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

#include "mainwindow.h"
#include "scene.h"
#include "simulation.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>

/*************************************************************************************/
/********************* Main application window for QRoadTraffic **********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

MainWindow::MainWindow() : QMainWindow()
{
  // add drop down menus
  QMenu* fileMenu = menuBar()->addMenu("&File");
  QMenu* editMenu = menuBar()->addMenu("&Edit");
  QMenu* viewMenu = menuBar()->addMenu("&View");
  QMenu* simMenu  = menuBar()->addMenu("&Simulate");
  QMenu* helpMenu = menuBar()->addMenu("&Help");

  helpMenu->addAction("Build with Qt"QT_VERSION_STR);

  // create scene and central widget view of scene
  m_scene               = new Scene();
  QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );

  addSimulatedItems();

  // add status bar message
  statusBar()->showMessage("QRoadTraffic has started");
}

/********************************* addSimulatedItems *********************************/

void MainWindow::addSimulatedItems()
{
  // add simulated items to the scene

  // add junctions
  foreach( QPointF pos, sim->junctionPoints() )
    qDebug("JUNCTION xxxxxx");

  // add roads
  foreach( QPointF pos, sim->roadPoints() )
    qDebug("ROAD xxxxxx");

  // add vehicles
  foreach( QPointF pos, sim->vehiclePoints() )
    qDebug("VEHICLE xxxxxx");


}
