#include "renderwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

Ui::RenderWindow::RenderWindow(QWidget *parent) : QWidget(parent)
{
    renderLabel = new QLabel();
    renderLabel->setScaledContents(true);
    renderLabel->setMaximumWidth(maxSize.width());
    renderLabel->setMaximumHeight(maxSize.height());
    renderModule = new Core::CaptureModule(this);

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(renderLabel);
    lay->addStretch(1);

    QVBoxLayout* vLay = new QVBoxLayout();
    vLay->addLayout(lay);
    vLay->addStretch(1);

    setLayout(vLay);

    QObject::connect(renderModule, SIGNAL(renderProcess(QImage, double)), SLOT(imageRendering(QImage, double)));
    QObject::connect(renderModule, SIGNAL(renderProcessEnd()), SLOT(imageRenderingEnded()));
}

Core::CaptureModule& Ui::RenderWindow::captureModule() const
{
    return *renderModule;
}

void Ui::RenderWindow::imageRendering(QImage image, double currentFrameNumber)
{
    Q_UNUSED(currentFrameNumber)

    auto pix = QPixmap::fromImage(image);

    if (pix.size().width() >= renderLabel->maximumWidth() || pix.size().height() >= renderLabel->maximumHeight())
        pix = pix.scaled(renderLabel->maximumWidth(), renderLabel->maximumHeight(), Qt::KeepAspectRatio);

    renderLabel->setPixmap(pix);
}

void Ui::RenderWindow::imageRenderingEnded()
{
    //renderLabel->setPixmap(QPixmap());
}
