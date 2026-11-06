#include "QuanLy.h"

QuanLy::QuanLy() : NhanVien() {
    luongCoBan = 0; heSoTrachNhiem = 0;
}

QuanLy::QuanLy(string ma, string ten, string ns, string dc, double luongCB, double heSo)
    : NhanVien(ma, ten, ns, dc) {
    luongCoBan = luongCB; heSoTrachNhiem = heSo;
}

double QuanLy::getLuongCoBan() const { return luongCoBan; }
void QuanLy::setLuongCoBan(double luongCB) { luongCoBan = luongCB; }
double QuanLy::getHeSoTrachNhiem() const { return heSoTrachNhiem; }
void QuanLy::setHeSoTrachNhiem(double heSo) { heSoTrachNhiem = heSo; }

double QuanLy::TinhLuongTrachNhiem() const { return luongCoBan * heSoTrachNhiem; }
double QuanLy::TinhLuong() const { return luongCoBan + TinhLuongTrachNhiem(); }

istream& operator>>(istream& in, QuanLy& ql) {
    in >> static_cast<NhanVien&>(ql);

    cout << "(VD: 10000000)\n";
    ql.luongCoBan = NhapSoThuc(in, "Nhap luong co ban: ", "Luong co ban", 0);

    cout << "(VD: 1.5 - dung dau cham '.' hoac dau phay ',' cho so thap phan)\n";
    ql.heSoTrachNhiem = NhapSoThuc(in, "Nhap he so trach nhiem: ", "He so trach nhiem", 0);
    return in;
}

ostream& operator<<(ostream& out, const QuanLy& ql) {
    ios_base::fmtflags f = out.flags();
    out << left;
    out << setw(24) << "Luong co ban" << ": " << DinhDangTien(ql.luongCoBan) << " VND\n";
    out << setw(24) << "He so trach nhiem" << ": " << SoThucChuoi(ql.heSoTrachNhiem) << "\n";
    out << setw(24) << "Luong trach nhiem" << ": " << DinhDangTien(ql.TinhLuongTrachNhiem()) << " VND\n";
    out.flags(f);
    return out;
}

void QuanLy::HienThiThongTin() const {
    cout << "[Chuc vu: Quan Ly]\n";
    NhanVien::HienThiThongTin();
    cout << *this;
}

int QuanLy::LayChucVu() const { return CV_QUAN_LY; }

void QuanLy::NhapLai() { cin >> *this; }

void QuanLy::InCacKhoanLuong(ostream& out) const {
    InDongPhieu(out, "Luong co ban", luongCoBan);
    InDongPhieu(out, "Luong trach nhiem (he so " + SoThucChuoi(heSoTrachNhiem) + ")",
        TinhLuongTrachNhiem());
}

void QuanLy::GhiDuLieu(ostream& out) const {
    const char c = CauHinh::DAU_PHAN_CACH;
    GhiChung(out);
    out << c << SoThucChuoi(luongCoBan) << c << SoThucChuoi(heSoTrachNhiem) << "\n";
}

void QuanLy::NapDuLieu(const vector<string>& cot) {
    if (cot.size() != 7) {
        throw LoiDuLieu("Quan ly can 7 cot, co " + to_string(cot.size()));
    }
    QuanLy tam;
    tam.NapChung(cot);
    tam.luongCoBan = DocSoThuc(cot[5], "luong co ban");
    tam.heSoTrachNhiem = DocSoThuc(cot[6], "he so trach nhiem");
    if (tam.luongCoBan < 0 || tam.heSoTrachNhiem < 0)
        throw LoiDuLieu("Luong co ban / he so trach nhiem am");
    *this = tam;
}