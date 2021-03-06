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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTimeLine>

#include <QMainWindow>
#include <QProgressBar>
#include <QDialog>

#include <cstdlib>

#include "kcmessagebox.h"

#include "kcgraphicbuttonrepair.h"
#include "kcgraphicbuttonuninstall.h"

#include "kcuninstallerglobal.h"

class ContextWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ContextWindow(QWidget *parent = 0);
    ~ContextWindow();

signals:
    void requireUninstall();
    void requireExit();

private slots:
    void onActionCancel();
    void onActionRepair();
    void onActionUninstall();
    void onActionHideButtons();

private:
    void processUninstall();
    QWidget *layoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *centerCancelButtonLayout;

    KCGraphicButtonRepair *repair;
    KCGraphicButtonUninstall *uninstall;
    KCGraphicButtonCancel *cancel;
    QLabel *progressingCaption;
    QLabel *progressingFile;
    QProgressBar *progressing;

    KCUninstallerGlobal *instance;
    KCMessageBox *uninstallProgress;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void animateShow();
    void animateClose();
    void animateDestory();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void updateBackgroundAlpha(qreal percent);
    void enabledUninstallMode();
    void launchBat();

private:
    ContextWindow *mainContext;
    QTimeLine *fadeAnimation;
    bool uninstallMode=false;
    bool reverse=false;
    qreal maxOpacity;
};

#endif // MAINWINDOW_H
