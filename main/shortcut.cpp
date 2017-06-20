#include <windows.h>
# include <direct.h>

int main()
{
    chdir("main");
    WinExec("main.exe",SW_SHOW);
}
