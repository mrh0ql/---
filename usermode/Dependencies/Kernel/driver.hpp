#pragma once
#include <fstream>
#include <Windows.h>
#include <cstdint>
#include <TlHelp32.h>


typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID    Pointer;
	};
	ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

/* typedefs */

typedef
VOID
(NTAPI* PIO_APC_ROUTINE) (
	IN PVOID ApcContext,
	IN PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG Reserved
	);

extern "C" __int64 DirectIO(
	HANDLE FileHandle,
	HANDLE Event,
	PIO_APC_ROUTINE
	ApcRoutine,
	PVOID ApcContext,
	PIO_STATUS_BLOCK IoStatusBlock,
	ULONG IoControlCode,
	PVOID InputBuffer,
	ULONG InputBufferLength,
	PVOID OutputBuffer,
	ULONG OutputBufferLength);

#define emulate inline

#pragma once


#define code_read_physical CTL_CODE(FILE_DEVICE_UNKNOWN, 0x28, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_read_virtual CTL_CODE(FILE_DEVICE_UNKNOWN, 0x8, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_write CTL_CODE(FILE_DEVICE_UNKNOWN, 0x881, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_get_base_address CTL_CODE(FILE_DEVICE_UNKNOWN, 0x773, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_decrypt_cr3 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x99, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_restart_driver CTL_CODE(FILE_DEVICE_UNKNOWN, 0x378, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_gma CTL_CODE(FILE_DEVICE_UNKNOWN, 0x777, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _rw {
    INT32 process_id;
    ULONGLONG address;
    ULONGLONG buffer;
    ULONGLONG size;
} rw, * WriteStruct;

typedef struct _r
{
    INT32 process_id;
    ULONGLONG address;
    ULONGLONG buffer;
    ULONGLONG size;
} rwr, * ReadStruct;

typedef struct _ba
{
    INT32 process_id;
    ULONGLONG* address;
} ba, * BaseAddressStruct;

typedef struct _cr3
{
    INT32 process_id;
} cr3, * DTBStruct;

typedef struct _restart
{
    bool bResetCr3;
} restart, * RestartStruct;

typedef struct _movemouse
{
    long x;
    long y;
    unsigned short button_flags;
} movemouse, * MouseMovementStruct;

typedef struct _hf
{
    INT32 process_id;
} hidefile, * HideFileStruct;

class m_vm {
public:
    static m_vm& getInstance() {
        static m_vm Instance;
        return Instance;
    }
    bool write1(void* address, void* buffer, std::uint32_t size);
    bool read2(uint64_t address, void* buffer, std::size_t size);

    bool init_();

    bool init_mouse();

    bool read1(void*, void*, std::uint32_t);

    uintptr_t get_base_address_();

    bool MoveMouse(long x, long y, USHORT button_flags);

    uintptr_t isruning_(LPCTSTR);

    bool cr3_();

    template <typename T>
    inline T read(uint64_t);

    template <typename T>
    inline T write(uint64_t address, T buffer);

    template <typename T>
    bool read_large_array(uint64_t address, T out[], size_t len);

    inline std::string read_ascii(uint64_t);

    template<typename T>
    inline bool read_array(uint64_t, T out[], size_t);


    bool IsValidAddress_(const uint64_t);

    HANDLE m_handle;
    INT32 m_pid;
    uintptr_t m_base;

    m_vm() = default;
    m_vm(const m_vm&) = delete;
    m_vm& operator=(const m_vm&) = delete;


private:

};
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <vector>

inline m_vm& device_()
{
    return m_vm::getInstance();
}

bool m_vm::read2(uint64_t address, void* buffer, std::size_t size) {
    return read1(reinterpret_cast<void*>(address), buffer, static_cast<uint32_t>(size));
}

std::wstring generator(size_t length) {
    const wchar_t charset[] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t max_index = (sizeof(charset) / sizeof(wchar_t)) - 1;
    std::wstring random_string;
    std::default_random_engine generator{ std::random_device{}() };
    std::uniform_int_distribution<size_t> distribution(0, max_index);

    for (size_t i = 0; i < length; ++i) {
        random_string += charset[distribution(generator)];
    }
    return random_string;
}

std::wstring gendevice(bool condition) {
    std::wstringstream ss;
    if (condition) {
        ss << L"\\\\.\\Win32k" << generator(5);
    }

    return ss.str();
}



#define CONFIG_FILE_PATH L"C:\\epic.txt"
#define code_mm CTL_CODE(FILE_DEVICE_UNKNOWN, 0x28, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_movemouse CTL_CODE(FILE_DEVICE_UNKNOWN, 0x891, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define MOUSE_LEFT_BUTTON_DOWN   0x0001 
#define MOUSE_LEFT_BUTTON_UP     0x0002

typedef struct _im
{
    bool nigga;
}im, * InitMouse;
#define code_im CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2828, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

bool m_vm::init_mouse() {

    IO_STATUS_BLOCK block;
    im arguments = { 0 };

    return DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_read_physical,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments));
}

bool m_vm::MoveMouse(long x, long y, USHORT button_flags) {
    IO_STATUS_BLOCK block;
    _movemouse arguments = { 0 };

    arguments.x = x;
    arguments.y = y;
    arguments.button_flags = button_flags;

    return DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_movemouse,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments));
}
HANDLE h_handke;

bool accesseac() {

    HANDLE hDriver = CreateFileW(L"\\\\.\\EAC_Core",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL);

    DWORD bytesReturned;
    BOOL result = DeviceIoControl(hDriver,
        code_read_physical,
        NULL, 0,
        NULL, 0,
        &bytesReturned,
        NULL);

    std::cout << "Successfully interacted with the EAC driver.\n";

    return true;
}


