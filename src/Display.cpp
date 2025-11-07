#include "Display.h"

Display::Display(int pinDC, int pinCS, int pinRST) {
    // 配置 SPI 总线
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = HardwareConfig::FREQ_WRITE;
    cfg.freq_read = HardwareConfig::FREQ_READ;
    cfg.spi_3wire = true;
    cfg.use_lock = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;
    cfg.pin_sclk = HardwareConfig::PIN_SCLK;
    cfg.pin_mosi = HardwareConfig::PIN_MOSI;
    cfg.pin_miso = HardwareConfig::PIN_MISO;
    cfg.pin_dc = pinDC;  // 使用传入的DC引脚
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    // 配置面板
    auto panelCfg = _panel_instance.config();
    panelCfg.pin_cs = pinCS;  // 使用传入的CS引脚
    panelCfg.pin_rst = pinRST;  // 使用传入的RST引脚
    panelCfg.pin_busy = -1;
    panelCfg.panel_width = HardwareConfig::SCREEN_WIDTH;
    panelCfg.panel_height = HardwareConfig::SCREEN_HEIGHT;
    panelCfg.offset_x = 0;
    panelCfg.offset_y = 0;
    panelCfg.offset_rotation = 0;
    panelCfg.dummy_read_pixel = 8;
    panelCfg.dummy_read_bits = 1;
    panelCfg.readable = false;
    panelCfg.invert = true;
    panelCfg.rgb_order = false;
    panelCfg.dlen_16bit = false;
    panelCfg.bus_shared = true;  // 改为true以支持共享SPI总线
    _panel_instance.config(panelCfg);

    setPanel(&_panel_instance);
}

void Display::begin() {
    init();
    setRotation(0);
    setBrightness(HardwareConfig::BRIGHTNESS);
    fillScreen(ColorConfig::BG_COLOR);
}
