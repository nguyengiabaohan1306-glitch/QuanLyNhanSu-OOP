#include "DanhSachNhanSu.h"
#include "NhanVienVanPhong.h"
#include "NhanVienSanXuat.h"
#include "QuanLy.h"
#include <fstream>

// ===================== NHAP MA NHAN VIEN =====================
// Ma hop le: tien to (VP/SX/QL) + 1 den 8 chu so, vi du VP01
bool HopLeMa(const string& ma, const string& tienTo) {
    if (ma.size() < tienTo.size() + 1 || ma.size() > 10) return false;
    if (ma.compare(0, tienTo.size(), tienTo) != 0) return false;
    for (size_t i = tienTo.size(); i < ma.size(); i++) {
        if (!isdigit((unsigned char)ma[i])) return false;
    }
    return true;
}

string NhapMaMoi(const DanhSachNhanSu& ds, const string& tienTo, const string& vdMa) {
    while (true) {
        cout << "(" << vdMa << ")\n";
        cout << "Nhap ma nhan vien: ";
        string ma = VietHoa(Trim(DocDong(cin)));

        if (!HopLeMa(ma, tienTo)) {
            InMau("-> Loi: Ma phai bat dau bang '" + tienTo + "' va theo sau la cac chu so (VD: " +
                tienTo + "01)!\n", MAU_DO);
        }
        else if (ds.TonTai(ma)) {
            InMau("-> Loi: Ma nhan vien '" + ma + "' da ton tai! Vui long nhap ma khac.\n", MAU_DO);
        }
        else {
            return ma;
        }
    }
}

string NhapMaCanTim(const string& loiMoi) {
    cout << "(VD: VP01, SX01, QL01...)\n";
    cout << loiMoi;
    return VietHoa(Trim(DocDong(cin)));
}

// ===================== 1-3. THEM NHAN VIEN (template) =====================
template <typename T>
void ThemNhanVien(DanhSachNhanSu& ds, const string& tienTo, const string& tenChucVu) {
    DoiMau(MAU_VANG);
    cout << "\n--- NHAP THONG TIN " << tenChucVu << " ---\n";
    ResetMau();

    string ma = NhapMaMoi(ds, tienTo, "VD: " + tienTo + "01, " + tienTo + "02...");

    T* nv = new T();                 // cap phat thu cong, phai tu delete neu khong them duoc
    try {
        nv->setMaNV(ma);
        cin >> *nv;                  // operator>> rieng cua tung lop con
    }
    catch (...) {                    // vd: NgungNhap khi bam Ctrl+Z giua chung
        delete nv;                   // giai phong truoc khi ne tiep, tranh ro ri bo nho
        throw;                       // nem tiep de main xu ly
    }

    ds.Them(nv);                     // tu day danh sach so huu nv, danh sach se delete
    InMau("-> Them " + tenChucVu + " thanh cong!\n", MAU_XANH_LA);
}

// ===================== 4. XUAT DANH SACH =====================
void XuatDanhSach(const DanhSachNhanSu& ds) {
    DanhSachNhanSu::InBang(ds.TatCa(), "DANH SACH TOAN BO NHAN SU");
}

// ===================== 5. TIM THEO MA =====================
void TimVaXuatNhanVien(const DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach trong!\n", MAU_DO);
        return;
    }
    string ma = NhapMaCanTim("\nNhap ma nhan vien can tim: ");
    const NhanVien* nv = ds.TimTheoMa(ma);
    if (nv != nullptr) {
        InMau("\n-> Tim thay nhan vien:\n", MAU_XANH_LA);
        nv->HienThiThongTin();
        cout << endl;
    }
    else {
        InMau("-> Khong tim thay nhan vien co ma: " + ma + "\n", MAU_DO);
    }
}

