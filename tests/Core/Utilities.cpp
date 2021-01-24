/**
 * \file Utilities.cpp
 */

#include <ATK/Core/Utilities.h>

#include <cstdint>
#include <vector>

#include <gtest/gtest.h>

TEST(Utilities, test_convert_array_int16_t_int16_t)
{
  std::vector<std::int16_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, std::int16_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_int16_t_int32_t)
{
  std::vector<std::int16_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, std::int32_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int32_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int32_t>::max()),
      output[2],
      4e-5 * static_cast<double>(std::numeric_limits<std::int32_t>::max()));
}

TEST(Utilities, test_convert_array_int16_t_int64_t)
{
  std::vector<std::int16_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, int64_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<int64_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<int64_t>::max()),
      output[2],
      0.01 * static_cast<double>(std::numeric_limits<std::int64_t>::max()));
}

TEST(Utilities, test_convert_array_int16_t_float)
{
  std::vector<std::int16_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, float>::convert_array(&input[0], &output[0], 3);

  ASSERT_NEAR(-1, output[0], 0.01);
  ASSERT_NEAR(0, output[1], 0.01);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_int16_t_double)
{
  std::vector<std::int16_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<std::int16_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int16_t>::max();
  
  ATK::ConversionUtilities<std::int16_t, double>::convert_array(&input[0], &output[0], 3);

  ASSERT_NEAR(-1, output[0], 0.01);
  ASSERT_NEAR(0, output[1], 0.01);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_int32_t_int16_t)
{
  std::vector<std::int32_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, std::int16_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int16_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_EQ(std::numeric_limits<std::int16_t>::max(), output[2]);
}

TEST(Utilities, test_convert_array_int32_t_int32_t)
{
  std::vector<std::int32_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, std::int32_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_int32_t_int64_t)
{
  std::vector<std::int32_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, int64_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<int64_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<int64_t>::max()),
      output[2],
      0.01 * static_cast<double>(std::numeric_limits<std::int64_t>::max()));
}

TEST(Utilities, test_convert_array_int32_t_float)
{
  std::vector<std::int32_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, float>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(-1, output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_int32_t_double)
{
  std::vector<std::int32_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<std::int32_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<std::int32_t>::max();
  
  ATK::ConversionUtilities<std::int32_t, double>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(-1, output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_int64_t_int16_t)
{
  std::vector<int64_t> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max() - (static_cast<int64_t>(1) << 48);
  
  ATK::ConversionUtilities<int64_t, std::int16_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int16_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int16_t>::max()), output[2], 0.01);
}

TEST(Utilities, test_convert_array_int64_t_int32_t)
{
  std::vector<int64_t> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max() - (1L << 16);
  
  ATK::ConversionUtilities<int64_t, std::int32_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int32_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int32_t>::max()), output[2], 0.01);
}

TEST(Utilities, test_convert_array_int64_t_int64_t)
{
  std::vector<int64_t> input(3);
  std::vector<int64_t> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, int64_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_int64_t_float)
{
  std::vector<int64_t> input(3);
  std::vector<float> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, float>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(-1, output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_int64_t_double)
{
  std::vector<int64_t> input(3);
  std::vector<double> output(3);
  input[0] = std::numeric_limits<int64_t>::min();
  input[1] = 0;
  input[2] = std::numeric_limits<int64_t>::max();
  
  ATK::ConversionUtilities<int64_t, double>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(-1, output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(1, output[2], 0.01);
}

TEST(Utilities, test_convert_array_float_int16_t)
{
  std::vector<float> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999;
  
  ATK::ConversionUtilities<float, std::int16_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int16_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int16_t>::max()),
      output[2],
      0.01 * static_cast<double>(std::numeric_limits<std::int16_t>::max()));
}

TEST(Utilities, test_convert_array_float_int32_t)
{
  std::vector<float> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .999999;
  
  ATK::ConversionUtilities<float, std::int32_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int32_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int32_t>::max()),
      output[2],
      1e-4 * static_cast<double>(std::numeric_limits<std::int32_t>::max()));
}

TEST(Utilities, test_convert_array_float_int64_t)
{
  std::vector<float> input(3);
  std::vector<int64_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999999;
  
  ATK::ConversionUtilities<float, int64_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<int64_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<int64_t>::max()),
      output[2],
      1e-4 * static_cast<double>(std::numeric_limits<std::int64_t>::max()));
}

TEST(Utilities, test_convert_array_float_float)
{
  std::vector<float> input(3);
  std::vector<float> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<float, float>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_float_double)
{
  std::vector<float> input(3);
  std::vector<double> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<float, double>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_double_int16_t)
{
  std::vector<double> input(3);
  std::vector<std::int16_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999;
  
  ATK::ConversionUtilities<double, std::int16_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int16_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int16_t>::max()), output[2], 3);
}

TEST(Utilities, test_convert_array_double_int32_t)
{
  std::vector<double> input(3);
  std::vector<std::int32_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .999999;
  
  ATK::ConversionUtilities<double, std::int32_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<std::int32_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<std::int32_t>::max()),
      output[2],
      1e-6 * static_cast<double>(std::numeric_limits<std::int32_t>::max()));
}

TEST(Utilities, test_convert_array_double_int64_t)
{
  std::vector<double> input(3);
  std::vector<int64_t> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = .9999999;
  
  ATK::ConversionUtilities<double, int64_t>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(std::numeric_limits<int64_t>::min(), output[0]);
  ASSERT_EQ(0, output[1]);
  ASSERT_NEAR(static_cast<double>(std::numeric_limits<int64_t>::max()),
      output[2],
      1e-7 * static_cast<double>(std::numeric_limits<std::int64_t>::max()));
}

TEST(Utilities, test_convert_array_double_float)
{
  std::vector<double> input(3);
  std::vector<float> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<double, float>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}

TEST(Utilities, test_convert_array_double_double)
{
  std::vector<double> input(3);
  std::vector<double> output(3);
  input[0] = -1;
  input[1] = 0;
  input[2] = 1;
  
  ATK::ConversionUtilities<double, double>::convert_array(&input[0], &output[0], 3);

  ASSERT_EQ(input[0], output[0]);
  ASSERT_EQ(input[1], output[1]);
  ASSERT_EQ(input[2], output[2]);
}
