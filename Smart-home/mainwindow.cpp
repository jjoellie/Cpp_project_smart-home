// Vraag 42, 43, 47: Qt GUI + signals/slots

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    home("Joel"),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    smarthome::Room living("Living Room");
    living.addDevice(std::make_unique<smarthome::Light>(1,"Ceiling","Living",100));
    living.addDevice(std::make_unique<smarthome::Thermostat>(2,"Thermostat","Living",22));
    living.addDevice(std::make_unique<smarthome::MotionSensor>(3,"Motion","Living"));

    home.addRoom(std::move(living));

    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr; // Vraag 37: nullptr usage
}

void MainWindow::updateSimulation()
{
    home.updateAll();
}
