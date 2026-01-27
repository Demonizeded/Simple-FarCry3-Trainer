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
Writes a fixed HP value (300.0f) through a pointer chain.  
Includes a counter showing how many times the routine executed.

### 4. Money  
Writes a large money value (99,999,999) to the resolved address.

### 5–6. Additional Pointer Chains  
Alternative pointer paths for ammo values, demonstrating pointer traversal logic.

### 10. Debug  
Displays how many times the god-mode routine has been triggered.

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

This project is **not intended for real gameplay modification**.


## Build Instructions

- **Visual Studio 2022**
- **C++ Console Application**
- **Windows (WinAPI)**
