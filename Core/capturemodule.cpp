#include "capturemodule.h"
#include <QMutex>
#include <QMutexLocker>
#include <QPainter>

Core::CaptureModule::CaptureModule(QObject *parent):
    QObject(parent)
{
    captureUpdater = new QTimer();

    QObject::connect(captureUpdater, SIGNAL(timeout()), SLOT(capture()));
}

Core::CaptureModule::~CaptureModule()
{
    delete captureUpdater;
}

bool Core::CaptureModule::isOpened() const
{
    return frameCapture.isOpened();
}

bool Core::CaptureModule::open(const QString &fileName)
{
    frameCapture.open(fileName.toStdString().c_str());

    if (frameCapture.isOpened())
        frameCapture.set(cv::CAP_PROP_FPS, _fps);

    return frameCapture.isOpened();
}

bool Core::CaptureModule::open(int index)
{
    frameCapture.open(index);

    if (frameCapture.isOpened())
        frameCapture.set(cv::CAP_PROP_FPS, _fps);

    return frameCapture.isOpened();
}

double Core::CaptureModule::fps() const
{
    return frameCapture.get(cv::CAP_PROP_FPS);
}

double Core::CaptureModule::frameWidth() const
{
    return frameCapture.get(cv::CAP_PROP_FRAME_WIDTH);
}

double Core::CaptureModule::frameHeight() const
{
    return frameCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
}

QSize Core::CaptureModule::frameSize() const
{
    return QSize(frameCapture.get(cv::CAP_PROP_FRAME_WIDTH), frameCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
}

void Core::CaptureModule::startRender(int msec)
{
    captureUpdater->start(msec);
}

void Core::CaptureModule::stopRender()
{
    captureUpdater->stop();
}

void Core::CaptureModule::close()
{
    frameCapture.release();
}

void Core::CaptureModule::release()
{
    captureUpdater->stop();
    frameCapture.release();
}

void Core::CaptureModule::setProcessing(Interface::IRenderProcess* process)
{
    QMutex mutex;
    QMutexLocker lock(&mutex);

    renderProcessing = process;
}

void Core::CaptureModule::clearProcessing()
{
    QMutex mutex;
    QMutexLocker lock(&mutex);

    renderProcessing = nullptr;
}

Interface::IRenderProcess* Core::CaptureModule::imageProcess() const
{
    return renderProcessing;
}

double Core::CaptureModule::frameCount() const
{
    return frameCapture.get(CV_CAP_PROP_FRAME_COUNT);
}

void Core::CaptureModule::setFrameNumberLayer(bool render)
{
    renderCurrentFrameNumber = render;
}

void Core::CaptureModule::setFrameNumberLayerPen(const QPen &pen)
{
    painterPen = pen;
}

void Core::CaptureModule::setFrameNumberLayerFont(const QFont &font)
{
    painterFont = font;
}

void Core::CaptureModule::setFrameNumberLayerText(const QString &text)
{
    painterText = text;
}

void Core::CaptureModule::setFrameNumberLayerRect(const QRect &rect)
{
    painterRect = rect;
}

bool Core::CaptureModule::moveToFrame(double frameNumber)
{
    auto flag = frameCapture.set(CV_CAP_PROP_POS_FRAMES, frameNumber - 1);
    if (flag)
        capture();

    return flag;
}

bool Core::CaptureModule::moveToStartFrame()
{
    return frameCapture.set(CV_CAP_PROP_POS_FRAMES, 0);
}

void Core::CaptureModule::moveToNextFrame()
{
    capture();
}

void Core::CaptureModule::capture()
{
    if (frameCapture.read(frameMatrix))
    {
        cv::cvtColor(frameMatrix, frameMatrix, CV_BGR2RGB);
        QImage img(frameMatrix.data, frameMatrix.cols, frameMatrix.rows, frameMatrix.step, QImage::Format_RGB888);
        auto currentFrame = frameCapture.get(CV_CAP_PROP_POS_FRAMES);

        if (renderProcessing)
            renderProcessing->imageProcessing(img);

        if (renderCurrentFrameNumber)
        {
            QPainter painter(&img);
            painter.setPen(painterPen);
            painter.setFont(painterFont);
            painter.drawText(painterRect, painterText + " " + QString::number(currentFrame));
        }

        //generate signal
        emit renderProcess(img.convertToFormat(QImage::Format_ARGB32), currentFrame);
    }
    else
    {
        captureUpdater->stop();

        //the end
        emit renderProcessEnd();
    }
}
