#pragma once

namespace Utilities
{
	namespace Singleton
	{
		template <class T>
		class ISingleton
		{
		public:
			static T* GetSingleton()
			{
				static T singleton;
				return std::addressof(singleton);
			}

			ISingleton(const ISingleton&) = delete;
			ISingleton(ISingleton&&) = delete;
			ISingleton& operator=(const ISingleton&) = delete;
			ISingleton& operator=(ISingleton&&) = delete;

		protected:
			ISingleton() = default;
			~ISingleton() = default;
		};
	}

	namespace String
	{

		// Credit: https://github.com/powerof3/CLibUtil
		inline std::vector<std::string> split(const std::string& a_str, const std::string& a_delimiter) {
			std::vector<std::string> result;
			size_t start = 0;
			size_t end = a_str.find(a_delimiter);

			while (end != std::string::npos) {
				result.push_back(a_str.substr(start, end - start));
				start = end + a_delimiter.length();
				end = a_str.find(a_delimiter, start);
			}

			result.push_back(a_str.substr(start));
			return result;
		}
	}

	template <class T>
	T to_num(const std::string& a_str, bool a_hex = false)
	{
		const int base = a_hex ? 16 : 10;

		if constexpr (std::is_same_v<T, double>) {
			return static_cast<T>(std::stod(a_str, nullptr));
		}
		else if constexpr (std::is_same_v<T, float>) {
			return static_cast<T>(std::stof(a_str, nullptr));
		}
		else if constexpr (std::is_same_v<T, std::int64_t>) {
			return static_cast<T>(std::stol(a_str, nullptr, base));
		}
		else if constexpr (std::is_same_v<T, std::uint64_t>) {
			return static_cast<T>(std::stoull(a_str, nullptr, base));
		}
		else if constexpr (std::is_signed_v<T>) {
			return static_cast<T>(std::stoi(a_str, nullptr, base));
		}
		else {
			return static_cast<T>(std::stoul(a_str, nullptr, base));
		}
	}

	namespace Forms
	{
	}
}