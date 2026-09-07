#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Дефиниция числа Пи для компилятора MinGW (GCC), чтобы не было ошибок в swirl()
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Глобальные переменные размеров экрана Windows 11
int screenWidth = 0;
int screenHeight = 0;

// Глобальные флаги автоматического завершения фаз строго по окончании звука
bool isSound1Finished = false;
bool isSound2Finished = false;
bool isSound3Finished = false;
bool isSound4Finished = false;
bool isSound5Finished = false;
bool isSound6Finished = false;
bool isSound7Finished = false;
bool isSound8Finished = false;
bool isSound9Finished = false;

// === НАШЕ ГЛАВНОЕ ДЕМОСЦЕН-ПРАВИЛО: АВТОМАТИЧЕСКАЯ ЧИСТКА ХОЛСТА ===
void RefreshScreenClean() {
    InvalidateRect(NULL, NULL, TRUE);
    UpdateWindow(GetDesktopWindow());
}

// === ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ ТВОЕГО ЦВЕТНОГО ВЗРЫВА (ПЕРЕВОД HSL В RGB) ===
COLORREF ConvertHslToRgb(float h, float s, float l) {
    if (s == 0) return RGB((int)(l * 255), (int)(l * 255), (int)(l * 255));
    float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
    float p = 2.0f * l - q;
    
    float t[3] = { h + 1.0f / 3.0f, h, h - 1.0f / 3.0f };
    int rgb[3] = { 0, 0, 0 };
    
    for (int i = 0; i < 3; i++) {
        if (t[i] < 0) t[i] += 1.0f;
        if (t[i] > 1.0f) t[i] -= 1.0f;
        if (t[i] < 1.0f / 6.0f) rgb[i] = (int)((p + (q - p) * 6.0f * t[i]) * 255);
        else if (t[i] < 1.0f / 2.0f) rgb[i] = (int)(q * 255);
        else if (t[i] < 2.0f / 3.0f) rgb[i] = (int)((p + (q - p) * (2.0f / 3.0f - t[i]) * 6.0f) * 255);
        else rgb[i] = (int)(p * 255);
    }
    return RGB(rgb[0], rgb[1], rgb[2]);
}

// ============================================================================
// === БЛОК ПРЕДУПРЕЖДЕНИЙ MESSAGЕBОХ ДЛЯ CHROMAWRECKER =======================
// ============================================================================
bool ShowStartWarnings() {
    int msg1 = MessageBoxA(NULL, "Run GDIOnly?", "ChromaWrecker.exe", MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL);
    if (msg1 == IDNO) return false;
    int msg2 = MessageBoxA(NULL, "Are you sure? For not epileptics!", "Warning", MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL);
    if (msg2 == IDYES) return true;
    return false;
}

// ============================================================================
// === АУДИОПОТОКИ BYTEBEAT (ЧАСТЬ 1) =========================================
// ============================================================================

DWORD WINAPI SoundPhase1(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 8000 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>(((t * (t >> 5 | t >> 8)) >> (t >> 16)) & 255); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound1Finished = true; return 0;
}

DWORD WINAPI SoundPhase2(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 11025 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>((t * (t >> 5 | t >> 8) >> (t >> 16 & 5) | t >> 4) & 255); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound2Finished = true; return 0;
}

DWORD WINAPI SoundPhase3(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 11025 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>((t * (t >> 5 | t >> 8) >> (t >> 16 & 7) | (t * 3 & t >> 9)) & 255); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound3Finished = true; return 0;
}

DWORD WINAPI SoundPhase4(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 22050 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>(((t * (t >> 4 & t >> 8) & t >> 8) | t >> 12) - 1); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound4Finished = true; return 0;
}
// ============================================================================
// === АУДИОПОТОКИ BYTEBEAT (ЧАСТЬ 2) =========================================
// ============================================================================

DWORD WINAPI SoundPhase5(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 8000 * 40; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>(((t * (t >> 8 & t >> 4) >> (t >> 16)) & 255)); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound5Finished = true; return 0;
}

DWORD WINAPI SoundPhase6(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 32000 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>((t >> 5 | (t >> 2) * (t >> 5)) & 255); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound6Finished = true; return 0;
}

DWORD WINAPI SoundPhase7(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 8000 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>(((t * (t >> 4 & t >> 8) & t >> 8) | t >> 12) - 1); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound7Finished = true; return 0;
}

