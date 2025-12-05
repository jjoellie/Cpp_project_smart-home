#pragma once
#include "Device.h"
#include <algorithm>


class Light : public Device
{
public:
    Light(const std::string& name, const std::string& roomName)
        : Device(name, roomName), brightness_(100)
    {}

    void update() override {}

    std::string getTypeName() const override { return "Light"; }

    int getBrightness() const { return brightness_; }
    void setBrightness(int value)
    {
        brightness_ = std::clamp(value, 0, 100);
    }

private:
    int brightness_;
};


class Thermostat : public Device
{
public:
    Thermostat(const std::string& name, const std::string& roomName, double targetTemp)
        : Device(name, roomName), currentTemp_(20.0), targetTemp_(targetTemp)
    {}

    void update() override
    {
        if (currentTemp_ < targetTemp_) currentTemp_ += 0.1;
        else if (currentTemp_ > targetTemp_) currentTemp_ -= 0.1;
    }

    std::string getTypeName() const override { return "Thermostat"; }

    double getCurrentTemp() const { return currentTemp_; }
    double getTargetTemp()  const { return targetTemp_; }

    void setTargetTemp(double t) { targetTemp_ = t; }

private:
    double currentTemp_;
    double targetTemp_;
};


class MotionSensor : public Device
{
public:
    MotionSensor(const std::string& name, const std::string& roomName)
        : Device(name, roomName), motionDetected_(false)
    {}

    void update() override {}

    std::string getTypeName() const override { return "MotionSensor"; }

    bool isMotionDetected() const { return motionDetected_; }

    void detect() { motionDetected_ = true; turnOn(); }
    void clearMotion() { motionDetected_ = false; turnOff(); }

private:
    bool motionDetected_;
};
