#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "compression.h"
#include "blocktransform.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QImage;
class Compression;
class BlockTransform;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buildRclDpcm_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage *image;
    Compression *jComp;
    BlockTransform *buildY;
    BlockTransform *buildU;
    BlockTransform *buildV;


    void createActions();
    void createMenus();
    void updateActions();



};

#endif // MAINWINDOW_H
