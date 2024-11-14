#include <Arduino.h>
#include <rtc_utils.h>

struct Data {
    uint16_t count = 0;  // счётчик перезагрузок
};

void setup() {
    Serial.begin(115200);
    Serial.println();

    Data data;
    rtc_read(&data);

    Serial.println(data.count);

    data.count++;

    rtc_write(&data);
}

void loop() {
}