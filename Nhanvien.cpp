#include "NhanVien.h"

// ===================== HAM TIEN ICH =====================
bool TachNgaySinh(const string& ns, int& ngay, int& thang, int& nam) {
    if (ns.length() != 10 || ns[2] != '/' || ns[5] != '/') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (ns[i] < '0' || ns[i] > '9') {
                return false;
            }
        }
    }
    ngay = stoi(ns.substr(0, 2));
    thang = stoi(ns.substr(3, 2));
    nam = stoi(ns.substr(6, 4));
    return true;
}

int SoNgayTrongThang(int thang, int nam) {
    if (thang == 2) {
        if (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0)) {
            return 29;
        }
        return 28;
    }
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        return 30;
    }
    return 31;
}

bool KiemTraNgaySinh(string ns) {
    int ngay, thang, nam;
    if (!TachNgaySinh(ns, ngay, thang, nam)) {
        return false;
    }
    if (thang < 1 || thang > 12 || nam < 1) {
        return false;
    }
    return ngay >= 1 && ngay <= SoNgayTrongThang(thang, nam);
}

int TinhTuoi(const string& ngaySinh) {
    int ngay, thang, nam;
    if (!TachNgaySinh(ngaySinh, ngay, thang, nam)) {
        return -1;
    }
    int hNgay, hThang, hNam;
    LayNgayHienTai(hNgay, hThang, hNam);
    int tuoi = hNam - nam;
    if (hThang < thang || (hThang == thang && hNgay < ngay)) {
        tuoi--;
    }
    return tuoi;
}

string TenChucVu(int cv) {
    switch (cv) {
    case CV_VAN_PHONG: return "Nhan vien Van Phong";
    case CV_SAN_XUAT:  return "Nhan vien San Xuat";
    case CV_QUAN_LY:   return "Quan Ly";
    }
    return "Khong xac dinh";
}

string TenChucVuNgan(int cv) {
    switch (cv) {
    case CV_VAN_PHONG: return "Nhan vien VP";
    case CV_SAN_XUAT:  return "Nhan vien SX";
    case CV_QUAN_LY:   return "Quan Ly";
    }
    return "?";
}

// ===================== GETTER / SETTER =====================
string NhanVien::getMaNV() const { return maNV; }
string NhanVien::getHoTen() const { return hoTen; }
string NhanVien::getNgaySinh() const { return ngaySinh; }
string NhanVien::getDiaChi() const { return diaChi; }

void NhanVien::setMaNV(string ma) { maNV = ma; }
void NhanVien::setHoTen(string ten) { hoTen = ten; }
void NhanVien::setNgaySinh(string ns) { ngaySinh = ns; }
void NhanVien::setDiaChi(string dc) { diaChi = dc; }

// ===================== CONSTRUCTOR =====================
NhanVien::NhanVien() {
    maNV = ""; hoTen = ""; ngaySinh = ""; diaChi = "";
}

NhanVien::NhanVien(string ma, string ten, string ns, string dc) {
    maNV = ma; hoTen = ten; ngaySinh = ns; diaChi = dc;
}

NhanVien::NhanVien(const NhanVien& nv) {
    maNV = nv.maNV; hoTen = nv.hoTen; ngaySinh = nv.ngaySinh; diaChi = nv.diaChi;
}

int NhanVien::Tuoi() const { return TinhTuoi(ngaySinh); }

int NhanVien::ThangSinh() const {
    int ngay, thang, nam;
    return TachNgaySinh(ngaySinh, ngay, thang, nam) ? thang : 0;
}

