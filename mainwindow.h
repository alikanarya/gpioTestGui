#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;

private slots:

    void ConnectedToServer();
    void NotConnectedToServer();

    void displayInputs();
    void transferData();

    void on_dOUT1_clicked();
    void on_dOUT2_clicked();
    void on_dOUT3_clicked();
    void on_dOUT4_clicked();

    void on_aOut1_sliderReleased();

    void on_aOut2_sliderReleased();

    void on_aOut3_sliderReleased();

    void on_aOut4_sliderReleased();

signals:

    void connectTo();
    void sendData();
};

#endif // MAINWINDOW_H
