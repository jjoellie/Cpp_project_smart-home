#pragma once
#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    SmartHome home;

    void showHomeStatus();
};

