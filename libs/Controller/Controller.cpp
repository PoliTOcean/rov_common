/**
 * @author pettinz
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>

#include "Controller.h"

namespace PiGPIO
{
    #include "pigpio.h"
}

using namespace Politocean::RPi;

void signal_handler(int signal_num)
{
    if (signal_num == SIGINT)
        exit(signal_num); // This will call destructor
}

Controller::~Controller()
{
    PiGPIO::gpioTerminate();
}

void Controller::setup()
{
    if (PiGPIO::gpioInitialise() < 0)
    {
        // TODO: throw error
    }
}

void Controller::pinMode(int pin, PinMode mode)
{
    PiGPIO::gpioSetMode(pin, static_cast<int>(mode));
}

void Controller::digitalWrite(int pin, PinLevel level)
{
    PiGPIO::gpioWrite(pin, static_cast<int>(level));
}

void Controller::setPwm(int pin, int dutyCycle)
{
    if ((err_ = PiGPIO::gpioPWM(pin, dutyCycle)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setPwmRange(int pin, int range)
{
    if ((err_ = PiGPIO::gpioSetPWMrange(pin, range)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setPwmFrequency(int pin, int frequency)
{
    if ((err_ = PiGPIO::gpioSetPWMfrequency(pin, frequency)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setHardwarePwm(int pin, int frequency, int range)
{
    if ((err_ = PiGPIO::gpioHardwarePWM(pin, frequency, range)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setupMotors()
{
    pinMode(Pinout::MOTORS, PinMode::PIN_OUTPUT);
}

void Controller::startMotors()
{
    motors_ = true;

    digitalWrite(Pinout::MOTORS, PinLevel::PIN_HIGH);
}

void Controller::stopMotors()
{
    motors_ = false;

    digitalWrite(Pinout::MOTORS, PinLevel::PIN_LOW);
}

void Controller::reset()
{
    pinMode(Pinout::RESET, PinMode::PIN_OUTPUT);

    digitalWrite(Pinout::RESET, PinLevel::PIN_LOW);
    std::this_thread::sleep_for(std::chrono::microseconds(100));

    digitalWrite(Pinout::RESET, PinLevel::PIN_HIGH);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Controller::spiOpen(int channel, int frequency)
{
    if ((spiHandle_ = PiGPIO::spiOpen(channel, frequency, 0)) < 0)
    {
        // TODO: throw error
    }
}

void Controller::spiClose()
{
    if (spiHandle_ < 0)
    {
        // TODO: throw error
    }

    if ((err_ = PiGPIO::spiClose(spiHandle_)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::spiXfer(char *txBuf, char *rxBuf, int count)
{
    if (spiHandle_ < 0)
    {
        // TODO: throw error
    }

    if (PiGPIO::spiXfer(spiHandle_, txBuf, rxBuf, count) != count)
    {
        // TODO: throw error
    }
}