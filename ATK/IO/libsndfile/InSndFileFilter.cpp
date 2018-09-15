/**
 * \file InSndFileFilter.cpp
 */

#include <ATK/IO/libsndfile/InSndFileFilter.h>

#include <sndfile.hh>

namespace ATK
{
  template<typename DataType>
  InSndFileFilter<DataType>::InSndFileFilter(const std::string& filename)
  :TypedBaseFilter<DataType>(0, 0)
  {
    stream.reset(new SndfileHandle(filename.c_str()));
    set_output_sampling_rate(stream->samplerate());
    set_nb_output_ports(stream->channels());
    stream->command(SFC_SET_SCALE_FLOAT_INT_READ, NULL, 1);
  }

  template<typename DataType>
  InSndFileFilter<DataType>::~InSndFileFilter()
  {
  }

  template<typename DataType>
  int64_t InSndFileFilter<DataType>::get_frames() const
  {
    return stream->frames();
  }

  template<typename DataType>
  void InSndFileFilter<DataType>::process_impl(gsl::index size) const
  {
    std::vector<DataType> temp(size * outputs.size());
    stream->read(temp.data(), size * outputs.size());
    
    for(gsl::index i = 0; i < size; ++i)
    {
      for(gsl::index j = 0; j < outputs.size(); ++j)
      {
        outputs[j][i] = temp[j + i * outputs.size()];
      }
    }

  }
  
  template class InSndFileFilter<std::int16_t>;
  template class InSndFileFilter<std::int32_t>;
  template class InSndFileFilter<float>;
  template class InSndFileFilter<double>;
}
