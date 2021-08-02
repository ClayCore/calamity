#pragma once

// C includes
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// C++ includes
#include <algorithm>
#include <any>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <numeric>
#include <optional>
#include <ostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

// helps to differentiate between different
// `static` use cases
#define local_persist static
#define internal static
#define global static

using u64   = uint64_t;
using u32   = uint32_t;
using u16   = uint16_t;
using u8    = uint8_t;
using usize = size_t;

using Byte  = u8;
using Word  = u16;
using Dword = u32;
using Qword = u64;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8  = int8_t;

using SignedByte  = i8;
using SignedWord  = i16;
using SignedDword = i32;
using SignedQword = i64;

using f32 = float;
using f64 = double;

// using char8  = char8_t;
// using char16 = char16_t;
// using char32 = char32_t;
