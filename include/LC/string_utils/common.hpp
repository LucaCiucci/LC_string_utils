
#pragma once

#include <vector>
#include <string>
#include <tuple>

namespace lc
{
	constexpr std::vector<std::string_view> split(std::string_view str, const std::string_view& delimiter, bool skipEmpty = false);
	constexpr std::string join(const std::vector<std::string_view>& strs, const std::string_view& delimiter);
	constexpr std::string join(const std::vector<std::string>& strs, const std::string_view& delimiter);
	constexpr std::string indent(std::string_view str, int count = 1, const std::string_view& style = "    ");
	inline constexpr size_t replace_all(std::string& inout, std::string_view what, std::string_view with);
	inline constexpr std::pair<std::string, size_t> creplace_all(const std::string& inout, std::string_view what, std::string_view with);
	constexpr std::vector<std::string> concatenate(const std::vector<std::string>& strsA, const std::vector<std::string>& strsB);
}

// ================================================================================================================================
// ================================================================================================================================
//                                                      IMPLEMENTATION
// ================================================================================================================================
// ================================================================================================================================

namespace lc
{
	constexpr std::vector<std::string_view> split(std::string_view str, const std::string_view& delimiter, bool skipEmpty)
	{
		using std::string;
		using std::string_view;
		using std::vector;

		// https://gist.github.com/tcmug/9712f9192571c5fe65c362e6e86266f8
		vector<string_view> result;
		size_t from = 0, to = 0;
		while (string::npos != (to = str.find(delimiter, from))) {
			result.push_back(str.substr(from, to - from));
			from = to + delimiter.length();
		}
		result.push_back(str.substr(from, to));
		return result;
	}

	constexpr std::string join(const std::vector<std::string_view>& strs, const std::string_view& delimiter)
	{
		using std::string;

		// TODO if c++23
		//return strs | std::views::join_with((string)delimiter);

		string result;
		for (auto it = strs.begin(); it != strs.end() && std::next(it) != strs.end(); ++it)
			result += (string)*it + (string)delimiter;
		if (!strs.empty())
			result += strs.back();
		return result;
	}

	constexpr std::string join(const std::vector<std::string>& strs, const std::string_view& delimiter)
	{
		using std::string;

		string result;
		for (auto it = strs.begin(); it != strs.end() && std::next(it) != strs.end(); ++it)
			result += *it + (string)delimiter;
		if (!strs.empty())
			result += strs.back();
		return result;
	}

	constexpr std::string indent(std::string_view str, int count, const std::string_view& style)
	{
		using std::string;

		string indent;
		for (int i = 0; i < count; ++i)
			indent += style;
		auto pieces = split(str, "\n");
		for (auto& piece : pieces)
			piece = (string)indent + (string)piece;
		return join(pieces, "\n");
	}

	// https://en.cppreference.com/w/cpp/string/basic_string/replace
	inline constexpr size_t replace_all(std::string& inout, std::string_view what, std::string_view with)
	{
		using std::string;

		size_t count{};
		for (string::size_type pos{};
			inout.npos != (pos = inout.find(what.data(), pos, what.length()));
			pos += with.length(), ++count) {
			inout.replace(pos, what.length(), with.data(), with.length());
		}
		return count;
	}

	inline constexpr std::pair<std::string, size_t> creplace_all(const std::string& inout, std::string_view what, std::string_view with)
	{
		using std::string;

		string result = inout;
		size_t count = replace_all(result, what, with);
		return { result, count };
	}

	constexpr std::vector<std::string> concatenate(const std::vector<std::string>& strsA, const std::vector<std::string>& strsB)
	{
		using std::string;
		using std::vector;

		vector<string> result;
		result.reserve(strsA.size() + strsB.size());
		result.insert(result.end(), strsA.begin(), strsA.end());
		result.insert(result.end(), strsB.begin(), strsB.end());
		return result;
	}
}