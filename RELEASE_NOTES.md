# Release Notes

## 1.3.0.5
- Added unit tests for `str::tokenize()`.
- `System.h`: Inlining all functions for ODR.
- `StringHelper.h`: Templatizing `rep_str()`.
- `StringHelper.h`: Templatizing `tokenize()`.
- `StringHelper.h`: Templatizing `rep_char()`.
- `StringHelper.h`: Templatizing `adjust_str()`.
- `StringBox.h`: Templatizing struct `StringBox`.

## 1.2.1.4
- `Utf8.h`: `decode_next_utf8_char32()` now returns `ch32 = none` if no valid codepoint was found.
- Added an `Examples` folder with an `examples.cpp` that will allow you to browse UTF-8 code point blocks.
- `Utf8.h`: Adding new function `num_utf8_codepoints()` which returns the number of glyph/character codepoints that are encoded inside of the supplied `std::string`.
- Added new header `Keyboard.h` with cross-platform functions `getch()`, `press_any_key()` and `press_any_key_or_quit()`.
- `StringHelper.h`: Templetizing function `hex2int()` on return type (default `int`) which makes it much more useful.
- `System.h`: Functions `is_wsl()` and `is_windows_cmd()` must both be marked `inline` for the static "one call" scheme to be safe.
- `StringHelper.h`: Improved `to_lower() / to_upper()` functions and adding more variants for a more complete API. Also added a few unit tests for these.
- `StringHelper.h`: Added new function `rep_str()` akin to `rep_char()`.
- `Rand.h`: Fixed bug in `rand_enum()` that caused the last element before `NUM_ITEMS` to never be returned.
- `StringHelper.h`: Adding `lenI()` overloads for `std::string`, `const char*`, `std::wstring_view`, `std::wstring` and `const wchar_t*`.
- Added new header `Term.h` containing the functions: `inline bool is_console_stdout()`, `inline bool enable_vt_on_stdout()`, `inline std::wstring utf8_to_utf16(std::string_view s)`, `inline void write_console_w(std::wstring_view ws)`, `inline void write_console_a(std::string_view s)`, `inline TermMode init_terminal_mode(int requested_codepage)`, `inline bool use_ansi_colors(const TermMode& m)`, `inline void emit_text(const TermMode& m, std::string_view s_utf8, std::string_view s_bytes_for_legacy = {})` and `inline void emit_text_nl(const TermMode& m, std::string_view s_utf8, std::string_view s_bytes_for_legacy = {})`.

## 1.1.1.3
- Fixed bug in utf8::encode_char32_codepage() that caused an ASCII character to be unidentified if passiung argument codepage = 437.

## 1.1.0.2
- Added new header Utf8.h with some useful functions for encoding `utf-8` bytes to and from an `std::string` object.

## 1.0.1.1
- Fixed windows warning in Histogram.
- Added version.h to the xcode project.

## 1.0.0.0
- First release.
