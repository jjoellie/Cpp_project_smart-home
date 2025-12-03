#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device
{
public:
    // Constructor
    Device(const std::string& name, const std::string& roomName)
        : name_(name), roomName_(roomName), poweredOn_(false)
    {
    }

    // Virtual destructor (belangrijk voor polymorfisme)
    virtual ~Device() = default;

    // --- Publieke interface (abstraction) ---
    void turnOn()
    {
        poweredOn_ = true;
    }

    void turnOff()
    {
        poweredOn_ = false;
    }

    bool isOn() const
    {
        return poweredOn_;
    }

    std::string getName() const
    {
        return name_;
    }

    std::string getRoomName() const
    {
        return roomName_;
    }

    // Pure virtual → maakt dit een abstract base class
    virtual void update() = 0;

    // Virtuele functie voor polymorfisme
    virtual void printInfo() const
    {
        std::cout << "[" << roomName_ << "] "
                  << getTypeName() << " \"" << name_ << "\" - "
                  << (poweredOn_ ? "ON" : "OFF");
    }

    // Nog een virtuele functie: type-naam
    virtual std::string getTypeName() const = 0;

protected:
    // Beschermde helperfunctie voor derived classes
    void setName(const std::string& newName)
    {
        name_ = newName;
    }

private:
    // Encapsulation: data is privé
    std::string name_;
    std::string roomName_;
    bool poweredOn_;
};

#endif // DEVICE_H
