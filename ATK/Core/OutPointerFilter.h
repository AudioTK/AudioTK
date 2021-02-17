/**
 * \file OutPointerFilter.h
 */

#ifndef ATK_CORE_OUTPOINTERFILTER_H
#define ATK_CORE_OUTPOINTERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Filter allowing to output data in an array
  template<typename DataType_>
  class ATK_CORE_EXPORT OutPointerFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::input_sampling_rate;
    
  public:
    using Parent::set_input_sampling_rate;

    /**
     * @brief Create a filter for the end of a pipeline
     * @param array is the pointer to the data that will be reused during all the processing
     * @param size in the size of the data for one channel
     * @param channels is the number of total channels
     * @param interleaved indicates if the data is interleaved (Wav/Fortran order) or not (C order). If interleaved, size and channels switch position.
     */
    OutPointerFilter(DataType* array, int channels, gsl::index size, bool interleaved);
    /// Destructor
    ~OutPointerFilter() override = default;
    OutPointerFilter(OutPointerFilter&&) = default;
    OutPointerFilter& operator=(OutPointerFilter&&) = default;

    /**
     * @brief Resets the pointer and the internal offset
     * @param array is the pointer to the new array
     * @param size is the allocated size of the array (whether interleaved or not)
     */
    void set_pointer(DataType* array, gsl::index size);

  protected:
    /// This implementation retrieves inputs from other filters and converts it accordingly
    void process_impl(gsl::index size) const final;
    /// Current offset in the array
    mutable gsl::index offset{0};
    /// Output array
    DataType* array = nullptr;
    /// Size of the output array
    gsl::index mysize{0};
    /// Number of channels/ports in the array
    unsigned int channels{0};
    /// Is the output array interleaved?
    bool interleaved = false;
  };
}

#endif
