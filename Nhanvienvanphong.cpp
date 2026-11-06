#include "NhanVienVanPhong.h"

// ===================== CONSTRUCTOR =====================
NhanVienVanPhong::NhanVienVanPhong() : NhanVien() {
    thangTinhLuong = 1;
    namTinhLuong = NamHienTai();

    soNgayLamViec = 0;
    soNgayLe = 0;
    donGiaNgay = 0;
    phuCap = 0;

    gioTangCaNgayThuong = 0;
    gioTangCaCuoiTuan = 0;
    gioTangCaLeTet = 0;
}

NhanVienVanPhong::NhanVienVanPhong(string ma, string ten, string ns, string dc,
    int ngayLam, int ngayLe, double donGia,
    double pc, double tcThuong,
    double tcCuoiTuan, double tcLeTet,
    int thang, int nam)
    : NhanVien(ma, ten, ns, dc) {

    thangTinhLuong = thang;
    namTinhLuong = (nam > 0) ? nam : NamHienTai();

    soNgayLamViec = ngayLam;
    soNgayLe = ngayLe;
    donGiaNgay = donGia;
    phuCap = pc;

    gioTangCaNgayThuong = tcThuong;
    gioTangCaCuoiTuan = tcCuoiTuan;
    gioTangCaLeTet = tcLeTet;
}

NhanVienVanPhong::NhanVienVanPhong(const NhanVienVanPhong& nv)
    : NhanVien(nv) {

    thangTinhLuong = nv.thangTinhLuong;
    namTinhLuong = nv.namTinhLuong;

    soNgayLamViec = nv.soNgayLamViec;
    soNgayLe = nv.soNgayLe;
    donGiaNgay = nv.donGiaNgay;
    phuCap = nv.phuCap;

    gioTangCaNgayThuong = nv.gioTangCaNgayThuong;
    gioTangCaCuoiTuan = nv.gioTangCaCuoiTuan;
    gioTangCaLeTet = nv.gioTangCaLeTet;
}

NhanVienVanPhong::~NhanVienVanPhong() {}

// ===================== GETTER / SETTER =====================
int NhanVienVanPhong::getThangTinhLuong() const { return thangTinhLuong; }
int NhanVienVanPhong::getNamTinhLuong() const { return namTinhLuong; }
int NhanVienVanPhong::getSoNgayLamViec() const { return soNgayLamViec; }
int NhanVienVanPhong::getSoNgayLe() const { return soNgayLe; }
double NhanVienVanPhong::getDonGiaNgay() const { return donGiaNgay; }
double NhanVienVanPhong::getPhuCap() const { return phuCap; }
double NhanVienVanPhong::getGioTangCaNgayThuong() const { return gioTangCaNgayThuong; }
double NhanVienVanPhong::getGioTangCaCuoiTuan() const { return gioTangCaCuoiTuan; }
double NhanVienVanPhong::getGioTangCaLeTet() const { return gioTangCaLeTet; }

void NhanVienVanPhong::setThangTinhLuong(int thang) { thangTinhLuong = thang; }
void NhanVienVanPhong::setNamTinhLuong(int nam) { namTinhLuong = nam; }
void NhanVienVanPhong::setSoNgayLamViec(int ngay) { soNgayLamViec = ngay; }
void NhanVienVanPhong::setSoNgayLe(int ngay) { soNgayLe = ngay; }
void NhanVienVanPhong::setDonGiaNgay(double gia) { donGiaNgay = gia; }
void NhanVienVanPhong::setPhuCap(double pc) { phuCap = pc; }
void NhanVienVanPhong::setGioTangCaNgayThuong(double gio) { gioTangCaNgayThuong = gio; }
void NhanVienVanPhong::setGioTangCaCuoiTuan(double gio) { gioTangCaCuoiTuan = gio; }
void NhanVienVanPhong::setGioTangCaLeTet(double gio) { gioTangCaLeTet = gio; }

// ===================== TINH LUONG =====================
double NhanVienVanPhong::DonGiaGio() const {
    return donGiaNgay / CauHinh::GIO_LAM_MOI_NGAY;
}

double NhanVienVanPhong::TinhLuongNgayThuong() const {
    return soNgayLamViec * donGiaNgay;
}

double NhanVienVanPhong::TinhLuongNgayLe() const {
    return soNgayLe * donGiaNgay * CauHinh::HE_SO_LUONG_NGAY_LE;
}

double NhanVienVanPhong::TinhTangCaNgayThuong() const {
    return gioTangCaNgayThuong * DonGiaGio() * CauHinh::HE_SO_TC_NGAY_THUONG;
}

