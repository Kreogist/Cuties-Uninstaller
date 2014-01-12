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

#include <QBitmap>
#include <QPainter>
#include <QHBoxLayout>

#include "KCGraphicUninstallButtonBase.h"

int KCGraphicUninstallButtonBase::normalBackgroundAlpha=100;
int KCGraphicUninstallButtonBase::hoverBackgroundAlpha=255;
int KCGraphicUninstallButtonBase::pressBackgroundAlpha=200;

KCGraphicUninstallButtonBase::KCGraphicUninstallButtonBase(QWidget *parent) :
    QWidget(parent)
{
    //Set Properties.
    setAutoFillBackground(true);
    setFixedSize(256, 256);

    //Set Background color.
    pal=palette();
    backgroundAlpha=normalBackgroundAlpha;
    backgroundColor=QColor(255,255,255,backgroundAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);

    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);

    QHBoxLayout *buttonLayout=new QHBoxLayout(this);
    buttonLayout->setContentsMargins(0,0,0,0);
    buttonLayout->setSpacing(0);
    setLayout(buttonLayout);

    //Set label.
    buttonGraphic=new QLabel(this);
    buttonGraphic->setContentsMargins(0,0,0,0);
    buttonGraphic->setScaledContents(true);
    buttonGraphic->setFixedSize(128,128);
    buttonLayout->addWidget(buttonGraphic);

    animation=new QTimeLine(400, this);
    animation->setUpdateInterval(5);
    connect(animation, SIGNAL(frameChanged(int)),
            this, SLOT(changeBackgroundAlpha(int)));
}

void KCGraphicUninstallButtonBase::enterEvent(QEvent *e)
{
    if(!enabled)
    {
        e->ignore();
        return;
    }
    animation->stop();
    animation->setFrameRange(backgroundAlpha, hoverBackgroundAlpha);
    animation->start();
    QWidget::enterEvent(e);
}

void KCGraphicUninstallButtonBase::leaveEvent(QEvent *e)
{
    if(!enabled)
    {
        e->ignore();
        return;
    }
    animation->stop();
    animation->setFrameRange(backgroundAlpha, normalBackgroundAlpha);
    animation->start();
    QWidget::leaveEvent(e);
}

void KCGraphicUninstallButtonBase::mousePressEvent(QMouseEvent *event)
{
    if(!enabled)
    {
        event->ignore();
        return;
    }
    animation->stop();
    animation->setFrameRange(backgroundAlpha, pressBackgroundAlpha);
    animation->start();
    QWidget::mousePressEvent(event);
}

void KCGraphicUninstallButtonBase::mouseReleaseEvent(QMouseEvent *event)
{
    if(!enabled)
    {
        event->ignore();
        return;
    }
    animation->stop();
    animation->setFrameRange(backgroundAlpha, normalBackgroundAlpha);
    animation->start();
    emit clicked();
    QWidget::mouseReleaseEvent(event);
}

void KCGraphicUninstallButtonBase::changeBackgroundAlpha(int alpha)
{
    backgroundAlpha=alpha;
    backgroundColor.setAlpha(backgroundAlpha);
    pal.setColor(QPalette::Window, backgroundColor);
    setPalette(pal);
}

void KCGraphicUninstallButtonBase::setButtonPixmap(const QString &filePath)
{
    buttonGraphic->setPixmap(QPixmap(filePath));
}

void KCGraphicUninstallButtonBase::animateDisabled()
{
    setEnabled(false);
    enabled=false;
    buttonGraphic->hide();
    animation->stop();
    animation->setFrameRange(backgroundAlpha, 0);
    animation->start();
}
