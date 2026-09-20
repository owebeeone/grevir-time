// Migrated from the retained Ardoinus cases to Catch2.
#include <grevir/time/units.hpp>


#include <catch2/catch_test_macros.hpp>
#include <grevir/base/compat/cstdint.hpp>

namespace setl_time_unit_test {



struct Setl_TIME_UNIT_TEST_DO_NOT_USE {

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::HOUR>::Converter<unsigned>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
    setl::TimeUnit::DAY, 
    setl::TimeUnit::HOUR>::Converter<std::uint16_t>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::HOUR>::Converter<unsigned long long>::multiplier == 24,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::MINUTE>::Converter<unsigned>::multiplier == 24 * 60,
    "conversion error");

  static_assert(
    setl::ConvertTime<
      setl::TimeUnit::DAY,
      setl::TimeUnit::MINUTE>::Converter<unsigned long long>::multiplier == 24 * 60,
    "conversion error");

  template <typename T>
  struct TestCollection {
    TestCollection() {
      to_test();
    }

    template <setl::TimeUnit w_from, setl::TimeUnit w_to>
    using ConvertTime = setl::ConvertTime<w_from, w_to>;

    static const auto DAY = setl::TimeUnit::DAY;
    static const auto HOUR = setl::TimeUnit::HOUR;
    static const auto MINUTE = setl::TimeUnit::MINUTE;
    static const auto SECOND = setl::TimeUnit::SECOND;
    static const auto MICROS = setl::TimeUnit::MICROS;
    static const auto NANOS = setl::TimeUnit::NANOS;

    void to_test() {
      REQUIRE((ConvertTime<DAY, MINUTE>::convert(T(1))) == (24 * 60));
      REQUIRE((ConvertTime<MICROS, NANOS>::convert(T(1))) == (1000));
      REQUIRE((ConvertTime<NANOS, MICROS>::convert(T(10001))) == (T(10001)/1000));
    }

  };

  bool run() {
    TestCollection<unsigned> t1;
    TestCollection<unsigned short> t2;
    TestCollection<unsigned long> t3;
    TestCollection<unsigned long long> t4;
    TestCollection<signed long> t5;
    TestCollection<signed long long> t6;
    TestCollection<float> t7;
    TestCollection<double> t8;
    TestCollection<long double> t9;
    return true;
  }
};

TEST_CASE("time unit conversions preserve legacy results") {
  Setl_TIME_UNIT_TEST_DO_NOT_USE test;
  REQUIRE(test.run());
}

}