#include "compass.hpp"
#include "stepper.hpp"
#include "servo.hpp"
#include "vector.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <cmath>
#include <ctime>

#define PIN_COMPASS_SDA GPIO_NUM_21                 /* Compass SDA Pin */
#define PIN_COMPASS_SCL GPIO_NUM_22                 /* Compass SCL Pin */

#define PIN_STEPPER_A GPIO_NUM_16                   /* Stepper Coil 1 Terminal 1 Signal Pin */
#define PIN_STEPPER_B GPIO_NUM_17                   /* Stepper Coil 1 Terminal 2 Signal Pin */
#define PIN_STEPPER_C GPIO_NUM_18                   /* Stepper Coil 2 Terminal 1 Signal Pin */
#define PIN_STEPPER_D GPIO_NUM_19                   /* Stepper Coil 2 Terminal 2 Signal Pin */

#define PIN_SERVO GPIO_NUM_23                       /* Servo Signal Pin */

#define STEPPER_STEPS_PER_REVOLUTION 2048           /* Number of steps per full revolution of stepper */

#define COMPASS_MAX_FIELD_STRENGTH 0.5f             /* Maximum magnetic field strength considered natural (no interference) */
#define COMPASS_MAX_Z 0.25f                         /* Maximum z component of compass vector considered flat */

#define ISS_POSITION_FETCH_INTERVAL 24 * 60 * 60    /* Interval (s) of ISS position re-fetch from API */

#define COORDINATES_LAT 0.0f                        /* Latitude of user */
#define COORDINATES_LON 0.0f                        /* Longitude of user */

static const char* TAG = "main";

Vector3 latLongToVector3(float lat, float lon);
Vector3 project(Vector3 vector, Vector3 normal);
float angle(Vector3 a, Vector3 b);

extern "C" void app_main() {
    ESP_LOGI(TAG, "Initializing...");

    Compass compass(PIN_COMPASS_SDA, PIN_COMPASS_SCL);
    Stepper stepper(PIN_STEPPER_A, PIN_STEPPER_B, PIN_STEPPER_C, PIN_STEPPER_D);
    Servo servo(PIN_SERVO, true);

    Vector3 userPosition = latLongToVector3(COORDINATES_LAT, COORDINATES_LON);
    Vector3 northPoleProjected = project(Vector3(0.0f, 0.0f, 1.0f), userPosition);

    time_t lastIssPositionFetch = 0;

    ESP_LOGI(TAG, "Starting...");

    while (true) {
        ESP_LOGD(TAG, "Updating...");

        time_t currentTime = time(nullptr);
        if (currentTime - lastIssPositionFetch > ISS_POSITION_FETCH_INTERVAL) {
            ESP_LOGI(TAG, "Fetching ISS position...");

            // TODO: Fetch ISS position from API

            lastIssPositionFetch = currentTime;
        }

        Vector3 issPosition = latLongToVector3(0.0f /* TODO: Set ISS latitude */, 0.0f /* TODO: Set ISS longitude */);
        Vector3 issDirectionProjected = project(issPosition - userPosition, userPosition);

        Vector3 compassVector = compass.read();

        if (compassVector.length() > COMPASS_MAX_FIELD_STRENGTH) {
            ESP_LOGW(TAG, "Magnetic field strength too high");
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        if (abs(compassVector.z) > COMPASS_MAX_Z) {
            ESP_LOGW(TAG, "Compass not flat");
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        float compassAngle = angle(Vector3(compassVector.x, compassVector.y, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

        float issAngle = angle(userPosition, issPosition);
        servo.set(issAngle);

        float northPoleToIssAngle = angle(northPoleProjected, issDirectionProjected);
        stepper.move((compassAngle + northPoleToIssAngle) / 360.0f * STEPPER_STEPS_PER_REVOLUTION);
    }
}

Vector3 latLongToVector3(float lat, float lon) {
    float latRad = lat / 180.0f * M_PI;
    float lonRad = lon / 180.0f * M_PI;

    return Vector3(cos(latRad) * cos(lonRad), cos(latRad) * sin(lonRad), sin(latRad));
}

Vector3 project(Vector3 vector, Vector3 normal) {
    return vector - normal * vector.dot(normal);
}

float angle(Vector3 a, Vector3 b) {
    return acos(a.dot(b) / (a.length() * b.length())) / M_PI * 180.0f;
}
