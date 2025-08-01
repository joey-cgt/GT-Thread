#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__

#include <cstdint>  // 包含标准整数类型

// 有符号整数
using INT8   = int8_t;    // 8-bit 整数（-128 ~ 127）
using INT16  = int16_t;   // 16-bit 整数（-32768 ~ 32767）
using INT32  = int32_t;   // 32-bit 整数
using INT64  = int64_t;   // 64-bit 整数

// 无符号整数
using UINT8  = uint8_t;   // 8-bit 无符号整数（0 ~ 255）
using UINT16 = uint16_t;  // 16-bit 无符号整数（0 ~ 65535）
using UINT32 = uint32_t;  // 32-bit 无符号整数
using UINT64 = uint64_t;  // 64-bit 无符号整数

// 浮点数类型
using FLOAT32 = float;    // 32-bit 单精度浮点数
using FLOAT64 = double;   // 64-bit 双精度浮点数

// 字符类型
using CHAR    = char;      // 8-bit 字符（可能是 signed 或 unsigned）
using SCHAR   = signed char;   // 有符号 8-bit 字符
using UCHAR   = unsigned char; // 无符号 8-bit 字符
using WCHAR   = wchar_t;       // 宽字符（Windows 通常是 16-bit，Linux 通常是 32-bit）

// 布尔类型
using BOOL = bool;  // 布尔类型（true/false）

#endif // __BASIC_TYPES_H__