/**
 * \file HadamardFeedbackDelayNetworkFilter.h
 */

#ifndef ATK_DELAY_HADAMARDFEEDBACKDELAYNETWORKFILTER_H
#define ATK_DELAY_HADAMARDFEEDBACKDELAYNETWORKFILTER_H

#include <array>
#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Delay/config.h>

namespace ATK
{
  /// Mixture matrix for Hadamard
  template<typename DataType_, unsigned int order>
  class HadamardMixture
  {
  public:
    static const gsl::index nb_channels = 1 << order;
    typedef DataType_ DataType;
    /// Gain factor to take into account in the feedback loop due to the instability of the mixture
    static constexpr float gain_factor = 1.f;

    class MixtureImpl;
  };
}

#endif
