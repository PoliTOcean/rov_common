/**
 * @author pettinz
 */

#include <iostream>
#include <thread>
#include <chrono>

#include "Controller.h"

namespace pigpio
{
    #include "pigpio.h"
}

using namespace Politocean::RPi;

void Controller::setup()
{
    pigpio::gpioInitialise();
}

void Controller::pinMode(int pin, PinMode mode)
{
    pigpio::gpioSetMode(pin, static_cast<int>(mode));
}

void Controller::digitalWrite(int pin, PinLevel level)
{
    pigpio::gpioWrite(pin, static_cast<int>(level));
}

void Controller::softPwmCreate(int pwmPin, int start, int stop)
{
    pigpio::gpioSetPWMrange(pwmPin, (unsigned)stop);
}

void Controller::softPwmWrite(int pwmPin, int value)
{
    pigpio::gpioPWM(pwmPin, value);
}

void Controller::softPwmStop(int pwmPin)
{
    pigpio::gpioPWM(pwmPin, 0);
}

void Controller::setupSPI(int device, int frequency)
{
    pigpio::spiOpen(device, frequency, 0);
}

unsigned char Controller::SPIDataRW(unsigned char data)
{
    char tmp = data;

    pigpio::spiXfer(spiDevice_, &tmp, &tmp, sizeof(char));

    return tmp;
}

void Controller::reset()
{
    pinMode(Pinout::RESET, PinMode::PIN_OUTPUT);

    digitalWrite(Pinout::RESET, PinLevel::PIN_LOW);
    std::this_thread::sleep_for(std::chrono::microseconds(100));

    digitalWrite(Pinout::RESET, PinLevel::PIN_HIGH);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

Controller::PinLevel Controller::setupMotors()
{
    pinMode(Pinout::MOTORS, PinMode::PIN_OUTPUT);

    return pigpio::gpioRead(Pinout::MOTORS) ? PinLevel::PIN_HIGH : PinLevel::PIN_LOW;

}

void Controller::stopMotors()
{
    motors_ = false;

    digitalWrite(Pinout::MOTORS, PinLevel::PIN_LOW);
}

void Controller::startMotors()
{
    motors_ = true;

    digitalWrite(Pinout::MOTORS, PinLevel::PIN_HIGH);
}

