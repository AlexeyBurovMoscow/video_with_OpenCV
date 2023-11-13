#include "selectionwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>

Ui::SelectionWindow::SelectionWindow(QWidget* parent) :
    QDockWidget(parent)
{
    QWidget* widget = new QWidget();

    videoButton = new QPushButton("Выбор видео", widget);
    sampleButton = new QPushButton("Выбор эталона", widget);
    playCheck = new QCheckBox("Play on open", widget);
    playCheck->setChecked(true);

    sampleRenderLabel = new QLabel(widget);
    sampleLabel = new QLabel(widget);

    QVBoxLayout* lay = new QVBoxLayout();
    lay->addWidget(videoButton);
    lay->addWidget(sampleButton);
    lay->addWidget(playCheck);
    lay->addWidget(sampleRenderLabel);
    lay->addWidget(sampleLabel);
    lay->addStretch(1);

    widget->setLayout(lay);
    setWidget(widget);

    QObject::connect(videoButton, SIGNAL(clicked(bool)), SLOT(openVideo()));
    QObject::connect(sampleButton, SIGNAL(clicked(bool)), SLOT(openSample()));
}

bool Ui::SelectionWindow::renderOnOpen() const
{
    return playCheck->isChecked();
}

void Ui::SelectionWindow::showImageStats(const QImage &image)
{
    sampleLabel->setText("Size: " + QString::number(image.width()) + "x" + QString::number(image.height()));
    sampleRenderLabel->setMinimumSize(image.width(), image.height());
}

void Ui::SelectionWindow::openVideo()
{
    videoFileName = QFileDialog::getOpenFileName(this, "Выбор видео", "", QObject::tr("Video Files (*.avi *.mpeg) ;; All()"));

    emit videoOpened(videoFileName);
}

void Ui::SelectionWindow::openSample()
{
    sampleFileName = QFileDialog::getOpenFileName(this, "Выбор эталона", "", QObject::tr("Sample Files (*.bmp *.jpeg *.png *.jpg)"));

    if (sampleFileName.size() != 0)
    {
        QImage image;

        if (image.load(sampleFileName))
        {
            sampleRenderLabel->setPixmap(QPixmap::fromImage(image));
            showImageStats(image);
        }
    }
}
