#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
using namespace std;

DWORD GetProcessID(const wchar_t* processName) {

    DWORD processID = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snap != INVALID_HANDLE_VALUE) {

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);

        if (Process32First(snap, &pe)) {
            do {
                if (!_wcsicmp(pe.szExeFile, processName)) {
                    processID = pe.th32ProcessID;
                    break;

                }


            } while (Process32Next(snap, &pe));
        } 
    }
    CloseHandle(snap);
    return processID;
}

uintptr_t GetbasemodAddress(DWORD processID, const wchar_t* moduleName) {

    uintptr_t baseadd = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID); 

    if (snap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 me;
        me.dwSize = sizeof(me);

        if (Module32First(snap, &me)) {

            do {
                if (!_wcsicmp(me.szModule, moduleName)) {
                    baseadd = (uintptr_t)me.modBaseAddr;
                    break;
                }

            } while (Module32Next(snap, &me));

        }


    }
    CloseHandle(snap);
    return baseadd;
}

template<typename T>
bool ReadMemory(HANDLE prochandle, uintptr_t address, T& value) {
    return ReadProcessMemory(prochandle, (LPCVOID)address, &value, sizeof(T), nullptr);

}

template<typename T>
bool WriteMemory(HANDLE prochandle, uintptr_t address, T value) {

    return WriteProcessMemory(prochandle, (LPVOID)address, &value, sizeof(T), nullptr);
}
int opti;
int god = 0;

