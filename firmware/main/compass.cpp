#include "compass.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/i2c.h>
#include <esp_log.h>

#define I2C_ADDRESS 0x0d

#define REG_DATA_START 0x00
#define REG_STATUS 0x06
#define REG_CONTROL_1 0x09
#define REG_RESET 0x0b

#define MODE_STANDBY 0x00

static const char* TAG = "compass";

bool Compass::_initialized = false;

Compass::Compass(gpio_num_t sda, gpio_num_t scl) {
    _sda = sda;
    _scl = scl;

    if (_initialized) {
        ESP_LOGE(TAG, "Compass is already initialized");
        return;
    }

    ESP_LOGI(TAG, "Initializing I2C on pins %d (SDA) and %d (SCL)", sda, scl);

    i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda,
        .scl_io_num = scl,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {
            .clk_speed = 100000
        },
        .clk_flags = 0
    };

    i2c_param_config(I2C_NUM_0, &config);
    i2c_driver_install(I2C_NUM_0, config.mode, 0, 0, 0);

    uint8_t data[2];

    data[0] = REG_RESET;
    data[1] = 0x01;
    i2c_master_write_to_device(I2C_NUM_0, I2C_ADDRESS, data, 2, pdMS_TO_TICKS(50));

    data[0] = REG_CONTROL_1;
    data[1] = 0b01000000;
    i2c_master_write_to_device(I2C_NUM_0, I2C_ADDRESS, data, 2, pdMS_TO_TICKS(50));
}

Vector3 Compass::read() {
    uint8_t data[6];

    bool ready = false;
    while (!ready) {
        data[0] = REG_STATUS;
        i2c_master_write_to_device(I2C_NUM_0, I2C_ADDRESS, data, 1, pdMS_TO_TICKS(50));

        i2c_master_read_from_device(I2C_NUM_0, I2C_ADDRESS, data, 1, pdMS_TO_TICKS(50));

        ready = data[0] & 0x01;

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    data[0] = REG_DATA_START;
    i2c_master_write_to_device(I2C_NUM_0, I2C_ADDRESS, data, 1, pdMS_TO_TICKS(50));

    i2c_master_read_from_device(I2C_NUM_0, I2C_ADDRESS, data, 6, pdMS_TO_TICKS(50));

    int16_t x = data[1] << 8 | data[0];
    int16_t y = data[3] << 8 | data[2];
    int16_t z = data[5] << 8 | data[4];

    return Vector3(x / 2048.0f, y / 2048.0f, z / 2048.0f);
}

void Compass::_write(uint8_t address, uint8_t value) {
}
