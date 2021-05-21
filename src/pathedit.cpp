#include "pathedit.hpp"
#include "winreg.hpp"

using namespace winreg;
using std::wstring;
using std::wcout, std::endl;

RegKey systemPathKey { 
    HKEY_LOCAL_MACHINE, 
    L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" 
};

RegKey userPathKey { 
    HKEY_CURRENT_USER, 
    L"Environment" 
};

bool EndsWithSemicolon(wstring str) {
    if (str.back() == L';')
        return true;

    return false;
}

wstring ToLowerCase(wstring str) {
    using std::tolower;

    for (auto& letter : str) {
        letter = tolower(letter);
    }

    return str;
}

void EraseAllSubstrings(wstring& string, wstring& substring) {
    size_t pos = wstring::npos;
    while ((pos = ToLowerCase(string).find(ToLowerCase(substring))) != wstring::npos) {
        string.erase(pos, substring.length());
    }
}

void FindAndReplaceAll(wstring& data, wstring toSearch, wstring replaceStr) {
    size_t pos = data.find(toSearch);
    while (pos != wstring::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void SetPath(EnvType envType, std::wstring newPath) {
    if (envType == EnvType::USER)
        userPathKey.SetStringValue(L"Path", newPath);
    else if (envType == EnvType::SYSTEM)
        systemPathKey.SetStringValue(L"Path", newPath);
}

void SetUserPath(wstring newPath) {
    SetPath(EnvType::USER, newPath);
}

void SetSystemPath(wstring newPath) {
    SetPath(EnvType::SYSTEM, newPath);
}

wstring GetPath(EnvType envType) {
    if (envType == EnvType::USER)
        return userPathKey.GetStringValue(L"Path");
    else if (envType == EnvType::SYSTEM)
        return systemPathKey.GetStringValue(L"Path");
}

wstring GetUserPath() {
    return GetPath(EnvType::USER);
}

wstring GetSystemPath() {
    return GetPath(EnvType::SYSTEM);
}

void AppendToPath(EnvType envType, wstring path) {
    wstring targetPath = GetPath(envType);
	
	if (!EndsWithSemicolon(targetPath))
		targetPath += L';';

	targetPath += path;
	SetPath(envType, targetPath);
}

void AppendToUserPath(wstring path) {
    AppendToPath(EnvType::USER, path);
}

void AppendToSystemPath(wstring path) {
    AppendToPath(EnvType::SYSTEM, path);
}

void RemoveFromPath(EnvType envType, wstring path) {
    wstring targetPath = GetPath(envType);

    EraseAllSubstrings(targetPath, path);
    FindAndReplaceAll(targetPath, L";;", L";");

    SetPath(envType, targetPath);
}

void RemoveFromUserPath(wstring path) {
    RemoveFromPath(EnvType::USER, path);
}

void RemoveFromSystemPath(wstring path) {
    RemoveFromPath(EnvType::SYSTEM, path);
}
