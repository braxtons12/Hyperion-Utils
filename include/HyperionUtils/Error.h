/// @brief Error is the base type for communicating recoverable errors inside Hyperion
///
/// Error speaks `std::error_code` as well as custom error messages, and combined with `Result`
/// is easily composable and propogated
#pragma once

#include <cstring>
#include <gsl/gsl>
#include <memory>
#include <string>
#include <system_error>
#include <type_traits>

#include "BasicTypes.h"
#include "Macros.h"

namespace hyperion {
	using namespace std::literals::string_literals;

	IGNORE_PADDING_START
	IGNORE_WEAK_VTABLES_START
	/// @brief Base error interface.
	/// Used to implement custom error types used as the `E` in `Result<T, E>`
	/// to represent and communicate failure of a function
	///
	/// @see `Result<T, E>`
	class [[nodiscard]] Error {
	  public:
		/// Constructs a default `Error` with no message
		Error() noexcept = default;

		/// @brief Constructs an `Error` from the given `std::error_code`
		///
		/// @param code - The error code
		Error(const std::error_code& code) noexcept // NOLINT
			: m_error_code(code), m_message(code.message()), m_has_error_code(true) {
		}

		/// @brief Constructs an `Error` with the given message
		///
		/// @param message - The error message
		template<usize N>
		explicit Error(const char(message)[N]) noexcept : m_message(message, N) { // NOLINT
		}

		/// @brief Constructs an `Error` with the given message
		///
		/// @param message - The error message
		explicit Error(const std::string& message) noexcept : m_message(message) { // NOLINT
		}

		/// @brief Constructs an `Error` with the given message
		///
		/// @param message - The error message
		explicit Error(std::string&& message) noexcept
			: m_message(std::forward<std::string>(message)) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		/// Takes ownership of `source`
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		template<usize N>
		Error(const char(message)[N], gsl::owner<Error*> source) noexcept // NOLINT
			: m_source(source), m_message(message, N), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		/// Takes ownership of `source`
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(const std::string& message, gsl::owner<Error*> source) noexcept // NOLINT
			: m_source(source), m_message(message), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		/// Takes ownership of `source`
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(std::string&& message, gsl::owner<Error*> source) noexcept
			: m_source(source), m_message(std::forward<std::string>(message)), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		template<usize N>
		Error(const char(message)[N], const Error& source) noexcept // NOLINT
			: m_source(std::make_shared<Error>(source)), m_message(message, N), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(const std::string& message, const Error& source) noexcept // NOLINT
			: m_source(std::make_shared<Error>(source)), m_message(message), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(std::string&& message, const Error& source) noexcept
			: m_source(std::make_shared<Error>(source)),
			  m_message(std::forward<std::string>(message)), m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		template<usize N>
		Error(const char(message)[N], Error&& source) noexcept // NOLINT
			: m_source(std::make_shared<Error>(std::forward<Error>(source))), m_message(message, N),
			  m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(const std::string& message, Error&& source) noexcept // NOLINT
			: m_source(std::make_shared<Error>(std::forward<Error>(source))), m_message(message),
			  m_has_source(true) {
		}

		/// @brief Constructs an `Error` with the given message and source.
		///
		/// @param message - The error message
		/// @param source - The source/cause `Error`
		Error(std::string&& message, Error&& source) noexcept
			: m_source(std::make_shared<Error>(std::forward<Error>(source))),
			  m_message(std::forward<std::string>(message)), m_has_source(true) {
		}

		Error(const Error& error) = default;
		Error(Error&& error) noexcept = default;

		virtual ~Error() noexcept = default;

		/// @brief Returns the source/cause `Error` of this error if there is one,
		/// passing ownership to the containing `Option`.
		///
		/// @return sourceError, if there is one, or nullptr
		[[nodiscard]] auto source() const noexcept -> const std::weak_ptr<Error> {
			return m_source;
		}

		/// @brief Returns whether this `Error` resulted from a `std::error_code`
		///
		/// @return `true` if this originated from a `std::error_code`, `false` otherwise
		[[nodiscard]] constexpr auto has_std_error_code() const noexcept -> bool {
			return m_has_error_code;
		}

		/// @brief Returns the `std::error_code` associated with this `Error`
		///
		/// @return The associated `std::error_code`
		[[nodiscard]] auto error_code() const noexcept -> const std::error_code {
			return m_error_code;
		}

		/// @brief Returns the error message for this `Error`
		///
		/// @return The error message
		[[nodiscard]] inline auto message() const noexcept -> std::string {
			return m_message;
		}

		/// @brief Returns the error message for this `Error`
		///
		/// @return The error message
		[[nodiscard]] auto message_as_cstr() const noexcept -> const char* {
			return m_message.c_str();
		}

		/// @brief Converts this `Error` to a `std::string`
		/// Generally implemented by combining the `source`'s `to_std_string`
		/// and this `Error`'s `message`
		///
		/// @return this `Error` formatted as a `std::string`
		[[nodiscard]] auto to_string() const noexcept -> std::string {
			if(m_has_source) {
				return "Error: "s + std::string(m_message) + "\n"s + "Source: "s
					   + m_source->to_string() + "\n"s;
			}
			else {
				return "Error: "s + std::string(m_message) + "\n"s;
			}
		}

		auto operator=(const Error& error) -> Error& = default;
		auto operator=(Error&& error) noexcept -> Error& = default;

	  protected:
		/// error code
		std::error_code m_error_code = std::error_code();
		/// the source `Error` of this one
		/// We use `std::shared_ptr` instead of `std::unique_ptr` so we can be copyable
		std::shared_ptr<Error> m_source = nullptr;
		/// the error message.
		std::string m_message;
		/// whether this `Error` originated from a `std::error_code`
		bool m_has_error_code = false;
		/// whether this `Error` has a source `Error`
		bool m_has_source = false;
	};
	IGNORE_PADDING_STOP
	IGNORE_WEAK_VTABLES_STOP

} // namespace hyperion
