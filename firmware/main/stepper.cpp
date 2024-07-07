#include "stepper.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <rom/ets_sys.h>
#include <esp_log.h>

#define STEP_DELAY_US 3500

static const char* TAG = "stepper";

Stepper::Stepper(gpio_num_t a, gpio_num_t b, gpio_num_t c, gpio_num_t d) {
    _a = a;
    _b = b;
    _c = c;
    _d = d;
    _state = A;

    ESP_LOGI(TAG, "Initializing stepper on pins %d, %d, %d, %d", _a, _b, _c, _d);

    gpio_config_t config = {
        .pin_bit_mask = (1ULL << _a) | (1ULL << _b) | (1ULL << _c) | (1ULL << _d),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&config);

    _clear();
}

void Stepper::move(int16_t steps) {
    ESP_LOGD(TAG, "Moving stepper on pins %d, %d, %d, %d by %d steps", _a, _b, _c, _d, steps);

    bool direction = steps > 0;

    for (int16_t i = 0; i < (direction ? steps : -steps); i++) {
        if (i % 1024 == 1023) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        _step(direction);
    }

    _clear();
}

void Stepper::_step(bool direction) {
    _state = (State)((direction ? _state + 1 : _state + 7) % 4);

    switch (_state) {
    case A:
        gpio_set_level(_a, 1);
        gpio_set_level(_b, 0);
        gpio_set_level(_c, 0);
        gpio_set_level(_d, 0);
        break;
    case B:
        gpio_set_level(_a, 0);
        gpio_set_level(_b, 1);
        gpio_set_level(_c, 0);
        gpio_set_level(_d, 0);
        break;
    case C:
        gpio_set_level(_a, 0);
        gpio_set_level(_b, 0);
        gpio_set_level(_c, 1);
        gpio_set_level(_d, 0);
        break;
    case D:
        gpio_set_level(_a, 0);
        gpio_set_level(_b, 0);
        gpio_set_level(_c, 0);
        gpio_set_level(_d, 1);
        break;
    }

    ets_delay_us(STEP_DELAY_US);
}

void Stepper::_clear() {
    gpio_set_level(_a, 0);
    gpio_set_level(_b, 0);
    gpio_set_level(_c, 0);
    gpio_set_level(_d, 0);
}