int main() {
    
    const wchar_t* processName = L"farcry3_d3d11.exe";   
    const wchar_t* moduleName = L"FC3_d3d11.dll";   

    DWORD processID = GetProcessID(processName);
    if (!processID) {

        cout << "Nie znaleziono procesu" << endl;
        return 1;

    }

    uintptr_t basemod = GetbasemodAddress(processID, moduleName);
    if (!basemod) {
        cout << "Nie znaleziono bazy modułu!" << endl;
        return 1;
    }

    HANDLE prochandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (!prochandle) {
        cout << "Nie mozna otworzyc programu" << endl;
        return 1;
    }
    
    do {
        
        cout << "Wybierz cheata" << "\n" << "1 - ammo do luku\n" << "2 - ammo do snajpy\n" << "3 - przelacz goda\n" << "4 - dodaj kase \n" << "0 - zamknij program" << endl;
        cin >> opti;

        if (opti == 1) {
            cout << "dodano amunicje do luku\n\n";
            //ammo do łuku
            uintptr_t baseadd = basemod + 0x0284F620; 
            uintptr_t offset[] = { 0x4, 0xE8, 0x20, 0xF0, 0x30, 0x10 };     
            uintptr_t finaladd = baseadd;

            for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                ReadMemory(prochandle, finaladd, finaladd);
                finaladd += offset[i];
            }

            int value;
            if (ReadMemory(prochandle, finaladd, value)) {
                cout << "\nOdczytana wartosc: " << value << endl;

                int newValue = 999;  
                if (WriteMemory(prochandle, finaladd, newValue)) {
                    cout << "Zmieniono wartosc na: " << newValue << endl;
                }
                else {
                    cout << "Nie udalo sie zapisac nowej wartosci!" << endl;
                }
            }
            else {
                cout << "Nie mozna odczytac pamieci!" << endl;
            }
        }
        else if (opti == 2) {
            //ammo snajpa
            cout << "dodano ammo do snajpy\n\n";
            uintptr_t baseadd = basemod + 0x02829490; 
            uintptr_t offset[] = { 0x4, 0x38, 0x4, 0x4C, 0x0, 0x8, 0x10 };     
            uintptr_t finaladd = baseadd;

            for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                ReadMemory(prochandle, finaladd, finaladd);
                finaladd += offset[i];
            }
            
            int value;
            if (ReadMemory(prochandle, finaladd, value)) {
                cout << "Odczytana wartosc: " << value << endl;

                int newValue = 999;  
                if (WriteMemory(prochandle, finaladd, newValue)) {
                    cout << "\nZmieniono wartosc na: " << newValue << endl;
                }
                else {
                    cout << "Nie udalo sie zapisac nowej wartosci!" << endl;
                }
            }
            else {
                cout << "Nie mozna odczytac pamieci!" << endl;
            }
        }
        else if (opti == 3) {
            //godzik
            cout << "ogolnie to jeszcze zrobie zeby pisalo kiedy jest wlaczany a kiedy wylaczany - GOD\n\n";
                uintptr_t baseadd = basemod + 0x028624D0; 
                uintptr_t offset[] = { 0x4, 0x10, 0x44, 0x2C, 0x10 };     
                uintptr_t finaladd = baseadd;

                for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                    ReadMemory(prochandle, finaladd, finaladd);
                    finaladd += offset[i];
                }

                float value;
                
                if (ReadMemory(prochandle, finaladd, value)) {
                    
                    float newValue = 300.0f;
                    do {
                        if (WriteMemory(prochandle, finaladd, newValue)) {
                            god += 1;
                        }
                        else {
                            cout << "Nie udalo sie zapisac nowej wartosci!" << endl;
                        }
                    } while (value <=290.0f);
                }
                else {
                        cout << "Nie mozna odczytac pamieci!" << endl;
                }
                
            

        }
        else if (opti == 4) {
            //siano
            cout << "milioner\n\n";
            uintptr_t baseadd = basemod + 0x02861838; 
            uintptr_t offset[] = { 0x0, 0xE4, 0x24, 0xC48 };     
            uintptr_t finaladd = baseadd;

            for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                ReadMemory(prochandle, finaladd, finaladd);
                finaladd += offset[i];
            }

            int value;
            if (ReadMemory(prochandle, finaladd, value)) {
                cout << "Odczytana wartosc: " << value << endl;

                int newValue = 99999999;  
                if (WriteMemory(prochandle, finaladd, newValue)) {
                    cout << "Zmieniono wartosc na: " << newValue << endl;
                }
                else {
                    cout << "Nie udalo sie zapisac nowej wartosci!" << endl;
                }
            }
            else {
                cout << "Nie mozna odczytac pamieci!" << endl;
            }
        }
        else if (opti == 5) {
            //bazowyadres:0x02829490 offsety:0x4, 0x38, 0x4, 0x4C, 0x0, 0x14, 0x10
            uintptr_t baseadd = basemod + 0x02829490;
            uintptr_t offset[] = { 0x4, 0x38, 0x4, 0x4C, 0x0, 0x14, 0x10 };
            uintptr_t finaladd = baseadd;

            for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                ReadMemory(prochandle, finaladd, finaladd);
                finaladd += offset[i];

            }
            int value;
            if (ReadMemory(prochandle, finaladd, value)) {

                int newvalue = 999;
                if (WriteMemory(prochandle, finaladd, newvalue)) {
                    cout << "Zmieniono wartosc na: " << newvalue << endl;
                }
                else {
                    cout << "Nie udalo sie zapisac nowej wartosci!" << endl;
                }
            }
            else {
                cout << "Nie mozna odczytac pamieci!" << endl;

            }
        }
        else if (opti==6) {
            uintptr_t baseadd = basemod + 0x02829490;
            uintptr_t offset[] = { 0x4, 0x38, 0x4, 0x4C, 0x0, 0xC, 0x10 };
            uintptr_t finaladd = baseadd;
            
            for (int i = 0; i < sizeof(offset) / sizeof(offset[0]); i++) {
                ReadMemory(prochandle, finaladd, finaladd);
                finaladd += offset[i];
            }
                int value;
                if(ReadMemory(prochandle, finaladd, value))
                {
                    cout << "pomyslnie odczytano: " << value;
                    int newvalue = 999;
                    if (WriteMemory(prochandle, finaladd, newvalue)) {
                        cout << "pomyslnie dodano : " << newvalue;
                    }
                    else {
                        cout << "nie udało się nadpisać wartości";
                    }
                
                   
                }
                else {
                    cout << "Nie udało się odczytać wartości";
                }
            
            

        }
        else if (opti == 0) {
            CloseHandle(prochandle);
            return 0;
        }
        else if (opti == 10) {
            cout << "god wykonany: " << god << endl;
        }
     }while(true);

}
