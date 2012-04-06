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
#include "scenejunction.h"
#include "sceneroad.h"
#include "sceneroadbend.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QPixmap>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QDateTime>

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
  fileMenu->addAction( "New...", this, SLOT(newScene()), QKeySequence(QKeySequence::New) );
  fileMenu->addAction( "Open...", this, SLOT(loadScene()), QKeySequence(QKeySequence::Open) );
  fileMenu->addAction( "Save As...", this, SLOT(saveAsScene()), QKeySequence(QKeySequence::SaveAs) );
  fileMenu->addSeparator();
  fileMenu->addAction( "Add background...", this, SLOT(loadBackground()) );
  viewMenu->addAction( "Zoom in", this, SLOT(zoomIn()), QKeySequence(QKeySequence::ZoomIn) );
  viewMenu->addAction( "Zoom out", this, SLOT(zoomOut()), QKeySequence(QKeySequence::ZoomOut) );
  helpMenu->addAction( "Build with Qt"QT_VERSION_STR );

  // add status bar message
  statusBar()->showMessage("QRoadTraffic has started");
}

/************************************* newScene **************************************/

void  MainWindow::newScene()
{
  qDebug("MainWindow::newScene()");
}

/************************************* loadScene *************************************/

void  MainWindow::loadScene()
{
  qDebug("MainWindow::loadScene()");
}

/************************************* saveScene *************************************/

bool  MainWindow::saveAsScene()
{
  qDebug("MainWindow::saveAsScene()");

  // get user to select filename and location
  QString filename = QFileDialog::getSaveFileName();
  if ( filename.isEmpty() ) return false;

  // open the file and check we can write to it
  QFile file( filename );
  if ( !file.open( QIODevice::WriteOnly ) )
  {
    //showMessage( QString("Failed to write to '%1'").arg(filename) );
    return false;
  }

  // open an xml stream writer and write simulation data
  QXmlStreamWriter  stream( &file );
  stream.setAutoFormatting( true );
  stream.writeStartDocument();
  stream.writeStartElement( "qroadtraffic" );
  stream.writeAttribute( "version", "2012-04" );
  stream.writeAttribute( "user", QString(getenv("USERNAME")) );
  stream.writeAttribute( "when", QDateTime::currentDateTime().toString(Qt::ISODate) );

  // write scene data to xml stream
  foreach( QGraphicsItem*  item, m_scene->items() )
  {
    SceneJunction*  junc = dynamic_cast<SceneJunction*>( item );
    if ( junc )
    {
      stream.writeEmptyElement( "junction" );
      stream.writeAttribute( "x", QString("%1").arg(junc->x()) );
      stream.writeAttribute( "y", QString("%1").arg(junc->y()) );
    }

    SceneRoad*  road = dynamic_cast<SceneRoad*>( item );
    if ( road )
    {
      stream.writeEmptyElement( "road" );
      stream.writeAttribute( "start", QString("%1").arg(1) );
      stream.writeAttribute( "end", QString("%1").arg(2) );
    }

    SceneRoadBend*  bend = dynamic_cast<SceneRoadBend*>( item );
    if ( bend )
    {
      stream.writeEmptyElement( "bend" );
      stream.writeAttribute( "x", QString("%1").arg(bend->x()) );
      stream.writeAttribute( "y", QString("%1").arg(bend->y()) );
      stream.writeAttribute( "road", QString("%1").arg(10) );
    }


  }


  stream.writeEndDocument();

  // close the file and display useful message
  file.close();
  //showMessage( QString("Saved to '%1'").arg(filename) );
  return true;
}

/************************************** zoomIn ***************************************/

void  MainWindow::zoomIn()
{
  qDebug("MainWindow::zoomIn()");
  m_view->scale( 1.1, 1.1 );
}

/************************************** zoomOut **************************************/

void  MainWindow::zoomOut()
{
  qDebug("MainWindow::zoomOut()");
  m_view->scale( 1/1.1, 1/1.1 );
}

/*********************************** loadBackground **********************************/

void  MainWindow::loadBackground()
{
  qDebug("MainWindow::loadBackground()");

  // get user to select filename and location
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() ) return;

  QPixmap  map = QPixmap( filename );
  m_scene->addPixmap( map );
}
