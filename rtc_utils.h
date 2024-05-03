#pragma once
#include <Arduino.h>

// записать данные в rtc память. Вернёт false при ошибке
template <typename T>
bool rtc_write(T* data, uint8_t offset = 0, uint32_t* _crc = nullptr) {
#ifdef ESP8266
    uint32_t crc = _crc ? *_crc : crc32((void*)data, sizeof(T));
    if (!ESP.rtcUserMemoryWrite(offset, &crc, sizeof(crc))) return 0;
    if (!ESP.rtcUserMemoryWrite(offset + 1, (uint32_t*)data, sizeof(T))) return 0;
#endif
    return 1;
}

// прочитать данные из rtc памяти. Вернёт false при ошибке
template <typename T>
bool rtc_read(T* data, uint8_t offset = 0) {
#ifdef ESP8266
    uint32_t crc;
    if (!ESP.rtcUserMemoryRead(offset, &crc, sizeof(crc))) return 0;
    if (!ESP.rtcUserMemoryRead(offset + 1, (uint32_t*)data, sizeof(T))) return 0;
    uint32_t _crc = crc32((void*)data, sizeof(T));
    if (_crc != crc) {
        *data = T();
        return rtc_write(data, offset, &_crc);
    }
#endif
    return 1;
}