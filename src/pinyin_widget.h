#ifndef PINYINWIDGET_H
#define PINYINWIDGET_H

#include <QWidget>

class PinyinWidget : public QWidget
{
    Q_OBJECT
    
public:
    PinyinWidget(QWidget *parent = 0);
    
    void setPinyin(QStringList chineseWords, QStringList pinyinWords);
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    QStringList chineseWords;
    QStringList pinyinWords;
};

#endif
