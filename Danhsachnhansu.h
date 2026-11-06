#pragma once
#include "NhanVien.h"
#include <memory>

// Quan ly danh sach nhan su: doi tuong tu giai phong bo nho nho unique_ptr
class DanhSachNhanSu {
private:
    vector<unique_ptr<NhanVien>> ds;
    bool daThayDoi;                    // true neu co thay doi chua luu ra tep

public:
    DanhSachNhanSu();

    // ----- Thong tin chung -----
    size_t SoLuong() const;
    bool Rong() const;
    bool DaThayDoi() const;
    void DanhDauThayDoi();

    // ----- Them / xoa / truy cap -----
    void Them(unique_ptr<NhanVien> nv);
    bool Xoa(const string& ma);                    // unique_ptr tu delete
    bool TonTai(const string& ma) const;
    NhanVien* TimTheoMa(const string& ma) const;

    // ----- Truy van (tra ve danh sach con tro khong so huu) -----
    vector<const NhanVien*> TatCa() const;
    vector<const NhanVien*> LocTheoChucVu(int chucVu) const;
    vector<const NhanVien*> TimTheoTen(const string& tuKhoa) const;
    vector<const NhanVien*> LocTheoKhoangLuong(double tu, double den) const;
    vector<const NhanVien*> SinhNhatTrongThang(int thang) const;

    // ----- Nghiep vu -----
    void SapXepTheoLuong(bool tangDan);
    void InThongKe() const;

    // ----- Tep du lieu (CSV, dau ';') -----
    void LuuTep(const string& duongDan);                       // nem LoiDuLieu neu khong ghi duoc
    int DocTep(const string& duongDan, int& soDongLoi);        // tra ve so nhan vien doc duoc

    // ----- Hien thi bang dang Excel -----
    static void InBang(const vector<const NhanVien*>& danhSach, const string& tieuDe);
};