#include <windows.h>
#include <string>
#include <vector>
#include <tchar.h>
class _ed_jqb {
public:
    // �����а��ʽ
    static bool hasText() {
        return IsClipboardFormatAvailable(CF_TEXT) || 
               IsClipboardFormatAvailable(CF_UNICODETEXT);
    }
    // ��ȡANSI�ı�
    static std::string getTextA() {
        if (!OpenClipboard(NULL)) return "";
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (!hData) {
            CloseClipboard();
            return "";
        }
        char* pszText = static_cast<char*>(GlobalLock(hData));
        if (!pszText) {
            CloseClipboard();
            return "";
        }
        std::string text(pszText);
        GlobalUnlock(hData);
        CloseClipboard();
        return text;
    }
    // ��ȡUnicode�ı�
    static std::wstring getTextW() {
        if (!OpenClipboard(NULL)) return L"";
        HANDLE hData = GetClipboardData(CF_UNICODETEXT);
        if (!hData) {
            CloseClipboard();
            return L"";
        }
        wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
        if (!pszText) {
            CloseClipboard();
            return L"";
        }
        std::wstring text(pszText);
        GlobalUnlock(hData);
        CloseClipboard();
        return text;
    }
    // ��ȡUTF8�ı�
    static std::string getTextUTF8() {
        std::wstring wstr = getTextW();
        if (wstr.empty()) return "";
        int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
        if (size <= 0) return "";
        std::vector<char> buffer(size);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, buffer.data(), size, NULL, NULL);
        return std::string(buffer.data());
    }
    // ����ANSI�ı�
    static bool setTextA(const std::string& text) {
        if (!OpenClipboard(NULL)) return false;
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        if (!hMem) {
            CloseClipboard();
            return false;
        }
        char* pszCopy = static_cast<char*>(GlobalLock(hMem));
        if (!pszCopy) {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
        strncpy(pszCopy, text.c_str(), text.size());
		pszCopy[text.size()] = '\0';  // ȷ���ַ�����ֹ
        GlobalUnlock(hMem);
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        return true;
    }
    // ����Unicode�ı�
    static bool setTextW(const std::wstring& text) {
        if (!OpenClipboard(NULL)) return false;
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(wchar_t));
        if (!hMem) {
            CloseClipboard();
            return false;
        }
        wchar_t* pszCopy = static_cast<wchar_t*>(GlobalLock(hMem));
        if (!pszCopy) {
            GlobalFree(hMem);
            CloseClipboard();
            return false;
        }
        wcsncpy(pszCopy, text.c_str(), text.size());
		pszCopy[text.size()] = L'\0';  // ȷ�����ַ�����ֹ
        GlobalUnlock(hMem);
        SetClipboardData(CF_UNICODETEXT, hMem);
        CloseClipboard();
        return true;
    }
    // ����UTF8�ı�
    static bool setTextUTF8(const std::string& text) {
        int size = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
        if (size <= 0) return false;
        std::vector<wchar_t> buffer(size);
        MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, buffer.data(), size);
        return setTextW(std::wstring(buffer.data()));
    }
    // ��ռ��а�
    static void clear() {
        if (OpenClipboard(NULL)) {
            EmptyClipboard();
            CloseClipboard();
        }
    }
};

