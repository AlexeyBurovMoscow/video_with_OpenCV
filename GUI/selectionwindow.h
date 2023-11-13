#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QCheckBox>

namespace Ui {

    //ui for user control
    class SelectionWindow : public QDockWidget
    {

        Q_OBJECT

    public:

        explicit SelectionWindow(QWidget* parent = nullptr);

        //get start render state
        bool renderOnOpen() const;

    private:

        //sample info
        QLabel* sampleLabel;

        //video choose
        QPushButton* videoButton;

        //play on start checkbox
        QCheckBox* playCheck;

        //sample choose
        QPushButton* sampleButton;

        //sample render label
        QLabel* sampleRenderLabel;

        //video file name
        QString videoFileName = "";

        //sample file name
        QString sampleFileName = "";

        //helper
        void showImageStats(const QImage& image);

    private slots:

        //open video
        void openVideo();

        //open sample picture
        void openSample();

    signals:

        //send video file name
        void videoOpened(const QString& fileName);
    };
}

#endif // SELECTIONWINDOW_H
