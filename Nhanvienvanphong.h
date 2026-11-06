#pragma once
#include "NhanVien.h"

class NhanVienVanPhong : public NhanVien {
private:
    int thangTinhLuong;
    int namTinhLuong;

    int soNgayLamViec;
    int soNgayLe;

    double donGiaNgay;
    double phuCap;

    double gioTangCaNgayThuong;
    double gioTangCaCuoiTuan;
    double gioTangCaLeTet;

    // Cac khoan thanh phan cua luong (dung chung cho TinhLuong va phieu luong)
    double DonGiaGio() const;
    double TinhLuongNgayThuong() const;
    double TinhLuongNgayLe() const;
    double TinhTangCaNgayThuong() const;
    double TinhTangCaCuoiTuan() const;
    double TinhTangCaLeTet() const;

public:
    NhanVienVanPhong();

    // nam = 0 nghia la lay nam hien tai
    NhanVienVanPhong(string ma, string ten, string ns, string dc,
        int ngayLam, int ngayLe, double donGia,
        double pc, double tcThuong,
        double tcCuoiTuan, double tcLeTet,
        int thang = 1, int nam = 0);

    NhanVienVanPhong(const NhanVienVanPhong& nv);
    NhanVienVanPhong& operator=(const NhanVienVanPhong& nv) = default;

    virtual ~NhanVienVanPhong();

    int getThangTinhLuong() const;
    int getNamTinhLuong() const;
    int getSoNgayLamViec() const;
    int getSoNgayLe() const;

    double getDonGiaNgay() const;
    double getPhuCap() const;
    double getGioTangCaNgayThuong() const;
    double getGioTangCaCuoiTuan() const;
    double getGioTangCaLeTet() const;

    void setThangTinhLuong(int thang);
    void setNamTinhLuong(int nam);
    void setSoNgayLamViec(int ngay);
    void setSoNgayLe(int ngay);
    void setDonGiaNgay(double gia);
    void setPhuCap(double pc);
    void setGioTangCaNgayThuong(double gio);
    void setGioTangCaCuoiTuan(double gio);
    void setGioTangCaLeTet(double gio);

    double TinhLuong() const override;
    void HienThiThongTin() const override;
    int LayChucVu() const override;
    void NhapLai() override;
    void InCacKhoanLuong(ostream& out) const override;
    void GhiDuLieu(ostream& out) const override;
    void NapDuLieu(const vector<string>& cot) override;

    friend istream& operator>>(istream& in, NhanVienVanPhong& nv);
    friend ostream& operator<<(ostream& out, const NhanVienVanPhong& nv);
};