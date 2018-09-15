/**
 * \file AllPassReverbFilter.h
 */

#ifndef ATK_REVERBERATION_ALLPASSREVERBFILTER_H
#define ATK_REVERBERATION_ALLPASSREVERBFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Reverberation/config.h>

namespace ATK
{
  /// Simple all pass reverb filter
  template<typename DataType_>
  class ATK_REVERBERATION_EXPORT AllPassReverbFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_delay;
    using Parent::outputs;
    using Parent::output_delay;

  public:
    /*!
    * @brief construct the filter with a maximum delay line size
    * @param max_delay is the maximum delay allowed
    */
    AllPassReverbFilter(gsl::index max_delay);
    /// Destructor
    ~AllPassReverbFilter() override;

    /// Changes the delay used for the filter
    void set_delay(gsl::index delay);
    /// Returns the elay used for the system
    gsl::index get_delay() const;

    /// Sets feedback amount (between -1 and 1)
    void set_feedback(DataType_ feedback);
    /// Gets feedback amount
    DataType_ get_feedback() const;
  protected:
    void process_impl(gsl::index size) const final;

  private:
    gsl::index delay;
    DataType_ feedback;
  };
}

#endif
