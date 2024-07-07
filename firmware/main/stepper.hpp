#pragma once

#include <driver/gpio.h>

class Stepper {
private:
    enum State { A, B, C, D };
    gpio_num_t _a;
    gpio_num_t _b;
    gpio_num_t _c;
    gpio_num_t _d;
    State _state;
    void _step(bool direction);
    void _clear();
public:
    Stepper(gpio_num_t a, gpio_num_t b, gpio_num_t c, gpio_num_t d);
    void move(int16_t steps);
};
