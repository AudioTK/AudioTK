/**
 * \file TypeTraits.cpp
 */

#include <ATK/Core/TypeTraits.h>

#include <gtest/gtest.h>

TEST(TypeTraits, test_to_double_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::to_double(std::numeric_limits<std::int16_t>::min()), -1);
}

TEST(TypeTraits, test_to_double_char3)
{
  char data[3] = {static_cast<char>(0),static_cast<char>(0),static_cast<char>(0x80)};
  ASSERT_EQ(ATK::TypeTraits<char[3]>::to_double(data), -1);
}

TEST(TypeTraits, test_to_double_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::to_double(std::numeric_limits<std::int32_t>::min()), -1);
}

TEST(TypeTraits, test_to_double_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::to_double(std::numeric_limits<int64_t>::min()), -1);
}

TEST(TypeTraits, test_from_double_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::from_double(-1), std::numeric_limits<std::int16_t>::min());
}

TEST(TypeTraits, test_from_double_char3)
{
  std::int32_t ref = (1L << 8) * std::numeric_limits<std::int16_t>::min();
  ASSERT_EQ(ATK::TypeTraits<char[3]>::from_double(-1), ref);
}

TEST(TypeTraits, test_from_double_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::from_double(-1), std::numeric_limits<std::int32_t>::min());
}

TEST(TypeTraits, test_from_double_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::from_double(-1), std::numeric_limits<int64_t>::min());
}

TEST(TypeTraits, test_conj_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::conj(-1), -1);
}

TEST(TypeTraits, test_conj_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::conj(-1), -1);
}

TEST(TypeTraits, test_conj_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::conj(-1), -1);
}

TEST(TypeTraits, test_conj_float)
{
  ASSERT_EQ(ATK::TypeTraits<float>::conj(-1), -1);
}

TEST(TypeTraits, test_conj_double)
{
  ASSERT_EQ(ATK::TypeTraits<double>::conj(-1), -1);
}

TEST(TypeTraits, test_conj_cfloat)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<float>>::conj(std::complex<float>(-1, 1)), std::complex<float>(-1, -1));
}

TEST(TypeTraits, test_conj_cdouble)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<double>>::conj(std::complex<double>(-1, 1)), std::complex<double>(-1, -1));
}

TEST(TypeTraits, test_zero_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::Zero(), 0);
}

TEST(TypeTraits, test_zero_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::Zero(), 0);
}

TEST(TypeTraits, test_zero_char3)
{
  ASSERT_EQ(ATK::TypeTraits<char[3]>::Zero(), 0);
}

TEST(TypeTraits, test_zero_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::Zero(), 0);
}

TEST(TypeTraits, test_zero_float)
{
  ASSERT_EQ(ATK::TypeTraits<float>::Zero(), 0);
}

TEST(TypeTraits, test_zero_double)
{
  ASSERT_EQ(ATK::TypeTraits<double>::Zero(), 0);
}

TEST(TypeTraits, test_zero_cfloat)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<float>>::Zero(), 0);
}

TEST(TypeTraits, test_zero_cdouble)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<double>>::Zero(), 0);
}

TEST(TypeTraits, test_one_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::One(), 1);
}

TEST(TypeTraits, test_one_char3)
{
  ASSERT_EQ(ATK::TypeTraits<char[3]>::One(), 1);
}

TEST(TypeTraits, test_one_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::One(), 1);
}

TEST(TypeTraits, test_one_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::One(), 1);
}

TEST(TypeTraits, test_one_float)
{
  ASSERT_EQ(ATK::TypeTraits<float>::One(), 1);
}

TEST(TypeTraits, test_one_double)
{
  ASSERT_EQ(ATK::TypeTraits<double>::One(), 1);
}

TEST(TypeTraits, test_one_cfloat)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<float>>::One(), 1);
}

TEST(TypeTraits, test_one_cdouble)
{
  ASSERT_EQ(ATK::TypeTraits<std::complex<double>>::One(), 1);
}

TEST(TypeTraits, test_max_int16_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int16_t>::max(0, 1), 1);
}

TEST(TypeTraits, test_max_int32_t)
{
  ASSERT_EQ(ATK::TypeTraits<std::int32_t>::max(0, 1), 1);
}

TEST(TypeTraits, test_max_int64_t)
{
  ASSERT_EQ(ATK::TypeTraits<int64_t>::max(0, 1), 1);
}

TEST(TypeTraits, test_max_float)
{
  ASSERT_EQ(ATK::TypeTraits<float>::max(0, 1), 1);
}

TEST(TypeTraits, test_max_double)
{
  ASSERT_EQ(ATK::TypeTraits<double>::max(0, 1), 1);
}
