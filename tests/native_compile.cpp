#include <GrevirTime.h>

using setl::TimeUnit;
static_assert(setl::timeScale<TimeUnit::SECOND, TimeUnit::MILLIS, unsigned>::value == 1000);
static_assert(setl::timeScale<TimeUnit::MINUTE, TimeUnit::SECOND, unsigned>::value == 60);

// Instantiate conversions, time arithmetic, literals and the interactive scaler.
unsigned grevir_time_compile_usage(unsigned now_value) {
    using namespace setl::time_suffix_ops;
    setl::Time<unsigned> now(now_value);
    setl::Period<unsigned> interval(2_sec);
    auto later = now + interval;
    auto elapsed = later - now;
    setl::RelativeInteractiveScaler<int> scaler;
    auto scaled = scaler.scaleForNow(1, setl::Time<unsigned long>(now_value));
    return elapsed.get() + static_cast<unsigned>(scaled);
}
