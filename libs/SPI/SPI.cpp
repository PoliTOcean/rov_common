#include "SPI.h"

#include <stdlib.h>

using namespace Politocean::RPi;

SPI::~SPI()
{
    controller_.spiClose();
}

void SPI::setup(int channel, int speed)
{
    channel_    = channel;
    speed_      = speed;

    controller_.spiOpen(channel, speed);
}

char SPI::transfer(char msg)
{
    char txBuf = msg, rxBuf;

    controller_.spiXfer(&txBuf, &rxBuf, 1);

    return rxBuf;
}

std::vector<char> SPI::transfer(const std::vector<char>& msg, int bytes)
{
    char *rxBuf, *txBuf;
    int i;

    std::vector<char> rx;

    rxBuf = (char *)malloc(bytes * sizeof(char));
    rxBuf = (char *)malloc(bytes * sizeof(char));

    for (i = 0; i < bytes; txBuf[i] = msg[i], i++);

    controller_.spiXfer(txBuf, rxBuf, bytes);

    for (i = 0; i < bytes; rx.emplace_back(rxBuf[i++]));

    free(txBuf);
    free(rxBuf);

    return rx;
}