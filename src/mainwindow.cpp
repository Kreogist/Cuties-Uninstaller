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

#include <QMessageBox>

#include <QApplication>
#include <QDebug>
#include <QLabel>

#include <windows.h>
#include <w32api.h>

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
    progressingFile=new QLabel(this);
    progressingFile->hide();

    instance=KCUninstallerGlobal::getInstance();
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
        uninstallProgress=new KCMessageBox(this);
        uninstallProgress->setTitle("Uninstall");
        uninstallProgress->addWidget(progressingCaption);
        uninstallProgress->addWidget(progressingFile);
        uninstallProgress->addWidget(progressing);
        uninstallProgress->disabledOK();
        uninstallProgress->setEscEnabled(false);
        uninstallProgress->setSoundEffect(false);
        uninstallProgress->show();
        progressingCaption->show();
        progressing->show();
        processUninstall();
    }
}

void ContextWindow::onActionHideButtons()
{
    repair->animateDisabled();
    uninstall->animateDisabled();
    cancel->visibleDisabled();
}

void ContextWindow::processUninstall()
{
    progressingCaption->setText("Preparing Uninstall");
    progressing->setMaximum(instance->prepareUninstall(QApplication::applicationDirPath()));
    int progressValue=0;
    QStringList processList=instance->getFolderLists();
    int processNum=processList.count();
    for(int i=0; i<processNum; i++)
    {
        progressValue++;
        progressing->setValue(progressValue);
        progressingFile->setText(processList.at(i));
        instance->removeDirectory(processList.at(i));
    }
    processList=instance->getFileLists();
    processNum=processList.count();
    QString currentFile, waitToDeleteCommand,
            meFile=QApplication::applicationFilePath().toLower();
    for(int i=0; i<processNum; i++)
    {
        progressValue++;
        progressing->setValue(progressValue);
        currentFile=processList.at(i).toLower();
        if(currentFile.right(4)!=".dll" &&
                currentFile!=meFile)
        {
            progressingFile->setText(processList.at(i));
            instance->removeFile(currentFile);
        }
        else
        {
            waitToDeleteCommand=processList.at(i);
            waitToDeleteCommand.replace("/","\\");
            waitToDeleteCommand="del /F /S /Q " + waitToDeleteCommand + "\n";
            /*
             * Delete myself need to try sometimes.
             */
            instance->flushCommand(waitToDeleteCommand);
            instance->flushCommand(waitToDeleteCommand);
            instance->flushCommand(waitToDeleteCommand);
        }
    }
    instance->flushToBat();
    progressingCaption->setText("Finish");
    uninstallProgress->enabledOK();

    connect(uninstallProgress, SIGNAL(finished(int)),
            this, SIGNAL(requireUninstall()));
}

void ContextWindow::onActionCancel()
{
    emit requireExit();
    close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Set Main Window Properties.
    setWindowOpacity(0);
    setWindowState(Qt::WindowFullScreen);

    //Set Main Window Palette.
    QPalette pal=palette();
    pal.setColor(QPalette::Window, QColor(0,0,0));
    setPalette(pal);

    fadeAnimation=new QTimeLine(200, this);
    fadeAnimation->setUpdateInterval(5);
    fadeAnimation->setFrameRange(0,9);
    connect(fadeAnimation, SIGNAL(valueChanged(qreal)),
            this, SLOT(updateBackgroundAlpha(qreal)));

    mainContext=new ContextWindow(this);
    setCentralWidget(mainContext);
    connect(mainContext, SIGNAL(requireExit()),
            this, SLOT(animateClose()));
    connect(mainContext, SIGNAL(requireUninstall()),
            this, SLOT(animateDestory()));
}

void MainWindow::animateShow()
{
    fadeAnimation->start();
}

void MainWindow::animateClose()
{
    connect(fadeAnimation, SIGNAL(finished()),
            this, SLOT(close()));
    reverse=true;
    fadeAnimation->start();
}

void MainWindow::animateDestory()
{
    connect(fadeAnimation, SIGNAL(finished()),
            this, SLOT(launchBat()));
    reverse=true;
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

void MainWindow::updateBackgroundAlpha(qreal percent)
{
    qreal currentOpacity=percent/4*3;
    if(reverse)
    {
        currentOpacity=maxOpacity-currentOpacity;
    }
    else
    {
        maxOpacity=currentOpacity;
    }
    setWindowOpacity(currentOpacity);
}

void MainWindow::enabledUninstallMode()
{
    uninstallMode=true;
}

void MainWindow::launchBat()
{
    QString exeCommand=KCUninstallerGlobal::getInstance()->getTempFilePath();
    exeCommand.replace("/","\\");
    exeCommand="cmd.exe /C \""+exeCommand+"\"";
    QByteArray command=exeCommand.toLatin1();
    system(command.data());
}