// ===================== 6. LOC THEO CHUC VU =====================
void LocNhanVienTheoChucVu(const DanhSachNhanSu& ds) {
    DoiMau(MAU_VANG);
    cout << "\n===== LOC NHAN VIEN THEO CHUC VU =====\n";
    DoiMau(MAU_XANH_NGOC);
    cout << "1. Nhan vien van phong\n";
    cout << "2. Nhan vien san xuat\n";
    cout << "3. Quan ly\n";
    ResetMau();
    int chon = NhapSoNguyen(cin, "Nhap chuc vu can loc: ", "Chuc vu", 1, 3);

    vector<const NhanVien*> dsLoc = ds.LocTheoChucVu(chon);
    if (dsLoc.empty()) {
        InMau("Khong co nhan vien thuoc chuc vu nay!\n", MAU_DO);
        return;
    }

    string tieuDe;
    if (chon == CV_VAN_PHONG)    tieuDe = "DANH SACH NHAN VIEN VAN PHONG";
    else if (chon == CV_SAN_XUAT) tieuDe = "DANH SACH NHAN VIEN SAN XUAT";
    else                          tieuDe = "DANH SACH QUAN LY";
    DanhSachNhanSu::InBang(dsLoc, tieuDe);
}

// ===================== 7. XOA / CAP NHAT =====================
void XoaNhanVienTheoMa(DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    string ma = NhapMaCanTim("Nhap ma nhan vien can xoa: ");
    if (ds.Xoa(ma)) {
        InMau("-> Da xoa thanh cong nhan vien co ma: " + ma + "\n", MAU_XANH_LA);
    }
    else {
        InMau("-> Khong tim thay nhan vien co ma: " + ma + " de xoa!\n", MAU_DO);
    }
}

void CapNhatThongTinNhanVien(DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    string ma = NhapMaCanTim("Nhap ma nhan vien can cap nhat thong tin: ");
    NhanVien* nv = ds.TimTheoMa(ma);
    if (nv == nullptr) {
        InMau("-> Khong tim thay nhan vien co ma: " + ma + " de cap nhat!\n", MAU_DO);
        return;
    }
    InMau("\n-> Da tim thay nhan vien. Nhap lai thong tin moi (ma nhan vien giu nguyen):\n", MAU_XANH_LA);
    nv->NhapLai();                  // da hinh: goi dung operator>> cua lop con
    ds.DanhDauThayDoi();
    InMau("-> Cap nhat thong tin nhan vien thanh cong!\n", MAU_XANH_LA);
}

void XoaHoacCapNhatNhanVien(DanhSachNhanSu& ds) {
    DoiMau(MAU_VANG);
    cout << "\n=================== XOA HOAC CAP NHAT THONG TIN NHAN VIEN ===================\n";
    DoiMau(MAU_XANH_NGOC);
    cout << "1. Xoa nhan vien theo ma\n";
    cout << "2. Cap nhat thong tin nhan vien theo ma\n";
    DoiMau(MAU_DO);
    cout << "0. Quay lai menu chinh\n";
    DoiMau(MAU_VANG);
    cout << "=================================================\n";
    ResetMau();
    int chon = NhapSoNguyen(cin, "Nhap lua chon cua ban: ", "Lua chon", 0, 2);

    switch (chon) {
    case 1: XoaNhanVienTheoMa(ds); break;
    case 2: CapNhatThongTinNhanVien(ds); break;
    default: break;
    }
}

// ===================== 8. SAP XEP =====================
void SapXepTheoLuong(DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    DoiMau(MAU_VANG);
    cout << "\n===== SAP XEP NHAN VIEN THEO LUONG =====\n";
    DoiMau(MAU_XANH_NGOC);
    cout << "1. Tang dan\n";
    cout << "2. Giam dan\n";
    ResetMau();
    int chon = NhapSoNguyen(cin, "Nhap lua chon (1-2): ", "Lua chon", 1, 2);

    ds.SapXepTheoLuong(chon == 1);
    InMau("\n-> Da sap xep danh sach thanh cong!\n", MAU_XANH_LA);
    XuatDanhSach(ds);
}

