/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Cuties Uninstaller.
 *
 *    Cuties Uninstaller is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *    Cuties Uninstaller is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  Cuties Uninstaller. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \copyright GNU Public License v3
 * \details
 *
 */

#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QFontDatabase>

#include <QDebug>

#include "mainwindow.h"

void initApplicationProperties()
{
    QApplication::setApplicationName("Cuties Uninstaller");
    QApplication::setApplicationVersion("0.0.3");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("fusion"));

    QFile saoFontResource(":/font/font/sao.ttf");
    if(saoFontResource.open(QIODevice::ReadOnly))
    {
        QFontDatabase::addApplicationFontFromData(saoFontResource.readAll());
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
