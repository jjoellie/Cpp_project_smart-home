#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , home("Joel")
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    smarthome::Room living("Living Room");
    smarthome::Room bed("Bedroom");

    // -------- DEVICES --------

    // Living room light
    living.addDevice(std::make_unique<smarthome::Light>("Ceiling Light", "Living Room"));

    // Living room thermostat
    {
        auto t = std::make_unique<smarthome::Thermostat>("Main Thermostat", "Living Room", 22.5);
        t->turnOn();
        living.addDevice(std::move(t));
    }

    // Living room motion sensor
    living.addDevice(std::make_unique<smarthome::MotionSensor>("Entrance Sensor", "Living Room"));

    // Bedroom light
    bed.addDevice(std::make_unique<smarthome::Light>("Bedside Lamp", "Bedroom"));

    // Bedroom thermostat
    {
        auto t = std::make_unique<smarthome::Thermostat>("Bedroom Thermostat", "Bedroom", 20.0);
        t->turnOn();
        bed.addDevice(std::move(t));
    }

    home.addRoom(std::move(living));
    home.addRoom(std::move(bed));

    // -------- TIMER --------
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(1000);

    ui->sliderBrightness->setRange(0, 100);
    ui->sliderBrightness->setValue(100);

    ui->spinTargetTemp->setRange(5.0, 35.0);
    ui->spinTargetTemp->setSingleStep(0.5);
    ui->spinTargetTemp->setValue(22.5);

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

            const std::string type = dev->getTypeName();

            if (type == "Light")
            {
                auto* l = dynamic_cast<const smarthome::Light*>(dev.get());
                info += l->isOn() ? " | ON" : " | OFF";
                info += " | Brightness: " + QString::number(l->getBrightness()) + "%";
            }
            else if (type == "Thermostat")
            {
                auto* t = dynamic_cast<const smarthome::Thermostat*>(dev.get());
                info += t->isOn() ? " | ON" : " | OFF";
                info += " | Current: " + QString::number(t->getCurrentTemp(), 'f', 1) + "°C";
                info += " | Target: " + QString::number(t->getTargetTemp(), 'f', 1) + "°C";
            }
            else if (type == "MotionSensor")
            {
                auto* m = dynamic_cast<const smarthome::MotionSensor*>(dev.get());
                info += m->isOn() ? " | ON" : " | OFF";
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

void MainWindow::on_btnLightsOff_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Light")
            {
                auto* l = dynamic_cast<smarthome::Light*>(dev.get());
                l->turnOff();
                l->setBrightness(0);
            }

    showHomeStatus();
}

void MainWindow::on_btnSetTemp_clicked()
{
    double newTemp = ui->spinTargetTemp->value();

    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Thermostat")
                dynamic_cast<smarthome::Thermostat*>(dev.get())->setTargetTemp(newTemp);

    showHomeStatus();
}

void MainWindow::on_btnSimulateMotion_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "MotionSensor")
                dynamic_cast<smarthome::MotionSensor*>(dev.get())->detect();

    showHomeStatus();
}

void MainWindow::on_btnClearMotion_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "MotionSensor")
                dynamic_cast<smarthome::MotionSensor*>(dev.get())->clearMotion();

    showHomeStatus();
}

void MainWindow::on_sliderBrightness_valueChanged(int value)
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Light")
                dynamic_cast<smarthome::Light*>(dev.get())->setBrightness(value);

    showHomeStatus();
}

void MainWindow::updateSimulation()
{
    home.updateAll();
    showHomeStatus();
}
