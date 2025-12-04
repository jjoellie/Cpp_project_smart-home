#pragma once
#include "Device.h"
#include <algorithm>

class Light : public Device
{
public:
    Light(const std::string& name, const std::string& roomName)
        : Device(name, roomName), brightness_(100)
    {}

    void setBrightness(int value)
    {
        brightness_ = std::clamp(value, 0, 100);
    }

    void update() override
    {
        std::cout << "[Light update] " << getName() << "\n";
    }

    std::string getTypeName() const override { return "Light"; }

    void printInfo() const override
    {
        Device::printInfo();
        std::cout << " | Brightness: " << brightness_ << "%";
    }

private:
    int brightness_;
};


class Thermostat : public Device
{
public:
    Thermostat(const std::string& name, const std::string& roomName, double targetTemp)
        : Device(name, roomName), targetTemp_(targetTemp), currentTemp_(20.0)
    {}

    void update() override
    {
        if (currentTemp_ < targetTemp_) currentTemp_ += 0.1;
        if (currentTemp_ > targetTemp_) currentTemp_ -= 0.1;
    }

    std::string getTypeName() const override { return "Thermostat"; }

    void printInfo() const override
    {
        Device::printInfo();
        std::cout << " | Current: " << currentTemp_
                  << "°C, Target: " << targetTemp_ << "°C";
    }

private:
    double targetTemp_;
    double currentTemp_;
};


class MotionSensor : public Device
{
public:
    MotionSensor(const std::string& name, const std::string& roomName)
        : Device(name, roomName), motionDetected_(false)
    {}

    void detect() { motionDetected_ = true; }
    void clear() { motionDetected_ = false; }

    void update() override {}

    std::string getTypeName() const override { return "MotionSensor"; }

    void printInfo() const override
    {
        Device::printInfo();
        std::cout << " | Motion: " << (motionDetected_ ? "YES" : "NO");
    }

private:
    bool motionDetected_;
};
