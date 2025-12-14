#pragma once

#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>

namespace smarthome
{
template <typename T>
inline T clampValue(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

class Device
{
public:
    Device(uint8_t id, const std::string& name, const std::string& room)
        : id_(id), name_(name), room_(room), poweredOn_(false)
    {}

    virtual ~Device() = default;

    virtual void update() = 0;
    virtual std::string getTypeName() const = 0;

    void turnOn()  { poweredOn_ = true; }
    void turnOff() { poweredOn_ = false; }
    bool isOn() const { return poweredOn_; }

    const std::string& getName() const { return name_; }
    const std::string& getRoom() const { return room_; }

protected:
    uint8_t id_;
    std::string name_;
    std::string room_;
    bool poweredOn_;
};

// ---------- LIGHT ----------
class Light : public Device
{
public:
    Light(uint8_t id,
          const std::string& name,
          const std::string& room,
          uint8_t brightness = 100)
        : Device(id, name, room),
        brightness_(brightness)
    {}

    void update() override
    {

    }

    std::string getTypeName() const override
    {
        return "Light";
    }

    void setBrightness(uint8_t value)
    {
        brightness_ = clampValue<uint8_t>(value, 0, 100);
    }

    uint8_t getBrightness() const
    {
        return brightness_;
    }

private:
    uint8_t brightness_;
};

// ---------- THERMOSTAT ----------
class Thermostat : public Device
{
public:
    Thermostat(uint8_t id,
               const std::string& name,
               const std::string& room,
               double targetTemp = 20.0)
        : Device(id, name, room),
        currentTemp_(targetTemp),
        targetTemp_(targetTemp)
    {}

    void update() override
    {
        if (!poweredOn_) return;

        if (currentTemp_ < targetTemp_)
            currentTemp_ += 0.1;
        else if (currentTemp_ > targetTemp_)
            currentTemp_ -= 0.1;
    }

    std::string getTypeName() const override
    {
        return "Thermostat";
    }

    double getCurrentTemp() const { return currentTemp_; }
    double getTargetTemp() const { return targetTemp_; }

    void setTargetTemp(double value)
    {
        targetTemp_ = value;
    }

private:
    double currentTemp_;
    double targetTemp_;
};

// ---------- MOTION SENSOR ----------
class MotionSensor : public Device
{
public:
    MotionSensor(uint8_t id,
                 const std::string& name,
                 const std::string& room)
        : Device(id, name, room),
        motionDetected_(false)
    {}

    void update() override
    {

    }

    std::string getTypeName() const override
    {
        return "MotionSensor";
    }

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

    bool isMotionDetected() const
    {
        return motionDetected_;
    }

private:
    bool motionDetected_;
};
}
