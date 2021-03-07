#pragma  once
#include <string>
#include <locale>
#include <codecvt>

namespace TomUtils

{
	class StringConverter {
	public:
		static std::wstring s2ws(const std::string& str);
		static std::string ws2s(const std::wstring& ws);
	};
}