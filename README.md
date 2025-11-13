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
* ´class day_t : public datetime_unit_t<30, 1>`
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

Classes:

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

### MarkovChain.h

### MathUtils.h

### Mtx2.h

### OneShot.h

### Physics.h

### Rand.h

### StlOperators.h

### StlUtils.h

### StringBox.h

### StringHelper.h

### System.h

### TextIO.h

### Timer.h

### Utils.h

### Uuid.h

### bool_vector.h

### build.bat

### build.sh
