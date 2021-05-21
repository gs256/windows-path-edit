#include <iostream>
#include "pathedit.hpp"

using std::wstring;
using std::wcout;
using std::endl;

wstring manual =
    L"How to use:\n"
    L"pathedit.exe [mode] [variable type] [path]\n"
    L"\n"
    L"[mode] - append / get / remove\n"
    L"[variable type] - user / system\n"
    L"[path] - path you want to add";

wstring GetArgument(int argc, wchar_t** argv, int num);
void PrintArgs(int argc, wchar_t* argv[]);
void AppendPath(wstring envType, wstring path);
void DoActionWithPath(wstring mode, wstring envType, wstring path);
void PrintPathValue(wstring envType);
void RemovePathFromVariable(wstring envType, wstring pathToRemove);

int wmain(int argc, wchar_t *argv[]) {
    wstring mode = GetArgument(argc, argv, 1);
    wstring envType = GetArgument(argc, argv, 2);
    wstring path = GetArgument(argc, argv, 3);

    DoActionWithPath(mode, envType, path);

    return 0;
}

wstring GetArgument(int argc, wchar_t** argv, int num) {
    if (num < argc)
        return  wstring(argv[num]);

    return wstring();
}

void PrintArgs(int argc, wchar_t* argv[]) {
    for (int i = 0; i < argc; i++) {
        wcout << i << L": " << wstring(argv[i]) << endl;
    }

    wcout << endl;
}

void DoActionWithPath(wstring mode, wstring envType, wstring path) {
    if (mode == L"append")
        AppendPath(envType, path);
    else if (mode == L"get")
        PrintPathValue(envType);
    else if (mode == L"remove")
        RemovePathFromVariable(envType, path);
    else
        wcout << manual << endl;
}

void AppendPath(wstring envType, wstring path) {
    if (path.empty())
        throw std::exception("Invalid path");

    if (envType == L"user")
        AppendToUserPath(path);
    else if (envType == L"system")
        AppendToSystemPath(path);
    else
        throw std::exception("Invalid variable type");
}

void PrintPathValue(wstring envType) {
    if (envType == L"user")
        wcout << GetUserPath() << endl;
    else if (envType == L"system")
        wcout << GetSystemPath() << endl;
    else
        throw std::exception("Invalid variable type");
}

void RemovePathFromVariable(wstring envType, wstring pathToRemove) {
    if (envType == L"user")
        RemoveFromUserPath(pathToRemove);
    else if (envType == L"system")
        RemoveFromSystemPath(pathToRemove);
    else
        throw std::exception("Invalid variable type");
}

