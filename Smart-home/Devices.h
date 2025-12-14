#pragma once
#include "Device.h"
#include "Utils.h"
#include <cstdint>
#include <memory>
#include <string>

namespace smarthome {

// LIGHT
class Light final : public Device
{
public:
    Light() : Light(1, "Unnamed Light", "Unknown", 100) {}

    Light(uint8_t id, const std::string& name, const std::string& roomName, uint8_t brightness = 100)
        : Device(id, name, roomName), brightness_(brightness)
    {}

    Light(const Light& other)
        : Device(other), brightness_(other.brightness_)
    {}

    ~Light() override = default;

    uint8_t brightness() const { return brightness_; }

    Light& setBrightness(uint8_t b)
    {
        this->brightness_ = clampValue<uint8_t>(b, 0, 100);
        return *this;
    }

    void update(double /*dtSeconds*/ = 1.0) override
    {

    }

    std::string typeName() const override { return "Light"; }

    std::unique_ptr<Device> clone() const override
    {
        return std::make_unique<Light>(*this);
    }

private:
    uint8_t brightness_;
};

// THERMOSTAT
class Thermostat final : public Device
{
public:
    Thermostat() : Thermostat(2, "Unnamed Thermostat", "Unknown", 21.0) {}

    Thermostat(uint8_t id, const std::string& name, const std::string& roomName,
               double targetTempC = 21.0, bool autoMode = true)
        : Device(id, name, roomName),
        currentTempC_(20.0),
        targetTempC_(targetTempC),
        autoMode_(autoMode)
    {}

    Thermostat(const Thermostat& other)
        : Device(other),
        currentTempC_(other.currentTempC_),
        targetTempC_(other.targetTempC_),
        autoMode_(other.autoMode_)
    {}

    ~Thermostat() override = default;

    double currentTemp() const { return currentTempC_; }
    double targetTemp()  const { return targetTempC_; }
    bool autoMode() const { return autoMode_; }

    Thermostat& setTargetTemp(double t) { this->targetTempC_ = t; return *this; }
    Thermostat& setAutoMode(bool on) { this->autoMode_ = on; return *this; }

    void update(double dtSeconds = 1.0) override
    {
        if (!autoMode_) return;

        const double step = 0.1 * dtSeconds;
        if (currentTempC_ < targetTempC_) currentTempC_ += step;
        else if (currentTempC_ > targetTempC_) currentTempC_ -= step;
    }

    std::string typeName() const override { return "Thermostat"; }

    std::unique_ptr<Device> clone() const override
    {
        return std::make_unique<Thermostat>(*this);
    }

private:
    double currentTempC_;
    double targetTempC_;
    bool autoMode_;
};

// MOTION SENSOR
class MotionSensor final : public Device
{
public:
    MotionSensor() : MotionSensor(3, "Unnamed Motion", "Unknown") {}

    MotionSensor(uint8_t id, const std::string& name, const std::string& roomName)
        : Device(id, name, roomName),
        motionDetected_(false),
        lastMotionSeconds_(0.0)
    {}

    MotionSensor(const MotionSensor& other)
        : Device(other),
        motionDetected_(other.motionDetected_),
        lastMotionSeconds_(other.lastMotionSeconds_)
    {}

    ~MotionSensor() override = default;

    bool motionDetected() const { return motionDetected_; }

    void detect()
    {
        motionDetected_ = true;
        turnOn();
        lastMotionSeconds_ = 0.0;
    }

    void clearMotion()
    {
        motionDetected_ = false;
        turnOff();
        lastMotionSeconds_ = 0.0;
    }

    void update(double dtSeconds = 1.0) override
    {
        if (!motionDetected_) return;
        lastMotionSeconds_ += dtSeconds;

        if (lastMotionSeconds_ >= 10.0)
            clearMotion();
    }

    std::string typeName() const override { return "MotionSensor"; }

    std::unique_ptr<Device> clone() const override
    {
        return std::make_unique<MotionSensor>(*this);
    }

private:
    bool motionDetected_;
    double lastMotionSeconds_;
};

}
