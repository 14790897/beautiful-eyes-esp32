import os

# esp32c3使用的引脚：
#     constexpr int PIN_SCLK = 2;
#     constexpr int PIN_MOSI = 3;
#     constexpr int PIN_MISO = -1;
#     constexpr int PIN_DC = 10;
#     constexpr int PIN_CS = 6;
#     constexpr int PIN_RST = 7;
# esp32c3左边从上到下是1-16，右边是17-32
# <tbody>
# <tr class="row-even"><td><p>32</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>31</p></td>
# <td><p>5V</p></td>
# <td><p>5V电源接口，与USB的VBUS相连</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>30</p></td>
# <td><p>BOOT</p></td>
# <td><p>GPIO09,输入</p></td>
# <td><p>BOOTMODE</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>29</p></td>
# <td><p>IO08</p></td>
# <td><p>GPIO08,输入，输出，高阻</p></td>
# <td><p></p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>28</p></td>
# <td><p>IO04</p></td>
# <td><p>GPIO04,输入，输出，高阻</p></td>
# <td><p>I2C_SDA/ADC_4</p></td>
# <td><p>VDD3P3_RTC</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>27</p></td>
# <td><p>IO05</p></td>
# <td><p>GPIO05,输入，输出，高阻</p></td>
# <td><p>I2C_SCL/ADC_5</p></td>
# <td><p>VDD3P3_RTC</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>26</p></td>
# <td><p>3.3V</p></td>
# <td><p>芯片电源，3.3V</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>25</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>24</p></td>
# <td><p>PB_11</p></td>
# <td><p>GPIO11,输入，输出，高阻</p></td>
# <td><p>VDD_SPI</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>23</p></td>
# <td><p>IO07</p></td>
# <td><p>GPIO07,输入，输出，高阻</p></td>
# <td><p>SPI2_CS</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>22</p></td>
# <td><p>IO06</p></td>
# <td><p>GPIO06,输入，输出，高阻</p></td>
# <td><p></p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>21</p></td>
# <td><p>IO10</p></td>
# <td><p>GPIO10,输入，输出，高阻</p></td>
# <td><p>SPI2_MISO</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>20</p></td>
# <td><p>IO03</p></td>
# <td><p>GPIO03,输入，输出，高阻</p></td>
# <td><p>SPI2_MOSI/ADC_3</p></td>
# <td><p>VDD3P3_RTC</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>19</p></td>
# <td><p>IO02</p></td>
# <td><p>GPIO02,输入，输出，高阻</p></td>
# <td><p>SPI2_CK/ADC_2</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>18</p></td>
# <td><p>3.3V</p></td>
# <td><p>芯片电源，3.3V</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>17</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>16</p></td>
# <td><p>5V</p></td>
# <td><p>5V电源接口，与USB的VBUS相连</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>15</p></td>
# <td><p>PWB</p></td>
# <td><p>芯片3.3V供电控制,高电平有效，不用可悬空</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>14</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>13</p></td>
# <td><p>3.3V</p></td>
# <td><p>芯片电源，3.3V</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>12</p></td>
# <td><p>RESET</p></td>
# <td><p>芯片复位</p></td>
# <td><p></p></td>
# <td><p>VDD3P3_RTC</p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-odd"><td><p>11</p></td>
# <td><p>NC</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>10</p></td>
# <td><p>IO13</p></td>
# <td><p>GPIO13,输入，输出，高阻</p></td>
# <td><p></p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>09</p></td>
# <td><p>U0_TX</p></td>
# <td><p>GPIO21,输入，输出，高阻</p></td>
# <td><p>UART0_TX</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>08</p></td>
# <td><p>U0_RX</p></td>
# <td><p>GPIO20,输入，输出，高阻</p></td>
# <td><p>UART0_RX</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>07</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# <tr class="row-even"><td><p>06</p></td>
# <td><p>IO19</p></td>
# <td><p>GPIO19,输入，输出，高阻</p></td>
# <td><p>USB_D+</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>05</p></td>
# <td><p>IO18</p></td>
# <td><p>GPIO18,输入，输出，高阻</p></td>
# <td><p>USB_D-</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>04</p></td>
# <td><p>IO12</p></td>
# <td><p>GPIO12,输入，输出，高阻</p></td>
# <td><p>SPIHD</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>03</p></td>
# <td><p>IO01</p></td>
# <td><p>GPIO1,输入，输出，高阻</p></td>
# <td><p>UART1_RX/ADC_1</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-even"><td><p>02</p></td>
# <td><p>IO00</p></td>
# <td><p>GPIO0,输入，输出，高阻</p></td>
# <td><p>UART1_TX/ADC_0</p></td>
# <td><p>VDD3P3_CPU</p></td>
# <td><p>UP/DOWN</p></td>
# </tr>
# <tr class="row-odd"><td><p>01</p></td>
# <td><p>GND</p></td>
# <td><p>接地</p></td>
# <td><p></p></td>
# <td><p></p></td>
# <td><p></p></td>
# </tr>
# </tbody>


