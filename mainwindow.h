#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QList<QImage> QImageList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnLoad_clicked();

    void clearLbl();

    void on_btnPrevPic_clicked();

    void on_btnNextPic_clicked();

    void getInfo(QImage);

    void on_checkBoxInfo_stateChanged(int arg1);

    void updateInfo();

    void scanImage(QImage);

    void markImage(int);

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    QImage picPrimary;
    QImage picPrevious;
    QImage picNext;
    QImage picClear;
    QImage logo;

    QImageList imageList;
    QStringList nameList;
    QStringList infoList;
    QList <int> rgbSearchList;
    QList <int> deviationList;
    QList <int> watermarkCoordinatesList;

    int watermarkCoordinates[2];

    int num = 0;
    int R = 0;
    int G = 0;
    int B = 0;
    int tmpRGB = 0;

    QString infoText  = "Info available";
};
#endif // MAINWINDOW_H
