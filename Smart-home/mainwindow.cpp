#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QPropertyAnimation>

// Vraag 2: clean main (no logic in main.cpp)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    home("Joel"),           // Vraag 13 & 16
    timer(new QTimer(this)),
    motionTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Vraag 18: object composition
    smarthome::Room living("Living Room");
    smarthome::Room bedroom("Bedroom");

    living.addDevice(std::make_unique<smarthome::Light>(1, "Ceiling Light", "Living Room", 100));
    living.addDevice(std::make_unique<smarthome::Thermostat>(2, "Main Thermostat", "Living Room", 22.0));
    living.addDevice(std::make_unique<smarthome::MotionSensor>(3, "Entrance Sensor", "Living Room"));

    bedroom.addDevice(std::make_unique<smarthome::Light>(4, "Bedside Lamp", "Bedroom", 100));
    bedroom.addDevice(std::make_unique<smarthome::Thermostat>(5, "Bedroom Thermostat", "Bedroom", 21.5));

    home.addRoom(std::move(living));
    home.addRoom(std::move(bedroom));

    // Vraag 43: signal / slot
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(1000);

    // Vraag 51: motion timeout → lights OFF
    motionTimer->setSingleShot(true);
    connect(motionTimer, &QTimer::timeout, this, [this]() {
        for (auto& room : home.getRooms())
            for (auto& dev : room.getDevices())
                if (dev->getTypeName() == "Light")
                    dev->turnOff();

        statusBar()->showMessage("Motion timeout → lights OFF", 3000);
        showHomeStatus();
    });

    ui->sliderBrightness->setRange(0, 100);
    ui->spinTargetTemp->setRange(5.0, 35.0);

    showHomeStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr; // Vraag 37: nullptr usage
}

// Vraag 20: useful member function (status renderer)
void MainWindow::showHomeStatus()
{
    ui->textEdit->clear();

    for (const auto& room : home.getRooms())
    {
        ui->textEdit->append("Room: " + QString::fromStdString(room.getName()));

        for (const auto& dev : room.getDevices())
        {
            QString info = dev->isOn() ? "🟢 " : "🔴 ";
            info += QString::fromStdString(dev->getName());
            info += " (" + QString::fromStdString(dev->getTypeName()) + ")";

            if (dev->getTypeName() == "Light")
            {
                auto* l = dynamic_cast<const smarthome::Light*>(dev.get());
                info += " | Brightness: " + QString::number(l->getBrightness()) + "%";
            }
            else if (dev->getTypeName() == "Thermostat")
            {
                auto* t = dynamic_cast<const smarthome::Thermostat*>(dev.get());
                info += " | Current: " + QString::number(t->getCurrentTemp(), 'f', 1);
                info += " | Target: " + QString::number(t->getTargetTemp(), 'f', 1);
                info += " | Mode: " + QString::fromStdString(t->getMode());
            }
            else if (dev->getTypeName() == "MotionSensor")
            {
                auto* m = dynamic_cast<const smarthome::MotionSensor*>(dev.get());
                info += m->isMotionDetected() ? " | Motion: YES" : " | Motion: NO";
            }

            ui->textEdit->append(info);
        }

        ui->textEdit->append("");
    }
}

// ================= BUTTONS =================

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

    statusBar()->showMessage("Lights have been turned ON", 2000);
    showHomeStatus();
}

void MainWindow::on_btnLightsOff_clicked()
{
    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Light")
                dev->turnOff();

    statusBar()->showMessage("Lights have been turned OFF", 2000);
    showHomeStatus();
}

void MainWindow::on_btnSetTemp_clicked()
{
    double temp = ui->spinTargetTemp->value();

    for (auto& room : home.getRooms())
        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "Thermostat")
                dynamic_cast<smarthome::Thermostat*>(dev.get())->setTargetTemp(temp);

    statusBar()->showMessage(
        "Target temperature set to " + QString::number(temp) + " °C", 2500
        );
    showHomeStatus();
}

// Vraag 51: motion → lights ON + timeout
void MainWindow::on_btnSimulateMotion_clicked()
{
    for (auto& room : home.getRooms())
    {
        bool motion = false;

        for (auto& dev : room.getDevices())
            if (dev->getTypeName() == "MotionSensor")
            {
                dynamic_cast<smarthome::MotionSensor*>(dev.get())->detect();
                motion = true;
            }

        if (motion)
            for (auto& dev : room.getDevices())
                if (dev->getTypeName() == "Light")
                    dev->turnOn();
    }

    motionTimer->start(5000);
    statusBar()->showMessage("Motion detected – lights ON", 2500);
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

// Vraag 20: simulation loop
void MainWindow::updateSimulation()
{
    home.updateAll();
    showHomeStatus();
}