# 屏幕引脚顺序：
# gnd vcc scl sda res dc cs blk


from skidl import *

# -----------------------------------------------------------------
# 1. 重置 SKiDL
# -----------------------------------------------------------------
reset()
print("SKiDL 已重置。")
# $env:KICAD_SYMBOL_DIR = 'C:\Program Files\KiCad\9.0\share\kicad'
# -----------------------------------------------------------------
# 解决方案：添加 KiCad 9.0 的【符号】和【封装】路径
# -----------------------------------------------------------------
kicad_path_base = r"C:\Program Files\KiCad\9.0\share\kicad"

# 添加符号库路径
k_sym_path = os.path.join(kicad_path_base, "symbols")
if os.path.exists(k_sym_path):
    # 修正：使用 = [path] 来创建一个新列表，而不是 .append()
    lib_search_paths[KICAD] = [k_sym_path]
    print(f"已设置 KiCad 符号库路径: {k_sym_path}")
else:
    print(f"!!! 警告: 符号库路径不存在: {k_sym_path}")

# 添加封装库路径 (修复 fp-lib-table 警告)
k_fp_path = os.path.join(kicad_path_base, "footprints")
if os.path.exists(k_fp_path):
    # 修正：同样使用 = [path] 来创建新列表，解决 'str' object has no attribute 'append' 错误
    footprint_search_paths[KICAD] = [k_fp_path]
    print(f"已设置 KiCad 封装库路径: {k_fp_path}")
else:
    print(f"!!! 警告: 封装库路径不存在: {k_fp_path}")
# -----------------------------------------------------------------

# -----------------------------------------------------------------
# 2. 定义元器件
# -----------------------------------------------------------------
LIB_CONN = "Connector_Generic"  # KiCad generic connector symbol library

try:
    # --- 开发板 (使用母头插座) ---
    board_left = Part(LIB_CONN, "Conn_01x16")  # 1x16 single-row connector symbol
    board_right = Part(LIB_CONN, "Conn_01x16")  # another 1x16 connector symbol

    board_left.footprint = "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical"
    board_right.footprint = "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical"

    # --- SPI 屏幕 (同样使用母头插座) ---
    spi_screen = Part(LIB_CONN, "Conn_01x08")  # 1x8 single-row connector symbol
    spi_screen.footprint = "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical"

    print("✓ 元器件定义完毕 (全部使用 PinSocket 母座)")

except (ValueError, FileNotFoundError) as e:
    print(f"✗ 错误: {e}")
    exit()
# -----------------------------------------------------------------
# 3. 【已修改】定义电源和地 (根据新的开发板引脚图)
# -----------------------------------------------------------------
print("正在连接电源 (根据新的引脚图)...")
vcc = Net("3V3")
gnd = Net("GND")

