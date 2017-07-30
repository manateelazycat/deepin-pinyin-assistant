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

#include "dthememanager.h"
#include "dwindowmanagerhelper.h"
#include "main_window.h"
#include <DTitlebar>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QStyleFactory>
#include <iostream>
#include <signal.h>

using namespace std;

MainWindow::MainWindow(DMainWindow *parent) : DMainWindow(parent)
{
    installEventFilter(this);   // add event filter

    if (this->titlebar()) {
        this->titlebar()->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        this->setFixedSize(478, 379);
    }

    DThemeManager::instance()->setTheme("light");

    listenVoice.startListen();
}

MainWindow::~MainWindow()
{
    // We don't need clean pointers because application has exit here.
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    return false;
}

void MainWindow::paintEvent(QPaintEvent *)
{
}
