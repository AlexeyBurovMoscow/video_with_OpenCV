#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QCheckBox>
#include <QLineEdit>

namespace Core {
    class CaptureModule;
}

namespace Ui {

    //ui for user capture module control
    class ControlWindow : public QDockWidget
    {
        Q_OBJECT

    public:

        explicit ControlWindow(QWidget* parent = nullptr);

        //get fps setup
        int getFps() const;

        //main state
        bool getPlayState() const;

    private:

        //play/pause button
        QPushButton* playButton;

        //stop button
        QPushButton* stopButton;

        //go to frame
        QPushButton* moveButton;

        //go to next frame
        QPushButton* nextButton;

        //frame move number
        QLineEdit* moveEdit;

        //fps edit
        QLineEdit* fpsEdit;

        //frame control element
        QCheckBox* frameRenderCheck;

        //play flag
        bool playState = false;

        //helper
        void changeIcon();

    public slots:

        //on play button pressed
        void play();

        //on stop button pressed
        void stop();

        //control state
        void setPlayState(bool state);

    private slots:

        //move to frame
        void move();

        //fps recalculation
        void fps();

        //prepare
        void moveNextSlot();

    signals:

        //play state emit
        void stateChanged(bool state);
        void stopState();

        //move to next frame
        void moveNext();

        //move to
        void moveState(double frame);

        //error
        void errorReceived(const QString& error);

        //render frame state
        void renderFrameStateChanged(bool state);

        //fps changed
        void frameRateChanged(int fps);
    };

}

#endif // CONTROLWINDOW_H
