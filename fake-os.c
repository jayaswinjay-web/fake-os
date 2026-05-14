#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// --- Configurations ---
#define SCREEN_WIDTH  GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define TASKBAR_HEIGHT 40
#define START_BTN_WIDTH 48

// Colors (BGR format for GDI)
#define COL_BG        RGB(0, 120, 215)    // Windows Blue
#define COL_TASKBAR   RGB(30, 30, 30)     // Dark Taskbar
#define COL_START     RGB(255, 255, 255)  // White Icon
#define COL_WINDOW    RGB(240, 240, 240)  // Window Grey

// State variables
bool isStartMenuOpen = false;
HWND hFakeWindow = NULL; // Handle for our fake sub-window

// Function to draw a gradient desktop (More realistic)
void DrawDesktop(HDC hdc, int w, int h) {
    TRIVERTEX vertex[2] ;
    vertex[0].x     = 0;
    vertex[0].y     = 0;
    vertex[0].Red   = 0x0000;
    vertex[0].Green = 0x5a00;
    vertex[0].Blue  = 0x9e00; // Windows 10 Dark Blue
    vertex[0].Alpha = 0x0000;

    vertex[1].x     = w;
    vertex[1].y     = h; 
    vertex[1].Red   = 0x0000;
    vertex[1].Green = 0x7800;
    vertex[1].Blue  = 0xd700; // Lighter Blue
    vertex[1].Alpha = 0x0000;

    GRADIENT_RECT gRect;
    gRect.UpperLeft  = 0;
    gRect.LowerRight = 1;
    GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
}

// Function to Draw Text
void DrawString(HDC hdc, int x, int y, const char* text, int size) {
    HFONT hFont = CreateFont(size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 
                             CLEARTYPE_QUALITY, VARIABLE_PITCH, "Segoe UI");
    SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));
    TextOut(hdc, x, y, text, strlen(text));
    DeleteObject(hFont);
}

// Window Procedure (The Brain)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // 1. Draw Desktop Gradient
            DrawDesktop(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);

            // 2. Draw Taskbar
            HBRUSH hBrushTask = CreateSolidBrush(COL_TASKBAR);
            RECT rTask = {0, SCREEN_HEIGHT - TASKBAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
            FillRect(hdc, &rTask, hBrushTask);
            DeleteObject(hBrushTask);

            // 3. Draw Start Icon (Simple Windows Logo)
            int sX = 15, sY = SCREEN_HEIGHT - TASKBAR_HEIGHT + 12;
            HBRUSH hWhite = CreateSolidBrush(RGB(255,255,255));
            RECT r1 = {sX, sY, sX+8, sY+8};
            RECT r2 = {sX+10, sY, sX+18, sY+8};
            RECT r3 = {sX, sY+10, sX+8, sY+18};
            RECT r4 = {sX+10, sY+10, sX+18, sY+18};
            FillRect(hdc, &r1, hWhite); FillRect(hdc, &r2, hWhite);
            FillRect(hdc, &r3, hWhite); FillRect(hdc, &r4, hWhite);
            DeleteObject(hWhite);

            // 4. Draw "Clock"
            SYSTEMTIME st;
            GetLocalTime(&st);
            char timeStr[10];
            sprintf(timeStr, "%02d:%02d", st.wHour, st.wMinute);
            DrawString(hdc, SCREEN_WIDTH - 60, SCREEN_HEIGHT - 30, timeStr, 20);

            // 5. Draw Desktop Icon (Recycle Bin)
            HBRUSH hIconColor = CreateSolidBrush(RGB(255,255,255));
            RECT rIcon = {30, 30, 70, 80}; // Simple white rect for icon
            FrameRect(hdc, &rIcon, hIconColor);
            DrawString(hdc, 20, 90, "My PC", 16);
            DeleteObject(hIconColor);

            // 6. Draw Start Menu (If open)
            if(isStartMenuOpen) {
                HBRUSH hMenu = CreateSolidBrush(RGB(40, 40, 40));
                RECT rMenu = {0, SCREEN_HEIGHT - 400, 300, SCREEN_HEIGHT - TASKBAR_HEIGHT};
                FillRect(hdc, &rMenu, hMenu);
                DeleteObject(hMenu);
                DrawString(hdc, 20, SCREEN_HEIGHT - 380, "Pinned Apps", 20);
                DrawString(hdc, 20, SCREEN_HEIGHT - 340, "> Notepad", 18);
                DrawString(hdc, 20, SCREEN_HEIGHT - 300, "> Calculator", 18);
                DrawString(hdc, 20, SCREEN_HEIGHT - 260, "> Settings", 18);
            }

            EndPaint(hwnd, &ps);
        } break;

        case WM_LBUTTONDOWN: {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            // Click Start Button
            if (x >= 0 && x <= 50 && y >= SCREEN_HEIGHT - TASKBAR_HEIGHT) {
                isStartMenuOpen = !isStartMenuOpen;
                InvalidateRect(hwnd, NULL, FALSE); // Redraw screen
            }
            // Click "My PC" Icon
            else if (x >= 20 && x <= 80 && y >= 20 && y <= 100) {
                MessageBox(hwnd, "Opening File Explorer...", "System", MB_OK | MB_ICONINFORMATION);
            }
        } break;

        case WM_KEYDOWN:
            if(wParam == VK_ESCAPE) PostQuitMessage(0); // Press ESC to exit
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WinSimClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST, // Keep on top
        "WinSimClass", 
        "Windows OS Simulator", 
        WS_POPUP | WS_VISIBLE, // Borderless Fullscreen
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
        NULL, NULL, hInstance, NULL
    );

    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}