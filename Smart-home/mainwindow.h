#pragma once

#include <QMainWindow>
#include <QTimer>

// Vraag 6: separate header files
#include "SmartHome.h"
#include "Devices.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Vraag 42: useful Qt class
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Vraag 43: signals / slots
    void on_btnShow_clicked();
    void on_btnLightsOn_clicked();
    void on_btnLightsOff_clicked();
    void on_btnSetTemp_clicked();
    void on_btnSimulateMotion_clicked();
    void on_btnClearMotion_clicked();
    void on_sliderBrightness_valueChanged(int value);

    // Vraag 20: useful member function
    void updateSimulation();

private:
    // Vraag 3: no globals
    Ui::MainWindow *ui;

    // Vraag 27: namespace usage
    smarthome::SmartHome home;

    // Vraag 42: Qt classes
    QTimer* timer;
    QTimer* motionTimer;   // Vraag 51: nice extra (motion timeout)

    void showHomeStatus();
};
