#include "servo.hpp"
#include <esp_log.h>

#define NORMAL_RANGE_OFFSET 0.05f
#define REGULAR_RANGE_COEFFICIENT 0.0002777777777f
#define WIDE_RANGE_OFFSET 0.025f
#define WIDE_RANGE_COEFFICIENT 0.0005555555555f

#define DUTY_RESOLUTION LEDC_TIMER_10_BIT

static const char* TAG = "servo";

bool Servo::_timerInitialized = false;
uint8_t Servo::_instanceCount = 0;

Servo::Servo(gpio_num_t pin, bool wideRange) {
    _pin = pin;
    _wideRange = wideRange;

    if (!_timerInitialized) {
        ESP_LOGI(TAG, "Initializing LEDC timer");

        ledc_timer_config_t config = {
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .duty_resolution = DUTY_RESOLUTION,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = 50,
            .clk_cfg = LEDC_AUTO_CLK,
            .deconfigure = false
        };

        ledc_timer_config(&config);

        ledc_fade_func_install(0);

        _timerInitialized = true;
    }

    this->_channel = (ledc_channel_t)(LEDC_CHANNEL_0 + _instanceCount++);

    ESP_LOGI(TAG, "Configuring pin %d (channel %d)", _pin, _channel);

    ledc_channel_config_t config = {
        .gpio_num = _pin,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = _channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0,
        .flags = 0
    };

    ledc_channel_config(&config);
}

void Servo::set(float angle) {
    if (angle < 0.0f) {
        ESP_LOGW(TAG, "Invalid angle: %f, clamping to 0", angle);
        angle = 0.0f;
    }

    if (angle > 180.0f) {
        ESP_LOGW(TAG, "Invalid angle: %f, clamping to 180", angle);
        angle = 180.0f;
    }

    ESP_LOGD(TAG, "Setting angle on pin %d to %f", _pin, angle);

    float offset = _wideRange ? WIDE_RANGE_OFFSET : NORMAL_RANGE_OFFSET;
    float coefficient = _wideRange ? WIDE_RANGE_COEFFICIENT : REGULAR_RANGE_COEFFICIENT;

    float duty = offset + angle * coefficient;

    ledc_set_duty_and_update(LEDC_HIGH_SPEED_MODE, _channel, (uint32_t)(duty * (1 << DUTY_RESOLUTION)), 0);
}
