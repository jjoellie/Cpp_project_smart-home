#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , home("Joel")
{
    ui->setupUi(this);

    // Rooms
    Room living("Living Room");
    Room bed("Bedroom");

    // Devices
    living.addDevice(std::make_unique<Light>("Ceiling Light", "Living Room"));
    living.addDevice(std::make_unique<Thermostat>("Main Thermostat", "Living Room", 22.5));
    living.addDevice(std::make_unique<MotionSensor>("Entrance Sensor", "Living Room"));

    bed.addDevice(std::make_unique<Light>("Bedside Lamp", "Bedroom"));
    bed.addDevice(std::make_unique<Thermostat>("Bedroom Thermostat", "Bedroom", 20.0));

    home.addRoom(std::move(living));
    home.addRoom(std::move(bed));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showHomeStatus()
{
    ui->textEdit->clear();

    for (const auto& room : home.getRooms())
    {
        ui->textEdit->append("Room: " + QString::fromStdString(room.getName()));
        for (const auto& dev : room.getDevices())
        {
            ui->textEdit->append(
                QString::fromStdString("  - " + dev->getName()
                                       + " (" + dev->getTypeName() + ")"));
        }
        ui->textEdit->append("");
    }
}

void MainWindow::on_btnShow_clicked()
{
    showHomeStatus();
}

void MainWindow::on_btnLightsOn_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Light")
                dev->turnOn();

    showHomeStatus();
}
