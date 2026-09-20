#include <cstdint>
#include <limits>
#include <type_traits>
// Migrated from the retained Ardoinus cases to Catch2.


#include <grevir/time/time.hpp>

#include <catch2/catch_test_macros.hpp>




namespace {
  


#if 0
template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) * Rhs(1))>
struct Mul {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) / Rhs(1))>
struct Div {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) + Rhs(1))>
struct Add {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) - Rhs(1))>
struct Sub {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) == Rhs(1))>
struct Eq {};

template <typename Lhs, typename Rhs, int n = sizeof(Lhs(1) != Rhs(1))>
struct Neq {};

template <template <typename Lhs, typename Rhs, int n = 1> class OP>
struct OpTest {
  template <typename Lhs, typename Rhs>
  static int allowed(const Lhs& x, const Rhs& y, int q,
    int(*z)[sizeof(OP<Lhs, Rhs>)] = 0) {
    return true;
  }

  template <typename Lhs, typename Rhs>
  static char allowed(const Lhs& x, const Rhs& y, long q) {
    return false;
  }
};

template <template <typename Lhs, typename Rhs, int n = 1> class Op, typename Lhs, typename Rhs>
constexpr bool allowed = sizeof(OpTest<Op>::allowed(Lhs(1), Rhs(1), 0)) == sizeof(int);

static_assert(!allowed<Mul, setl::Time<int>, setl::Time<int>>, "t*t should not be allowed");
static_assert(allowed<Sub, setl::Time<int>, setl::Time<int>>, "t-t should be allowed");
static_assert(allowed<Add, setl::Time<int>, setl::Period<int>>, "t+p should be allowed");
#endif

// Test time...
struct SetlTimeTest_DO_NOT_USE {

  template <typename T>
  struct TimeTest {
    using TType = setl::Time<T>;
    using PType = setl::Period<T>;
    using PTypeSecs = setl::Period<T, setl::TimeUnit::SECOND>;
    using PTypeWeek = setl::Period<T, setl::TimeUnit::WEEK>;
    using PTypeNanos = setl::Period<T, setl::TimeUnit::NANOS>;

    TimeTest() {
      do_test();
    }

    void do_test() {
      REQUIRE((((TType(2) + PType(4)) == TType(6))) == (true));
      REQUIRE((((PType(2) + TType(4)) == TType(6))) == (true));
      REQUIRE(((t2 - t1) == PType(t2.get() - t1.get())) == (true));
      REQUIRE((((PType(4) * 1.5) == PType(6))) == (true));
      REQUIRE((((PType(4) * 1.5f) == PType(6))) == (true));
      REQUIRE((((PType(4) * 1.5) != PType(6))) == (false));
      REQUIRE((((PType(4) += PType(2)) == PType(6))) == (true));
      REQUIRE(((PType(PTypeSecs(4)) == PType(4000))) == (true));
      // PTypeNanos n{ PTypeWeek(1) }; // should fail to compile. Overflow of scale.
    }

    TType t1{ 5 };
    TType t2{ 11 };
    PType p1{ 5 };
    PType p2{ 11 };
  };


  bool run() {
    TimeTest<int> test0;
    TimeTest<unsigned> test1;
    TimeTest<unsigned long long> test2;
    TimeTest<float> test3;
    TimeTest<double> test4;

    using setl::operator"" _sec;
    using setl::operator"" _min;

    REQUIRE(((12.1_sec == setl::Period<long double, setl::TimeUnit::SECOND>(12.1L))));
    REQUIRE(((12.1_sec == setl::period<setl::TimeUnit::SECOND>(12.1L))));
    REQUIRE(((12_sec == setl::Period<unsigned long long, setl::TimeUnit::SECOND>(12))));

    REQUIRE(((1.1_min == (66.0_sec).to<setl::TimeUnit::MINUTE>())));

    REQUIRE(((1.1_min == (66.0_sec).to())));

    return true;
  }

};

TEST_CASE("typed time arithmetic and literals") {
  SetlTimeTest_DO_NOT_USE test;
  REQUIRE(test.run());
}

}
TEST_CASE("unsigned time subtraction measures elapsed time across wraparound") {
  using Tick = setl::Time<std::uint32_t>;
  using Delta = Tick::period_type;
  const auto maximum = std::numeric_limits<std::uint32_t>::max();
  Tick start(maximum - 2);
  Tick now(2);
  REQUIRE((now - start).get() == 5);
  start += Delta(5);
  REQUIRE(start == now);
  now -= Delta(5);
  REQUIRE(now.get() == maximum - 2);
}

TEST_CASE("period division preserves units and uses numeric division") {
  using Millis = setl::Period<int>;
  const Millis duration(12);
  REQUIRE((duration / 3).get() == 4);
  REQUIRE((Millis(13) / 3).get() == 4);
  REQUIRE((Millis(-13) / 3).get() == -4);
  REQUIRE((duration / -3).get() == -4);
  REQUIRE((Millis(0) / 3).get() == 0);
  REQUIRE((setl::Period<unsigned>(12) / 3u).get() == 4u);
  using Seconds = setl::Period<double, setl::TimeUnit::SECOND>;
  const auto quotient = Seconds(7.5) / 2.5;
  REQUIRE(quotient.get() == 3.0);
  REQUIRE((Millis(9) / 2.0).get() == 4);
  static_assert(decltype(quotient)::UNITS == setl::TimeUnit::SECOND);
  static_assert(std::is_same_v<decltype(duration / 3), Millis>);
}
