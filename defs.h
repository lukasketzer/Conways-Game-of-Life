#pragma once

#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 500
#define WINDOW_NAME "Conways game of life"


typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef size_t   usize;
typedef __ssize_t isize;

#define CHECKFLAGS(byte, flag) !!((byte & flag) == flag)



