#ifndef SPI_H
#define SPI_H

#include <vector>

#include "Controller.h"

namespace Politocean
{
    namespace RPi
    {
        class SPI
        {
            int err_;

            Controller& controller_;
            int handle_, channel_, speed_;

        public:
            static const int DFLT_CHANNEL   = 0;
            static const int DFLT_SPEED     = 1000000;

            SPI(Controller& controller) : controller_(controller), handle_(Controller::DFLT_SPI_HANDLE), channel_(DFLT_CHANNEL), speed_(DFLT_SPEED) {}
            ~SPI();

            void setup(int channel, int speed);

            char transfer(char msg);
            std::vector<char> transfer(const std::vector<char>& msg, int bytes);
        };
    }
}

#endif // SPI_H