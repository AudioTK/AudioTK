/**
 * \file OffsetVolumeFilter.h
 */

#ifndef ATK_TOOLS_SIMD_OFFSETVOLUMEFILTER_H
#define ATK_TOOLS_SIMD_OFFSETVOLUMEFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to split channels M/S
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOffsetVolumeFilter(gsl::index nb_channels = 1);
}

#endif
