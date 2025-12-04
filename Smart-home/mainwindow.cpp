#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , home("Joel")
{
    ui->setupUi(this);

    Room living("Living Room");
    Room bed("Bedroom");

    living.addDevice(std::make_unique<Light>("Ceiling Light", "Living Room"));
    living.addDevice(std::make_unique<Thermostat>("Main Thermostat", "Living Room", 22.5));
    living.addDevice(std::make_unique<MotionSensor>("Entrance Sensor", "Living Room"));

    bed.addDevice(std::make_unique<Light>("Bedside Lamp", "Bedroom"));
    bed.addDevice(std::make_unique<Thermostat>("Bedroom Thermostat", "Bedroom", 20.0));

    home.addRoom(std::move(living));
    home.addRoom(std::move(bed));

    showHomeStatus();
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
            QString info = "  - ";
            info += QString::fromStdString(dev->getName()) + " (";
            info += QString::fromStdString(dev->getTypeName()) + ")";

            if (dev->getTypeName() == "Light")
            {
                const Light* l = dynamic_cast<const Light*>(dev.get());
                info += " | Brightness: " + QString::number(l->getBrightness()) + "%";
            }
            else if (dev->getTypeName() == "Thermostat")
            {
                const Thermostat* t = dynamic_cast<const Thermostat*>(dev.get());
                info += " | Current: " + QString::number(t->getCurrentTemp()) + "°C";
                info += " | Target: " + QString::number(t->getTargetTemp()) + "°C";
            }
            else if (dev->getTypeName() == "MotionSensor")
            {
                const MotionSensor* m = dynamic_cast<const MotionSensor*>(dev.get());
                info += m->isMotionDetected() ? " | Motion: YES" : " | Motion: NO";
            }

            ui->textEdit->append(info);
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
