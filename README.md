# Core Lib

![GitHub License](https://img.shields.io/github/license/razterizer/Core?color=blue)
![Static Badge](https://img.shields.io/badge/linkage-header_only-yellow)
![Static Badge](https://img.shields.io/badge/C%2B%2B-20-yellow)

[![build and test ubuntu](https://github.com/razterizer/Core/actions/workflows/build-and-test-ubuntu.yml/badge.svg)](https://github.com/razterizer/Core/actions/workflows/build-and-test-ubuntu.yml)
[![build macos](https://github.com/razterizer/Core/actions/workflows/build-macos.yml/badge.svg)](https://github.com/razterizer/Core/actions/workflows/build-macos.yml)
[![build windows](https://github.com/razterizer/Core/actions/workflows/build-windows.yml/badge.svg)](https://github.com/razterizer/Core/actions/workflows/build-windows.yml)

![Top Languages](https://img.shields.io/github/languages/top/razterizer/Core)
![GitHub repo size](https://img.shields.io/github/repo-size/razterizer/Core)
![C++ LOC](https://raw.githubusercontent.com/razterizer/Core/badges/loc-badge.svg)
![Commit Activity](https://img.shields.io/github/commit-activity/t/razterizer/Core)
![Last Commit](https://img.shields.io/github/last-commit/razterizer/Core?color=blue)
![Contributors](https://img.shields.io/github/contributors/razterizer/Core?color=blue)

This is a cross-platform, header-only library for core routines.

## Summary

* [Benchmark.h](https://github.com/razterizer/Core?tab=readme-ov-file#benchmarkh)
* [DateTime.h](https://github.com/razterizer/Core?tab=readme-ov-file#datetimeh)
* [Delay.h](https://github.com/razterizer/Core?tab=readme-ov-file#delayh)
* [FlankDetector.h](https://github.com/razterizer/Core?tab=readme-ov-file#flankdetectorh)
* [FolderHelper.h](https://github.com/razterizer/Core?tab=readme-ov-file#folderhelperh)
* [Histogram.h](https://github.com/razterizer/Core?tab=readme-ov-file#histogramh)
* [MarkovChain.h](https://github.com/razterizer/Core?tab=readme-ov-file#markovchainh)
* [MathUtils.h](https://github.com/razterizer/Core?tab=readme-ov-file#mathutilsh)
* [Mtx2.h](https://github.com/razterizer/Core?tab=readme-ov-file#mtx2h)
* [OneShot.h](https://github.com/razterizer/Core?tab=readme-ov-file#oneshoth)
* [Physics.h](https://github.com/razterizer/Core?tab=readme-ov-file#physicsh)
* [Rand.h](https://github.com/razterizer/Core?tab=readme-ov-file#randh)
* [StlOperators.h](https://github.com/razterizer/Core?tab=readme-ov-file#stloperatorsh)
* [StlUtils.h](https://github.com/razterizer/Core?tab=readme-ov-file#stlutilsh)
* [StringBox.h](https://github.com/razterizer/Core?tab=readme-ov-file#stringboxh)
* [StringHelper.h](https://github.com/razterizer/Core?tab=readme-ov-file#stringhelperh)
* [System.h](https://github.com/razterizer/Core?tab=readme-ov-file#systemh)
* [TextIO.h](https://github.com/razterizer/Core?tab=readme-ov-file#textioh)
* [Timer.h](https://github.com/razterizer/Core?tab=readme-ov-file#timerh)
* [Utils.h](https://github.com/razterizer/Core?tab=readme-ov-file#utilsh)
* [Uuid.h](https://github.com/razterizer/Core?tab=readme-ov-file#uuidh)
* [Vec2.h](https://github.com/razterizer/Core?tab=readme-ov-file#vec2h)
* [bool_vector.h](https://github.com/razterizer/Core?tab=readme-ov-file#bool_vectorh)
* [build.sh](https://github.com/razterizer/Core?tab=readme-ov-file#buildsh)
* [build.bat](https://github.com/razterizer/Core?tab=readme-ov-file#buildbat)

---

### Benchmark.h

Namespace: `benchmark`.

Macros:

* `BM_FUNC` (for use with `Benchmark::reg()`)

Classes / Structs:

* `class Benchmark`
  - `void reg(Lambda&& func, const std::string& tag)`
  - `void start(const std::string& tag)`
  - `void stop(const std::string& tag)`

Functions:

* `float calc_time_ms(Lambda&& func)`
* `void tic(TicTocTimer& time)`
* `float toc(const TicTocTimer& time)`
* `void tic()` (global `TicTocTimer` object)
* `float toc()` (-''-)

### DateTime.h

Namespace: `datetime`.

Classes / Structs:

* `class datetime_unit_t`
* `class day_t : public datetime_unit_t<30, 1>`
* `struct Date`
* `struct Time`
* `struct DateTime`
* `using hour_t = datetime_unit_t<24, 0>`
* `using sexagesimal_t = datetime_unit_t<60, 0>`
* `using month_t = datetime_unit_t<12, 1>`

Functions:

* `void update_date_time(DateTime& date_time, const DateTime& date_time_0, double time_s)`
* `Time rand_time(const Time& start, const Time& end)`
* `Time randn_time(const Time& mu, float sigma_seconds, const Time& start, const Time& end)`
* `Date rand_date(const Date& start, const Date& end)`
* `Date randn_date(const Date& mu, float sigma_days, const Date& start, const Date& end)`
* `DateTime rand_datetime(const DateTime& start, const DateTime& end)`
* `DateTime randn_datetime(const Date& mu, float sigma_days, const DateTime& start, const DateTime& end)`
* `std::string get_datetime_str(const DateTime& date_time, const std::string& format = "%Y-%m-%d %H:%M:%S")`

### Delay.h

Namespace: `Delay`.

Functions:

* `sleep(T us)`
* `update_loop(int fps, std::function<bool(void)> update_func)`

### FlankDetector.h

Namespace: `-`

Classes / Structs:

* `class FlankDetector<T>`
  - `FlankDetector() = default`
  - `FlankDetector(T curr, T prev)`
  - `void update()`
  - `void set(T val)`
  - `void update(T val)`
  - `bool pos_flank(T threshold = static_cast<T>(0)) const`
  - `bool neg_flank(T threshold = static_cast<T>(0)) const`
  - `T curr() const`
  - `T prev() const`

### FolderHelper.h

Namespace: `folder`

Functions:

* `bool delete_file(const std::string& file_path)`
* `std::string get_exe_dir()` (Windows only for now)
* `std::string get_pwd()`
* `void set_pwd(const std::string& new_pwd)`
* `char get_path_separator()`
* `bool is_path_separator(char c)`
* `std::vector<std::string> split_path(const std::string& path)`
* `std::string join_path(const std::vector<std::string>& path_parts)`
* `std::string format_path(const std::string& path)`
* `std::pair<std::string, std::string> split_file_path(const std::string& file_path)`
* `std::string join_file_path(const std::pair<std::string, std::string>& path_and_filename)`
* `std::pair<std::string, std::string> split_filename_ext(const std::string& filename)`
* `std::string join_filename_ext(const std::pair<std::string, std::string>& basefilename_and_ext)`
* `bool exists(const std::string file_path)`

### Histogram.h

Namespace: `hist`

Classes / Structs:

* `struct Buck<T>`
* `class Histogram<T>`
  - `Histogram(size_t N_buck, T start, T end)`
  - `void operator+=(T val)`
  - `void resize(size_t N_buck, T start, T end)`
  - `str::StringBox to_stringbox(int nr, int nc)`
  - `int sanity_check_bucket_samples() const`

### MarkovChain.h

Namespace: `markov_chain`

Classes / Structs:

* `class MarkovChain<T>`
  - `MarkovChain(T empty_val)`
  - `void add_transitions(const std::vector<T>& items)`
  - `int import_transitions(const std::string& filename)`
  - `void print() const`
  - `void normalize_transition_weights()`
  - `T generate(int min_num_items = -1, int max_num_items = -1) const`

### MathUtils.h

Namespace: `math`

Constants:

* `static constexpr long double cld_pi`
* `static constexpr long double cld_2pi`
* `static constexpr long double cld_pi_2`
* `static constexpr long double cld_pi_3`
* `static constexpr long double cld_pi_4`
* `static constexpr long double cld_pi_6`
* `static constexpr long double cld_3pi_2`
* `static constexpr long double cld_3pi_4`
* `static constexpr long double cld_5pi_4`
* `static constexpr long double cld_7pi_4`
* `static constexpr long double cld_1_pi`
* `static constexpr long double cld_2_pi`
* `static constexpr long double cld_sqrt2`
* `static constexpr long double cld_2_sqrt_pi` (`2/sqrt(pi)`)
* `static constexpr long double cld_sqrt1_2` (`1/sqrt(2)`)
* `static constexpr long double cld_ln2`
* `static constexpr long double cld_ln10`
* `static constexpr long double cld_e`
* `static constexpr long double cld_1_e`
* `static constexpr long double cld_log2e`
* `static constexpr long double cld_log10e`
* `static constexpr double cd_pi`
* `static constexpr double cd_2pi`
* `static constexpr double cd_pi_2`
* `static constexpr double cd_pi_3`
* `static constexpr double cd_pi_4`
* `static constexpr double cd_pi_6`
* `static constexpr double cd_3pi_2`
* `static constexpr double cd_3pi_4`
* `static constexpr double cd_5pi_4`
* `static constexpr double cd_7pi_4`
* `static constexpr double cd_1_pi`
* `static constexpr double cd_2_pi`
* `static constexpr double cd_sqrt2`
* `static constexpr double cd_2_sqrt_pi` (`2/sqrt(pi)`)
* `static constexpr double cd_sqrt1_2` (`1/sqrt(2)`)
* `static constexpr double cd_ln2`
* `static constexpr double cd_ln10`
* `static constexpr double cd_e`
* `static constexpr double cd_1_e`
* `static constexpr double cd_log2e`
* `static constexpr double cd_log10e`
* `static constexpr float c_pi`
* `static constexpr float c_2pi`
* `static constexpr float c_pi_2`
* `static constexpr float c_pi_3`
* `static constexpr float c_pi_4`
* `static constexpr float c_pi_6`
* `static constexpr float c_3pi_2`
* `static constexpr float c_3pi_4`
* `static constexpr float c_5pi_4`
* `static constexpr float c_7pi_4`
* `static constexpr float c_1_pi`
* `static constexpr float c_2_pi`
* `static constexpr float c_sqrt2`
* `static constexpr float c_2_sqrt_pi` (`2/sqrt(pi)`)
* `static constexpr float c_sqrt1_2` (`1/sqrt(2)`)
* `static constexpr float c_ln2`
* `static constexpr float c_ln10`
* `static constexpr float c_e`
* `static constexpr float c_1_e`
* `static constexpr float c_log2e`
* `static constexpr float c_log10e`

Enums:

* `enum class Range { Free, Closed, Open, ClosedOpen, OpenClosed, ClosedFree, FreeClosed, OpenFree, FreeOpen };`

Classes / Structs:

* `struct RangeData<T>`

Functions:

* `int roundI(T val)`
* `int floorI(T val)`
* `int ceilI(T val)`
* `int sgn(T val)`
* `int sign(T val)`
* `T sq(T val)`
* `T cube(T val)`
* `T length_squared(T x, T y)`
* `T length_squared(T x, T y, T z)`
* `T length_squared(T x, T y, T z, T w)`
* `T length(T x, T y)`
* `T length(T x, T y, T z)`
* `T length(T x, T y, T z, T w)`
* `T distance_squared(T x0, T y0, T x1, T y1)`
* `T distance_squared(T x0, T y0, T z0, T x1, T y1, T z1)`
* `T distance_squared(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)`
* `T distance(T x0, T y0, T x1, T y1)`
* `T distance(T x0, T y0, T z0, T x1, T y1, T z1)`
* `T distance(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)`
* `bool normalize(T& x, T& y)`
* `bool normalize(T& x, T& y, T& z)`
* `bool normalize(T& x, T& y, T& z, T& w)`
* `T normalize_angle(T ang)` (Normalizes the angle to the range [-0, 2pi])
* `T atan2n(T y, T x)` (Normalizes the angle to the range [-0, 2pi])
* `T dot(T x0, T y0, T x1, T y1)`
* `T dot(T x0, T y0, T z0, T x1, T y1, T z1)`
* `T dot(T x0, T y0, T z0, T w0, T x1, T y1, T z1, T w1)`
* `T clamp(T val, T lo, T hi)`
* `T lerp(float t, T a, T b)`
* `float value_to_param(T val, T start, T end)`
* `float value_to_param_clamped(T val, T start, T end)`
* ´std::vector<T> linspace(T start, T step, T end)`
* `T1 linmap(T0 val_0, T0 start_0, T0 end_0, T1 start_1, T1 end_1)`
* `T1 linmap_clamped(T0 val_0, T0 start_0, T0 end_0, T1 start_1, T1 end_1)`
* `bool in_range(T val, std::optional<T> start, std::optional<T> end, Range type)`
* `bool in_range(T val, const RangeData<T>& rd)`
* `bool in_unit_range(T val, Range type)`
* `inline bool in_r_c(T val, T start, T end) noexcept`
* `inline bool in_r_o(T val, T start, T end) noexcept`
* `inline bool in_r_co(T val, T start, T end) noexcept`
* `inline bool in_r_oc(T val, T start, T end) noexcept`
* `inline bool in_r_cu(T val) noexcept`
* `inline bool in_r_ou(T val) noexcept`
* `inline bool in_r_cou(T val) noexcept`
* `inline bool in_r_ocu(T val) noexcept`
* `bool minimize(T& val, T test, const RangeData<T>& rd = {})`
* `bool maximize(T& val, T test, const RangeData<T>& rd = {})`
* `constexpr T get_max()`
* `constexpr T get_min()`
* `bool fuz_zero(T v, T eps = std::numeric_limits<T>::epsilon())`
* `bool fuz_eq(T a, T b, T eps = std::numeric_limits<T>::epsilon())`
* `T deg2rad(T deg)`
* `T rad2deg(T rad)`
* `int gcd(int a, int b)`
* `float gcd(float a, float b)`
* `bool toggle(bool& val)`

### Mtx2.h

Namespace: `-`

Classes / Structs:

* `struct Mtx2`
  - `Mtx2() = default`
  - `Mtx2(float v00, float v01, float v10, float v11)`
  - `Vec2 operator*(const Vec2& v)`

### OneShot.h

Namespace: `-`

Classes / Structs:

* `class OneShot`
  - `OneShot() = default`
  - `OneShot(bool preset)`
  - `bool once()`
  - `bool was_triggered() const`
  - `void reset()`

### Physics.h

Namespaces: `physics`, `physics::UnitConversion`

Functions:

* `float deg_celcius_to_kelvin(float degC)`
* `float kelvin_to_deg_celcius(float K)`

### Rand.h

Namespace: `rnd`

Functions:

* `unsigned int srand_time()`
* `void srand(unsigned int seed)`
* `float rand()` (Uniform random value in range [0, 1])
* `float randn(float mu, float sigma)` (Normal-distributed random value using the Box-Muller algorithm)
* `int randn_int(float mu, float sigma)`
* `float randn_clamp(float mu, float sigma, float min, float max)`
* `float randn_range(float lo, float hi)`
* `float randn_range_clamp(float lo, float hi)`
* `int randn_clamp_int(float mu, float sigma, int min, int max)`
* `int randn_range_int(int lo, int hi)`
* `int randn_range_clamp_int(int lo, int hi)`
* `EnumType rand_enum()`
* `EnumType randn_enum(float mu, float sigma)`
* `bool rand_bool()`
* `float rand_float(float start, float end)`
* `int rand_int(int start, int end)`
* `int rand_idx(size_t N)`
* `T rand_select(const std::vector<T>& values)`
* `T rand_select(const std::vector<std::pair<float, T>>& values)`
* `int rand_select_index(const std::vector<float>& values)`
* `T randn_select(float mu, float sigma, const std::vector<T>& values)`
* `int dice(int num_faces = 6)`
* `bool one_in(int N)` (Returns true if the dice of size N rolled a 1)

### StlOperators.h

Namespace: `stloperators`

Functions:

* `std::optional<T> operator* (const std::optional<T>& A, const std::optional<T>& B)`
* `std::optional<T> operator* (const std::optional<T>& A, const T& B)`
* `std::optional<T> operator* (const T& A, const std::optional<T>& B)`

### StlUtils.h

Namespace: `stlutils`

Functions:

* `constexpr int sizeI(const Cont& c) noexcept`
* `void fill(Cont& c, typename Cont::value_type v)`
* `void memset(Cont& c, typename Cont::value_type val)`
* `void memclr(Cont& c)`
* `typename Cont::value_type sum(const Cont& c)`
* `T sum(const Cont& c, Lambda unary_op)´
* `T sum(const std::vector<std::vector<T>>& v)`
* `Cont diff(const Cont& c)`
* `RetT average(const Cont& c)`
* `typename Cont::value_type prod(const Cont& c)`
* `Cont comp_prod(const Cont& cA, const Cont& cB)`
* `Cont comp_sq(const Cont& c)`
* `std::vector<std::vector<T>> comp_prod(const std::vector<std::vector<T>>& vA,
                                        const std::vector<std::vector<T>>& vB)`
* `Cont mult_scalar(const Cont& c, typename Cont::value_type s)`
* `std::vector<std::vector<T>> mult_scalar(const std::vector<std::vector<T>>& vec, T s)`
* `Cont comp_div(const Cont& cA, const Cont& cB)`
* `Cont scalar_div(typename Cont::value_type s, const Cont& c)`
* `Cont add(const Cont& cA, const Cont& cB)`
* `std::vector<std::vector<T>> add(const std::vector<std::vector<T>>& vA,
                                  const std::vector<std::vector<T>>& vB)`
* `Cont subtract(const Cont& cA, const Cont& cB)`
* `std::vector<std::vector<T>> subtract(const std::vector<std::vector<T>>& vA,
                                       const std::vector<std::vector<T>>& vB)`
* `Cont add_scalar(const Cont& c, typename Cont::value_type s)`
* `std::vector<std::vector<T>> add_scalar(const std::vector<std::vector<T>>& vec, T s)`
* `Cont subtract_scalar(const Cont& c, typename Cont::value_type s)`
* `std::vector<std::vector<T>> subtract_scalar(const std::vector<std::vector<T>>& vec, T s)`
* `Cont scalar_subtract(typename Cont::value_type s, const Cont& c)`
* `Cont unary_minus(const Cont& c)`
* `typename Cont::value_type dot(const Cont& cA, const Cont& cB)`
* `T dot(const std::vector<std::vector<T>>& vA, const std::vector<std::vector<T>>& vB)`
* `Cont sqrt(const Cont& c)`
* `Cont sin(const Cont& c)`
* `Cont cos(const Cont& c)`
* `std::vector<Tdst> static_cast_vector(const std::vector<Tsrc>& v)`
* `size_t max_element_idx(const Cont& c)`
* `size_t min_element_idx(const Cont& c)`
* `constexpr decltype(auto) select_if(T&& a, T&& b, Lambda&& pred)
  noexcept(noexcept(pred(a, b)))` (Returns a if pred(a, b) == true (i.e. "a < b" for "min_if" or "a > b" for "max_if"))
* `std::vector<size_t> argmax(const Cont& c)`
* `std::vector<size_t> argmin(const Cont& c)`
* `Cont cat(const Cont& c) { return c; }`
* `Cont cat(const Cont& c, ContN... cn)`
* `void append(Cont& c, ContN... cn)`
* `std::vector<T> repval(T val, size_t n)`
* `std::vector<T> subset(const std::vector<T>& v, size_t idx_begin, size_t idx_end)`
* `std::vector<std::vector<T>> subset(const std::vector<std::vector<T>>& v,
                                     size_t r_idx_begin, size_t r_idx_end,
                                     size_t c_idx_begin, size_t c_idx_end)`
* `std::vector<std::vector<T>> subset_columns(const std::vector<std::vector<T>>& v,
                                             size_t c_idx_begin, size_t c_idx_end)`
* `std::vector<T> to_vector(const std::array<T, N>& arr)`
* `std::vector<std::vector<T>> to_vector(const std::array<std::array<T, Nc>, Nr>& arr)`
* `std::array<T, N> to_array(const std::vector<T>& vec)`
* `std::array<std::array<T, Nc>, Nr> to_array(const std::vector<std::vector<T>>& vec)`
* `void resize(std::vector<T>& vec, size_t N)`
* `void resize(std::vector<std::vector<T>>& vec, size_t Nr, size_t Nc)`
* `void resize(std::vector<std::vector<std::vector<T>>>& vec, size_t Ns, size_t Nr, size_t Nc)`
* `size_t count(const std::vector<T>& vec, T val)`
* `size_t count(const std::array<T, N>& arr, T val)`
* `size_t count_if(const std::vector<T>& vec, Lambda&& pred)`
* `size_t count_if(const std::array<T, N>& arr, Lambda&& pred)`
* `void sort(Cont& c)`
* `void sort(Cont& c, Lambda pred)`
* `int find_if_idx(Cont& c, Lambda pred)`
* `typename Cont::iterator find_if(Cont& c, Lambda pred)`
* `typename Cont::const_iterator find_if(const Cont& c, Lambda pred)`
* `typename Cont::iterator find(Cont& c, const typename Cont::value_type& val)`
* `int find_idx(Cont& c, const typename Cont::value_type& val)`
* `bool contains_if(const Cont& c, Lambda pred)`
* `bool contains_if(const Iterator it_begin, const Iterator it_end, Lambda pred)`
* `bool contains(const Cont& c, const typename Cont::value_type& val)`
* `bool emplace_back_unique(Cont& c, const typename Cont::value_type& val)`
* `bool emplace_back_if_not(Cont& c, const typename Cont::value_type& val, Lambda pred)`
* `void erase(Cont& c, const typename Cont::value_type& val)`
* `bool erase_at(Cont& c, size_t idx)`
* `bool erase_if(Cont& c, Lambda pred)`
* `bool erase_if_idcs(Cont& c, std::vector<Int>& indices, Lambda pred)`
* `typename Cont::value_type try_get(const Cont& cont, int idx,
                                    typename Cont::value_type def_val = static_cast<typename Cont::value_type>(0))`
* `T& at_growing(std::vector<T>& vec, int idx, T default_val = {})`
* `bool in_range(const Cont& c, size_t idx)`
* `bool in_range(const Cont& c, int idx)`

### StringBox.h

Namespace: `str`

Structs / Classes:

* `struct StringBox`
  - `StringBox() = default`
  - `StringBox(size_t N)`
  - `StringBox(const std::vector<std::string>& texts)`
  - `StringBox(const std::string& text)`
  - `std::string& operator[](size_t r_idx)`
  - `void print() const`
  - `size_t size() const`
  - `bool empty() const noexcept`

### StringHelper.h

Namespace: `str`

Enums:

* `enum class BracketType { None, Parentheses, SquareBrackets, Braces, MatrixStyle };`

Functions:

* `std::string rep_char(char c, int num)`
* `enum class Adjustment { Left, Center, Right, LeftInteger };
  std::string adjust_str(const std::string& str, Adjustment adj, int width, int start_idx = 0, char empty_char = ' ')`
* `char_t to_lower(char_t ch)`
* `char_t to_upper(char_t ch)`
* `std::basic_string<char_t> to_lower(const std::basic_string<char_t>& str)`
* `std::basic_string<char_t> to_upper(const std::basic_string<char_t>& str)`
* `bool is_digit(char ch)`
* `int to_digit(char ch)`
* `bool is_vowel(char ch)`
* `bool is_letter(char ch)`
* `std::string cat(const std::vector<std::string>& strings)`
* `std::string row_vector(const Cont& c, BracketType bracket = BracketType::SquareBrackets, const std::string& separator = ", ")`
* `std::string column_vector(const Cont& c, BracketType bracket = BracketType::SquareBrackets)`
* `inline void ltrim(std::string& s)` (trim from start (in place))
* `inline void rtrim(std::string& s)` (trim from end (in place))
* `inline void trim(std::string &s)` (trim from both ends (in place))
* `inline std::string ltrim_ret(std::string s)` (trim from start (copying))
* `inline std::string rtrim_ret(std::string s)` (trim from end (copying))
* `inline std::string trim_ret(std::string s)` (trim from both ends (copying))
* `inline void remove_spaces(std::string& str)`
* `bool is_an(const std::string& str)`
* `std::string indef_art(const std::string& str)`
* `std::string anfangify(std::string str)`
* `std::vector<std::basic_string<CharT>> tokenize(const std::basic_string<CharT>& str,
                                                 const std::vector<CharT>& delim,
                                                 const std::vector<CharT>& scope_delim = {},
                                                 size_t min_scope_size = 1)`
* `std::vector<std::string> to_string_vector(const Cont& c)`
* `std::string flatten(const std::vector<std::string>& string_vec, const std::string& separator = ", ")`

### System.h

Namespace: `sys`

Functions:

* `std::string exec(const char* cmd)`
* `bool is_wsl()`
* `bool is_bsd()`
* `bool is_linux()`
* `bool is_windows()`
* `bool is_apple()`
* `bool is_windows_cmd()`

### TextIO.h

Namespace: `TextIO`

Functions:

* `bool read_file(const std::string& file_path, std::vector<std::string>& lines)`
* `bool write_file(const std::string& file_path, const std::vector<std::string>& lines)`

### Timer.h

Namespace: `-`

Structs / Classes:

* `class Timer`
  - `Timer(float d)`
  - `bool start_if_stopped(float t)`
  - `void force_start(float t)`
  - `bool finished(float t) const`
  - `bool wait_then_reset(float t)`
  - `bool is_ticking(float t) const`
  - `void reset()`
  - `bool is_active() const`
  - `void set_delay(float d)`
  - `float get_delay() const`

### Utils.h

Namespaces: `utils`, `utils::literals`

Functions:

* `bool try_set(T* dst, const T& src)`
* `T try_get(T* ptr, const T def_val = static_cast<T>(0))`
* `T* get_raw_ptr(T& o)`
* `const T* get_raw_ptr(const T& o)`
* `T* get_raw_ptr(T* o)`
* `const T* get_raw_ptr(const T* o)`
* `T* get_raw_ptr(std::unique_ptr<T>& o)`
* `const T* get_raw_ptr(const std::unique_ptr<T>& o)`

### Uuid.h

Namespace: `uuid`

Functions:

* `std::string generate_uuid_v4()`

### Vec2.h

Namespace: `-`

Structs / Classes:

* `struct Vec2`
  - `Vec2()`
  - `Vec2(float rr, float cc)`
  - `Vec2(const Vec2& v)`
  - `const Vec2& operator+() const`
  - `Vec2 operator-() const`
  - `Vec2 operator+(const Vec2& v) const`
  - `Vec2 operator-(const Vec2& v) const`
  - `Vec2& operator+=(const Vec2& v)`
  - `Vec2& operator-=(const Vec2& v)`
  - `Vec2 operator*(float v) const`
  - `Vec2 operator/(float v) const´
  - `Vec2& operator/=(float v)`
  - `std::string str() const`
  
Functions:

* `Vec2 operator*(float v, const Vec2& p)`
* `float length_squared(const Vec2& pt)` (namespace `math`)
* `float length(const Vec2& pt)` (namespace `math`)
* `float distance_squared(const Vec2& ptA, const Vec2& ptB)` (namespace `math`)
* `float distance(const Vec2& ptA, const Vec2& ptB)` (namespace `math`)
* `float distance_squared_ar(const Vec2& ptA, const Vec2& ptB, float ar)` (namespace `math`)
* `float distance_ar(const Vec2& ptA, const Vec2& ptB, float ar)` (namespace `math`)
* `Vec2 normalize(const Vec2& v)` (namespace `math`)
* `float dot(const Vec2& vA, const Vec2& vB)` (namespace `math`)

### bool_vector.h

Namespace: `-`

Structs / Classes:

* `class Bool`
  - `Bool()`
  - `Bool(bool v)`
  - `Bool(const Bool& b)`
  - `Bool(int v)`
  - `Bool(double v)`
  - `operator bool() const`
  - `operator bool&()`
  - `bool operator==(Bool b) const`
  - `bool operator!=(Bool b) const`
* `using bool_vector = std::vector<Bool>`

### build.bat

### build.sh