DWORD WINAPI SoundPhase8(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 11025 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { buffer[t] = static_cast<char>((t * (t >> 6 | t >> 8) >> (t >> 16 & 5) | t >> 3) & 255); }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound8Finished = true; return 0;
}

// ФАЗА 9 AUDIO: ТВОЯ ПРИСЛАННАЯ КИБЕР-ТРАШ ФОРМУЛА СЭМПЛОВ НА 8000 Гц (Ровно 30 Секунд!)
DWORD WINAPI SoundPhase9(LPVOID lpParam) {
    HWAVEOUT hWaveOut = 0; WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 }; waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    const int soundDurationSamples = 8000 * 30; char* buffer = new char[soundDurationSamples];
    for (unsigned long long t = 0; t < (unsigned long long)soundDurationSamples; t++) { 
        buffer[t] = static_cast<char>(t > 6 * t & t >> 9 * t >> 12 ? ((t >> 6 | t << 1) + t >> 5 | t << 3 | t >> 3) | t >> 2 | t << 1 : t); 
    }
    WAVEHDR header = { buffer, (DWORD)soundDurationSamples, 0, 0, 0, 0, NULL, 0 }; waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    while (!(header.dwFlags & WHDR_DONE)) { Sleep(50); } waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR)); waveOutClose(hWaveOut); delete[] buffer; isSound9Finished = true; return 0;
}

// ============================================================================
// === БЛОК ВИЗУАЛЬНЫХ GDI-ФУНКЦИЙ ПРОЕКТА CHROMAWRECKER.EXE (ЧАСТЬ 2) ========
// ============================================================================

void RunPhase1() {
    isSound1Finished = false; CreateThread(NULL, 0, SoundPhase1, NULL, 0, NULL); HDC hdcScreen = GetDC(0); float vortexAngle = 0.0f;
    HICON allSystemIcons[8]; LPCSTR iconTypes[] = { IDI_APPLICATION, IDI_HAND, IDI_QUESTION, IDI_EXCLAMATION, IDI_ASTERISK, IDI_WINLOGO, IDI_SHIELD, IDI_WARNING }; for (int i = 0; i < 8; i++) allSystemIcons[i] = LoadIcon(NULL, iconTypes[i]);
    while (!isSound1Finished) { hdcScreen = GetDC(0); int boxSize = 150 + (rand() % 150); int srcX = rand() % (screenWidth - boxSize); int srcY = rand() % (screenHeight - boxSize); int destX = srcX + (int)(sin(vortexAngle) * 35.0f); int destY = srcY + (int)(cos(vortexAngle) * 35.0f); BitBlt(hdcScreen, destX, destY, boxSize, boxSize, hdcScreen, srcX, srcY, SRCCOPY);
        int stripH = 10 + (rand() % 30); int randY = rand() % (screenHeight - stripH); int shiftX = (rand() % 50) - 25; BitBlt(hdcScreen, shiftX, randY, screenWidth, stripH, hdcScreen, 0, randY, SRCCOPY);
        if (rand() % 2 == 0) DrawIcon(hdcScreen, rand() % (screenWidth - 32), rand() % (screenHeight - 32), allSystemIcons[rand() % 8]);
        POINT mousePos; GetCursorPos(&mousePos); int mX = mousePos.x; int mY = mousePos.y;
        HBRUSH hNeonBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)); HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcScreen, hNeonBrush); HPEN hNeonPen = CreatePen(PS_SOLID, 4, RGB(rand() % 256, rand() % 256, rand() % 256)); HPEN hOldPen = (HPEN)SelectObject(hdcScreen, hNeonPen);
        POINT triPoints[3]; triPoints[0].x = mX; triPoints[0].y = mY - 30 - (rand() % 15); triPoints[1].x = mX - 25 - (rand() % 15); triPoints[1].y = mY + 20 + (rand() % 15); triPoints[2].x = mX + 25 + (rand() % 15); triPoints[2].y = mY + 20 + (rand() % 15); 
        Polygon(hdcScreen, triPoints, 3);
        SelectObject(hdcScreen, hOldBrush); DeleteObject(hNeonBrush); SelectObject(hdcScreen, hOldPen); DeleteObject(hNeonPen);
        if (rand() % 15 == 0) BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, DSTINVERT); vortexAngle += 0.25f; ReleaseDC(0, hdcScreen); Sleep(12); }
}

