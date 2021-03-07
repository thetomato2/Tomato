#include "StringConverter.h"

namespace TomUtils

{

	std::wstring StringConverter::s2ws(const std::string& str) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.from_bytes(str);
	}

	std::string StringConverter::ws2s(const std::wstring& ws) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.to_bytes(ws);
	}

}