#pragma once
// Tien ich dung chung: hang so nghiep vu, ngoai le, ham nhap lieu an toan, dinh dang.
#include "Mau.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cerrno>
#include <cstdlib>
#include <cctype>
#include <ctime>

using namespace std;

// ===================== NGOAI LE =====================
// Du lieu (tu tep) bi hong / khong hop le
class LoiDuLieu : public runtime_error {
public:
    explicit LoiDuLieu(const string& thongBao) : runtime_error(thongBao) {}
};

// Luong nhap da het (Ctrl+Z / Ctrl+D / het tep) -> thoat chuong trinh an toan
class NgungNhap : public exception {
public:
    const char* what() const noexcept override { return "Het du lieu nhap"; }
};

// ===================== HANG SO NGHIEP VU =====================
namespace CauHinh {
    const int    TUOI_TOI_THIEU = 18;
    const int    TUOI_TOI_DA = 100;
    const int    NAM_TINH_LUONG_TOI_THIEU = 1980;

    // Nhan vien van phong
    const double GIO_LAM_MOI_NGAY = 8;
    const double HE_SO_LUONG_NGAY_LE = 2;
    const double HE_SO_TC_NGAY_THUONG = 1.5;
    const double HE_SO_TC_CUOI_TUAN = 2;
    const double HE_SO_TC_LE_TET = 3;

    // Nhan vien san xuat
    const double THUONG_MOI_SP_VUOT_CHI_TIEU = 2000;

    // Tep du lieu
    const char DAU_PHAN_CACH = ';';
    const char* const TEP_MAC_DINH = "nhansu.csv";
}

// ===================== CHUOI =====================
inline string Trim(const string& s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
}

inline string VietHoa(string s) {
    for (size_t i = 0; i < s.size(); i++) s[i] = (char)toupper((unsigned char)s[i]);
    return s;
}

inline string VietThuong(string s) {
    for (size_t i = 0; i < s.size(); i++) s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

// "  nGUYEN   van a " -> "Nguyen Van A"
inline string ChuanHoaTen(const string& s) {
    istringstream iss(s);
    string tu, kq;
    while (iss >> tu) {
        tu = VietThuong(tu);
        tu[0] = (char)toupper((unsigned char)tu[0]);
        if (!kq.empty()) kq += ' ';
        kq += tu;
    }
    return kq;
}

inline vector<string> TachChuoi(const string& s, char phanCach) {
    vector<string> kq;
    size_t dau = 0;
    while (true) {
        size_t vt = s.find(phanCach, dau);
        if (vt == string::npos) { kq.push_back(s.substr(dau)); break; }
        kq.push_back(s.substr(dau, vt - dau));
        dau = vt + 1;
    }
    return kq;
}

// ===================== NGAY GIO =====================
inline void LayNgayHienTai(int& ngay, int& thang, int& nam) {
    time_t t = time(nullptr);
    tm lt;
#ifdef _WIN32
    localtime_s(&lt, &t);
#else
    localtime_r(&t, &lt);
#endif
    ngay = lt.tm_mday;
    thang = lt.tm_mon + 1;
    nam = lt.tm_year + 1900;
}

inline int NamHienTai() {
    int n, t, y;
    LayNgayHienTai(n, t, y);
    return y;
}

// ===================== DINH DANG =====================
// 15687500 -> "15.687.500"
inline string DinhDangTien(double v) {
    long long n = llround(v);
    bool am = n < 0;
    if (am) n = -n;
    string s = to_string(n), kq;
    int dem = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        kq.push_back(s[i]);
        if (++dem % 3 == 0 && i > 0) kq.push_back('.');
    }
    reverse(kq.begin(), kq.end());
    return am ? "-" + kq : kq;
}

// 1.5 -> "1.5", 1000000 -> "1000000" (khong dung ky hieu khoa hoc)
inline string SoThucChuoi(double v) {
    ostringstream os;
    os << setprecision(15) << v;
    return os.str();
}

// Mot dong cua phieu luong: nhan ben trai, so tien ben phai
inline void InDongPhieu(ostream& out, const string& nhan, double tien) {
    ios_base::fmtflags f = out.flags();
    out << left << setw(48) << nhan << right << setw(14) << DinhDangTien(tien) << " VND\n";
    out.flags(f);
}

// ===================== CHUYEN DOI CHAT CHE =====================
inline bool ChuyenSoNguyen(const string& chuoi, long long& kq) {
    string s = Trim(chuoi);
    if (s.empty()) return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (i == s.size()) return false;
    for (size_t k = i; k < s.size(); k++)
        if (!isdigit((unsigned char)s[k])) return false;
    errno = 0;
    kq = strtoll(s.c_str(), nullptr, 10);
    return errno != ERANGE;
}

