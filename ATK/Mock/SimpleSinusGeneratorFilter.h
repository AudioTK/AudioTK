/**
 * \file SimpleSinusGeneratorFilter.h
 */

#ifndef ATK_MOCK_SIMPLESINUSGENERATORFILTER_H
#define ATK_MOCK_SIMPLESINUSGENERATORFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Mock/config.h>

namespace ATK
{
  /// Filter creating a sinus signal (usng std::sin, so not precise enough and fast enough)
  template<class DataType_>
  class ATK_MOCK_EXPORT SimpleSinusGeneratorFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    
    /// Constructor
    SimpleSinusGeneratorFilter();
    /// Destructor
    ~SimpleSinusGeneratorFilter() override;
    
    /// Sets the amplitude of the sinusoid
    void set_amplitude(DataType_ amplitude);
    /// Sets the frequency of the sinusoid
    void set_frequency(int frequency);
    
  protected:
    void process_impl(gsl::index size) const final;

  private:
    mutable double state;
    DataType_ amplitude;
    int frequency;
  };
}

#endif
