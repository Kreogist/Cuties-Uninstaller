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

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QList>
#include <QApplication>
#include <QDebug>

#include "kcuninstallerglobal.h"

KCUninstallerGlobal *KCUninstallerGlobal::instance=nullptr;

KCUninstallerGlobal *KCUninstallerGlobal::getInstance()
{
    return instance==nullptr?instance=new KCUninstallerGlobal:instance;
}

KCUninstallerGlobal::KCUninstallerGlobal()
{
    ;
}

QString KCUninstallerGlobal::getTempFilePath() const
{
    return tempFilePath;
}

QStringList KCUninstallerGlobal::getFolderLists() const
{
    return folderLists;
}

QStringList KCUninstallerGlobal::getFileLists() const
{
    return fileLists;
}

bool KCUninstallerGlobal::removeDirectory(const QString &folderPath)
{
    if(folderPath.isEmpty())
    {
        return false;
    }

    QDir dir(folderPath);
    if(!dir.exists())
    {
        //No dir means: dir has been deleted.
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            fi.dir().remove(fi.fileName());
        }
        else
        {
            removeDirectory(fi.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}

bool KCUninstallerGlobal::removeFile(const QString &filePath)
{
    return QFile::remove(filePath);
}

int KCUninstallerGlobal::prepareUninstall(const QString &uninstallPath)
{
    //Clear file list
    folderLists.clear();
    fileLists.clear();

    //Create file list
    QStringList filter;
    QDir *dir=new QDir(uninstallPath);
    QList<QFileInfo> *list=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(QList<QFileInfo>::iterator i=list->begin();
        i!=list->end();
        ++i)
    {
        if(i->fileName()=="." || i->fileName()=="..")
        {
            continue;
        }
        if(i->isFile())
        {
            fileLists.append(i->absoluteFilePath());
        }
        else
        {
            folderLists.append(i->absoluteFilePath());
        }
    }

    //Create bat file for delete uninstall itself.
    /*
     * We will create a temp file at the root of the disk.
     * e.g.: Cuties is set up at D:\Program Files\Kreogist\Cuties\,
     * we will write to D:\cuties_clear.bat.
     */
    QFileInfo meFile(QApplication::applicationFilePath());
    QString windowsApplicationFilePath=meFile.fileName();
    windowsApplicationFilePath.replace("/","\\");
    tempFileTextOut=QString("@echo off\ntaskkill /F /IM " +
                            windowsApplicationFilePath + "\n");

    return fileLists.count()+folderLists.count();
}

void KCUninstallerGlobal::uninstallIt()
{
    ;
}

void KCUninstallerGlobal::flushCommand(const QString &text)
{
    tempFileTextOut.append(text);
}

void KCUninstallerGlobal::flushToBat()
{
    tempFilePath=QApplication::applicationDirPath().left(3)+
            "cuties_clear.bat";
    QFile tempFile(tempFilePath);
    flushCommand(QString("del %0\n"));

    if(tempFile.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QTextStream tempFileOutputStream(&tempFile);
        tempFileOutputStream<<tempFileTextOut<<flush;
    }
    tempFile.close();
}
