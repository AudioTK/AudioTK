/**
* \file GainFilter.cpp
*/

#include <gsl/gsl>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/Dynamic/GainCompressorFilter.h>
#include <ATK/Dynamic/GainExpanderFilter.h>
#include <ATK/Dynamic/GainFilter.h>
#include <ATK/Dynamic/GainLimiterFilter.h>
#include <ATK/Dynamic/GainSwellFilter.h>

#include <ATK/Dynamic/GainColoredCompressorFilter.h>
#include <ATK/Dynamic/GainColoredExpanderFilter.h>
#include <ATK/Dynamic/GainMaxColoredExpanderFilter.h>
#include <ATK/Dynamic/GainMaxCompressorFilter.h>
#include <ATK/Dynamic/GainMaxExpanderFilter.h>

namespace py = pybind11;

using namespace ATK;

namespace
{
  
  template<typename DataType, typename T>
  void populate_ParentGainFilter(py::module& m, const char* type, T& parent)
  {
    py::class_<ParentGainFilter<DataType>>(m, type, parent)
    .def_property("threshold", &ParentGainFilter<DataType>::get_threshold, &ParentGainFilter<DataType>::set_threshold)
    .def_property("ratio", &ParentGainFilter<DataType>::get_ratio, &ParentGainFilter<DataType>::set_ratio);
  }
  
  template<typename Filter>
  void populate_SimpleGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness);
  }
  
  template<typename Filter>
  void populate_ColoredGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("color", &Filter::get_color, &Filter::set_color)
    .def_property("quality", &Filter::get_quality, &Filter::set_quality);
  }
  
  template<typename Filter>
  void populate_MaxColoredGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("color", &Filter::get_color, &Filter::set_color)
    .def_property("quality", &Filter::get_quality, &Filter::set_quality)
    .def_property("max_reduction", &Filter::get_max_reduction, &Filter::set_max_reduction);
  }
  
  template<typename Filter>
  void populate_MaxGainFilter(py::module& m, const char* type)
  {
    py::class_<Filter, typename Filter::Parent>(m, type)
    .def_property("softness", &Filter::get_softness, &Filter::set_softness)
    .def_property("max_reduction", &Filter::get_max_reduction, &Filter::set_max_reduction);
  }
  
  template<typename Filter>
  void populate_GainFilter(py::module& m, const char* type)
  {
    py::class_<GainFilter<Filter>, Filter>(m, type)
    .def(py::init<gsl::index, gsl::index, gsl::index>(), py::arg("nb_channels") = gsl::index(1), py::arg("LUTsize") = gsl::index(128*1024), py::arg("LUTprecision") = gsl::index(64));
  }
}

void populate_GainFilter(pybind11::module& m,
#if ATK_ENABLE_INSTANTIATION
    const pybind11::object& f1,
#endif
    const pybind11::object& f2)
{
#if ATK_ENABLE_INSTANTIATION
  populate_ParentGainFilter<float>(m, "FloatParentGainFilter", f1);
#endif
  populate_ParentGainFilter<double>(m, "DoubleParentGainFilter", f2);
  
#if ATK_ENABLE_INSTANTIATION
  populate_SimpleGainFilter<GainCompressorFilter<float>>(m, "FloatTempGainCompressorFilter");
  populate_SimpleGainFilter<GainExpanderFilter<float>>(m, "FloatTempGainExpanderFilter");
  populate_SimpleGainFilter<GainLimiterFilter<float>>(m, "FloatTempGainLimiterFilter");
  populate_SimpleGainFilter<GainSwellFilter<float>>(m, "FloatTempGainSwellFilter");
#endif
  populate_SimpleGainFilter<GainCompressorFilter<double>>(m, "DoubleTempGainCompressorFilter");
  populate_SimpleGainFilter<GainExpanderFilter<double>>(m, "DoubleTempGainExpanderFilter");
  populate_SimpleGainFilter<GainLimiterFilter<double>>(m, "DoubleTempGainLimiterFilter");
  populate_SimpleGainFilter<GainSwellFilter<double>>(m, "DoubleTempGainSwellFilter");
  
#if ATK_ENABLE_INSTANTIATION
  populate_GainFilter<GainCompressorFilter<float>>(m, "FloatGainCompressorFilter");
  populate_GainFilter<GainExpanderFilter<float>>(m, "FloatGainExpanderFilter");
  populate_GainFilter<GainLimiterFilter<float>>(m, "FloatGainLimiterFilter");
  populate_GainFilter<GainSwellFilter<float>>(m, "FloatGainSwellFilter");
#endif
  populate_GainFilter<GainCompressorFilter<double>>(m, "DoubleGainCompressorFilter");
  populate_GainFilter<GainExpanderFilter<double>>(m, "DoubleGainExpanderFilter");
  populate_GainFilter<GainLimiterFilter<double>>(m, "DoubleGainLimiterFilter");
  populate_GainFilter<GainSwellFilter<double>>(m, "DoubleGainSwellFilter");
  
#if ATK_ENABLE_INSTANTIATION
  populate_ColoredGainFilter<GainColoredCompressorFilter<float>>(m, "FloatTempGainColoredCompressorFilter");
  populate_ColoredGainFilter<GainColoredExpanderFilter<float>>(m, "FloatTempGainColoredExpanderFilter");
  populate_MaxColoredGainFilter<GainMaxColoredExpanderFilter<float>>(m, "FloatTempGainMaxColoredExpanderFilter");
  populate_MaxGainFilter<GainMaxCompressorFilter<float>>(m, "FloatTempGainMaxCompressorFilter");
  populate_MaxGainFilter<GainMaxExpanderFilter<float>>(m, "FloatTempGainMaxExpanderFilter");
#endif
  populate_ColoredGainFilter<GainColoredCompressorFilter<double>>(m, "DoubleTempGainColoredCompressorFilter");
  populate_ColoredGainFilter<GainColoredExpanderFilter<double>>(m, "DoubleTempGainColoredExpanderFilter");
  populate_MaxColoredGainFilter<GainMaxColoredExpanderFilter<double>>(m, "DoubleTempGainMaxColoredExpanderFilter");
  populate_MaxGainFilter<GainMaxCompressorFilter<double>>(m, "DoubleTempGainMaxCompressorFilter");
  populate_MaxGainFilter<GainMaxExpanderFilter<double>>(m, "DoubleTempGainMaxExpanderFilter");
  
#if ATK_ENABLE_INSTANTIATION
  populate_GainFilter<GainColoredCompressorFilter<float>>(m, "FloatGainColoredCompressorFilter");
  populate_GainFilter<GainColoredExpanderFilter<float>>(m, "FloatGainColoredExpanderFilter");
  populate_GainFilter<GainMaxColoredExpanderFilter<float>>(m, "FloatGainMaxColoredExpanderFilter");
  populate_GainFilter<GainMaxCompressorFilter<float>>(m, "FloatGainMaxCompressorFilter");
  populate_GainFilter<GainMaxExpanderFilter<float>>(m, "FloatGainMaxExpanderFilter");
#endif
  populate_GainFilter<GainColoredCompressorFilter<double>>(m, "DoubleGainColoredCompressorFilter");
  populate_GainFilter<GainColoredExpanderFilter<double>>(m, "DoubleGainColoredExpanderFilter");
  populate_GainFilter<GainMaxColoredExpanderFilter<double>>(m, "DoubleGainMaxColoredExpanderFilter");
  populate_GainFilter<GainMaxCompressorFilter<double>>(m, "DoubleGainMaxCompressorFilter");
  populate_GainFilter<GainMaxExpanderFilter<double>>(m, "DoubleGainMaxExpanderFilter");
}
