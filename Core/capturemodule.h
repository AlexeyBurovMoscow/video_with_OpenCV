#ifndef CAPTUREMODULE_H
#define CAPTUREMODULE_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include <QString>
#include <QSize>
#include <QPen>
#include <QFont>
#include <QRect>

#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/cv.h>
#include <Core/irenderprocess.h>

namespace Core {

    using namespace Interface;

    //main module for image processing
    class CaptureModule : public QObject
    {
        Q_OBJECT

    public:

        explicit CaptureModule(QObject* parent = 0);
        ~CaptureModule();

        //module interface
        bool isOpened() const;

        //open capture module by file
        bool open(const QString& fileName);

        //open capture module by index
        bool open(int index);

        //return fps
        double fps() const;

        //get frame width
        double frameWidth() const;

        //get frame height
        double frameHeight() const;

        //get frame size
        QSize frameSize() const;

        //controll interface

        //render start command, should be use after capture device opened
        void startRender(int msec);

        //render stop
        void stopRender();

        //close module
        void close();

        //fast render end
        void release();

        //setup image processing
        void setProcessing(IRenderProcess* process);

        //remove process
        void clearProcessing();

        //get image processing, returns nullptr if no process in time
        IRenderProcess* imageProcess() const;

        //get max frame count
        double frameCount() const;

        //set frame number layer on image
        void setFrameNumberLayer(bool render);

        //setup frame number layer
        void setFrameNumberLayerPen(const QPen& pen);
        void setFrameNumberLayerFont(const QFont& font);
        void setFrameNumberLayerText(const QString& text);
        void setFrameNumberLayerRect(const QRect& rect);

        //move to frame
        bool moveToFrame(double frameNumber);
        bool moveToStartFrame();
        void moveToNextFrame();

    private:

        //frame values
        float _fps = 25.0f;

        //update timer
        QTimer* captureUpdater = nullptr;

        //openCV
        cv::VideoCapture frameCapture;
        cv::Mat frameMatrix;

        //process interface
        IRenderProcess* renderProcessing = nullptr;

        //layer flag
        bool renderCurrentFrameNumber = false;
        QPen painterPen = QPen(Qt::red);
        QFont painterFont = QFont("Times", 12, QFont::Bold);
        QString painterText = "";
        QRect painterRect = QRect(0, 0, 60, 20);

    private slots:

        //tick on timer
        void capture();

    signals:

        //signal of updater tick
        void renderProcess(QImage image, double curFrameNum);

        //signal of the end of render process
        void renderProcessEnd();
    };
}

#endif // CAPTUREMODULE_H