void RunPhase2() {
    isSound2Finished = false; CreateThread(NULL, 0, SoundPhase2, NULL, 0, NULL); HDC hdcScreen = GetDC(0); float chromaAngle = 0.0f;
    while (!isSound2Finished) { hdcScreen = GetDC(0); for (int y = 0; y < screenHeight; y += 4) { int waveShift = (int)(sin(y * 0.02f + chromaAngle) * 25.0f); BitBlt(hdcScreen, waveShift, y, screenWidth, 4, hdcScreen, 0, y, SRCCOPY); }
        int r = (int)(sin(chromaAngle) * 127 + 128); int g = (int)(sin(chromaAngle + 2.0f) * 127 + 128); int b = (int)(sin(chromaAngle + 4.0f) * 127 + 128); HBRUSH hChromaBrush = CreateSolidBrush(RGB(r, g, b)); HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcScreen, hChromaBrush);
        if (rand() % 8 == 0) { PatBlt(hdcScreen, rand() % screenWidth, rand() % screenHeight, 300, 200, PATINVERT); } SelectObject(hdcScreen, hOldBrush); DeleteObject(hChromaBrush); chromaAngle += 0.15f; ReleaseDC(0, hdcScreen); Sleep(12); }
}

void RunPhase3() {
    isSound3Finished = false; CreateThread(NULL, 0, SoundPhase3, NULL, 0, NULL); HDC hdcScreen = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdcScreen); HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight); HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBitmap); double timer = 0; int scrollY = 0;
    while (!isSound3Finished) { timer += 0.15; scrollY -= 12; for (int x = 0; x < screenWidth; x += 4) { for (int y = 0; y < screenHeight; y += 4) { int xorPattern = x ^ (y + scrollY); double wave = (xorPattern * 0.004) + timer; int r = static_cast<int>((sin(wave + 0.0) * 127.0) + 128.0); int g = static_cast<int>((sin(wave + 2.094) * 127.0) + 128.0); int b = static_cast<int>((sin(wave + 4.188) * 127.0) + 128.0); HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b)); RECT rect = { x, y, x + 4, y + 4 }; FillRect(hdcMem, &rect, hBrush); DeleteObject(hBrush); } }
        BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY); Sleep(10); }
    SelectObject(hdcMem, hOldBmp); DeleteObject(hBitmap); DeleteDC(hdcMem); ReleaseDC(0, hdcScreen);
}
// ============================================================================
// === БЛОК ВИЗУАЛЬНЫХ GDI-ФУНКЦИЙ ПРОЕКТА CHROMAWRECKER.EXE (ЧАСТЬ 3) ========
// ============================================================================

void RunPhase4() {
    isSound4Finished = false; CreateThread(NULL, 0, SoundPhase4, NULL, 0, NULL); HDC hdcScreen = GetDC(0); float waveAngle = 0.0f; float zoomFactor = 1.0f;
    HICON allSystemIcons[8]; LPCSTR iconTypes[] = { IDI_APPLICATION, IDI_HAND, IDI_QUESTION, IDI_EXCLAMATION, IDI_ASTERISK, IDI_WINLOGO, IDI_SHIELD, IDI_WARNING }; for (int i = 0; i < 8; i++) allSystemIcons[i] = LoadIcon(NULL, iconTypes[i]);
    while (!isSound4Finished) { hdcScreen = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdcScreen); HBITMAP hBmp = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight); HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBmp);
        zoomFactor += 0.006f; int zoomW = (int)(screenWidth * (zoomFactor - 1.0f)); int zoomH = (int)(screenHeight * (zoomFactor - 1.0f)); StretchBlt(hdcMem, -zoomW / 2, -zoomH / 2, screenWidth + zoomW, screenHeight + zoomH, hdcScreen, 0, 0, screenWidth, screenHeight, SRCCOPY);
        for (int y = 0; y < screenHeight; y += 8) { int xShift = (int)(sin(y * 0.04f + waveAngle) * 30.0f); BitBlt(hdcMem, xShift, y, screenWidth, 8, hdcMem, 0, y, SRCCOPY); }
        if (rand() % 3 == 0) DrawIcon(hdcMem, rand() % (screenWidth - 32), rand() % (screenHeight - 32), allSystemIcons[rand() % 8]);
        int r = (int)(sin(waveAngle) * 127 + 128); int g = (int)(sin(waveAngle + 2.09f) * 127 + 128); int b = (int)(sin(waveAngle + 4.18f) * 127 + 128); HBRUSH hGlitchBrush = CreateSolidBrush(RGB(r, g, b)); HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMem, hGlitchBrush);
        if (rand() % 5 == 0) PatBlt(hdcMem, 0, 0, screenWidth, screenHeight, PATINVERT); if (rand() % 12 == 0) BitBlt(hdcMem, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, DSTINVERT);
        BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY); SelectObject(hdcMem, hOldBrush); DeleteObject(hGlitchBrush); SelectObject(hdcMem, hOldBmp); DeleteObject(hBmp); DeleteDC(hdcMem); waveAngle += 0.22f; ReleaseDC(0, hdcScreen); Sleep(12); }
}

