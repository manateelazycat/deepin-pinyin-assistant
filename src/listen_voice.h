#ifndef LISTENVOICE_H
#define LISTENVOICE_H

#include <QThread>
#include <QObject>

class ListenVoice : public QThread
{
    Q_OBJECT
    
public:
    ListenVoice(QObject *parent = 0);
    
    void startListen();
    
    static void listenFromMicrophone(const char* sessionBeginParams);
    static void showResult(char *string, char isOver);
    static void resultHandler(const char *result, char isLast);
    static void speechBeginHandler();
    static void speechEndHandler(int reason);
    
signals:
    void voiceText(QString text);
    
protected:
    void run();
};

#endif

