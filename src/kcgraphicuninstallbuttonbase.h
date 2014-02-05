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

#ifndef KCGRAPHICUNINSTALLBUTTONBASE_H
#define KCGRAPHICUNINSTALLBUTTONBASE_H

#include <QEvent>
#include <QTimeLine>
#include <QMouseEvent>
#include <QLabel>

#include <QWidget>

class KCGraphicUninstallButtonBase : public QWidget
{
    Q_OBJECT
public:
    explicit KCGraphicUninstallButtonBase(QWidget *parent = 0);
    void setButtonPixmap(const QString &filePath);
    void animateDisabled();

signals:
    void clicked();

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:

private slots:
    void changeBackgroundAlpha(int alpha);

private:
    static int normalBackgroundAlpha;
    static int hoverBackgroundAlpha;
    static int pressBackgroundAlpha;

    QPalette pal;
    QColor backgroundColor;
    int backgroundAlpha;
    QTimeLine *animation;
    QLabel *buttonGraphic;
    QLabel *buttonText;
    bool enabled=true;
};

#endif // KCGRAPHICUNINSTALLBUTTONBASE_H