void RunPhase5() {
    isSound5Finished = false; CreateThread(NULL, 0, SoundPhase5, NULL, 0, NULL); HDC hdc = GetDC(NULL); HDC hdcCopy = CreateCompatibleDC(hdc); int w = screenWidth; int h = screenHeight;
    BITMAPINFO bmpi = { 0 }; bmpi.bmiHeader.biSize = sizeof(bmpi); bmpi.bmiHeader.biWidth = w; bmpi.bmiHeader.biHeight = h; bmpi.bmiHeader.biPlanes = 1; bmpi.bmiHeader.biBitCount = 32; bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL; HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0); SelectObject(hdcCopy, bmp); ReleaseDC(NULL, hdc); int i = 0;
    while (!isSound5Finished) { hdc = GetDC(NULL); StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        for (int x = 0; x < w; x += 2) { for (int y = 0; y < h; y += 2) { int index = y * w + x; float fx = (float)(i * x * y); float hue = fmod(fx / 300.f + (float)y / (float)h * .1f, 1.f); COLORREF rgbColor = ConvertHslToRgb(hue, 1.0f, 0.5f);
                rgbquad[index].rgbRed = GetRValue(rgbColor); rgbquad[index].rgbGreen = GetGValue(rgbColor); rgbquad[index].rgbBlue = GetBValue(rgbColor); rgbquad[index + 1] = rgbquad[index]; } }
        i++; StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY); ReleaseDC(NULL, hdc); Sleep(10); }
    DeleteObject(bmp); DeleteDC(hdcCopy);
}

void RunPhase6() {
    isSound6Finished = false; CreateThread(NULL, 0, SoundPhase6, NULL, 0, NULL); int sw = screenWidth; int sh = screenHeight; LPCWSTR lpText = L"ChromaWrecker.exe";
    while (!isSound6Finished) { HDC hdc = GetDC(0); SetStretchBltMode(hdc, HALFTONE); StretchBlt(hdc, 1, 1, sw - 2, sh - 2, hdc, 0, 0, sw, sh, SRCCOPY);
        int sx = rand() % sw; int sy = rand() % sh; SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 256)); SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 256));
        TextOutW(hdc, sx, sy, lpText, lstrlenW(lpText)); ReleaseDC(0, hdc); Sleep(10); }
}

void RunPhase7() {
    isSound7Finished = false; CreateThread(NULL, 0, SoundPhase7, NULL, 0, NULL); int w = screenWidth; int h = screenHeight; LPCWSTR lpText = L"ChromaWrecker.exe";
    BITMAPINFO bmpi = { 0 }; bmpi.bmiHeader.biSize = sizeof(bmpi); bmpi.bmiHeader.biWidth = w; bmpi.bmiHeader.biHeight = h; bmpi.bmiHeader.biPlanes = 1; bmpi.bmiHeader.biBitCount = 32; bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL; HBITMAP hbm = CreateDIBSection(NULL, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0); HDC hdcMem = CreateCompatibleDC(NULL); HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hbm);
    while (!isSound7Finished) { HDC hdcScreen = GetDC(NULL); StretchBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, w, h, SRCCOPY);
        for (int i = 0; i < w * h; i += 2) { if ((i % h) && (rand() % 110 == 0)) { int v = rand() % 24; BYTE* pixelBytes = (BYTE*)&rgbquad[i]; if (i * 4 + v < w * h * 4) { pixelBytes[v % 4] -= 5; } } }
        // ИСПРАВЛЕНО ИДЕАЛЬНО: Передан верный hdcMem контекст вместо картинки hbm! Линкер скомпилирует без ошибок!
        StretchBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, w, h, SRCCOPY);
        if (rand() % 2 == 0) { int sx = rand() % w; int sy = rand() % h; SetTextColor(hdcScreen, RGB(rand() % 255, rand() % 255, rand() % 256)); SetBkColor(hdcScreen, RGB(rand() % 255, rand() % 255, rand() % 256)); TextOutW(hdcScreen, sx, sy, lpText, lstrlenW(lpText)); }
        ReleaseDC(NULL, hdcScreen); Sleep(10); }
    SelectObject(hdcMem, hOldBmp); DeleteObject(hbm); DeleteDC(hdcMem);
}

