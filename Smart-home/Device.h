#pragma once
#include <cstdint>
#include <memory>
#include <string>

namespace smarthome {

class Device
{
public:
    Device()
        : deviceId_(0), name_("Unnamed"), roomName_("Unknown"), poweredOn_(false)
    {}

    Device(uint8_t deviceId, const std::string& name, const std::string& roomName)
        : deviceId_(deviceId), name_(name), roomName_(roomName), poweredOn_(false)
    {}

    Device(const Device& other)
        : deviceId_(other.deviceId_), name_(other.name_), roomName_(other.roomName_), poweredOn_(other.poweredOn_)
    {}

    virtual ~Device() = default;

    uint8_t deviceId() const { return deviceId_; }
    const std::string& name() const { return name_; }
    const std::string& roomName() const { return roomName_; }
    bool isOn() const { return poweredOn_; }

    Device& setName(const std::string& n) { this->name_ = n; return *this; }
    Device& setRoomName(const std::string& rn) { this->roomName_ = rn; return *this; }

    void turnOn()  { poweredOn_ = true; }
    void turnOff() { poweredOn_ = false; }

    virtual void update(double dtSeconds = 1.0) = 0;
    virtual std::string typeName() const = 0;

    virtual std::unique_ptr<Device> clone() const = 0;

protected:
    void setPowered(bool on) { poweredOn_ = on; }

private:
    uint8_t deviceId_;
    std::string name_;
    std::string roomName_;
    bool poweredOn_;
};

}
