#include "Includes/includes.hpp"
#include "Includes/call.hh"
#include "Dependencies/Fortnite/loop.hpp"
#include "Dependencies/UI/Renderer/c_overlay.h"
#include <tchar.h>
#include <ntstatus.h>
#include "Includes/Definitions/xorst.h"
#include "Includes/Definitions/skcrypt.h"
#include <thread>
#include <urlmon.h>
#include "auth.hpp"
#include "../usermode/map_driver.hpp"
#include "bytes.h"





#pragma comment(lib, "urlmon.lib")





Overlay::DX11Overlay* D11Overlay = nullptr;
bool developer_mode = true;

__declspec(noinline) void log() {

#define LOG printf("success");

}


__declspec(noinline) auto initServer_() -> call::status {

    char title[256];

    sprintf_s(title, _(" "));

    if (developer_mode)
    {
        sprintf_s(title, _(" Immortal | Development Version"));
    };

    (SetConsoleTitleA)(title);

    return call_success;
}

std::uint32_t get_process_id(const wchar_t* process_name) {
    std::uint32_t process_id = 0;

    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (snap_shot == INVALID_HANDLE_VALUE)

        return process_id;

    PROCESSENTRY32W entry = { };
    entry.dwSize = sizeof(decltype(entry));

    if (Process32FirstW(snap_shot, &entry) == TRUE) {
        if (_wcsicmp(process_name, entry.szExeFile) == 0) {
            process_id = entry.th32ProcessID;
        }
        else {
            while (Process32NextW(snap_shot, &entry) == TRUE) {
                if (_wcsicmp(process_name, entry.szExeFile) == 0) {
                    process_id = entry.th32ProcessID;
                    break;
                }
            }
        }
    }

    CloseHandle(snap_shot);
    return process_id;
}

__declspec(noinline) auto init_overlay() -> call::status {

    Overlay::DX11Overlay::GetWindow(FindWindow(0, (_("Fortnite  "))));

    auto overlay = D11Overlay->InitOverlay();

    std::thread([]() {
        for (;; ) {
            GameCache::cachep();
        }
        }).detach();





    switch (overlay) {
    case 0: {
        break;
    }
    case 1: {

        while (D11Overlay->MainLoop(actor_loop)) {

        }
        break;
    }
    }

    return call_success;
}

void attach()
{
    SPOOF_FUNC;

    {
        while (true)
        {


            for (int i = 0; i < 5; i++) {
                //! IsDebuggerPresent will return 0 if one wasn't found
                if (IsDebuggerPresent()) {
                    //აპლიკაცია.ban();
                    //	you may put ur BSOD here
                    _exit(0);
                }
                else {

                }
                Sleep(500);
            }
        }
    }

}



bool DownloadFile(const std::wstring& url, const std::wstring& outputPath) {
    SPOOF_FUNC;
    HRESULT hr = URLDownloadToFileW(NULL, url.c_str(), outputPath.c_str(), 0, NULL);
    return SUCCEEDED(hr);
}


bool ExecuteCommand(const std::wstring& command) {
    SPOOF_FUNC;
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    BOOL success = CreateProcessW(NULL, const_cast<LPWSTR>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (success) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return success;
}


bool DeleteFileSafe(const std::wstring& filePath) {
    SPOOF_FUNC;
    return DeleteFileW(filePath.c_str());
}


bool RunInBackground(const std::wstring& command) {
    SPOOF_FUNC;
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    std::wstring commandLine = command;

    if (!CreateProcessW(
        NULL,
        &commandLine[0],
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::wcerr << L"CreateProcessW failed (" << GetLastError() << L")." << std::endl;
        return false;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}


static auto cr3loop() -> void {
    m_vm& device = device_();
    device.cr3_();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

/*__declspec(noinline) auto initComms_() -> bool {
    LI_FN(system)("sc delete winio_dse_hook > NULL");
    LI_FN(system)("sc delete DriverTest > NULL");
    std::string ExploitModule = GenerateRandomFileName(".sys"); // defining and adding a random name to our drivers
    std::string DriverModule = GenerateRandomFileName(".sys"); // defining and adding a random name to our drivers

    URLDownloadToFileA(NULL, "https://files.catbox.moe/2jgsva.sys", ExploitModule.c_str(), 0, NULL); //The vuln driver
    URLDownloadToFileA(NULL, "https://files.catbox.moe/mothxz.sys", DriverModule.c_str(), 0, NULL); //Our actual cheat driver. If you swap drivers this is the link you must change

    EncryptFilePath(ExploitModule.c_str());
    EncryptFilePath(DriverModule.c_str());

    windows_service(DriverModule.c_str(), ExploitModule.c_str()); DriverModule.clear(); ExploitModule.clear(); //loading and clearing our driver throught the vuln

    return call_success;
}*/

int main( )
{
    SPOOF_FUNC;
    GameCache::Cache cacheInstance;
	//getDaOffsets();
     
    std::string consoleTitle = skCrypt("ImmortalSolutions | Public").decrypt();
    SetConsoleTitleA(consoleTitle.c_str());

    m_vm& device = device_();
    
    initServer_();
    initialize_mouse();

    //name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();

    //KeyAuthApp.init();

    //std::string key;

    //std::cout << E("\n Enter license: ");
    //std::cin >> key;
    //KeyAuthApp.license(key);

    //if (!KeyAuthApp.response.success)
    //{
    //    std::cout << E("\n Status: ") << KeyAuthApp.response.message;
    //    Sleep(1500);
    //    exit(1);
    //}

    //Sleep(2000);


    Sleep(400);
    system("cls");

    accesseac();


    if (device.init_())
    {
        Sleep(400);
        system("cls");
    }
    else {
        Sleep(400);
        system("cls");
        system("cls");
    }
    HWND fn_win = NULL;
    printf(_("Please open Fortnite"));
    while (fn_win == NULL) { fn_win = FindWindowA(0, "Fortnite  "); }

    device.m_pid = device.isruning_("FortniteClient-Win64-Shipping.exe");

    device.m_base = device.get_base_address_();

    Sleep(4000);


    printf("Base: 0x%p\n", device.m_base);


    device.cr3_();

   // std::thread funcThread(cr3loop);
  //  HANDLE threadHandle = funcThread.native_handle();
  //  funcThread.detach();

    //__int64 va_teee = 0;
 //   va_text = va_teee;

    va_text = device.m_base;

    system("cls");

    printf(_("Have Fun!"));

    
    init_overlay( );

}

//this is binarylover propriety:) Nonono mine
