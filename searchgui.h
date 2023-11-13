#ifndef SEARCHGUI_H
#define SEARCHGUI_H

#include <QMainWindow>
#include <GUI/renderwindow.h>
#include <GUI/selectionwindow.h>
#include <GUI/controlwindow.h>

namespace Ui {
    class SearchGUI;
}

//project main gui
class SearchGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchGUI(QWidget *parent = 0);
    ~SearchGUI();

private:

    Ui::SearchGUI *ui;
    Ui::RenderWindow* renderWidget;
    Ui::SelectionWindow* selectionWidget;
    Ui::ControlWindow* controlWidget;

    int updateTime = 40;

private slots:

    void onVideoOpened(const QString& fileName);
    void onPlayStateChanged(bool state);
    void onStop();
    void onMove(double frame);
    void onError(const QString& error);
    void onFrameRender(bool state);
    void onMoveNext();
    void onFpsChanged(int msec);
};

#endif // SEARCHGUI_H
