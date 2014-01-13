/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Project Nerve.
 *
 *    Kreogist Nerve is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *    Kreogist Nerve is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  Kreogist Nerve. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \copyright GNU Public License v3
 * \details
 *
 */

#ifndef KCUNINSTALLERGLOBAL_H
#define KCUNINSTALLERGLOBAL_H

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QObject>

class KCUninstallerGlobal : public QObject
{
    Q_OBJECT
public:
    static KCUninstallerGlobal *getInstance();
    static bool removeDirectory(const QString &folderPath);
    static bool removeFile(const QString &filePath);
    int prepareUninstall(const QString &uninstallPath);
    void uninstallIt();
    void flushCommand(const QString &text);
    void flushToBat();

    QStringList getFileLists() const;
    QStringList getFolderLists() const;
    QString getTempFilePath() const;

signals:

public slots:

private:
    KCUninstallerGlobal();
    static KCUninstallerGlobal *instance;
    QStringList folderLists;
    QStringList fileLists;
    QString tempFilePath;
    QString tempFileTextOut;
};

#endif // KCUNINSTALLERGLOBAL_H
