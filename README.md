<div align="center">
  <img src="https://raw.githubusercontent.com/jayaswinjay-web/shared-assets/main/screenshots/fake-os-demo.svg" width="100%" alt="Fake OS Screenshot">
</div>

<br>

<div align="center">

[![License](https://img.shields.io/github/license/jayaswinjay-web/fake-os?style=flat&color=1a8a7a)](LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/jayaswinjay-web/fake-os?style=flat&color=1a8a7a)](https://github.com/jayaswinjay-web/fake-os/commits)
[![CI](https://github.com/jayaswinjay-web/fake-os/actions/workflows/ci.yml/badge.svg)](https://github.com/jayaswinjay-web/fake-os/actions)
[![Repo Size](https://img.shields.io/github/repo-size/jayaswinjay-web/fake-os?style=flat&color=1a8a7a)](https://github.com/jayaswinjay-web/fake-os)
[![Stars](https://img.shields.io/github/stars/jayaswinjay-web/fake-os?style=social)](https://github.com/jayaswinjay-web/fake-os)

---

### ⭐ Support This Project — [Star on GitHub](https://github.com/jayaswinjay-web/fake-os) ⭐

---

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

## Show Your Support

- ⭐ **Star this repo** — helps others discover it
- 🐛 **Report issues** — I respond within 24 hours
- 📬 **Share feedback** — contact@jaytechsoln.in
- ☕ **Buy me a coffee** — [Sponsor](https://github.com/sponsors/jayaswinjay-web)

Made with ❤️ by [Aswin Jay](https://github.com/Aswinajay) — part of [JAY TECH SOLUTIONS](https://jaytechsoln.in)

## License

MIT License — see [LICENSE](LICENSE) for details.
