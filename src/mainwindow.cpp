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

#include "mainwindow.h"

ContextWindow::ContextWindow(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(512,512);

    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    buttonsLayout=new QHBoxLayout();

    repair=new QPushButton(this);
    connect(repair, SIGNAL(clicked()),
            this, SLOT(onActionRepair()));
    buttonsLayout->addWidget(repair);

    uninstall=new QPushButton(this);
    connect(uninstall, SIGNAL(clicked()),
            this, SLOT(onActionUninstall()));
    buttonsLayout->addWidget(uninstall);
    mainLayout->addLayout(buttonsLayout);

    cancel=new QPushButton(this);
    connect(cancel, SIGNAL(clicked()),
            this, SLOT(onActionCancel()));
    mainLayout->addWidget(cancel);
}

ContextWindow::~ContextWindow()
{
    buttonsLayout->deleteLater();
}

void ContextWindow::onActionRepair()
{
    ;
}

void ContextWindow::onActionUninstall()
{
    KCMessageBox *confirmUninstall=new KCMessageBox(this);
    confirmUninstall->setTitle("Confirm");
    confirmUninstall->addText("Sure to uninstall Cuties?");
    confirmUninstall->exec();
}

void ContextWindow::onActionCancel()
{
    close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Set Main Window Properties.
    setWindowOpacity(backgroundAlpha);
    setWindowState(Qt::WindowFullScreen);

    //Set Main Window Palette.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0));
    setPalette(pal);

    fadeAnimation=new QTimeLine(200, this);
    fadeAnimation->setUpdateInterval(5);
    fadeAnimation->setStartFrame(0);
    fadeAnimation->setEndFrame(14);
    connect(fadeAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(updateBackgroundAlpha()));

    mainContext=new ContextWindow(this);
    setCentralWidget(mainContext);
    connect(mainContext, SIGNAL(finished(int)),
            this, SLOT(animateClose()));
}

void MainWindow::animateShow()
{
    fadeAnimation->start();
}

void MainWindow::animateClose()
{
    connect(fadeAnimation, SIGNAL(finished()),
            this, SLOT(close()));
    backgroundAlphaInterval*=-1.0;
    fadeAnimation->start();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    animateShow();
    mainContext->move((width()-mainContext->width())/2,
                      (height()-mainContext->height())/2);
    mainContext->show();
}

void MainWindow::updateBackgroundAlpha()
{
    backgroundAlpha+=backgroundAlphaInterval;
    setWindowOpacity(backgroundAlpha);
}
