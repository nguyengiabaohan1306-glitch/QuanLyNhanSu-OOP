#pragma once
#include "NhanVien.h"

class QuanLy : public NhanVien {
private:
    double luongCoBan;
    double heSoTrachNhiem;

public:
    QuanLy();
    QuanLy(string ma, string ten, string ns, string dc, double luongCB, double heSo);

    double getLuongCoBan() const;
    void setLuongCoBan(double luongCB);
    double getHeSoTrachNhiem() const;
    void setHeSoTrachNhiem(double heSo);

    double TinhLuongTrachNhiem() const;

    double TinhLuong() const override;
    void HienThiThongTin() const override;
    int LayChucVu() const override;
    void NhapLai() override;
    void InCacKhoanLuong(ostream& out) const override;
    void GhiDuLieu(ostream& out) const override;
    void NapDuLieu(const vector<string>& cot) override;

    friend istream& operator>>(istream& in, QuanLy& ql);
    friend ostream& operator<<(ostream& out, const QuanLy& ql);
};
