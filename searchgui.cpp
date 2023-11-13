#include "searchgui.h"
#include "ui_searchgui.h"
#include <QDebug>

SearchGUI::SearchGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchGUI),
    renderWidget(new Ui::RenderWindow()),
    selectionWidget(new Ui::SelectionWindow()),
    controlWidget(new Ui::ControlWindow())
{
    ui->setupUi(this);
    setWindowTitle("Perigey Power");

    setCentralWidget(renderWidget);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, selectionWidget);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, controlWidget);

    updateTime = 1000/controlWidget->getFps();

    QObject::connect(selectionWidget, SIGNAL(videoOpened(QString)), SLOT(onVideoOpened(QString)));
    QObject::connect(controlWidget, SIGNAL(stateChanged(bool)), SLOT(onPlayStateChanged(bool)));
    QObject::connect(controlWidget, SIGNAL(stopState()), SLOT(onStop()));
    QObject::connect(controlWidget, SIGNAL(errorReceived(QString)), SLOT(onError(QString)));
    QObject::connect(controlWidget, SIGNAL(moveState(double)), SLOT(onMove(double)));
    QObject::connect(controlWidget, SIGNAL(renderFrameStateChanged(bool)), SLOT(onFrameRender(bool)));
    QObject::connect(controlWidget, SIGNAL(moveNext()), SLOT(onMoveNext()));
    QObject::connect(controlWidget, SIGNAL(frameRateChanged(int)), SLOT(onFpsChanged(int)));
}

SearchGUI::~SearchGUI()
{
    delete ui;

    if (renderWidget->captureModule().isOpened())
        renderWidget->captureModule().release();
}

void SearchGUI::onVideoOpened(const QString &fileName)
{
    if (renderWidget->captureModule().open(fileName))
        controlWidget->setPlayState(selectionWidget->renderOnOpen());// открытие видео
    else
        ui->statusBar->showMessage("Can not open file", 2000);
}

void SearchGUI::onPlayStateChanged(bool state)
{
    state ? renderWidget->captureModule().startRender(updateTime) : renderWidget->captureModule().stopRender();
}

void SearchGUI::onStop()
{
    renderWidget->captureModule().stopRender();
    renderWidget->captureModule().moveToStartFrame();
}

void SearchGUI::onMove(double frame)
{
    if (!renderWidget->captureModule().moveToFrame(frame))
        ui->statusBar->showMessage("Wrong frame number", 2000);
}

void SearchGUI::onError(const QString &error)
{
    ui->statusBar->showMessage(error, 2000);
}

void SearchGUI::onFrameRender(bool state)
{
    renderWidget->captureModule().setFrameNumberLayer(state);
}

void SearchGUI::onMoveNext()
{
    if (!controlWidget->getPlayState())
        renderWidget->captureModule().moveToNextFrame();
    else
        ui->statusBar->showMessage("Use move next only in pause mode", 2000);
}

void SearchGUI::onFpsChanged(int msec)
{
    updateTime = msec;

    if (controlWidget->getPlayState())
    {
        renderWidget->captureModule().stopRender();
        renderWidget->captureModule().startRender(updateTime);
    }
}
