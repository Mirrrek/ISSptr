#pragma once

#include <driver/gpio.h>
#include <driver/ledc.h>

class Servo {
private:
    gpio_num_t _pin;
    ledc_channel_t _channel;
    bool _wideRange;
    static bool _timerInitialized;
    static uint8_t _instanceCount;
public:
    Servo(gpio_num_t pin, bool wideRange = false);
    void set(float angle);
};
