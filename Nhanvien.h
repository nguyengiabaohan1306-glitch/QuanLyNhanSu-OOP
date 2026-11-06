#pragma once
#include "TienIch.h"

// Ma chuc vu tra ve boi LayChucVu()
enum ChucVu { CV_VAN_PHONG = 1, CV_SAN_XUAT = 2, CV_QUAN_LY = 3 };

// ----- Ham tien ich ve ngay thang / chuc vu -----
bool TachNgaySinh(const string& ns, int& ngay, int& thang, int& nam);
bool KiemTraNgaySinh(string ns);
int SoNgayTrongThang(int thang, int nam);
int TinhTuoi(const string& ngaySinh);        // -1 neu ngay sinh sai dinh dang
string TenChucVu(int cv);                    // "Nhan vien Van Phong"...
string TenChucVuNgan(int cv);                // "Nhan vien VP"... (dung trong bang)

// Lop co so TRUU TUONG: khong the tao doi tuong NhanVien truc tiep
class NhanVien {
private:
    string maNV;
    string hoTen;
    string ngaySinh;
    string diaChi;

public:
    string getMaNV() const;
    string getHoTen() const;
    string getNgaySinh() const;
    string getDiaChi() const;

    void setMaNV(string ma);
    void setHoTen(string ten);
    void setNgaySinh(string ns);
    void setDiaChi(string dc);

    NhanVien();
    NhanVien(string ma, string ten, string ns, string dc);
    NhanVien(const NhanVien& nv);
    NhanVien& operator=(const NhanVien& nv) = default;

    virtual ~NhanVien() {}

    int Tuoi() const;
    int ThangSinh() const;

    friend istream& operator>>(istream& in, NhanVien& nv);
    friend ostream& operator<<(ostream& out, const NhanVien& nv);

    // So sanh: < theo luong, == theo ma nhan vien
    bool operator<(const NhanVien& other) const;
    bool operator==(const NhanVien& other) const;

    // ----- Cac phuong thuc da hinh (ham thuan ao) -----
    virtual double TinhLuong() const = 0;
    virtual int LayChucVu() const = 0;
    virtual void NhapLai() = 0;
    virtual void InCacKhoanLuong(ostream& out) const = 0;   // tung khoan trong phieu luong
    virtual void GhiDuLieu(ostream& out) const = 0;         // ghi 1 dong ra tep
    virtual void NapDuLieu(const vector<string>& cot) = 0;  // nap tu 1 dong cua tep

    // ----- Phuong thuc ao co cai dat mac dinh -----
    virtual void HienThiThongTin() const;

    // Template Method: khung phieu luong co dinh, cac khoan luong do lop con in
    void InPhieuLuong(ostream& out = cout) const;

protected:
    void GhiChung(ostream& out) const;                // loai;ma;ten;ngay sinh;dia chi
    void NapChung(const vector<string>& cot);         // doc + kiem tra 5 cot dau
};