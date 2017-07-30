/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UTILS_H
#define UTILS_H

#include <QFileInfoList>
#include <QLayout>
#include <QObject>
#include <QPainter>
#include <QString>

const int RECTANGLE_PADDING = 24;
const int RECTANGLE_RADIUS = 8;
const int RECTANGLE_FONT_SIZE = 11;

namespace Utils {
    QSize getRenderSize(int fontSize, QString string);
    QString getImagePath(QString imageName);
    QString getQrcPath(QString imageName);
    QString getQssPath(QString qssName);
    bool fileExists(QString path);
    qreal easeInOut(qreal x);
    qreal easeInQuad(qreal x);
    qreal easeInQuint(qreal x);
    qreal easeOutQuad(qreal x);
    qreal easeOutQuint(qreal x);
    void addLayoutWidget(QLayout *layout, QWidget *widget);
    void applyQss(QWidget *widget, QString qssName);
    void drawLoadingRing(QPainter &painter, 
                         int centerX, 
                         int centerY, 
                         int radius, 
                         int penWidth, 
                         int loadingAngle, 
                         int rotationAngle, 
                         QString foregroundColor, 
                         double foregroundOpacity,
                         QString backgroundColor, 
                         double backgroundOpacity,
                         double percent);
    void drawRing(QPainter &painter, int centerX, int centerY, int radius, int penWidth, int loadingAngle, int rotationAngle, QString color, double opacity);
    void removeChildren(QWidget *widget);
    void removeLayoutChild(QLayout *layout, int index);
    void setFontSize(QPainter &painter, int textSize);
}


#endif
