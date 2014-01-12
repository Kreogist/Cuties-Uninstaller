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

#include <QDebug>
#include <QLabel>

#include "mainwindow.h"

ContextWindow::ContextWindow(QWidget *parent) :
    QDialog(parent)
{
    int parentWidth=parentWidget()->width();
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(parentWidth,512);

    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
    mainLayout->addStretch();

    QLabel *title=new QLabel(this);
    QPalette titlePalette=title->palette();
    titlePalette.setColor(QPalette::WindowText, QColor(255,255,255));
    title->setPalette(titlePalette);
    QFont titleFont=title->font();
    titleFont.setPixelSize(50);
    titleFont.setFamily("sao");
    title->setFont(titleFont);
    title->setFixedWidth(parentWidth);
    title->setAlignment(Qt::AlignCenter);
    title->setText("Cuties Maintenance Tool");
    mainLayout->addWidget(title);
    mainLayout->addSpacing(30);

    buttonsLayout=new QHBoxLayout();
    buttonsLayout->setSpacing(10);

    buttonsLayout->addStretch();
    repair=new KCGraphicButtonRepair(this);
    connect(repair, SIGNAL(clicked()),
            this, SLOT(onActionRepair()));
    buttonsLayout->addWidget(repair);

    uninstall=new KCGraphicButtonUninstall(this);
    connect(uninstall, SIGNAL(clicked()),
            this, SLOT(onActionUninstall()));
    buttonsLayout->addWidget(uninstall);
    buttonsLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    centerCancelButtonLayout=new QHBoxLayout();
    cancel=new KCGraphicButtonCancel(this);
    cancel->setFixedSize(48,48);
    connect(cancel, SIGNAL(clicked()),
            this, SLOT(onActionCancel()));
    centerCancelButtonLayout->addWidget(cancel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(centerCancelButtonLayout);
    mainLayout->addStretch();

    progressing=new QProgressBar(this);
    progressing->setFixedSize(300,25);
    progressing->hide();
    progressingCaption=new QLabel(this);
    progressingCaption->hide();
}

ContextWindow::~ContextWindow()
{
    buttonsLayout->deleteLater();
    centerCancelButtonLayout->deleteLater();
}

void ContextWindow::onActionRepair()
{
    KCMessageBox *confirmReset=new KCMessageBox(this);
    confirmReset->setTitle("Reset");
    confirmReset->addText("Sure to reset Cuties?");
    confirmReset->enabledCancel();
    confirmReset->exec();
    if(confirmReset->messageBoxState()==KCMessageBoxPanel::buttonOK)
    {
        onActionHideButtons();
        KCMessageBox *resetProgress=new KCMessageBox(this);
        resetProgress->setTitle("Reset");
        resetProgress->addWidget(progressingCaption);
        resetProgress->addWidget(progressing);
        resetProgress->disabledOK();
        resetProgress->setEscEnabled(false);
        resetProgress->setSoundEffect(false);
        resetProgress->show();
        progressingCaption->show();
        progressing->show();
    }
}

void ContextWindow::onActionUninstall()
{
    KCMessageBox *confirmUninstall=new KCMessageBox(this);
    confirmUninstall->setTitle("Uninstall");
    confirmUninstall->addText("Sure to uninstall Cuties?");
    confirmUninstall->enabledCancel();
    confirmUninstall->exec();
    if(confirmUninstall->messageBoxState()==KCMessageBoxPanel::buttonOK)
    {
        onActionHideButtons();
        KCMessageBox *uninstallProgress=new KCMessageBox(this);
        uninstallProgress->setTitle("Uninstall");
        uninstallProgress->addWidget(progressingCaption);
        uninstallProgress->addWidget(progressing);
        uninstallProgress->disabledOK();
        uninstallProgress->setEscEnabled(false);
        uninstallProgress->setSoundEffect(false);
        uninstallProgress->show();
        progressingCaption->show();
        progressing->show();
    }
}

void ContextWindow::onActionHideButtons()
{
    repair->animateDisabled();
    uninstall->animateDisabled();
    cancel->visibleDisabled();
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
    fadeAnimation->setEndFrame(16);
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