// ===================== NHAP / XUAT =====================
// Luu y: KHONG con hoi ma nhan vien o day. Ma do ham them nhan vien nhap va kiem tra trung.
istream& operator>>(istream& in, NhanVien& nv) {
    cout << "(VD: Nguyen Van A)\n";
    nv.hoTen = ChuanHoaTen(NhapChuoi(in, "Nhap ho ten: ", "Ho ten", 60));

    while (true) {
        cout << "(VD: 29/10/2005 - nhan vien phai tu "
            << CauHinh::TUOI_TOI_THIEU << " tuoi tro len)\n";
        cout << "Nhap ngay sinh: ";
        string ns = Trim(DocDong(in));

        if (!KiemTraNgaySinh(ns)) {
            InMau("Ngay sinh khong hop le! Vui long nhap lai (dinh dang dd/mm/yyyy).\n", MAU_DO);
            continue;
        }
        int tuoi = TinhTuoi(ns);
        if (tuoi < CauHinh::TUOI_TOI_THIEU) {
            InMau("Nhan vien phai tu " + to_string(CauHinh::TUOI_TOI_THIEU) +
                " tuoi tro len (hien chi " + to_string(tuoi < 0 ? 0 : tuoi) + " tuoi)!\n", MAU_DO);
            continue;
        }
        if (tuoi > CauHinh::TUOI_TOI_DA) {
            InMau("Tuoi khong hop le (lon hon " + to_string(CauHinh::TUOI_TOI_DA) + ")!\n", MAU_DO);
            continue;
        }
        nv.ngaySinh = ns;
        break;
    }

    cout << "(VD: TP.HCM)\n";
    nv.diaChi = NhapChuoi(in, "Nhap dia chi: ", "Dia chi", 100);
    return in;
}

ostream& operator<<(ostream& out, const NhanVien& nv) {
    ios_base::fmtflags f = out.flags();
    out << left;
    out << setw(24) << "Ma nhan vien" << ": " << nv.maNV << "\n";
    out << setw(24) << "Ho ten" << ": " << nv.hoTen << "\n";
    out << setw(24) << "Ngay sinh" << ": " << nv.ngaySinh << " (" << nv.Tuoi() << " tuoi)\n";
    out << setw(24) << "Dia chi" << ": " << nv.diaChi << "\n";
    out << setw(24) << "Tien luong" << ": " << DinhDangTien(nv.TinhLuong()) << " VND\n";
    out.flags(f);
    return out;
}

bool NhanVien::operator<(const NhanVien& other) const { return TinhLuong() < other.TinhLuong(); }
bool NhanVien::operator==(const NhanVien& other) const { return maNV == other.maNV; }

void NhanVien::HienThiThongTin() const { cout << *this; }

// ===================== PHIEU LUONG (Template Method) =====================
void NhanVien::InPhieuLuong(ostream& out) const {
    ios_base::fmtflags f = out.flags();          // khoi phuc dinh dang cua luong khi ket thuc
    const string vachDoi(66, '=');
    const string vachDon(66, '-');
    out << "\n" << vachDoi << "\n";
    out << right << setw(38) << "PHIEU LUONG" << "\n";
    out << vachDoi << "\n";
    out << left << setw(14) << "Ma nhan vien" << ": " << maNV << "\n";
    out << setw(14) << "Ho ten" << ": " << hoTen << "\n";
    out << setw(14) << "Chuc vu" << ": " << TenChucVu(LayChucVu()) << "\n";
    out << vachDon << "\n";
    InCacKhoanLuong(out);                                    // phan thay doi theo lop con
    out << vachDon << "\n";
    InDongPhieu(out, "TONG LUONG", TinhLuong());
    out << vachDoi << "\n";
    out.flags(f);
}

// ===================== GHI / NAP TEP =====================
void NhanVien::GhiChung(ostream& out) const {
    const char c = CauHinh::DAU_PHAN_CACH;
    out << LayChucVu() << c << maNV << c << hoTen << c << ngaySinh << c << diaChi;
}

void NhanVien::NapChung(const vector<string>& cot) {
    if (cot.size() < 5) {
        throw LoiDuLieu("Thieu cot du lieu chung");
    }
    string ma = Trim(cot[1]);
    string ten = Trim(cot[2]);
    string ns = Trim(cot[3]);
    string dc = Trim(cot[4]);
    if (ma.empty())  throw LoiDuLieu("Ma nhan vien rong");
    if (ten.empty()) throw LoiDuLieu("Ho ten rong");
    if (!KiemTraNgaySinh(ns)) throw LoiDuLieu("Ngay sinh khong hop le: '" + ns + "'");
    maNV = ma; hoTen = ten; ngaySinh = ns; diaChi = dc;
}