#pragma once
#include "NhanVien.h"

class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham;
    int chiTieuSanPham;
    int soSanPhamDatChuan;
    double donGiaSanPham;

    double TinhLuongSanPham() const;
    double TinhThuongNangSuat() const;     
    double TiLeDatChuan() const;// phan tram

public:
    NhanVienSanXuat();

    NhanVienSanXuat(string ma, string ten, string ns, string dc,
        int soSP, int chiTieu, int datChuan, double donGia);

    NhanVienSanXuat(const NhanVienSanXuat& nv);
    NhanVienSanXuat& operator=(const NhanVienSanXuat& nv) = default;

    virtual ~NhanVienSanXuat();

    int getSoSanPham() const;
    int getChiTieuSanPham() const;
    int getSoSanPhamDatChuan() const;
    double getDonGiaSanPham() const;

    void setSoSanPham(int soSP);
    void setChiTieuSanPham(int chiTieu);
    void setSoSanPhamDatChuan(int datChuan);
    void setDonGiaSanPham(double donGia);

    double TinhLuong() const override;
    void HienThiThongTin() const override;
    int LayChucVu() const override;
    void NhapLai() override;
    void InCacKhoanLuong(ostream& out) const override;
    void GhiDuLieu(ostream& out) const override;
    void NapDuLieu(const vector<string>& cot) override;

    friend istream& operator>>(istream& in, NhanVienSanXuat& nv);
    friend ostream& operator<<(ostream& out, const NhanVienSanXuat& nv);
};