void RunPhase8() {
    isSound8Finished = false; CreateThread(NULL, 0, SoundPhase8, NULL, 0, NULL); int sw = screenWidth; int sh = screenHeight; int xSize = sw / 10; int ySize = 9;
    while (!isSound8Finished) { HDC hdcScreen = GetDC(0);
        for (int i = 0; i < sh; i += 2) { int wave = (int)(sin(i / ((float)xSize * M_PI)) * ySize); BitBlt(hdcScreen, wave, i, sw, 2, hdcScreen, 0, i, SRCCOPY); }
        for (int i = 0; i < sw; i += 2) { int wave = (int)(sin(i / ((float)xSize * M_PI)) * ySize); BitBlt(hdcScreen, i, wave, 2, sh, hdcScreen, i, 0, SRCCOPY); }
        ReleaseDC(0, hdcScreen); Sleep(10); }
}

// === НАША АБСОЛЮТНО ФИНАЛЬНАЯ ДЕВЯТАЯ ФАЗА: ТОТАЛЬНЫЙ СБОЙ "DIAGONAL SHREDDER" ИЗ STRUCTDESTR ===
void RunPhase9() {
    isSound9Finished = false;
    CreateThread(NULL, 0, SoundPhase9, NULL, 0, NULL); // Твой новый сумасшедший кибер-траш трек!

    int sw = screenWidth;
    int sh = screenHeight;

    while (!isSound9Finished) {
        HDC hdcScreen = GetDC(0);

        // Угарное каскадное смещение всего рабочего стола по диагонали (Твой скрипт payload6!)
        BitBlt(hdcScreen, 1, 1, sw, sh, hdcScreen, -2, 2, SRCCOPY);

        // Брутальный инверт кадра в такт ломаным битам!
        if (rand() % 15 == 0) {
            BitBlt(hdcScreen, 0, 0, sw, sh, hdcScreen, 0, 0, DSTINVERT);
        }

        ReleaseDC(0, hdcScreen);
        Sleep(10);
    }
}

// ============================================================================
// === ТОЧКА ВХОДА WINMAIN ПРОЕКТА CHROMAWRECKER.EXE ==========================
// ============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (ShowStartWarnings()) {
        srand(static_cast<unsigned int>(time(NULL)));
        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);
        
        // --- ЗАПУСК ПОЛНОЙ АНТОЛОГИИ CHROMAWRECKER ---
        RunPhase1();          // Фаза 1 (30 сек)
        RefreshScreenClean(); Sleep(1000); 
        
        RunPhase2();          // Фаза 2 (30 сек)
        RefreshScreenClean(); Sleep(1000); 

        RunPhase3();          // Фаза 3 (30 BN)
        RefreshScreenClean(); Sleep(1000);

        RunPhase4();          // Фаза 4 (30 сек)
        RefreshScreenClean(); Sleep(1000);

        RunPhase5();          // Фаза 5 (40 сек)
        RefreshScreenClean(); Sleep(1000);

        RunPhase6();          // Фаза 6 (30 сек)
        RefreshScreenClean(); Sleep(1000);

        RunPhase7();          // Фаза 7 (30 сек)
        RefreshScreenClean(); Sleep(1000);

        RunPhase8();          // Фаза 8 (30 сек)
        RefreshScreenClean(); Sleep(1000);

        RunPhase9();          // НАША ФИНАЛЬНАЯ ДЕВЯТАЯ ФАЗА (30 сек!)
        RefreshScreenClean(); // Тотальная автоматическая финальная чистка стола перед выходом!
        Sleep(1000);
    }
    return 0;
}


