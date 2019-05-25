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
    if ((err = PiGPIO::gpioPWM(pin, dutyCycle)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setPwmRange(int pin, int range)
{
    if ((err = PiGPIO::gpioSetPWMrange(pin, range)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setPwmFrequency(int pin, int frequency)
{
    if ((err = PiGPIO::gpioSetPWMfrequency(pin, frequency)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::setHardwarePwm(int pin, int frequency, int range)
{
    if ((err = PiGPIO::gpioHardwarePWM(pin, frequency, range)) != 0)
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

void Controller::SPI::spiOpen(int channel, int frequency)
{
    if ((handle_ = PiGPIO::spiOpen(channel, frequency, 0)) < 0)
    {
        // TODO: throw error
    }
}

void Controller::SPI::spiClose()
{
    if (handle_ < 0)
    {
        // TODO: throw error
    }

    if ((err_ = PiGPIO::spiClose(handle_)) != 0)
    {
        // TODO: throw error
    }
}

void Controller::SPI::spiXfer(char *txBuf, char *rxBuf, int count)
{
    if (handle_ < 0)
    {
        // TODO: throw error
    }

    if (PiGPIO::spiXfer(handle_, txBuf, rxBuf, count) != count)
    {
        // TODO: throw error
    }
}

void Controller::SPI::setup(int channel, int speed, int bytes)
{
    channel_    = channel;
    speed_      = speed;
    bytes_      = bytes;

    spiOpen(channel, speed);
}

char Controller::SPI::transfer(char msg)
{
    char txBuf = msg, rxBuf;

    spiXfer(&txBuf, &rxBuf, bytes_);

    return rxBuf;
}