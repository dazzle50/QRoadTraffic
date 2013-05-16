/***************************************************************************
 *   Copyright (C) 2013 by Richard Crook                                   *
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
#include <QMessageBox>

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
  m_view->setMouseTracking( true );
  setCentralWidget( m_view );

  // add drop down menus
  QMenu* fileMenu = menuBar()->addMenu( "&File" );
  QMenu* editMenu = menuBar()->addMenu( "&Edit" );
  QMenu* viewMenu = menuBar()->addMenu( "&View" );
  QMenu* simMenu  = menuBar()->addMenu( "&Simulate" );
  QMenu* helpMenu = menuBar()->addMenu( "&Help" );

  // add menu actions
  fileMenu->addAction( "New...", this, SLOT(fileNew()), QKeySequence(QKeySequence::New) );
  fileMenu->addAction( "Open...", this, SLOT(fileOpen()), QKeySequence(QKeySequence::Open) );
  fileMenu->addAction( "Save As...", this, SLOT(fileSaveAs()), QKeySequence(QKeySequence::SaveAs) );
  fileMenu->addSeparator();
  fileMenu->addAction( "Add background...", this, SLOT(fileLoadBackground()) );

  viewMenu->addAction( "Zoom in", this, SLOT(viewZoomIn()), QKeySequence(QKeySequence::ZoomIn) );
  viewMenu->addAction( "Zoom out", this, SLOT(viewZoomOut()), QKeySequence(QKeySequence::ZoomOut) );

  helpMenu->addAction( "Build with Qt"QT_VERSION_STR );

  Q_UNUSED(editMenu)
  Q_UNUSED(simMenu)

  // add status bar message
  statusBar()->showMessage( "QRoadTraffic has started" );

  // TEMP
  loadSimulation("C:\\Users\\Richard\\Documents\\Qt\\new.xml");
}

/************************************* fileNew ***************************************/

