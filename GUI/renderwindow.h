#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <Core/capturemodule.h>

namespace Ui {

    //central widget for image render
    class RenderWindow : public QWidget
    {
        Q_OBJECT

    public:

        explicit RenderWindow(QWidget* parent = 0);

        //interface

        //get render module
        Core::CaptureModule& captureModule() const;

    private:

        //label for data render
        QLabel* renderLabel;

        //Max label size
        QSize maxSize = QSize(1024, 768);

        //core capture
        Core::CaptureModule* renderModule;

    private slots:

        //render to label
        void imageRendering(QImage image, double currentFrameNumber);

        //stop render
        void imageRenderingEnded();
    };

}

#endif // RENDERWINDOW_H
