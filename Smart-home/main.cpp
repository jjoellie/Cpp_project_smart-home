#include <iostream>
#include <memory>

#include "SmartHome.h"
#include "Devices.h"

int main()
{
    SmartHome home("Joel");

    Room livingRoom("Living Room");
    Room bedroom("Bedroom");

    livingRoom.addDevice(std::make_unique<Light>("Ceiling Light", "Living Room"));
    livingRoom.addDevice(std::make_unique<Thermostat>("Main Thermostat", "Living Room", 22.5));
    livingRoom.addDevice(std::make_unique<MotionSensor>("Entrance Sensor", "Living Room"));

    bedroom.addDevice(std::make_unique<Light>("Bedside Lamp", "Bedroom"));
    bedroom.addDevice(std::make_unique<Thermostat>("Bedroom Thermostat", "Bedroom", 20.0));
