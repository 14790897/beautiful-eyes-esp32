#!/usr/bin/env python3
import os
from skidl import * # 导入 SKiDL 的所有工具

# -----------------------------------------------------------------
# 1. 设置 KiCad 9.0 路径 (必须！否则 SKiDL 找不到库)
# -----------------------------------------------------------------
kicad_path_base = r'`C:\Program Files\KiCad\9.0\share\kicad`'

k_sym_path = os.path.join(kicad_path_base, 'symbols')
if os.path.exists(k_sym_path):
    lib_search_paths[KICAD] = [k_sym_path] 
else:
    print(f"!!! 警告: 符号库路径不存在: {k_sym_path}")

k_fp_path = os.path.join(kicad_path_base, 'footprints')
if os.path.exists(k_fp_path):
    footprint_search_paths[KICAD] = [k_fp_path]
else:
    print(f"!!! 警告: 封装库路径不存在: {k_fp_path}")
# -----------------------------------------------------------------


# -----------------------------------------------------------------
# 2. 执行搜索
# -----------------------------------------------------------------
search_term = 'PinHeader_1x16' # 您要搜索的关键词
print(f"\n--- 正在搜索包含 '{search_term}' 的 KiCad 封装 ---")

# search() 默认搜索符号，我们需要指定搜索封装
search_results = search(search_term)

# 打印搜索结果
print(search_results)

print(f"\n--- 搜索完毕 ---")