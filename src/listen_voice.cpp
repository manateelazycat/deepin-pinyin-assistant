#include "listen_voice.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "speech_recognizer.h"
#include <QDebug>

#define FRAME_LEN   640
#define BUFFER_SIZE 4096

static char *recognizeResult = NULL;
static unsigned int resultBufferSize = BUFFER_SIZE;
static bool speakDone = false;
static QString text = "";

void ListenVoice::showResult(char *string, char)
{
    text = QString::fromStdString(string);
}

void ListenVoice::resultHandler(const char *result, char isLast)
{
    if (result) {
        size_t left = resultBufferSize - 1 - strlen(recognizeResult);
        size_t size = strlen(result);
        if (left < size) {
            recognizeResult = (char*)realloc(recognizeResult, resultBufferSize + BUFFER_SIZE);
            if (recognizeResult)
                resultBufferSize += BUFFER_SIZE;
            else {
                printf("mem alloc failed\n");
                return;
            }
        }
        strncat(recognizeResult, result, size);
        ListenVoice::showResult(recognizeResult, isLast);
    }
}

void ListenVoice::speechBeginHandler()
{
    if (recognizeResult) {
        free(recognizeResult);
    }
    
    recognizeResult = (char*)malloc(BUFFER_SIZE);
    resultBufferSize = BUFFER_SIZE;
    memset(recognizeResult, 0, resultBufferSize);

    printf("Start Listening...\n");
}

void ListenVoice::speechEndHandler(int reason)
{
    if (reason == END_REASON_VAD_DETECT) {
        printf("\nSpeaking done \n");
        
        speakDone = true;
    } else {
        printf("\nRecognizer error %d\n", reason);
    }
}

/* demo recognize the audio from microphone */
void ListenVoice::listenFromMicrophone(const char* sessionBeginParams)
{
    int errcode;
    int i = 0;

    struct speech_rec iat;

    struct speech_rec_notifier recnotifier = {
        ListenVoice::resultHandler,
        ListenVoice::speechBeginHandler,
        ListenVoice::speechEndHandler
    };

    errcode = sr_init(&iat, sessionBeginParams, SR_MIC, &recnotifier);
    if (errcode) {
        printf("speech recognizer init failed\n");
        return;
    }
    
    errcode = sr_start_listening(&iat);
    if (errcode) {
        printf("start listen failed %d\n", errcode);
    }
    
    /* demo 15 seconds recording */
    while (!speakDone && i++ < 15) {
        sleep(1);
    }
    
    errcode = sr_stop_listening(&iat);
    if (errcode) {
        printf("stop listening failed %d\n", errcode);
    }

    sr_uninit(&iat);
}

ListenVoice::ListenVoice(QObject *parent) : QThread(parent)
{

}

void ListenVoice::run()
{
    int ret = MSP_SUCCESS;
    const char* loginParams = "appid = 513e0a70, work_dir = .";
    
    /*
     * See "iFlytek MSC Reference Manual"
     */
    const char* sessionBeginParams =
        "sub = iat, domain = iat, language = zh_cn, "
        "accent = mandarin, sample_rate = 16000, "
        "result_type = plain, result_encoding = utf8";

    /* Login first. the 1st arg is username, the 2nd arg is password
     * just set them as NULL. the 3rd arg is login paramertes
     * */
    ret = MSPLogin(NULL, NULL, loginParams);
    if (MSP_SUCCESS != ret) {
        printf("MSPLogin failed , Error code %d.\n",ret);
        MSPLogout(); // Logout...
        return;
    }

    printf("Demo recognizing the speech from microphone\n");
    printf("Speak in 15 seconds\n");

    speakDone = false;
    text = "";
    ListenVoice::listenFromMicrophone(sessionBeginParams);

    voiceText(text);
}

void ListenVoice::startListen()
{
    QThread::start();
}
