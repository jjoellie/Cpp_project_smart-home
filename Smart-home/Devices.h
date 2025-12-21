#pragma once

#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>

// Vraag 27: everything in namespace
namespace smarthome
{
// Vraag 25 & 24: template + inline function
template <typename T>
inline T clampValue(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

// Vraag 18: polymorphism (abstract base class)
class Device
{
public:
    // Vraag 13 & 16: parameterized constructor + init list
    Device(uint8_t id, const std::string& name, const std::string& room)
        : id_(id), name_(name), room_(room), poweredOn_(false)
    {}

    // Vraag 15: destructor
    virtual ~Device() = default;

    // Vraag 18: virtual functions
    virtual void update() = 0;
    virtual std::string getTypeName() const = 0;

    // Vraag 20: useful member functions
    void turnOn()  { poweredOn_ = true; }
    void turnOff() { poweredOn_ = false; }

    // Vraag 23: getters
    bool isOn() const { return poweredOn_; }
    const std::string& getName() const { return name_; }

    // Vraag 26: friend function
    friend std::ostream& operator<<(std::ostream& os, const Device& d)
    {
        return os << d.name_;
    }

protected:
    // Vraag 28 & 31: memory efficient + bool
    uint8_t id_;
    std::string name_;
    std::string room_;
    bool poweredOn_;
};

// ---------------- LIGHT ----------------
class Light : public Device
{
public:
    // Vraag 21: default value
    Light(uint8_t id, const std::string& name, const std::string& room, uint8_t brightness = 100)
        : Device(id, name, room), brightness_(brightness)
    {}

    void update() override {}

    std::string getTypeName() const override { return "Light"; }

    // Vraag 19: useful usage of this
    void setBrightness(uint8_t value)
    {
        this->brightness_ = clampValue<uint8_t>(value, 0, 100);
    }

    uint8_t getBrightness() const { return brightness_; }

private:
    uint8_t brightness_;
};

// ---------------- THERMOSTAT ----------------
class Thermostat : public Device
{
public:
    // Vraag 12 & 17: default constructor + constructor forwarding
    Thermostat() : Thermostat(0, "Default Thermostat", "None", 20.0) {}

    Thermostat(uint8_t id, const std::string& name, const std::string& room, double targetTemp)
        : Device(id, name, room),
        currentTemp_(targetTemp),
        targetTemp_(targetTemp)
    {}

    void update() override
    {
        if (!poweredOn_) return;

        if (currentTemp_ < targetTemp_) currentTemp_ += 0.1;
        else if (currentTemp_ > targetTemp_) currentTemp_ -= 0.1;
    }

    std::string getTypeName() const override { return "Thermostat"; }

    double getCurrentTemp() const { return currentTemp_; }
    double getTargetTemp() const { return targetTemp_; }

    void setTargetTemp(double t) { targetTemp_ = t; }

private:
    double currentTemp_;
    double targetTemp_;
};

// ---------------- MOTION SENSOR ----------------
class MotionSensor : public Device
{
public:
    MotionSensor(uint8_t id, const std::string& name, const std::string& room)
        : Device(id, name, room), motionDetected_(false)
    {}

    void update() override {}

    std::string getTypeName() const override { return "MotionSensor"; }

    void detect()
    {
        motionDetected_ = true;
        poweredOn_ = true;
    }

    void clearMotion()
    {
        motionDetected_ = false;
        poweredOn_ = false;
    }

    bool isMotionDetected() const { return motionDetected_; }

private:
    bool motionDetected_;
};
}
