# Simple Far Cry 3 Trainer

Console-based trainer for **Far Cry 3 (DX11)** written in C++.  
This project is intended **strictly as a demonstration of programming and reverse engineering skills**, not as a practical cheating tool.
It showcases how to work with external processes, navigate pointer chains, and perform safe memory manipulation using WinAPI.  
Project is designed for **educational and portfolio purposes only**.

## Features (Demonstration Only)

The trainer attaches to:

- **Process:** `farcry3_d3d11.exe`
- **Module:** `FC3_d3d11.dll`

Available demonstration options:

### 1. Bow Ammo  
Resolves a pointer chain and writes a new ammo value (999).

### 2. Sniper Ammo  
Resolves a different pointer chain and writes 999 ammo.

### 3. Simple God Mode  
Writes a fixed HP value (99.0f) through a pointer chain.  

### 4. God Mode Off
Just a switch to turn godmode off.

### 0. Exit  
Closes the process handle and terminates the program.


## Technical Overview

This project demonstrates:

### Process Enumeration  
Using `CreateToolhelp32Snapshot` and `Process32First/Next` to locate a running process.

### Module Base Address Retrieval  
Using `Module32First/Next` to find the base address of `FC3_d3d11.dll`.

### Memory Reading & Writing  
Template wrappers around `ReadProcessMemory` and `WriteProcessMemory`.

### Pointer Chain Resolution  
Iteratively reading pointers and applying offsets to reach dynamic in‑game values.

## Usage (Educational Only)

1. Launch **Far Cry 3 (DX11)**.  
2. Run the trainer **as administrator**.  
3. Select any option to observe how memory editing logic works.  
4. Use `0` to exit safely.

NOTICE: Godmode runs in a separate thread is active as long as this application is running. Once you close the trainer, the thread stops automatically and godmode will stop working.

This project is **not intended for real gameplay modification**.


## Build Instructions

- **Visual Studio 2022**
- **C++ Console Application**
- **Windows (WinAPI)**
