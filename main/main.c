#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h" 
#include "hal/gpio_types.h"

#define TRIG_PIN GPIO_NUM_22 
#define ECHO_PIN GPIO_NUM_21
#define LED_PIN GPIO_NUM_2

void setup_ultrasonic() {
    // Configure Trigger Pin as Output
    gpio_reset_pin(TRIG_PIN);
    gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    
    // Configure Echo Pin as Input
    gpio_reset_pin(ECHO_PIN);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
}

float read_distance() {
    // 1. Send Trigger HIGH signal for 20us
    gpio_set_level(TRIG_PIN, 0);
    esp_rom_delay_us(20);
    gpio_set_level(TRIG_PIN, 1);
    esp_rom_delay_us(20);
    gpio_set_level(TRIG_PIN, 0);

    // 2. Wait for Echo to go HIGH
    int64_t start_time = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 0) {
        if ((esp_timer_get_time() - start_time) > 100000) return -1.0; // Timeout 100ms
    }

    // 3. Note the start time when Echo HIGH
    int64_t echo_start = esp_timer_get_time();
    
    // 4. Wait for Echo to go LOW
    while (gpio_get_level(ECHO_PIN) == 1) {
        if ((esp_timer_get_time() - echo_start) > 100000) return -1.0; // Timeout 100ms
    }
    
    // 5. Note the completion time
    int64_t echo_end = esp_timer_get_time();

    // 6. Calculate distance (Duration in us / 2) * 0.0343
    float duration = (float)(echo_end - echo_start);
    return (duration * 0.0343) / 2.0;
}

void app_main(void) {
    setup_ultrasonic();
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    printf(" Ultrasonic Sensor Ready!\n");

    while (1) {
        float distance = read_distance();
        float delay = distance*10;
        
        if (distance >= 0) {
            printf("Readable Distance : %.2f cm\n", distance);
            // Test with LED Blink using distance to control the delay of the LED 
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(delay)); 
            gpio_set_level(LED_PIN, 0);
            
            
        } else {
            printf("Error: Filed to Read Sensor\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}