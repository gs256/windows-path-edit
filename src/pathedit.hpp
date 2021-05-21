#pragma once
#include <iostream>

enum EnvType {
	USER,
	SYSTEM
};

void SetPath(EnvType envType, std::wstring newPath);
void SetUserPath(std::wstring newPath);
void SetSystemPath(std::wstring newPath);
std::wstring GetPath(EnvType envType);
std::wstring GetUserPath();
std::wstring GetSystemPath();
void AppendToPath(EnvType envType, std::wstring path);
void AppendToUserPath(std::wstring path);
void AppendToSystemPath(std::wstring path);
void RemoveFromPath(EnvType envType, std::wstring path);
void RemoveFromUserPath(std::wstring path);
void RemoveFromSystemPath(std::wstring path);

bool EndsWithSemicolon(std::wstring str);
std::wstring ToLowerCase(std::wstring str);
void EraseAllSubstrings(std::wstring& string, std::wstring& substring);
void FindAndReplaceAll(std::wstring& data, std::wstring toSearch, std::wstring replaceStr);
