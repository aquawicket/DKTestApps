#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LPCWSTR myText = L"Text for the message box";
    LPCWSTR myCaption = L"Caption for the message box";
    MessageBoxW(NULL, myText, myCaption, MB_OKCANCEL);
    return 0;
}