inline bool ChuyenSoThuc(const string& chuoi, double& kq) {
    string s = Trim(chuoi);
    replace(s.begin(), s.end(), ',', '.');          // chap nhan "1,5"
    if (s.empty()) return false;
    size_t i = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    int soCham = 0, soChuSo = 0;
    for (size_t k = i; k < s.size(); k++) {
        if (s[k] == '.') soCham++;
        else if (isdigit((unsigned char)s[k])) soChuSo++;
        else return false;
    }
    if (soCham > 1 || soChuSo == 0) return false;
    kq = strtod(s.c_str(), nullptr);
    return isfinite(kq);
}

// Dung khi doc tep: sai dinh dang thi nem LoiDuLieu
inline int DocSoNguyen(const string& s, const string& ten) {
    long long v;
    if (!ChuyenSoNguyen(s, v) || v < INT_MIN || v > INT_MAX)
        throw LoiDuLieu("'" + ten + "' khong phai so nguyen hop le: '" + s + "'");
    return (int)v;
}

inline double DocSoThuc(const string& s, const string& ten) {
    double v;
    if (!ChuyenSoThuc(s, v))
        throw LoiDuLieu("'" + ten + "' khong phai so hop le: '" + s + "'");
    return v;
}

// ===================== NHAP LIEU AN TOAN =====================
// Doc ca dong; het du lieu thi nem NgungNhap (tranh lap vo han khi cin bi dong)
inline string DocDong(istream& in) {
    string s;
    if (!getline(in, s)) throw NgungNhap();
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

inline string MoTaMienSo(const string& ten, double lo, double hi, bool loaiTruLo, bool coGioiHanTren) {
    if (!coGioiHanTren)
        return ten + (loaiTruLo ? " phai lon hon " : " phai >= ") + SoThucChuoi(lo) + "!";
    return ten + " phai nam trong khoang " + SoThucChuoi(lo) + " den " + SoThucChuoi(hi) + "!";
}

// Nhap so nguyen trong [lo, hi]; sai thi bao do va yeu cau nhap lai (khong bao gio treo)
inline int NhapSoNguyen(istream& in, const string& loiMoi, const string& tenTruong, int lo, int hi) {
    while (true) {
        cout << loiMoi;
        string s = DocDong(in);
        long long v;
        if (!ChuyenSoNguyen(s, v)) {
            InMau("Loi: Vui long chi nhap so nguyen hop le!\n", MAU_DO);
            continue;
        }
        if (v < lo || v > hi) {
            InMau(MoTaMienSo(tenTruong, lo, hi, false, hi != INT_MAX) + "\n", MAU_DO);
            continue;
        }
        return (int)v;
    }
}

// Nhap so thuc >= lo (hoac > lo neu loaiTruLo), tuy chon can tren hi
inline double NhapSoThuc(istream& in, const string& loiMoi, const string& tenTruong,
    double lo, bool loaiTruLo = false, double hi = DBL_MAX) {
    while (true) {
        cout << loiMoi;
        string s = DocDong(in);
        double v;
        if (!ChuyenSoThuc(s, v)) {
            InMau("Loi: Vui long chi nhap so hop le!\n", MAU_DO);
            continue;
        }
        bool duoi = loaiTruLo ? (v <= lo) : (v < lo);
        if (duoi || v > hi) {
            InMau(MoTaMienSo(tenTruong, lo, hi, loaiTruLo, hi != DBL_MAX) + "\n", MAU_DO);
            continue;
        }
        return v;
    }
}

// Nhap chuoi khong rong, toi da toiDa ky tu, khong chua dau ';' (dau phan cach cua tep)
inline string NhapChuoi(istream& in, const string& loiMoi, const string& tenTruong, size_t toiDa) {
    while (true) {
        cout << loiMoi;
        string s = Trim(DocDong(in));
        if (s.empty()) {
            InMau(tenTruong + " khong duoc de trong!\n", MAU_DO);
        }
        else if (s.size() > toiDa) {
            InMau(tenTruong + " toi da " + to_string(toiDa) + " ky tu!\n", MAU_DO);
        }
        else if (s.find(CauHinh::DAU_PHAN_CACH) != string::npos) {
            InMau(tenTruong + " khong duoc chua dau ';'!\n", MAU_DO);
        }
        else {
            return s;
        }
    }
}

// Hoi co/khong: y / n
inline bool NhapCoKhong(istream& in, const string& loiMoi) {
    while (true) {
        cout << loiMoi;
        string s = VietThuong(Trim(DocDong(in)));
        if (s == "y" || s == "yes" || s == "c" || s == "co") return true;
        if (s == "n" || s == "no" || s == "k" || s == "khong") return false;
        InMau("Vui long nhap y (co) hoac n (khong)!\n", MAU_DO);
    }
}