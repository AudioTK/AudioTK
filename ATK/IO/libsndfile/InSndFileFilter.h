/**
 * \file InSndFileFilter.h
 */

#ifndef ATK_IO_INSNDFILEFILTER_H
#define ATK_IO_INSNDFILEFILTER_H

#include <memory>
#include <string>

#include <ATK/IO/config.h>
#include <ATK/Core/TypedBaseFilter.h>

class SndfileHandle;

namespace ATK
{
  /// A source filter for sound files supported by lbsnd
  template<typename DataType_>
  class ATK_IO_EXPORT InSndFileFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::outputs;
    using Parent::output_sampling_rate;
    using Parent::set_output_sampling_rate;
    using Parent::set_nb_output_ports;
    
  private:
    std::unique_ptr<SndfileHandle> stream;
  protected:
    void process_impl(gsl::index size) const final;
  public:
    /*!
     * @brief Constructor
     * @param filename is the name of the input file
     */
    InSndFileFilter(const std::string& filename);
    /// Destructor
    ~InSndFileFilter();
    
    /// Returns the number of frames/samples in the opened file
    int64_t get_frames() const;
  };
}
#endif
