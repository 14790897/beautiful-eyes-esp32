#ifndef DISPLAY_H
#define DISPLAY_H

#include <LovyanGFX.hpp>
#include "Config.h"

// GC9A01圆形屏幕配置类
class Display : public lgfx::LGFX_Device {
private:
    lgfx::Panel_GC9A01 _panel_instance;
    lgfx::Bus_SPI _bus_instance;

public:
    Display();
    void begin();
};

#endif // DISPLAY_H