//WAIT caps ik what to do for the handle part look
bool m_vm::init_() {
    // Read UUID from configuration file
    std::wifstream uuidFile(CONFIG_FILE_PATH);
    if (!uuidFile.is_open()) {
        return false;
    }

    std::wstring uuid;
    std::getline(uuidFile, uuid);
    uuidFile.close();

    // Ensure UUID contains a valid UUID string
    if (uuid.empty() || uuid.size() != 36) { // UUID is typically 36 characters
        std::wcerr << L"Invalid UUID format in configuration file." << std::endl;
        return false;
    }

    std::wstring driverName = L"\\\\.\\" + uuid;

    // Attempt to open the driver handle
    m_handle = CreateFileW(driverName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    // Check if handle is valid
    if (!m_handle || m_handle == INVALID_HANDLE_VALUE) { // if can not find the driver return false and after this it will be "else" to load it
        DWORD error = GetLastError();
        return false;
    }

    LPCTSTR eacsys = "EasyAntiCheat_EOS.sys";

    for (int i = 0; i < 10; i++) {
        std::wstring drivername;
        if (isruning_(eacsys)) {
            if (accesseac) {
                drivername = gendevice(true);
            }

        }
        else {
            if (accesseac) {
                drivername = L"\\\\.\\" + uuid;
            }

        }


        m_handle = CreateFileW(drivername.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    }


    if (!this->m_handle || (this->m_handle == INVALID_HANDLE_VALUE))
        return false;

    return true;
}




bool m_vm::read1(void* address, void* buffer, std::uint32_t size) {
    IO_STATUS_BLOCK block;
    rwr arguments = { 0 };

    arguments.address = reinterpret_cast<uint64_t>(address);
    arguments.buffer = reinterpret_cast<uint64_t>(buffer);
    arguments.size = size;
    arguments.process_id = this->m_pid;

    return DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_read_physical,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments));
}

bool m_vm::write1(void* address, void* buffer, std::uint32_t size) {
    IO_STATUS_BLOCK block;
    rw arguments = { 0 };

    arguments.address = reinterpret_cast<uint64_t>(address);
    arguments.buffer = reinterpret_cast<uint64_t>(buffer);
    arguments.size = size;
    arguments.process_id = this->m_pid;

    return DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_write,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments));
}


uintptr_t m_vm::get_base_address_() {

    IO_STATUS_BLOCK block;

    uintptr_t image_address = { NULL };

    ba arguments = { NULL };

    arguments.process_id = this->m_pid;

    arguments.address = (ULONGLONG*)&image_address;

    DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_get_base_address,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments)
    );

    return image_address;
}

#define IOCTL_MOUSE_MOVE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _MOUSE_MOVE_STRUCT {
    LONG X;
    LONG Y;
} MOUSE_MOVE_STRUCT, * PMOUSE_MOVE_STRUCT;

uintptr_t m_vm::isruning_(LPCTSTR process_name) {

    PROCESSENTRY32 pt;

    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    pt.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hsnap, &pt)) {
        do {
            if (!lstrcmpi(pt.szExeFile, process_name)) {
                CloseHandle(hsnap);
                this->m_pid = pt.th32ProcessID;
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }

    CloseHandle(hsnap);

    return { NULL };
}

bool m_vm::cr3_() {

    IO_STATUS_BLOCK block;

    cr3 arguments = { NULL };

    arguments.process_id = this->m_pid;

    return DirectIO(this->m_handle,
        nullptr,
        nullptr,
        nullptr,
        &block,
        code_decrypt_cr3,
        &arguments,
        sizeof(arguments),
        &arguments,
        sizeof(arguments)
    );
}



template <typename T>
inline T m_vm::read(uint64_t address) {
    T buffer{};
    read1(reinterpret_cast<void*>(address), &buffer, sizeof(T));
    return buffer;
}

template <typename T>
inline T m_vm::write(uint64_t address, T buffer)
{
    write1((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

//this is 2
template <typename T>

bool m_vm::read_large_array(uint64_t address, T out[], size_t len) {

    size_t real_size = sizeof(T) * len;

    size_t read_size = 0;

    T* temp = out;  // Temporary pointer to keep track of the current position in the out array

    while (read_size < real_size) {
        BYTE* buffer = new BYTE[512];

        size_t diff = real_size - read_size;
        if (diff > 512)
            diff = 512;

        read1((PVOID)(address + read_size), buffer, diff);

        memcpy(temp, buffer, diff);

        read_size += diff;
        temp += (diff / sizeof(T));

        delete[] buffer;
    }

    return true;
}

inline std::string m_vm::read_ascii(uint64_t adr) {

    char buf[64] = { 0 };

    this->read1((PVOID)adr, &buf, 64);

    return buf;
}

template<typename T>
inline bool m_vm::read_array(uint64_t address, T out[], size_t len) {
    return this->read1((PVOID)address, (uint8_t*)out, sizeof(T) * len) == 0;
}



bool m_vm::IsValidAddress_(const uint64_t address) {
    if (address <= 0x400000 || address == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(address) == nullptr || address > 0x7FFFFFFFFFFFFFFF) {
        return false;
    }

    return true;
}

bool is_valid(const uint64_t adress)
{
    SPOOF_FUNC;
    if (adress <= 0x400000 || adress == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(adress) == nullptr || adress >
        0x7FFFFFFFFFFFFFFF) {
        return false;
    }
    return true;
}