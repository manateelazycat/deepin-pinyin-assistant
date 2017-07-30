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
#include "main_window.h"
#include <QCoreApplication>
#include <DApplication>
#include <DMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <DWidgetUtil>
#include <iostream>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();

    DApplication app(argc, argv);

    const QString socket_path(QString("deepin-pinyin-assistant"));
    if (app.setSingleInstance(socket_path)) {
        app.loadTranslator();

        const QString descriptionText = QApplication::tr("Deepin Font Installer is a simple font installer");

        const QString acknowledgementLink = "https://www.deepin.org/acknowledgments/deepin-pinyin-assistant#thanks";

        app.setOrganizationName("deepin");
        app.setApplicationName("deepin-pinyin-assistant");
        app.setApplicationDisplayName(QObject::tr("Deepin Font Installer"));
        app.setApplicationVersion("1.0");

        app.setProductIcon(QPixmap::fromImage(QImage(Utils::getQrcPath("logo_96.svg"))));
        app.setProductName(QApplication::tr("Deepin Font Installer"));
        app.setApplicationDescription(descriptionText);
        app.setApplicationAcknowledgementPage(acknowledgementLink);

        app.setWindowIcon(QIcon(Utils::getQrcPath("logo_48.png")));

        MainWindow window;

        QObject::connect(&app, &DApplication::newInstanceStarted, &window, &MainWindow::startListen);
        
        int width = 800;
        int height = 150;
        window.setFixedSize(width, height);
        window.move((QApplication::desktop()->screen()->rect().width() - width) / 2, 0);
        window.show();
        
        return app.exec();
    }

    return 0;
}
