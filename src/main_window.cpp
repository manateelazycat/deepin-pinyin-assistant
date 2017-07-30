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
#include "chinese2pinyin.h"

using namespace std;
using namespace Pinyin;

MainWindow::MainWindow(DMainWindow *parent) : DMainWindow(parent)
{
    // Init.
    installEventFilter(this);   // add event filter
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::BypassWindowManagerHint);

    // Init titlebar.
    if (this->titlebar()) {
        this->titlebar()->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    // Init background.
    DThemeManager::instance()->setTheme("light");
    setAttribute(Qt::WA_TranslucentBackground);
    setEnableBlurWindow(true);
    setTranslucentBackground(true);
    
    // Init time.
    recordingTime = 0;
    
    
    // Init widget.
    waveform = new Waveform();
    pinyinWidget = new PinyinWidget();
    
    layoutWidget = new QWidget();
    this->setCentralWidget(layoutWidget);
    
    stackedLayout = new QStackedLayout();
    layoutWidget->setLayout(stackedLayout);
    
    stackedLayout->addWidget(waveform);
    stackedLayout->addWidget(pinyinWidget);
    
    // Init audio recorder.
    audioRecorder = new QAudioRecorder(this);
    
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/PCM");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setEncodingSettings(audioSettings);
    audioRecorder->setContainerFormat("wav");

    audioProbe = new QAudioProbe(this);
    if (audioProbe->setSource(audioRecorder)) {
        connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(renderLevel(QAudioBuffer)));
    }

    // Start listen.
    connect(&listenVoice, &ListenVoice::voiceText, this, &MainWindow::showPinyin, Qt::QueuedConnection);
    startListen();
}

MainWindow::~MainWindow()
{
    // We don't need clean pointers because application has exit here.
}

void MainWindow::startListen()
{
    qDebug() << "Start listen";
    
    stackedLayout->setCurrentIndex(0);
    
    QDateTime currentTime = QDateTime::currentDateTime();
    lastUpdateTime = currentTime;
    audioRecorder->record();
    listenVoice.startListen();
}

void MainWindow::showPinyin(QString text)
{
    stackedLayout->setCurrentIndex(1);
    
    pinyinWidget->setPinyin(Pinyin::splitChinese(text), Pinyin::splitChineseToPinyin(text));
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QApplication::quit();
    }
    
    return false;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    
}

void MainWindow::renderLevel(const QAudioBuffer &buffer)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    recordingTime += lastUpdateTime.msecsTo(currentTime);
    lastUpdateTime = currentTime;

    QVector<qreal> levels = Waveform::getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i) {
        waveform->updateWave(levels.at(i));
    }
}