// ===================== 9. TIM KIEM NANG CAO =====================
void TimKiemNangCao(const DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    DoiMau(MAU_VANG);
    cout << "\n===== TIM KIEM NANG CAO =====\n";
    DoiMau(MAU_XANH_NGOC);
    cout << "1. Tim theo ho ten (chi can nhap mot phan)\n";
    cout << "2. Tim theo khoang luong\n";
    DoiMau(MAU_DO);
    cout << "0. Quay lai menu chinh\n";
    ResetMau();
    int chon = NhapSoNguyen(cin, "Nhap lua chon cua ban: ", "Lua chon", 0, 2);

    if (chon == 1) {
        cout << "Nhap tu khoa ho ten: ";
        string tuKhoa = Trim(DocDong(cin));
        vector<const NhanVien*> kq = ds.TimTheoTen(tuKhoa);
        if (kq.empty()) {
            InMau("-> Khong tim thay nhan vien nao co ten chua '" + tuKhoa + "'\n", MAU_DO);
        }
        else {
            DanhSachNhanSu::InBang(kq, "KET QUA TIM THEO TEN: " + tuKhoa);
        }
    }
    else if (chon == 2) {
        double tu = NhapSoThuc(cin, "Nhap luong tu: ", "Luong tu", 0);
        double den = NhapSoThuc(cin, "Nhap luong den: ", "Luong den", tu, false);
        vector<const NhanVien*> kq = ds.LocTheoKhoangLuong(tu, den);
        if (kq.empty()) {
            InMau("-> Khong co nhan vien nao co luong trong khoang nay!\n", MAU_DO);
        }
        else {
            DanhSachNhanSu::InBang(kq, "LUONG TU " + DinhDangTien(tu) + " DEN " + DinhDangTien(den));
        }
    }
}

// ===================== 10. THONG KE =====================
void ThongKe(const DanhSachNhanSu& ds) {
    ds.InThongKe();
}

// ===================== 11. PHIEU LUONG =====================
void InPhieuLuongNhanVien(const DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    string ma = NhapMaCanTim("Nhap ma nhan vien can in phieu luong: ");
    const NhanVien* nv = ds.TimTheoMa(ma);
    if (nv == nullptr) {
        InMau("-> Khong tim thay nhan vien co ma: " + ma + "\n", MAU_DO);
        return;
    }
    DoiMau(MAU_VANG);
    nv->InPhieuLuong();              // Template Method: khung chung, khoan luong theo lop con
    ResetMau();
}

// ===================== 12. SINH NHAT TRONG THANG =====================
void SinhNhatTrongThang(const DanhSachNhanSu& ds) {
    if (ds.Rong()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }
    int thang = NhapSoNguyen(cin, "Nhap thang (1-12, nhap 0 de chon thang hien tai): ", "Thang", 0, 12);
    if (thang == 0) {
        int ngay, nam;
        LayNgayHienTai(ngay, thang, nam);
    }
    vector<const NhanVien*> kq = ds.SinhNhatTrongThang(thang);
    if (kq.empty()) {
        InMau("-> Khong co nhan vien nao sinh nhat trong thang " + to_string(thang) + "\n", MAU_DO);
    }
    else {
        DanhSachNhanSu::InBang(kq, "SINH NHAT THANG " + to_string(thang));
    }
}

// ===================== 13-14. LUU / DOC TEP =====================
void LuuDuLieu(DanhSachNhanSu& ds) {
    try {
        ds.LuuTep(CauHinh::TEP_MAC_DINH);
        InMau("-> Da luu " + to_string(ds.SoLuong()) + " nhan vien vao tep '" +
            CauHinh::TEP_MAC_DINH + "'\n", MAU_XANH_LA);
    }
    catch (const LoiDuLieu& e) {
        InMau(string("-> Loi: ") + e.what() + "\n", MAU_DO);
    }
}

void DocDuLieu(DanhSachNhanSu& ds, bool hoiXacNhan) {
    if (hoiXacNhan && !ds.Rong() &&
        !NhapCoKhong(cin, "Danh sach hien tai se bi thay the. Tiep tuc? (y/n): ")) {
        return;
    }
    try {
        int soLoi = 0;
        int soDoc = ds.DocTep(CauHinh::TEP_MAC_DINH, soLoi);
        InMau("-> Da doc " + to_string(soDoc) + " nhan vien tu tep '" + CauHinh::TEP_MAC_DINH + "'", MAU_XANH_LA);
        if (soLoi > 0) {
            InMau(" (" + to_string(soLoi) + " dong loi da bo qua)", MAU_VANG);
        }
        cout << endl;
    }
    catch (const LoiDuLieu& e) {
        InMau(string("-> Loi: ") + e.what() + "\n", MAU_DO);
    }
}