double NhanVienVanPhong::TinhTangCaCuoiTuan() const {
    return gioTangCaCuoiTuan * DonGiaGio() * CauHinh::HE_SO_TC_CUOI_TUAN;
}

double NhanVienVanPhong::TinhTangCaLeTet() const {
    return gioTangCaLeTet * DonGiaGio() * CauHinh::HE_SO_TC_LE_TET;
}

double NhanVienVanPhong::TinhLuong() const {
    return TinhLuongNgayThuong() + TinhLuongNgayLe() + phuCap
        + TinhTangCaNgayThuong() + TinhTangCaCuoiTuan() + TinhTangCaLeTet();
}

// ===================== HIEN THI =====================
void NhanVienVanPhong::HienThiThongTin() const {
    cout << "[Chuc vu: Nhan vien Van Phong]\n";
    NhanVien::HienThiThongTin();
    cout << *this;
}

int NhanVienVanPhong::LayChucVu() const { return CV_VAN_PHONG; }

void NhanVienVanPhong::NhapLai() { cin >> *this; }

void NhanVienVanPhong::InCacKhoanLuong(ostream& out) const {
    InDongPhieu(out, "Luong ngay thuong (" + to_string(soNgayLamViec) + " ngay x " +
        DinhDangTien(donGiaNgay) + ")", TinhLuongNgayThuong());
    InDongPhieu(out, "Luong ngay le/tet (" + to_string(soNgayLe) + " ngay x " +
        DinhDangTien(donGiaNgay) + " x " + SoThucChuoi(CauHinh::HE_SO_LUONG_NGAY_LE) + ")",
        TinhLuongNgayLe());
    InDongPhieu(out, "Phu cap", phuCap);
    InDongPhieu(out, "Tang ca ngay thuong (" + SoThucChuoi(gioTangCaNgayThuong) + " gio x " +
        DinhDangTien(DonGiaGio()) + " x " + SoThucChuoi(CauHinh::HE_SO_TC_NGAY_THUONG) + ")",
        TinhTangCaNgayThuong());
    InDongPhieu(out, "Tang ca cuoi tuan (" + SoThucChuoi(gioTangCaCuoiTuan) + " gio x " +
        DinhDangTien(DonGiaGio()) + " x " + SoThucChuoi(CauHinh::HE_SO_TC_CUOI_TUAN) + ")",
        TinhTangCaCuoiTuan());
    InDongPhieu(out, "Tang ca le/tet (" + SoThucChuoi(gioTangCaLeTet) + " gio x " +
        DinhDangTien(DonGiaGio()) + " x " + SoThucChuoi(CauHinh::HE_SO_TC_LE_TET) + ")",
        TinhTangCaLeTet());
}

// ===================== GHI / NAP TEP =====================
void NhanVienVanPhong::GhiDuLieu(ostream& out) const {
    const char c = CauHinh::DAU_PHAN_CACH;
    GhiChung(out);
    out << c << thangTinhLuong << c << namTinhLuong
        << c << soNgayLamViec << c << soNgayLe
        << c << SoThucChuoi(donGiaNgay) << c << SoThucChuoi(phuCap)
        << c << SoThucChuoi(gioTangCaNgayThuong)
        << c << SoThucChuoi(gioTangCaCuoiTuan)
        << c << SoThucChuoi(gioTangCaLeTet) << "\n";
}

void NhanVienVanPhong::NapDuLieu(const vector<string>& cot) {
    if (cot.size() != 14) {
        throw LoiDuLieu("Nhan vien van phong can 14 cot, co " + to_string(cot.size()));
    }
    NhanVienVanPhong tam;                 // nap vao doi tuong tam, hop le het moi gan
    tam.NapChung(cot);
    tam.thangTinhLuong = DocSoNguyen(cot[5], "thang");
    tam.namTinhLuong = DocSoNguyen(cot[6], "nam");
    tam.soNgayLamViec = DocSoNguyen(cot[7], "so ngay lam");
    tam.soNgayLe = DocSoNguyen(cot[8], "so ngay le");
    tam.donGiaNgay = DocSoThuc(cot[9], "don gia ngay");
    tam.phuCap = DocSoThuc(cot[10], "phu cap");
    tam.gioTangCaNgayThuong = DocSoThuc(cot[11], "tang ca ngay thuong");
    tam.gioTangCaCuoiTuan = DocSoThuc(cot[12], "tang ca cuoi tuan");
    tam.gioTangCaLeTet = DocSoThuc(cot[13], "tang ca le/tet");

    if (tam.thangTinhLuong < 1 || tam.thangTinhLuong > 12)
        throw LoiDuLieu("Thang tinh luong ngoai 1-12");
    if (tam.namTinhLuong < CauHinh::NAM_TINH_LUONG_TOI_THIEU)
        throw LoiDuLieu("Nam tinh luong nho hon " + to_string(CauHinh::NAM_TINH_LUONG_TOI_THIEU));
    int toiDa = SoNgayTrongThang(tam.thangTinhLuong, tam.namTinhLuong);
    if (tam.soNgayLamViec < 0 || tam.soNgayLe < 0 || tam.soNgayLamViec + tam.soNgayLe > toiDa)
        throw LoiDuLieu("So ngay lam + ngay le vuot qua " + to_string(toiDa) + " ngay cua thang");
    if (tam.donGiaNgay < 0 || tam.phuCap < 0 || tam.gioTangCaNgayThuong < 0 ||
        tam.gioTangCaCuoiTuan < 0 || tam.gioTangCaLeTet < 0)
        throw LoiDuLieu("Co gia tri am");

    *this = tam;
}

