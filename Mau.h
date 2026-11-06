#pragma once
#include <iostream>
#include <string>

// Windows dung Windows API; Linux/macOS dung ma ANSI (cung 1 giao dien DoiMau/InMau)
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX            // tranh macro min/max cua Windows.h gay loi voi std::min/max
#endif
#include <Windows.h>
#endif

enum Mau {
    MAU_MAC_DINH = 7,
    MAU_XANH_LA = 10,
    MAU_XANH_NGOC = 11,
    MAU_DO = 12,
    MAU_TIM = 13,
    MAU_VANG = 14,
    MAU_TRANG = 15
};

inline void DoiMau(int mau) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
#else
    const char* ma = "0";
    switch (mau) {
    case MAU_XANH_LA:   ma = "92"; break;
    case MAU_XANH_NGOC: ma = "96"; break;
    case MAU_DO:        ma = "91"; break;
    case MAU_TIM:       ma = "95"; break;
    case MAU_VANG:      ma = "93"; break;
    case MAU_TRANG:     ma = "97"; break;
    default:            ma = "0";  break;
    }
    std::cout << "\033[" << ma << "m";
#endif
}

inline void ResetMau() { DoiMau(MAU_MAC_DINH); }

// In nhanh mot thong bao co mau roi tu tra mau ve
inline void InMau(const std::string& s, int mau) {
    DoiMau(mau);
    std::cout << s;
    ResetMau();
}