// ===================== MENU =====================
void InMenu() {
    DoiMau(MAU_VANG);
    cout << "\n=================== CHUONG TRINH QUAN LY NHAN SU ===================\n";
    DoiMau(MAU_XANH_NGOC);
    cout << " 1. Them nhan vien Van Phong\n";
    cout << " 2. Them nhan vien San Xuat\n";
    cout << " 3. Them Quan Ly\n";
    cout << " 4. Xuat toan bo danh sach nhan vien\n";
    cout << " 5. Tim kiem thong tin nhan vien theo ma\n";
    cout << " 6. Loc nhan vien theo chuc vu\n";
    cout << " 7. Xoa hoac cap nhat thong tin nhan vien theo ma\n";
    cout << " 8. Sap xep danh sach nhan vien theo tien luong\n";
    cout << " 9. Tim kiem nang cao (theo ten, theo khoang luong)\n";
    cout << "10. Thong ke nhan su\n";
    cout << "11. In phieu luong cua mot nhan vien\n";
    cout << "12. Nhan vien sinh nhat trong thang\n";
    cout << "13. Luu danh sach ra tep\n";
    cout << "14. Doc danh sach tu tep\n";
    DoiMau(MAU_DO);
    cout << " 0. Thoat chuong trinh\n";
    DoiMau(MAU_VANG);
    cout << "====================================================================\n";
    ResetMau();
}

int main() {
    DanhSachNhanSu dsNhanVien;
    int chon = -1;

    try {
        // Tu dong nap du lieu cu neu da co tep
        if (ifstream(CauHinh::TEP_MAC_DINH).good()) {
            DocDuLieu(dsNhanVien, false);
        }

        do {
            InMenu();
            chon = NhapSoNguyen(cin, "Nhap lua chon cua ban: ", "Lua chon", 0, 14);

            switch (chon) {
            case 1: ThemNhanVien<NhanVienVanPhong>(dsNhanVien, "VP", "NHAN VIEN VAN PHONG"); break;
            case 2: ThemNhanVien<NhanVienSanXuat>(dsNhanVien, "SX", "NHAN VIEN SAN XUAT"); break;
            case 3: ThemNhanVien<QuanLy>(dsNhanVien, "QL", "QUAN LY"); break;
            case 4: XuatDanhSach(dsNhanVien); break;
            case 5: TimVaXuatNhanVien(dsNhanVien); break;
            case 6: LocNhanVienTheoChucVu(dsNhanVien); break;
            case 7: XoaHoacCapNhatNhanVien(dsNhanVien); break;
            case 8: SapXepTheoLuong(dsNhanVien); break;
            case 9: TimKiemNangCao(dsNhanVien); break;
            case 10: ThongKe(dsNhanVien); break;
            case 11: InPhieuLuongNhanVien(dsNhanVien); break;
            case 12: SinhNhatTrongThang(dsNhanVien); break;
            case 13: LuuDuLieu(dsNhanVien); break;
            case 14: DocDuLieu(dsNhanVien, true); break;
            case 0:
                if (dsNhanVien.DaThayDoi() &&
                    NhapCoKhong(cin, string("Du lieu da thay doi. Luu vao tep '") +
                        CauHinh::TEP_MAC_DINH + "' truoc khi thoat? (y/n): ")) {
                    LuuDuLieu(dsNhanVien);
                }
                InMau("\nDang thoat chuong trinh. Tam biet!\n", MAU_VANG);
                break;
            }
        } while (chon != 0);
    }
    catch (const NgungNhap&) {
        InMau("\nKhong con du lieu nhap. Thoat chuong trinh.\n", MAU_VANG);
    }

    ResetMau();
    return 0;      
}
