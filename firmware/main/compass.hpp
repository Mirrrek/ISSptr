#pragma once

#include "vector.hpp"
#include <driver/gpio.h>

class Compass {
private:
    gpio_num_t _sda;
    gpio_num_t _scl;
    static bool _initialized;
    void _write(uint8_t address, uint8_t value);
    uint64_t _read(uint8_t address, uint8_t length);
public:
    Compass(gpio_num_t sda, gpio_num_t scl);
    Vector3 read();
};
