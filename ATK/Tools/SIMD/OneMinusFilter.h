/**
 * \file OneMinusFilter.h
 */

#ifndef ATK_TOOLS_SIMD_ONEMINUSFILTER_H
#define ATK_TOOLS_SIMD_ONEMINUSFILTER_H

#include <memory>

#include <ATK/Core/BaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Create a SIMD filter to get 1 - previous value
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createOneMinusFilter(gsl::index nb_channels = 1);
}

#endif
