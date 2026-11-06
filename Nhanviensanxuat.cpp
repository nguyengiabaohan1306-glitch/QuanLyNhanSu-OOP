#include "NhanVienSanXuat.h"

// ===================== CONSTRUCTOR =====================
NhanVienSanXuat::NhanVienSanXuat() : NhanVien() {
    soSanPham = 0;
    chiTieuSanPham = 0;
    soSanPhamDatChuan = 0;
    donGiaSanPham = 0;
}

NhanVienSanXuat::NhanVienSanXuat(string ma, string ten, string ns, string dc,
    int soSP, int chiTieu, int datChuan, double donGia)
    : NhanVien(ma, ten, ns, dc) {
    soSanPham = soSP;
    chiTieuSanPham = chiTieu;
    soSanPhamDatChuan = datChuan;
    donGiaSanPham = donGia;
}

NhanVienSanXuat::NhanVienSanXuat(const NhanVienSanXuat& nv)
    : NhanVien(nv) {
    soSanPham = nv.soSanPham;
    chiTieuSanPham = nv.chiTieuSanPham;
    soSanPhamDatChuan = nv.soSanPhamDatChuan;
    donGiaSanPham = nv.donGiaSanPham;
}

NhanVienSanXuat::~NhanVienSanXuat() {}

// ===================== GETTER / SETTER =====================
int NhanVienSanXuat::getSoSanPham() const { return soSanPham; }
int NhanVienSanXuat::getChiTieuSanPham() const { return chiTieuSanPham; }
int NhanVienSanXuat::getSoSanPhamDatChuan() const { return soSanPhamDatChuan; }
double NhanVienSanXuat::getDonGiaSanPham() const { return donGiaSanPham; }

void NhanVienSanXuat::setSoSanPham(int soSP) { soSanPham = soSP; }
void NhanVienSanXuat::setChiTieuSanPham(int chiTieu) { chiTieuSanPham = chiTieu; }
void NhanVienSanXuat::setSoSanPhamDatChuan(int datChuan) { soSanPhamDatChuan = datChuan; }
void NhanVienSanXuat::setDonGiaSanPham(double donGia) { donGiaSanPham = donGia; }

// ===================== TINH LUONG =====================
double NhanVienSanXuat::TinhLuongSanPham() const {
    return soSanPham * donGiaSanPham;
}

double NhanVienSanXuat::TinhThuongNangSuat() const {
    if (soSanPham > chiTieuSanPham) {
        return (soSanPham - chiTieuSanPham) * CauHinh::THUONG_MOI_SP_VUOT_CHI_TIEU;
    }
    return 0;
}

double NhanVienSanXuat::TiLeDatChuan() const {
    if (soSanPham > 0) {
        return (double)soSanPhamDatChuan / soSanPham * 100;
    }
    return 0;
}

double NhanVienSanXuat::TinhLuong() const {
    return TinhLuongSanPham() + TinhThuongNangSuat();
}

// ===================== HIEN THI =====================
void NhanVienSanXuat::HienThiThongTin() const {
    cout << "[Chuc vu: Nhan vien San Xuat]\n";
    NhanVien::HienThiThongTin();
    cout << *this;
}

int NhanVienSanXuat::LayChucVu() const { return CV_SAN_XUAT; }

void NhanVienSanXuat::NhapLai() { cin >> *this; }

void NhanVienSanXuat::InCacKhoanLuong(ostream& out) const {
    InDongPhieu(out, "Luong san pham (" + to_string(soSanPham) + " SP x " +
        DinhDangTien(donGiaSanPham) + ")", TinhLuongSanPham());
    int vuot = soSanPham > chiTieuSanPham ? soSanPham - chiTieuSanPham : 0;
    InDongPhieu(out, "Thuong nang suat (" + to_string(vuot) + " SP vuot x " +
        DinhDangTien(CauHinh::THUONG_MOI_SP_VUOT_CHI_TIEU) + ")", TinhThuongNangSuat());
}

// ===================== GHI / NAP TEP =====================
void NhanVienSanXuat::GhiDuLieu(ostream& out) const {
    const char c = CauHinh::DAU_PHAN_CACH;
    GhiChung(out);
    out << c << soSanPham << c << chiTieuSanPham << c << soSanPhamDatChuan
        << c << SoThucChuoi(donGiaSanPham) << "\n";
}

void NhanVienSanXuat::NapDuLieu(const vector<string>& cot) {
    if (cot.size() != 9) {
        throw LoiDuLieu("Nhan vien san xuat can 9 cot, co " + to_string(cot.size()));
    }
    NhanVienSanXuat tam;
    tam.NapChung(cot);
    tam.soSanPham = DocSoNguyen(cot[5], "so san pham");
    tam.chiTieuSanPham = DocSoNguyen(cot[6], "chi tieu");
    tam.soSanPhamDatChuan = DocSoNguyen(cot[7], "so san pham dat chuan");
    tam.donGiaSanPham = DocSoThuc(cot[8], "don gia san pham");

    if (tam.soSanPham < 0 || tam.chiTieuSanPham < 0)
        throw LoiDuLieu("So san pham / chi tieu am");
    if (tam.soSanPhamDatChuan < 0 || tam.soSanPhamDatChuan > tam.soSanPham)
        throw LoiDuLieu("So san pham dat chuan phai trong khoang 0 den tong so san pham");
    if (tam.donGiaSanPham <= 0)
        throw LoiDuLieu("Don gia san pham phai lon hon 0");

    *this = tam;
}

// ===================== NHAP / XUAT =====================
istream& operator>>(istream& in, NhanVienSanXuat& nv) {
    in >> static_cast<NhanVien&>(nv);

    nv.soSanPham = NhapSoNguyen(in, "Nhap so san pham: ", "So san pham", 0, INT_MAX);
    nv.chiTieuSanPham = NhapSoNguyen(in, "Nhap chi tieu san pham: ", "Chi tieu san pham", 0, INT_MAX);
    nv.soSanPhamDatChuan = NhapSoNguyen(in, "Nhap so san pham dat chuan: ", "So san pham dat chuan",
        0, nv.soSanPham);
    nv.donGiaSanPham = NhapSoThuc(in, "Nhap don gia san pham: ", "Don gia san pham", 0, true);
    return in;
}

ostream& operator<<(ostream& out, const NhanVienSanXuat& nv) {
    ios_base::fmtflags f = out.flags();
    out << left;
    out << setw(24) << "So san pham" << ": " << nv.soSanPham << "\n";
    out << setw(24) << "Chi tieu san pham" << ": " << nv.chiTieuSanPham << "\n";
    out << setw(24) << "San pham dat chuan" << ": " << nv.soSanPhamDatChuan << "\n";
    out << setw(24) << "Ti le dat chuan" << ": " << fixed << setprecision(2)
        << nv.TiLeDatChuan() << "%\n";
    out.unsetf(ios_base::floatfield);
    out << setw(24) << "Don gia san pham" << ": " << DinhDangTien(nv.donGiaSanPham) << " VND\n";
    out << setw(24) << "Thuong nang suat" << ": " << DinhDangTien(nv.TinhThuongNangSuat()) << " VND\n";
    out.flags(f);
    return out;
}