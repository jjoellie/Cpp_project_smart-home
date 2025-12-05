#pragma once
#include <string>

class Device
{
public:
    Device(const std::string& name, const std::string& roomName)
        : name_(name), roomName_(roomName), poweredOn_(false)
    {}

    virtual ~Device() = default;

    void turnOn()  { poweredOn_ = true; }
    void turnOff() { poweredOn_ = false; }
    bool isOn() const { return poweredOn_; }

    std::string getName() const     { return name_; }
    std::string getRoomName() const { return roomName_; }


    virtual void update() = 0;
    virtual std::string getTypeName() const = 0;

private:
    std::string name_;
    std::string roomName_;
    bool poweredOn_;
};
