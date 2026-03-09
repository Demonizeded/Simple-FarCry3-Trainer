#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <thread>
#include <float.h>



template<typename T> 
bool ReadMemory(const HANDLE OpP, const uintptr_t baseadd, T& newadd ) {
    return ReadProcessMemory(OpP, (LPCVOID)baseadd, &newadd, sizeof(T), nullptr);
}

template<typename T>
bool WriteMemory(const HANDLE OpP, const uintptr_t baseadd, const T newval) {
    return WriteProcessMemory(OpP, (LPVOID)baseadd, &newval,sizeof(T), nullptr);
}

DWORD FindPID(const wchar_t* procname) {
    HANDLE Snp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Snp == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 SnpPe;
    SnpPe.dwSize = sizeof(SnpPe);
    if (Process32First(Snp, &SnpPe)) {
        do {
        
            if (_wcsicmp(SnpPe.szExeFile, procname) == 0) {
                CloseHandle(Snp);
                return SnpPe.th32ProcessID;
            }
        
        
        } while (Process32Next(Snp, &SnpPe));
    }
    
    CloseHandle(Snp);
    return 0;
    

}

uintptr_t FindBaseModAdd(const wchar_t* modlname, const DWORD PID) {
    HANDLE Msnp = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
    if (Msnp == INVALID_HANDLE_VALUE) {
        return 0;
    }

    MODULEENTRY32 me;
    uintptr_t modbaseadd = 0;

    me.dwSize = sizeof(me);
    if (Module32First(Msnp, &me)) {
        do {
            if (_wcsicmp(me.szModule, modlname) == 0) {
                CloseHandle(Msnp);
                return (uintptr_t)me.modBaseAddr;
            }

        } while (Module32Next(Msnp, &me));
    }
    
    CloseHandle(Msnp);
    return 0;
    
}


class CheatsMenu {
public:
    std::atomic_bool isgodon = false;
    void AlterAmmo(uintptr_t baseadd, std::vector<uintptr_t>&& offsets, const DWORD PID, const uintptr_t baseoff) const {

        HANDLE OpProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, PID);

       baseadd += baseoff;
        for (auto offset : offsets) {
            if (ReadMemory(OpProc, baseadd, baseadd)) {
            }
            else { 
                std::cout << "Invalid Offsets or just cant read the value\n";
            }
            baseadd += offset;
        }
        int CheatedValue = 999;
        if (WriteMemory(OpProc, baseadd, CheatedValue)) {
        }
        else {
            std::cout << "Cant alter the value\n";
        }

        CloseHandle(OpProc);


    }

    void GodMode(uintptr_t baseadd, std::vector<uintptr_t>&& offsets, const DWORD PID, const uintptr_t baseoff) {
        isgodon = true;
        HANDLE OpProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, PID);

        baseadd += baseoff;
        for (auto offset : offsets) {
            if (ReadMemory(OpProc, baseadd, baseadd)) {
            }
            else { 
                std::cout << "Invalid Offsets or just cant read the value\n"; 
            }
            baseadd += offset;
        }
        CloseHandle(OpProc);

        std::thread([this, baseadd, PID]() {
            HANDLE OpProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_VM_READ, FALSE, PID);
            float hp = 99.00;
            while (isgodon) {
                if (WriteMemory(OpProc, baseadd, hp)) {
                }
                else {
                    std::cout << "Cant alter the value\n";
                }
                Sleep(50);
            }
            CloseHandle(OpProc);
            }).detach();
        

    }

    void GodModeOff() {
        isgodon = false;
    }


};

int main()
{
    const wchar_t* procname = L"farcry3_d3d11.exe";
    const wchar_t* modlname = L"FC3_d3d11.dll";
    
    DWORD PID = FindPID(procname);
    if (PID == 0) {
        std::cout << "Cant Find The Game, are sure its running?\n";
        return 0;
    }
    uintptr_t modbase = FindBaseModAdd(modlname, PID);
    if (modbase == 0) {
        std::cout << "Cant Find The Module or cant Access base address";
    }

    int x = 1;
    std::cout << "Farcry 3 Trainer Reworked" << "\n" << "1 - Bow Ammo\n" << "2 - Sniper Ammo \n" << "3 - Rifle Ammo\n" << "4 - God On \n" << "4 - God Off \n" << "0 - Close Mod Menu\nIf you are using god mode, DO NOT TURN OFF The Application";
    CheatsMenu opt;
    while (x>0) {
        std::cin >> x;
        switch (x) {
        case 1:
            opt.AlterAmmo(modbase, { 0x4, 0xE8, 0x20, 0xF0, 0x30, 0x10 }, PID, 0x0284F620);
            break;
        case 2:
            opt.AlterAmmo(modbase, { 0x4, 0x38, 0x4, 0x4C, 0x0, 0x8, 0x10 }, PID, 0x02829490);
            break;
        case 3:
            opt.AlterAmmo(modbase, { 0x4, 0x38, 0x4, 0x4C, 0x0, 0x14, 0x10 }, PID, 0x02829490);
            break;
        case 4:
            opt.GodMode(modbase, { 0x4, 0x10, 0x44, 0x2C, 0x10 }, PID, 0x028624D0);
            break;
        case 5:
            opt.GodModeOff();
            break;
        default:
            x = 0;
            break;
    }



}
