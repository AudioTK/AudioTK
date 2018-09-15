/**
 * \file OversamplingFilter.h
 */

#ifndef ATK_TOOLS_SIMD_OVERSAMPLINGFILTER_H
#define ATK_TOOLS_SIMD_OVERSAMPLINGFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to oversample channels (6 points, 5th order, x2)
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_2(gsl::index nb_channels = 1);
  /// Create a SIMD filter to oversample channels (6 points, 5th order, x4)
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_4(gsl::index nb_channels = 1);
  /// Create a SIMD filter to oversample channels (6 points, 5th order, x8)
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_8(gsl::index nb_channels = 1);
  /// Create a SIMD filter to oversample channels (6 points, 5th order, x16)
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_16(gsl::index nb_channels = 1);
  /// Create a SIMD filter to oversample channels (6 points, 5th order, x32)
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOversamplingFilter6points5order_32(gsl::index nb_channels = 1);
}

#endif
