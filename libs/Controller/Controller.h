/**
 * @author: pettinz
 * 
 * This class provides an interface with the Raspberry Pi GPIO and features
 * using the PiGPIO library
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace Politocean
{
    namespace RPi
    {
        class Pinout
        {
            // TODO: Change physical pins to gpio pins
        public:
            // Raspberry Pi 3
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

            // Raspberry Pi Zero
            static const int BRUSHLESS_L_DIR    = 32;
            static const int BRUSHLESS_R_PWM    = 33;

            static const int LED                = 16;
        };
        
        class Controller
        {
            int spiHandle_;
            bool motors_;

            int err_;

        public:
            enum class PinLevel { PIN_LOW, PIN_HIGH };
            enum class PinMode  { PIN_INPUT, PIN_OUTPUT };

            static const int DFLT_SPI_HANDLE = -1;

            Controller() : spiHandle_(DFLT_SPI_HANDLE), motors_(false) {}
            ~Controller();

            void setup();

            void pinMode(int pin, PinMode mode);
            void digitalWrite(int pin, PinLevel level);
            
            void setPwm(int pin, int dutyCycle);
            void setPwmRange(int pin, int range);
            void setPwmFrequency(int pin, int frequency);

            void setHardwarePwm(int pin, int frequency, int dutyCycle);


            void spiOpen(int channel, int frequency);
            void spiClose();
            void spiXfer(char *txBuf, char *rxBuf, int count);

            void sleep(double seconds);

            void setupMotors();
            void startMotors();
            void stopMotors();
            
            void reset();
        };
    }
}


#endif //CONTROLLER_H
