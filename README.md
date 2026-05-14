<div align="center">
  <h1>🖥️ Fake OS</h1>
  <p><em>A Windows desktop simulator built in C using the Win32 API</em></p>

  <p>
    <img src="https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c" alt="C">
    <img src="https://img.shields.io/badge/platform-Windows-0078D6?style=flat-square&logo=windows" alt="Windows">
    <img src="https://img.shields.io/badge/API-Win32%20GDI-00b894?style=flat-square" alt="Win32 GDI">
    <img src="https://img.shields.io/badge/license-MIT-blue?style=flat-square" alt="License">
  </p>

  <br>

  ```c
  // A simulated Windows desktop experience
  // Gradient backgrounds, taskbar, start menu — all in C
  ```
</div>

## Overview

Fake OS is a lightweight Windows desktop environment simulator written entirely in C using the native Win32 API and GDI (Graphics Device Interface). It demonstrates low-level systems programming by recreating the visual elements of a Windows operating system desktop — including gradient backgrounds, a dark taskbar, and a functional start menu.

Built without any external libraries or frameworks — just pure Windows API calls.

## Features

- **Gradient desktop** — Multi-color gradient background rendered with `GradientFill` API
- **Dark taskbar** — Windows 11-style semi-transparent taskbar at the bottom
- **Start menu** — Functional start button with menu popup
- **Window management** — Basic window creation and event handling
- **GDI rendering** — All graphics drawn using native GDI functions
- **Lightweight** — Single C file, compiles to a small executable

## Building

### Prerequisites

- Windows OS (Win32 API is platform-specific)
- MSVC (Microsoft Visual C++ Compiler) or MinGW-w64
- Windows SDK (comes with MSVC)

### Compile with MSVC

```cmd
cl fake-os.c /Fe:fake-os.exe /link user32.lib gdi32.lib
```

### Compile with MinGW-w64

```bash
gcc fake-os.c -o fake-os.exe -lgdi32 -luser32
```

### Compile with Visual Studio (Developer Command Prompt)

```cmd
cl.exe fake-os.c user32.lib gdi32.lib
```

## Usage

Simply run the compiled executable:

```cmd
fake-os.exe
```

The simulator window will appear with a gradient desktop background and taskbar.

## Code Structure

```
fake-os.c          # Single source file — the entire simulator
├── WinMain()      # Application entry point
├── WndProc()      # Window procedure (event handler)
├── RenderDesktop() # GDI gradient background rendering
├── Taskbar drawing # Dark taskbar with start button
└── Start menu     # Popup menu implementation
```

## Technical Details

- **API**: Win32 API (`windows.h`), GDI (`GradientFill`, `CreateSolidBrush`, etc.)
- **Rendering**: Double-buffered GDI rendering for smooth visuals
- **Messaging**: Standard Windows message loop with `GetMessage`/`DispatchMessage`
- **Entry point**: `WinMain` with proper window class registration

## Why Fake OS?

This project was built to explore low-level Windows programming concepts:
- Understanding the Windows message loop and event-driven architecture
- Working directly with GDI for graphics rendering
- OS-like UI element implementation (taskbar, start menu)
- Systems programming without frameworks or libraries

## License

MIT License — see [LICENSE](LICENSE) for details.