# --- 连接开发板上的 3.3V 电源 ---
# (根据新表格，Pin 13 是 3.3V)
vcc += board_left[13]  # 物理引脚 13

# --- 连接开发板上的所有 GND ---
# (根据新表格，Pin 1, 7, 14, 17, 25, 32 是 GND)
gnd += board_left[1]  # 物理引脚 1
gnd += board_left[7]  # 物理引脚 7
gnd += board_left[14]  # 物理引脚 14
gnd += board_right[1]  # 物理引脚 17 (右侧第1脚)
gnd += board_right[9]  # 物理引脚 25 (右侧第9脚)
gnd += board_right[16]  # 物理引脚 32 (右侧第16脚)

# --- 连接屏幕的电源 (根据新的屏幕引脚顺序) ---
# Pin 1 = gnd
# Pin 2 = vcc
gnd += spi_screen[1]
vcc += spi_screen[2]

print("✓ 电源连接完毕。")

# -----------------------------------------------------------------
# 4. 【已修改】定义并连接 SPI 和控制引脚 (根据新的注释)
# -----------------------------------------------------------------
print("正在连接 SPI 和控制引脚 (根据新的引脚定义)...")

# 目标: 屏幕引脚 -> ESP32 GPIO -> 物理引脚 -> SKiDL 引脚
# ----------------------------------------------------------------
# SCL (Pin 3) -> GPIO2  -> 物理 Pin 19 -> board_right[3]
# SDA (Pin 4) -> GPIO3  -> 物理 Pin 20 -> board_right[4]
# RES (Pin 5) -> GPIO7  -> 物理 Pin 23 -> board_right[7]
# DC  (Pin 6) -> GPIO10 -> 物理 Pin 21 -> board_right[5]
# CS  (Pin 7) -> GPIO6  -> 物理 Pin 22 -> board_right[6]
# BLK (Pin 8) -> GPIO11 -> 物理 Pin 24 -> board_right[8]

spi_screen[3] += board_right[3]  # SCL (Pin 19 / GPIO2)
spi_screen[4] += board_right[4]  # SDA/MOSI (Pin 20 / GPIO3)
spi_screen[5] += board_right[7]  # RES (Pin 23 / GPIO7)
spi_screen[6] += board_right[5]  # DC (Pin 21 / GPIO10)
spi_screen[7] += board_right[6]  # CS (Pin 22 / GPIO6)
spi_screen[8] += board_right[8]  # BLK (Pin 24 / GPIO11)

print("✓ SPI 引脚连接完毕。")

# -----------------------------------------------------------------
# 5. 【新】在 SKIDL 中定义物理位置
# -----------------------------------------------------------------
print("正在分配物理坐标...")

# KiCad 坐标系：Y 轴向下
# 我们把 J1 放在 (100, 100)
board_left.pos = (100, 100)

# 我们把 J2 放在 (100 + 18mm, 100)
# (18mm = 708.66 mils, 但我们直接用 mm)
board_right.pos = (118, 100)
# board_right.pos.unit = "MM"  # 确保单位是毫米
# board_left.pos.unit = "MM"  # 确保单位是毫米

spi_screen.pos = (109, 90)
# spi_screen.pos.unit = "MM"  
print(f"  - J1 (left)  位置: {board_left.pos}")
print(f"  - J2 (right) 位置: {board_right.pos} (间距 18mm)")
print(f"  - J3 (screen)位置: {spi_screen.pos}")

# -----------------------------------------------------------------
# 6. 生成网表 (Netlist) (脚本的其余部分保持不变)
# -----------------------------------------------------------------
print("正在生成 KiCad 网表文件...")
generate_xml("luatos_esp32_spi_screen.xml")
generate_netlist(tool=KICAD9)
generate_pcb()
print("==========================================================")
print(" 脚本执行完毕!")
print(" 已生成 luatos_esp32_spi_screen.xml 文件。")
print("==========================================================")
# ... (后面的 print 语句保持不变) ...
