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

#include "mainwindow.h"
#include "scene.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>

/*************************************************************************************/
/********************* Main application window for QRoadTraffic **********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

MainWindow::MainWindow() : QMainWindow()
{
  // create scene and central widget view of scene
  m_scene = new Scene( this );
  m_view  = new QGraphicsView( m_scene );
  m_view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  m_view->setFrameStyle( 0 );
  m_view->setRenderHint( QPainter::Antialiasing );
  m_view->setMouseTracking( TRUE );
  setCentralWidget( m_view );

  // add drop down menus
  QMenu* fileMenu = menuBar()->addMenu( "&File" );
  QMenu* editMenu = menuBar()->addMenu( "&Edit" );
  QMenu* viewMenu = menuBar()->addMenu( "&View" );
  QMenu* simMenu  = menuBar()->addMenu( "&Simulate" );
  QMenu* helpMenu = menuBar()->addMenu( "&Help" );

  // add menu actions
  viewMenu->addAction( "Zoom in", this, SLOT(zoomIn()), QKeySequence(QKeySequence::ZoomIn) );
  viewMenu->addAction( "Zoom out", this, SLOT(zoomOut()), QKeySequence(QKeySequence::ZoomOut) );
  helpMenu->addAction( "Build with Qt"QT_VERSION_STR );

  // add status bar message
  statusBar()->showMessage("QRoadTraffic has started");
}

/************************************** zoomIn ***************************************/

void  MainWindow::zoomIn()
{
  qDebug("MainWindow::zoomIn()");
  m_view->scale( 2.0, 2.0 );
}

/************************************** zoomOut **************************************/

void  MainWindow::zoomOut()
{
  qDebug("MainWindow::zoomOut()");
  m_view->scale( 0.5, 0.5 );
}
