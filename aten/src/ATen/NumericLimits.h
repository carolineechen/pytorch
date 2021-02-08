#pragma once

#include <c10/macros/Macros.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <limits>

// NumericLimits.h is a holder for numeric limits definitions of commonly used
// types. This header is very specific to ROCm HIP and may be removed in the
// future. This header is derived from the legacy THCNumerics.cuh.

// The lower_bound and upper_bound constants are same as lowest and max for
// integral types, but are -inf and +inf for floating point types. They are
// useful in implementing min, max, etc.

namespace at {

template <typename T>
struct numeric_limits {
};

// WARNING: the following at::numeric_limits definitions are there only to support
//          HIP compilation for the moment. Use std::numeric_limits if you are not
//          compiling for ROCm.
//          from @colesbury: "The functions on numeric_limits aren't marked with
//          __device__ which is why they don't work with ROCm. CUDA allows them
//          because they're constexpr."

namespace {
  // ROCm doesn't like INFINITY too.
  constexpr double inf = INFINITY;
}

template <>
struct numeric_limits<bool> {
  static inline C10_HOST_DEVICE bool lowest() { return false; }
  static inline C10_HOST_DEVICE bool max() { return true; }
  static inline C10_HOST_DEVICE bool lower_bound() { return false; }
  static inline C10_HOST_DEVICE bool upper_bound() { return true; }
};

template <>
struct numeric_limits<uint8_t> {
  static inline C10_HOST_DEVICE uint8_t lowest() { return 0; }
  static inline C10_HOST_DEVICE uint8_t max() { return UINT8_MAX; }
  static inline C10_HOST_DEVICE uint8_t lower_bound() { return 0; }
  static inline C10_HOST_DEVICE uint8_t upper_bound() { return UINT8_MAX; }
};

template <>
struct numeric_limits<int8_t> {
  static inline C10_HOST_DEVICE int8_t lowest() { return INT8_MIN; }
  static inline C10_HOST_DEVICE int8_t max() { return INT8_MAX; }
  static inline C10_HOST_DEVICE int8_t lower_bound() { return INT8_MIN; }
  static inline C10_HOST_DEVICE int8_t upper_bound() { return INT8_MAX; }
};

template <>
struct numeric_limits<int16_t> {
  static inline C10_HOST_DEVICE int16_t lowest() { return INT16_MIN; }
  static inline C10_HOST_DEVICE int16_t max() { return INT16_MAX; }
  static inline C10_HOST_DEVICE int16_t lower_bound() { return INT16_MIN; }
  static inline C10_HOST_DEVICE int16_t upper_bound() { return INT16_MAX; }
};

template <>
struct numeric_limits<int32_t> {
  static inline C10_HOST_DEVICE int32_t lowest() { return INT32_MIN; }
  static inline C10_HOST_DEVICE int32_t max() { return INT32_MAX; }
  static inline C10_HOST_DEVICE int32_t lower_bound() { return INT32_MIN; }
  static inline C10_HOST_DEVICE int32_t upper_bound() { return INT32_MAX; }
};

template <>
struct numeric_limits<int64_t> {
#ifdef _MSC_VER
  static inline C10_HOST_DEVICE int64_t lowest() { return _I64_MIN; }
  static inline C10_HOST_DEVICE int64_t max() { return _I64_MAX; }
  static inline C10_HOST_DEVICE int64_t lower_bound() { return _I64_MIN; }
  static inline C10_HOST_DEVICE int64_t upper_bound() { return _I64_MAX; }
#else
  static inline C10_HOST_DEVICE int64_t lowest() { return INT64_MIN; }
  static inline C10_HOST_DEVICE int64_t max() { return INT64_MAX; }
  static inline C10_HOST_DEVICE int64_t lower_bound() { return INT64_MIN; }
  static inline C10_HOST_DEVICE int64_t upper_bound() { return INT64_MAX; }
#endif
};

template <>
struct numeric_limits<at::Half> {
  static inline C10_HOST_DEVICE at::Half lowest() { return at::Half(0xFBFF, at::Half::from_bits()); }
  static inline C10_HOST_DEVICE at::Half max() { return at::Half(0x7BFF, at::Half::from_bits()); }
  static inline C10_HOST_DEVICE at::Half lower_bound() { return at::Half(0xFC00, at::Half::from_bits()); }
  static inline C10_HOST_DEVICE at::Half upper_bound() { return at::Half(0x7C00, at::Half::from_bits()); }
};

template <>
struct numeric_limits<at::BFloat16> {
  static inline C10_HOST_DEVICE at::BFloat16 lowest() { return at::BFloat16(0xFF7F, at::BFloat16::from_bits()); }
  static inline C10_HOST_DEVICE at::BFloat16 max() { return at::BFloat16(0x7F7F, at::BFloat16::from_bits()); }
  static inline C10_HOST_DEVICE at::BFloat16 lower_bound() { return at::BFloat16(0xFF80, at::BFloat16::from_bits()); }
  static inline C10_HOST_DEVICE at::BFloat16 upper_bound() { return at::BFloat16(0x7F80, at::BFloat16::from_bits()); }
};

template <>
struct numeric_limits<float> {
  static inline C10_HOST_DEVICE float lowest() { return -std::numeric_limits<float>::max(); }
  static inline C10_HOST_DEVICE float max() { return std::numeric_limits<float>::max(); }
  static inline C10_HOST_DEVICE float lower_bound() { return -std::numeric_limits<float>::infinity(); }
  static inline C10_HOST_DEVICE float upper_bound() { return std::numeric_limits<float>::infinity(); }
};

template <>
struct numeric_limits<double> {
  static inline C10_HOST_DEVICE float lowest() { return -std::numeric_limits<float>::max(); }
  static inline C10_HOST_DEVICE float max() { return std::numeric_limits<float>::max(); }
  static inline C10_HOST_DEVICE double lower_bound() { return -std::numeric_limits<double>::infinity(); }
  static inline C10_HOST_DEVICE double upper_bound() { return std::numeric_limits<double>::infinity(); }
};

} // namespace at