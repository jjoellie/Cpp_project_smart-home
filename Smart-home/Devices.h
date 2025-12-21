#pragma once

#include <string>
#include <cstdint>
#include <algorithm>

// Vraag 27: everything in one self-made namespace
namespace smarthome
{

// Vraag 24 & 25: inline + template function
template <typename T>
inline T clampValue(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

// Vraag 18: abstract base class (polymorphism)
class Device
{
public:
    // Vraag 13 & 16: parameterized constructor + init list
    Device(uint8_t id, const std::string& name, const std::string& room)
        : id_(id), name_(name), room_(room), poweredOn_(false)
    {}

    // Vraag 15: virtual destructor
    virtual ~Device() = default;

    // Vraag 18: pure virtual functions
    virtual void update() = 0;
    virtual std::string getTypeName() const = 0;

    // Vraag 20: useful member functions
    void turnOn()  { poweredOn_ = true; }
    void turnOff() { poweredOn_ = false; }

    // Vraag 23: getters
    bool isOn() const { return poweredOn_; }
    const std::string& getName() const { return name_; }

protected:
    // Vraag 28 & 31: memory efficient type + useful bool
    uint8_t id_;
    std::string name_;
    std::string room_;
    bool poweredOn_;
};

// Vraag 18: inheritance (Light is-a Device)
class Light : public Device
{
public:
    // Vraag 21: default value
    Light(uint8_t id, const std::string& name,
          const std::string& room, uint8_t brightness = 100)
        : Device(id, name, room), brightness_(brightness)
    {}

    void update() override {}

    std::string getTypeName() const override { return "Light"; }

    // Vraag 19: usage of this + clamp template
    void setBrightness(uint8_t value)
    {
        this->brightness_ = clampValue<uint8_t>(value, 0, 100);
        poweredOn_ = (brightness_ > 0);
    }

    uint8_t getBrightness() const { return brightness_; }

private:
    // Vraag 22: useful member variable
    uint8_t brightness_;
};

// Vraag 18: inheritance + polymorphism
class Thermostat : public Device
{
public:
    // Vraag 12 & 17: default constructor + forwarding
    Thermostat() : Thermostat(0, "Default Thermostat", "None", 20.0) {}

    Thermostat(uint8_t id, const std::string& name,
               const std::string& room, double targetTemp)
        : Device(id, name, room),
        currentTemp_(targetTemp),
        targetTemp_(targetTemp)
    {}

    // Vraag 20: useful member function
    void update() override
    {
        if (!poweredOn_) return;

        if (currentTemp_ < targetTemp_)
            currentTemp_ += 0.1;
        else if (currentTemp_ > targetTemp_)
            currentTemp_ -= 0.1;
    }

    std::string getTypeName() const override { return "Thermostat"; }

    double getCurrentTemp() const { return currentTemp_; }
    double getTargetTemp() const { return targetTemp_; }

    // Vraag 20 & 51: realistic behaviour
    void setTargetTemp(double t)
    {
        targetTemp_ = t;
        poweredOn_ = true;
    }

    // Vraag 51: nice extra (heating/cooling state)
    std::string getMode() const
    {
        if (!poweredOn_) return "OFF";
        if (currentTemp_ < targetTemp_) return "HEATING";
        if (currentTemp_ > targetTemp_) return "COOLING";
        return "STABLE";
    }

private:
    double currentTemp_;
    double targetTemp_;
};

// Vraag 18: inheritance
class MotionSensor : public Device
{
public:
    MotionSensor(uint8_t id, const std::string& name, const std::string& room)
        : Device(id, name, room), motionDetected_(false)
    {}

    void update() override {}

    std::string getTypeName() const override { return "MotionSensor"; }

    // Vraag 20: useful member functions
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
    // Vraag 31: useful bool
    bool motionDetected_;
};

} // namespace smarthome
