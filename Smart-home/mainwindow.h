#pragma once
#include <QMainWindow>
#include <QTimer>

#include "SmartHome.h"
#include "Devices.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnShow_clicked();
    void on_btnLightsOn_clicked();
    void on_btnSetTemp_clicked();
    void on_btnSimulateMotion_clicked();
    void on_btnClearMotion_clicked();
    void on_sliderBrightness_valueChanged(int value);
    void updateSimulation();     // QTimer slot

private:
    Ui::MainWindow *ui;
    SmartHome home;
    QTimer* timer;

    void showHomeStatus();
};
