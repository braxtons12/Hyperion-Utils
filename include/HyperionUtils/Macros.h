#define APEX_DECLARE_NON_HEAP_ALLOCATABLE()	   /** NOLINT(cppcoreguidelines-macro-usage): This isn't \
												  a function-like macro                      **/     \
	static auto operator new(std::size_t size) noexcept->void* = delete;                             \
	static auto operator new[](std::size_t size) noexcept->void* = delete;                           \
	static auto operator delete(void* obj) noexcept->void = delete;                                  \
	static auto operator delete[](void* obj) noexcept->void = delete;

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_START \
		_Pragma("GCC diagnostic push")\
		_Pragma("GCC diagnostic ignored \"-Wunused-macros\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_MACROS_STOP
#endif
// clang-format on

IGNORE_UNUSED_MACROS_START

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_START \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wpadded\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_START \
		_Pragma("warning( push )") \
		_Pragma("warning( disable : 4820 )")
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_PADDING_STOP \
		_Pragma("warning( pop )")
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_START \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wweak-vtables\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_WEAK_VTABLES_STOP
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_START \
		_Pragma("GCC diagnostic push")\
		_Pragma("GCC diagnostic ignored \"-Wunused-template\"")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_START
#endif
// clang-format on

// clang-format off
#ifndef _MSC_VER
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_STOP \
		_Pragma("GCC diagnostic pop")
#else
	// NOLINTNEXTLINE
	#define IGNORE_UNUSED_TEMPLATES_STOP
#endif
// clang-format on

IGNORE_UNUSED_MACROS_STOP