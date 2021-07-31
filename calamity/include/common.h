#pragma once

// C includes
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// helps to differentiate between different
// `static` use cases
#define local_persist static
#define internal static
#define global static

// typedefs for typing less
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef size_t   usize;

typedef int64_t   i64;
typedef int32_t   i32;
typedef int16_t   i16;
typedef int8_t    i8;
typedef long long isize;

typedef float  f32;
typedef double f64;

// TODO: Custom string type
typedef char* string_t;
