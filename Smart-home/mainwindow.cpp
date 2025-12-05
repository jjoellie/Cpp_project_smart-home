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


    Room living("Living Room");
    Room bed("Bedroom");

    living.addDevice(std::make_unique<Light>("Ceiling Light", "Living Room"));
    living.addDevice(std::make_unique<Thermostat>("Main Thermostat", "Living Room", 22.5));
    living.addDevice(std::make_unique<MotionSensor>("Entrance Sensor", "Living Room"));

    bed.addDevice(std::make_unique<Light>("Bedside Lamp", "Bedroom"));
    bed.addDevice(std::make_unique<Thermostat>("Bedroom Thermostat", "Bedroom", 20.0));

    home.addRoom(std::move(living));
    home.addRoom(std::move(bed));

    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(1000);

    // SLIDER RANGE
    ui->sliderBrightness->setRange(0, 100);
    ui->sliderBrightness->setValue(100);

    // TEMP SPINBOX
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
                auto* l = dynamic_cast<const Light*>(dev.get());
                info += l->isOn() ? " | ON" : " | OFF";
                info += " | Brightness: " + QString::number(l->getBrightness()) + "%";
            }
            else if (type == "Thermostat")
            {
                auto* t = dynamic_cast<const Thermostat*>(dev.get());
                info += t->isOn() ? " | ON" : " | OFF";
                info += " | Current: " + QString::number(t->getCurrentTemp(), 'f', 1) + "°C";
                info += " | Target: " + QString::number(t->getTargetTemp(), 'f', 1) + "°C";
            }
            else if (type == "MotionSensor")
            {
                auto* m = dynamic_cast<const MotionSensor*>(dev.get());
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
                auto* l = dynamic_cast<Light*>(dev.get());
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
                dynamic_cast<Thermostat*>(dev.get())->setTargetTemp(newTemp);

    showHomeStatus();
}

void MainWindow::on_btnSimulateMotion_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "MotionSensor")
                dynamic_cast<MotionSensor*>(dev.get())->detect();

    showHomeStatus();
}

void MainWindow::on_btnClearMotion_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "MotionSensor")
                dynamic_cast<MotionSensor*>(dev.get())->clearMotion();

    showHomeStatus();
}

void MainWindow::on_sliderBrightness_valueChanged(int value)
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Light")
                dynamic_cast<Light*>(dev.get())->setBrightness(value);

    showHomeStatus();
}

void MainWindow::updateSimulation()
{
    home.updateAll();
    showHomeStatus();
}
