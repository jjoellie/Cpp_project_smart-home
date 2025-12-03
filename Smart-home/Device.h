#ifndef DEVICES_H
#define DEVICES_H

#include "Device.h"


class Light : public Device
{
public:
    Light(const std::string& name, const std::string& roomName)
        : Device(name, roomName), brightness_(100)
    {
    }

    void setBrightness(int value)
    {
        if (value < 0) value = 0;
        if (value > 100) value = 100;
        brightness_ = value;
    }

    int getBrightness() const
    {
        return brightness_;
    }

    void update() override
    {

        std::cout << "[Light::update] " << getName() << " in "
                  << getRoomName() << " brightness=" << brightness_ << "%\n";
    }

    std::string getTypeName() const override
    {
        return "Light";
    }

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
        : Device(name, roomName), targetTemperature_(targetTemp), currentTemperature_(20.0)
    {
    }

    void setTargetTemperature(double t)
    {
        targetTemperature_ = t;
    }

    double getTargetTemperature() const
    {
        return targetTemperature_;
    }

    double getCurrentTemperature() const
    {
        return currentTemperature_;
    }

    void update() override
    {

        if (currentTemperature_ < targetTemperature_)
            currentTemperature_ += 0.1;
        else if (currentTemperature_ > targetTemperature_)
            currentTemperature_ -= 0.1;
    }

    std::string getTypeName() const override
    {
        return "Thermostat";
    }

    void printInfo() const override
    {
        Device::printInfo();
        std::cout << " | Current: " << currentTemperature_
                  << "°C, Target: " << targetTemperature_ << "°C";
    }

private:
    double targetTemperature_;
    double currentTemperature_;
};


class MotionSensor : public Device
{
public:
    MotionSensor(const std::string& name, const std::string& roomName)
        : Device(name, roomName), motionDetected_(false)
    {
    }

    void detectMotion()
    {
        motionDetected_ = true;
    }

    void clearMotion()
    {
        motionDetected_ = false;
    }

    bool isMotionDetected() const
    {
        return motionDetected_;
    }

    void update() override
    {

        std::cout << "[MotionSensor::update] " << getName()
                  << " motion=" << (motionDetected_ ? "YES" : "NO") << "\n";
    }

    std::string getTypeName() const override
    {
        return "MotionSensor";
    }

    void printInfo() const override
    {
        Device::printInfo();
        std::cout << " | Motion: " << (motionDetected_ ? "DETECTED" : "none");
    }

private:
    bool motionDetected_;
};

#endif
