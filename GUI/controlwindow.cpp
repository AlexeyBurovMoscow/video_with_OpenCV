#include "controlwindow.h"
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QBitmap>
#include <Core/capturemodule.h>

Ui::ControlWindow::ControlWindow(QWidget* parent):
    QDockWidget(parent)
{
    QWidget* widget = new QWidget();

    playButton = new QPushButton(widget);
    playButton->setIcon(QIcon((":/Images/play.png")));

    stopButton = new QPushButton(widget);
    stopButton->setIcon(QIcon(":/Images/stop.png"));

    moveButton = new QPushButton(widget);
    moveButton->setIcon(QIcon(":/Images/move.png"));

    moveEdit = new QLineEdit(widget);

    nextButton = new QPushButton("Next frame", widget);

    fpsEdit = new QLineEdit("25", widget);

    QHBoxLayout* hLay = new QHBoxLayout();
    hLay->addWidget(playButton);
    hLay->addWidget(stopButton);

    QLabel* moveLabel = new QLabel("move to frame");
    frameRenderCheck = new QCheckBox("Render frames", widget);

    QHBoxLayout* bottomHLay = new QHBoxLayout();
    bottomHLay->addWidget(nextButton);
    bottomHLay->addWidget(moveButton);
    bottomHLay->addWidget(moveLabel);
    bottomHLay->addWidget(moveEdit);

    QLabel* fpsLabel = new QLabel("Fps: ");
    fpsLabel->setBuddy(fpsEdit);

    QHBoxLayout* fpsLay = new QHBoxLayout();
    fpsLay->addWidget(fpsLabel);
    fpsLay->addWidget(fpsEdit);
    fpsLay->addStretch(1);

    QVBoxLayout* vLay = new QVBoxLayout();
    vLay->addLayout(hLay);
    vLay->addLayout(bottomHLay);
    vLay->addLayout(fpsLay);
    vLay->addWidget(frameRenderCheck);
    vLay->addStretch(1);

    //stretch lay
    QHBoxLayout* stretchLay = new QHBoxLayout();
    stretchLay->addLayout(vLay);
    stretchLay->addStretch(1);

    widget->setLayout(stretchLay);
    setWidget(widget);

    QObject::connect(playButton, &QPushButton::clicked, this, &ControlWindow::play);
    QObject::connect(stopButton, &QPushButton::clicked, this, &ControlWindow::stop);
    QObject::connect(moveButton, &QPushButton::clicked, this, &ControlWindow::move);
    QObject::connect(frameRenderCheck, &QCheckBox::stateChanged, this, &ControlWindow::renderFrameStateChanged);
    QObject::connect(fpsEdit, &QLineEdit::editingFinished, this, &ControlWindow::fps);
    QObject::connect(nextButton, &QPushButton::clicked, this, &ControlWindow::moveNextSlot);
}

int Ui::ControlWindow::getFps() const
{
    return fpsEdit->text().toInt();
}

bool Ui::ControlWindow::getPlayState() const
{
    return playState;
}

void Ui::ControlWindow::changeIcon()
{
    playState ? playButton->setIcon(QIcon((":/Images/pause.png"))) : playButton->setIcon(QIcon((":/Images/play.png")));
}

void Ui::ControlWindow::play()
{
    playState = !playState;
    changeIcon();

    emit stateChanged(playState);
}

void Ui::ControlWindow::stop()
{
    playState = false;
    changeIcon();

    emit stopState();
}

void Ui::ControlWindow::setPlayState(bool state)
{
    playState = state;
    changeIcon();

    emit stateChanged(playState);
}

void Ui::ControlWindow::move()
{
    auto isOk = false;
    auto frameNum = moveEdit->text().toDouble(&isOk);

    if (isOk)
        emit moveState(frameNum);
    else
        emit errorReceived("Wrong frame number");
}

void Ui::ControlWindow::fps()
{
    auto isOk = false;
    auto value = fpsEdit->text().toInt(&isOk);

    //emit
    isOk ? frameRateChanged(1000/value) : errorReceived("Wrong fps");
}

void Ui::ControlWindow::moveNextSlot()
{
    if (!playState)
        emit moveNext();
}