// ===================== NHAP / XUAT =====================
istream& operator>>(istream& in, NhanVienVanPhong& nv) {
    in >> static_cast<NhanVien&>(nv);     // tai su dung phan nhap chung cua lop cha

    nv.thangTinhLuong = NhapSoNguyen(in, "Nhap thang tinh luong (1-12): ", "Thang tinh luong", 1, 12);
    nv.namTinhLuong = NhapSoNguyen(in,
        "Nhap nam tinh luong (>= " + to_string(CauHinh::NAM_TINH_LUONG_TOI_THIEU) + "): ",
        "Nam tinh luong", CauHinh::NAM_TINH_LUONG_TOI_THIEU, INT_MAX);

    int soNgayToiDa = SoNgayTrongThang(nv.thangTinhLuong, nv.namTinhLuong);
    cout << "Thang " << nv.thangTinhLuong << "/" << nv.namTinhLuong
        << " co " << soNgayToiDa << " ngay.\n";

    nv.soNgayLamViec = NhapSoNguyen(in,
        "Nhap so ngay lam viec (0-" + to_string(soNgayToiDa) + "): ",
        "So ngay lam viec", 0, soNgayToiDa);

    int conLai = soNgayToiDa - nv.soNgayLamViec;
    nv.soNgayLe = NhapSoNguyen(in,
        "Nhap so ngay lam le/tet (0-" + to_string(conLai) + "): ",
        "So ngay le/tet", 0, conLai);

    nv.donGiaNgay = NhapSoThuc(in, "Nhap don gia ngay: ", "Don gia ngay", 0);
    nv.phuCap = NhapSoThuc(in, "Nhap phu cap: ", "Phu cap", 0);
    nv.gioTangCaNgayThuong = NhapSoThuc(in, "Nhap gio tang ca ngay thuong: ", "So gio tang ca", 0);
    nv.gioTangCaCuoiTuan = NhapSoThuc(in, "Nhap gio tang ca cuoi tuan: ", "So gio tang ca", 0);
    nv.gioTangCaLeTet = NhapSoThuc(in, "Nhap gio tang ca le/tet: ", "So gio tang ca", 0);
    return in;
}

ostream& operator<<(ostream& out, const NhanVienVanPhong& nv) {
    ios_base::fmtflags f = out.flags();
    out << left;
    out << setw(24) << "Thang tinh luong" << ": " << nv.thangTinhLuong << "\n";
    out << setw(24) << "Nam tinh luong" << ": " << nv.namTinhLuong << "\n";
    out << setw(24) << "So ngay lam viec" << ": " << nv.soNgayLamViec << "\n";
    out << setw(24) << "So ngay le/tet" << ": " << nv.soNgayLe << "\n";
    out << setw(24) << "Don gia ngay" << ": " << DinhDangTien(nv.donGiaNgay) << " VND\n";
    out << setw(24) << "Phu cap" << ": " << DinhDangTien(nv.phuCap) << " VND\n";
    out << setw(24) << "Tang ca ngay thuong" << ": " << SoThucChuoi(nv.gioTangCaNgayThuong) << " gio\n";
    out << setw(24) << "Tang ca cuoi tuan" << ": " << SoThucChuoi(nv.gioTangCaCuoiTuan) << " gio\n";
    out << setw(24) << "Tang ca le/tet" << ": " << SoThucChuoi(nv.gioTangCaLeTet) << " gio\n";
    out.flags(f);
    return out;
}