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

#include "utils.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFontMetrics>
#include <QIcon>
#include <QLayout>
#include <QPainter>
#include <QPixmap>
#include <QStandardPaths>
#include <QString>
#include <QWidget>
#include <QtMath>
#include <QtX11Extras/QX11Info>
#include <X11/extensions/shape.h>
#include <fstream>
#include <qdiriterator.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <unordered_set>

namespace Utils {
    QSize getRenderSize(int fontSize, QString string)
    {
        QFont font;
        font.setPointSize(fontSize);
        QFontMetrics fm(font);

        int width = 0;
        int height = 0;
        foreach (auto line, string.split("\n")) {
            int lineWidth = fm.width(line);
            int lineHeight = fm.height();

            if (lineWidth > width) {
                width = lineWidth;
            }
            height += lineHeight;
        }

        return QSize(width, height);
    }

    QString getImagePath(QString imageName)
    {
        QDir dir(qApp->applicationDirPath());
        dir.cdUp();

        return QDir(dir.filePath("image")).filePath(imageName);
    }

    
    QString getQrcPath(QString imageName)
    {
        return QString(":/image/%1").arg(imageName);
    }

    QString getQssPath(QString qssName)
    {
        return QString(":/qss/%1").arg(qssName);
    }

    bool fileExists(QString path)
    {
        QFileInfo check_file(path);

        // check if file exists and if yes: Is it really a file and no directory?
        return check_file.exists() && check_file.isFile();
    }

    qreal easeInOut(qreal x)
    {
        return (1 - qCos(M_PI * x)) / 2;
    }

    qreal easeInQuad(qreal x)
    {
        return qPow(x, 2);
    }

    qreal easeOutQuad(qreal x)
    {
        return -1 * qPow(x - 1, 2) + 1;
    }

    qreal easeInQuint(qreal x)
    {
        return qPow(x, 5);
    }

    qreal easeOutQuint(qreal x)
    {
        return qPow(x - 1, 5) + 1;
    }

    void addLayoutWidget(QLayout *layout, QWidget *widget)
    {
        layout->addWidget(widget);
        widget->show();
    }

    void applyQss(QWidget *widget, QString qssName)
    {
        QFile file(getQssPath(qssName));
        file.open(QFile::ReadOnly);
        QTextStream filetext(&file);
        QString stylesheet = filetext.readAll();
        widget->setStyleSheet(stylesheet);
        file.close();
    }

    void removeChildren(QWidget *widget)
    {
        qDeleteAll(widget->children());
    }

    void removeLayoutChild(QLayout *layout, int index)
    {
        QLayoutItem *item = layout->itemAt(index);
        if (item != 0) {
            QWidget *widget = item->widget();
            if (widget != NULL) {
                widget->hide();
                widget->setParent(NULL);
                layout->removeWidget(widget);
            }
        }
    }

    void setFontSize(QPainter &painter, int textSize)
    {
        QFont font = painter.font() ;
        font.setPointSize(textSize);
        painter.setFont(font);
    }
}
