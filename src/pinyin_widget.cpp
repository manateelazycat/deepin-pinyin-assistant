#include "pinyin_widget.h"
#include "utils.h"
#include <QPaintEvent>
#include <QPainter>

PinyinWidget::PinyinWidget(QWidget *parent) : QWidget(parent)
{
    
}

void PinyinWidget::setPinyin(QStringList cWords, QStringList pWords)
{
    chineseWords = cWords;
    pinyinWords = pWords;
    
    repaint();
}

void PinyinWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    
    int x = 0;
    int wordWidth = 60;
    
    int pinyinRenderY = 0;
    int chineseRenderY = 30;
    
    int paddingX = 20;
    
    for (int i = 0; i < chineseWords.length(); i++) {
        Utils::setFontSize(painter, 12);
        painter.setPen(QPen(QColor("#2CA7F8")));
        painter.drawText(QRect(paddingX + x, pinyinRenderY, rect().width() - x, rect().height()), Qt::AlignLeft | Qt::AlignTop, pinyinWords[i].toUpper());
        
        Utils::setFontSize(painter, 16);
        painter.setPen(QPen(QColor("#333333")));
        painter.drawText(QRect(paddingX + x, chineseRenderY, rect().width() - x, rect().height()), Qt::AlignLeft | Qt::AlignTop, chineseWords[i]);
        
        x += wordWidth;
    }
}

