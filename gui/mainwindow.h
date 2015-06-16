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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Scene;
class QGraphicsView;

/*************************************************************************************/
/********************* Main application window for QRoadTraffic **********************/
/*************************************************************************************/

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();                           // constructor

public slots:
  void  viewZoomIn();                     // slot to receive zoom in action signal
  void  viewZoomOut();                    // slot to receive zoom out action signal
  void  viewZoomNormal();                 // slot to receive zoom normal action signal

  void  fileLoadBackground();             // slot to receive load background action signal
  void  fileNew();                        // slot to receive new scene action signal
  void  fileOpen();                       // slot to receive load scene action signal
  bool  fileSaveAs();                     // slot to receive save as scene action signal

  bool  loadSimulation( QString );        // load simulation from specified xml file
  bool  saveSimulation( QString );        // save simulation to specified xml file

private:
  Scene*          m_scene;                // scene representing the simulated landscape
  QGraphicsView*  m_view;                 // view of scene showing simulated landscape
};

#endif  // MAINWINDOW_H
