/***************************************************************************
 *   Copyright (C) 2005 by Matthias Varnholt   *
 *   matto@gmx.de   *
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

// Qt
#include <QApplication>

// server
#include "server.h"
#include "servergui.h"
#include "serverversion.h"

// shared
#include "systemtools.h"

ServerGui* gui = nullptr;

void debugHandler(QtMsgType type, const QMessageLogContext& /*context*/, const QString &msg)
{
   if (gui)
   {
      gui->addDebugMessage(msg, type);
   }
}


int main( int argc, char ** argv )
{
   bool useGui = false;

   #ifdef Q_WS_X11
      useGui = getenv("DISPLAY") != 0;
   #else
      useGui = true;
   #endif

   // check qt version
   QString version;
   if (!checkQtVersion(5,0, &version))
   {
      qWarning(
            "The installed Qt version (%s) is invalid!\nRequired is version 4.8.x.",
            qPrintable( version )
      );
      return 0;
   }

   if (useGui)
      new QApplication(argc, argv, useGui);
   else
      new QCoreApplication(argc, argv, useGui);

   // install debug msg handler before the server is initialized
   if (useGui)
   {
      gui = new ServerGui();
      gui->setMinimumSize(640, 480);
      gui->show();
      gui->setWindowTitle(
         QString("Dynablaster Revenge Server v%1 rev. %2")
            .arg(SERVER_VERSION)
            .arg(SERVER_REVISION)
      );
      qInstallMessageHandler(debugHandler);
   }

   Server *server = new Server();

   // connect ui to server
   if (useGui)
   {
      gui->connect(
         server,
         SIGNAL(newPlayer(int,const QString&)),
         SLOT(newPlayer(int,const QString&))
      );

      gui->connect(
         server,
         SIGNAL(removePlayer(int,const QString&)),
         SLOT(removePlayer(int,const QString&))
      );

      gui->connect(
         server,
         SIGNAL(newGame(int,const QString&)),
         SLOT(newGame(int,const QString&))
      );

      gui->connect(
         server,
         SIGNAL(removeGame(int,const QString&)),
         SLOT(removeGame(int,const QString&))
      );
   }

   return qApp->exec();
}



