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
    
protected:
    void run();
};

#endif