void  MainWindow::fileNew()
{
  // if no scene items (only default top-left scene anchor) then nothing to do
  if ( m_scene->items().count() <= 1 ) return;

  // check if user wants to save before starting new simulation
  while (true)
    switch ( QMessageBox::warning( this, "QRoadTraffic",
        "Do you want to save before starting new?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel ) )
    {
      case QMessageBox::Save:
        // if save not successful ask again
        if ( !fileSaveAs() ) break;

      case QMessageBox::Discard:
        // start new simulation
        {
          Scene*  newScene = new Scene( this );
          m_view->setScene( newScene );
          m_scene->deletePropertiesDialogs();
          delete m_scene;
          m_scene = newScene;
        }
        return;

      default:    // "Cancel"
        return;
    }
}

/************************************* fileOpen **************************************/

void  MainWindow::fileOpen()
{
  // get user to select filename and location
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() ) return;

  // load simulation from specified file
  loadSimulation( filename );
}

/********************************** loadSimulation ***********************************/

bool  MainWindow::loadSimulation( QString filename )
{
  // open the file and check we can read from it
  QFile file( filename );
  if ( !file.open( QIODevice::ReadOnly ) )
  {
    statusBar()->showMessage( QString("Failed to open '%1'").arg(filename) );
    return false;
  }

  // open an xml stream reader and load simulation data
  QXmlStreamReader  stream( &file );
  Scene*            newScene = new Scene( this );
  while ( !stream.atEnd() )
  {
    stream.readNext();
    if ( stream.isStartElement() )
    {
      if ( stream.name() == "qroadtraffic" )
        newScene->readStream( &stream );
      else
        stream.raiseError( QString("Unrecognised element '%1' in file '%2'").arg(stream.name().toString())
                                                                            .arg(filename) );
    }
  }

  // check if error occured
  if ( stream.hasError() )
  {
    file.close();
    statusBar()->showMessage( QString("Failed to load '%1' (%2)").arg(filename).arg(stream.errorString()) );
    delete newScene;
    return false;
  }

  // close file, display new scene, delete old scene, and display useful message
  file.close();
  m_view->setScene( newScene );
  m_scene->deletePropertiesDialogs();
  delete m_scene;
  m_scene = newScene;
  statusBar()->showMessage( QString("Loaded '%1'").arg(filename) );
  return true;
}

/************************************ fileSaveAs *************************************/

bool  MainWindow::fileSaveAs()
{
  // get user to select filename and location
  QString filename = QFileDialog::getSaveFileName();
  if ( filename.isEmpty() ) return false;

  // save simulation to specified file
  return saveSimulation( filename );
}

/********************************** saveSimulation ***********************************/

bool  MainWindow::saveSimulation( QString filename )
{
  // open the file and check we can write to it
  QFile file( filename );
  if ( !file.open( QIODevice::WriteOnly ) )
  {
    statusBar()->showMessage( QString("Failed to write to '%1'").arg(filename) );
    return false;
  }

  // open an xml stream writer and write simulation data
  QXmlStreamWriter  stream( &file );
  stream.setAutoFormatting( true );
  stream.writeStartDocument();
  stream.writeStartElement( "qroadtraffic" );
  stream.writeAttribute( "version", "2012-06" );
  stream.writeAttribute( "user", QString(getenv("USERNAME")) );
  stream.writeAttribute( "when", QDateTime::currentDateTime().toString(Qt::ISODate) );

  // collect pointers to all scene junctions into a list
  QList<SceneJunction*> juncs;
  foreach( QGraphicsItem* item, m_scene->items() )
  {
    SceneJunction*  junc = dynamic_cast<SceneJunction*>( item );
    if ( junc ) juncs.append( junc );
  }

  // write scene junction data to xml stream
  for ( int i = 0; i < juncs.size(); ++i )
  {
    stream.writeEmptyElement( "junction" );
    stream.writeAttribute( "id", QString::number( i ) );
    stream.writeAttribute( "x" , QString::number( juncs.at(i)->x() ) );
    stream.writeAttribute( "y" , QString::number( juncs.at(i)->y() ) );
    stream.writeAttribute( "name",      juncs.at(i)->name() );
    stream.writeAttribute( "generator", juncs.at(i)->generator() );
  }

  // write road data to xml stream
  foreach( QGraphicsItem*  item, m_scene->items() )
  {
    SceneRoad*  road = dynamic_cast<SceneRoad*>( item );
    if ( road )
    {
      stream.writeStartElement( "road" );
      stream.writeAttribute( "start"   , QString::number( juncs.indexOf(road->startJunction()) ) );
      stream.writeAttribute( "end"     , QString::number( juncs.indexOf(road->endJunction()  ) ) );
      stream.writeAttribute( "name"    , road->name() );
      stream.writeAttribute( "se-lanes", QString::number( road->seLanes() ) );
      stream.writeAttribute( "es-lanes", QString::number( road->esLanes() ) );

      // for each road write bend data to xml stream
      foreach( SceneRoadBend*  bend, road->roadBends() )
      {
        stream.writeEmptyElement( "bend" );
        stream.writeAttribute( "x" , QString::number( bend->x() ) );
        stream.writeAttribute( "y" , QString::number( bend->y() ) );
      }

      stream.writeEndElement();
    }
  }

  // close the file and display useful message
  stream.writeEndDocument();
  file.close();
  statusBar()->showMessage( QString("Saved to '%1'").arg(filename) );
  return true;
}

/************************************ viewZoomIn *************************************/

void  MainWindow::viewZoomIn()
{
  // zoom in on main scene view
  m_view->scale( 1.1, 1.1 );
}

/************************************ viewZoomOut ************************************/

void  MainWindow::viewZoomOut()
{
  // zoom out on main scene view
  m_view->scale( 1/1.1, 1/1.1 );
}

/********************************* fileLoadBackground ********************************/

void  MainWindow::fileLoadBackground()
{
  // get user to select filename and location
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() ) return;

  // load scene background image from specified file
  loadBackground( filename );
}

/********************************* loadBackground ********************************/

void  MainWindow::loadBackground( QString filename )
{
  // load scene background image from specified file
  QPixmap  map = QPixmap( filename );
  m_scene->addPixmap( map );
}
