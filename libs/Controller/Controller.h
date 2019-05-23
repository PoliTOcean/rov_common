/**
 * @author: pettinz
 * 
 * This class provides an interface with the Raspberry Pi GPIO and features
 * using the WiringPi libraries
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "PolitoceanConstants.h"

namespace Politocean
{
    namespace RPi
    {
        class Pinout
        {
        public:
            // Pi 3
            static const int RESET              = 7;
            static const int MOTORS             = 12;
            
            static const int SHOULDER_EN        = 15;
            static const int SHOULDER_DIR       = 13;
            static const int SHOULDER_STEP      = 11;
            
            static const int WRIST_EN           = 40;
            static const int WRIST_DIR          = 38;
            static const int WRIST_STEP         = 36;
            
            static const int HAND_DIR           = 16;
            static const int HAND_PWM           = 18;
            
            static const int CAMERA_EN          = 33;
            static const int CAMERA_DIR         = 31;
            static const int CAMERA_STEP        = 29;

            // Pi Zero
            static const int BRUSHLESS_L_DIR    = 32;
            static const int BRUSHLESS_R_PWM    = 33;

            static const int LED                = 16;
        };
        
        class Controller
        {
            int spiDevice_;
            bool motors_;
        
        public:
            enum class PinLevel { PIN_LOW, PIN_HIGH };
            enum class PinMode  { PIN_INPUT, PIN_OUTPUT };
            
            static const int DEFAULT_SPI_CHANNEL    = 0;
            static const int DEFAULT_SPI_SPEED      = 1000000;
            
            Controller() : spiDevice_(DEFAULT_SPI_CHANNEL), motors_(false) {}
            
            // Setup GPIO using physical pins
            void setup();

            void pinMode(int pin, PinMode mode);
            void digitalWrite(int pin, PinLevel level);
            
            // Software PWM based on softPwm.h
            void softPwmCreate(int pwmPin, int start, int stop);
            void softPwmWrite(int pwmPin, int value);
            void softPwmStop(int pwmPin);
            
            void setupSPI(int device, int frequency);

            void setupMotors();
            
            unsigned char SPIDataRW(unsigned char data);
            
            void startMotors();
            void stopMotors();
            
            void reset();
        };
    }
}


#endif //CONTROLLER_H
