#include "DanhSachNhanSu.h"
#include "NhanVienVanPhong.h"
#include "NhanVienSanXuat.h"
#include "QuanLy.h"
#include <fstream>

// ===================== HAM NOI BO (chi dung trong tep nay) =====================
namespace {

    // Chia chuoi thanh cac dong, moi dong toi da 'rong' ky tu, uu tien ngat o dau cach
    vector<string> ChiaDong(string s, int rong) {
        vector<string> kq;
        while ((int)s.size() > rong) {
            size_t cat = s.rfind(' ', rong);
            if (cat == string::npos || cat == 0) cat = rong;
            kq.push_back(s.substr(0, cat));
            s = s.substr(cat);
            while (!s.empty() && s[0] == ' ') s.erase(0, 1);
        }
        kq.push_back(s);
        return kq;
    }

    // Ve duong ke ngang: +-----+--------+----...+
    void KeDuongNgang(const int w[], int n) {
        DoiMau(MAU_VANG);
        cout << "+";
        for (int i = 0; i < n; i++) {
            cout << string(w[i] + 2, '-') << "+";
        }
        cout << endl;
    }

    int MauTheoChucVu(int cv) {
        if (cv == CV_VAN_PHONG) return MAU_XANH_NGOC;
        if (cv == CV_SAN_XUAT) return MAU_XANH_LA;
        if (cv == CV_QUAN_LY) return MAU_TIM;
        return MAU_TRANG;
    }

    // Nha may (Factory): tao doi tuong dung loai theo ma chuc vu trong tep
    NhanVien* TaoTheoLoai(int loai) {
        switch (loai) {
        case CV_VAN_PHONG: return new NhanVienVanPhong();
        case CV_SAN_XUAT:  return new NhanVienSanXuat();
        case CV_QUAN_LY:   return new QuanLy();
        }
        throw LoiDuLieu("Ma chuc vu khong hop le: " + to_string(loai));
    }

// ===================== THONG TIN CHUNG =====================
DanhSachNhanSu::DanhSachNhanSu() : daThayDoi(false) {}

size_t DanhSachNhanSu::SoLuong() const { return ds.size(); }
bool DanhSachNhanSu::Rong() const { return ds.empty(); }
bool DanhSachNhanSu::DaThayDoi() const { return daThayDoi; }
void DanhSachNhanSu::DanhDauThayDoi() { daThayDoi = true; }

// ===================== THEM / XOA / TRUY CAP =====================
DanhSachNhanSu::~DanhSachNhanSu() {
    for (size_t i = 0; i < ds.size(); i++) delete ds[i];
}

void DanhSachNhanSu::Them(NhanVien* nv) {
    ds.push_back(nv);
    daThayDoi = true;
}

bool DanhSachNhanSu::Xoa(const string& ma) {
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i]->getMaNV() == ma) {
            delete ds[i];                       // phải tự delete TRƯỚC khi erase
            ds.erase(ds.begin() + i);
            daThayDoi = true;
            return true;
        }
    }
    return false;
}

// ===================== TRUY VAN =====================
vector<const NhanVien*> DanhSachNhanSu::TatCa() const {
    vector<const NhanVien*> kq;
    for (size_t i = 0; i < ds.size(); i++) kq.push_back(ds[i].get());
    return kq;
}

vector<const NhanVien*> DanhSachNhanSu::LocTheoChucVu(int chucVu) const {
    vector<const NhanVien*> kq;
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i]->LayChucVu() == chucVu) kq.push_back(ds[i].get());
    }
    return kq;
}

// Tim mot phan ho ten, khong phan biet hoa thuong
vector<const NhanVien*> DanhSachNhanSu::TimTheoTen(const string& tuKhoa) const {
    vector<const NhanVien*> kq;
    string k = VietThuong(Trim(tuKhoa));
    if (k.empty()) return kq;
    for (size_t i = 0; i < ds.size(); i++) {
        if (VietThuong(ds[i]->getHoTen()).find(k) != string::npos) kq.push_back(ds[i].get());
    }
    return kq;
}

vector<const NhanVien*> DanhSachNhanSu::LocTheoKhoangLuong(double tu, double den) const {
    vector<const NhanVien*> kq;
    for (size_t i = 0; i < ds.size(); i++) {
        double l = ds[i]->TinhLuong();
        if (l >= tu && l <= den) kq.push_back(ds[i].get());
    }
    return kq;
}

vector<const NhanVien*> DanhSachNhanSu::SinhNhatTrongThang(int thang) const {
    vector<const NhanVien*> kq;
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i]->ThangSinh() == thang) kq.push_back(ds[i].get());
    }
    return kq;
}

// ===================== NGHIEP VU =====================
void DanhSachNhanSu::SapXepTheoLuong(bool tangDan) {
    // Dung toan tu < cua NhanVien (so sanh theo luong); stable_sort giu thu tu khi bang luong
    stable_sort(ds.begin(), ds.end(),
        [tangDan](const NhanVien* a, const NhanVien* b) {
            return tangDan ? (*a < *b) : (*b < *a);
        });
    daThayDoi = true;
}

void DanhSachNhanSu::InThongKe() const {
    if (ds.empty()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }

    int soLuong[4] = { 0, 0, 0, 0 };
    double tong[4] = { 0, 0, 0, 0 };
    double tongTatCa = 0;
    const NhanVien* cao = ds[0].get();
    const NhanVien* thap = ds[0].get();

    for (size_t i = 0; i < ds.size(); i++) {
        int cv = ds[i]->LayChucVu();
        double luong = ds[i]->TinhLuong();
        soLuong[cv]++;
        tong[cv] += luong;
        tongTatCa += luong;
        if (luong > cao->TinhLuong()) cao = ds[i].get();
        if (luong < thap->TinhLuong()) thap = ds[i].get();
    }

    const int w[4] = { 20, 10, 18, 18 };
    DoiMau(MAU_VANG);
    cout << "\n+" << string(w[0] + w[1] + w[2] + w[3] + 11, '-') << "+\n";
    cout << "|" << string(30, ' ') << "THONG KE NHAN SU" << string(31, ' ') << "|\n";
    KeDuongNgang(w, 4);
    DoiMau(MAU_VANG);  cout << "| ";
    DoiMau(MAU_TRANG); cout << left << setw(w[0]) << "Chuc vu";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << right << setw(w[1]) << "So luong";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << right << setw(w[2]) << "Tong luong";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << right << setw(w[3]) << "Luong trung binh";
    DoiMau(MAU_VANG);  cout << " |" << endl;
    KeDuongNgang(w, 4);

    for (int cv = CV_VAN_PHONG; cv <= CV_QUAN_LY; cv++) {
        string tb = soLuong[cv] > 0 ? DinhDangTien(tong[cv] / soLuong[cv]) : "-";
        DoiMau(MAU_VANG);  cout << "| ";
        DoiMau(MauTheoChucVu(cv)); cout << left << setw(w[0]) << TenChucVuNgan(cv);
        DoiMau(MAU_VANG);  cout << " | ";
        DoiMau(MauTheoChucVu(cv)); cout << right << setw(w[1]) << soLuong[cv];
        DoiMau(MAU_VANG);  cout << " | ";
        DoiMau(MauTheoChucVu(cv)); cout << right << setw(w[2]) << DinhDangTien(tong[cv]);
        DoiMau(MAU_VANG);  cout << " | ";
        DoiMau(MauTheoChucVu(cv)); cout << right << setw(w[3]) << tb;
        DoiMau(MAU_VANG);  cout << " |" << endl;
    }
    KeDuongNgang(w, 4);
    ResetMau();

    cout << left;
    cout << setw(26) << "Tong so nhan vien" << ": " << ds.size() << "\n";
    cout << setw(26) << "Tong quy luong" << ": " << DinhDangTien(tongTatCa) << " VND\n";
    cout << setw(26) << "Luong trung binh chung" << ": " << DinhDangTien(tongTatCa / ds.size()) << " VND\n";
    cout << setw(26) << "Luong cao nhat" << ": " << DinhDangTien(cao->TinhLuong()) << " VND ("
        << cao->getMaNV() << " - " << cao->getHoTen() << ")\n";
    cout << setw(26) << "Luong thap nhat" << ": " << DinhDangTien(thap->TinhLuong()) << " VND ("
        << thap->getMaNV() << " - " << thap->getHoTen() << ")\n";
    cout << right;
}

// ===================== TEP DU LIEU =====================
void DanhSachNhanSu::LuuTep(const string& duongDan) {
    ofstream f(duongDan);
    if (!f) {
        throw LoiDuLieu("Khong mo duoc tep de ghi: " + duongDan);
    }
    f << "# DU LIEU NHAN SU - moi dong: loai;ma;ho ten;ngay sinh;dia chi;...(du lieu rieng)\n";
    f << "# loai: 1 = Van phong, 2 = San xuat, 3 = Quan ly\n";
    for (size_t i = 0; i < ds.size(); i++) {
        ds[i]->GhiDuLieu(f);                     // da hinh: moi lop tu ghi phan cua minh
    }
    f.flush();
    if (!f) {
        throw LoiDuLieu("Loi khi ghi tep: " + duongDan);
    }
    daThayDoi = false;
}

int DanhSachNhanSu::DocTep(const string& duongDan, int& soDongLoi) {
    ifstream f(duongDan);
    if (!f) {
        throw LoiDuLieu("Khong mo duoc tep: " + duongDan);
    }

    vector<NhanVien*> moi; // Dùng vector chứa con trỏ thô
    soDongLoi = 0;
    int soDong = 0;
    string dong;

    while (getline(f, dong)) {
        soDong++;
        dong = Trim(dong);
        if (dong.empty() || dong[0] == '#') continue;

        try {
            vector<string> cot = TachChuoi(dong, CauHinh::DAU_PHAN_CACH);
            NhanVien* nv = TaoTheoLoai(DocSoNguyen(cot[0], "loai")); // Tạo bằng new NhanVien...
            nv->NapDuLieu(cot);

            for (size_t i = 0; i < moi.size(); i++) {
                if (moi[i]->getMaNV() == nv->getMaNV()) {
                    delete nv; // Xóa ngay nếu trùng mã để tránh rò rỉ bộ nhớ
                    throw LoiDuLieu("Trung ma nhan vien '" + nv->getMaNV() + "'");
                }
            }
            moi.push_back(nv);
        }
        catch (const LoiDuLieu& e) {
            soDongLoi++;
            InMau("  Dong " + to_string(soDong) + ": " + e.what() + " -> bo qua\n", MAU_DO);
        }
    }

    // Dọn dẹp danh sách cũ trên RAM trước khi gán danh sách mới đọc từ file
    for (size_t i = 0; i < ds.size(); i++) {
        delete ds[i];
    }
    ds = moi;     // Gán danh sách mới vào
    daThayDoi = false;
    return (int)ds.size();
}

// ===================== BANG EXCEL =====================
void DanhSachNhanSu::InBang(const vector<const NhanVien*>& danhSach, const string& tieuDe) {
    if (danhSach.empty()) {
        InMau("\nDanh sach nhan vien dang trong!\n", MAU_DO);
        return;
    }

    // Do rong noi dung tung cot: STT | Ma NV | Ho Ten | Chuc Vu | Tien Luong
    const int w[6] = { 5, 10, 25, 12, 16, 15 };
    const int soCot = 6;

    int tongRong = 1;
    for (int i = 0; i < soCot; i++) tongRong += w[i] + 3;

    // ===== Tieu de bang =====
    int le = (tongRong - 2 - (int)tieuDe.size()) / 2;
    if (le < 0) le = 0;
    int lePhai = tongRong - 2 - (int)tieuDe.size() - le;
    if (lePhai < 0) lePhai = 0;

    cout << endl;
    DoiMau(MAU_VANG);
    cout << "+" << string(tongRong - 2, '-') << "+" << endl;
    cout << "|" << string(le, ' ') << tieuDe << string(lePhai, ' ') << "|" << endl;

    // ===== Dong tieu de cot =====
    KeDuongNgang(w, soCot);
    DoiMau(MAU_VANG);  cout << "| ";
    DoiMau(MAU_TRANG); cout << left << setw(w[0]) << "STT";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << left << setw(w[1]) << "Ma NV";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << left << setw(w[2]) << "Ho Va Ten";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << left << setw(w[3]) << "Ngay Sinh";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << left << setw(w[4]) << "Chuc Vu";
    DoiMau(MAU_VANG);  cout << " | ";
    DoiMau(MAU_TRANG); cout << right << setw(w[5]) << "Tien Luong";
    DoiMau(MAU_VANG);  cout << " |" << endl;
    KeDuongNgang(w, soCot);

    // ===== Du lieu tung nhan vien =====
    for (int i = 0; i < (int)danhSach.size(); i++) {
        int cv = danhSach[i]->LayChucVu();            // da hinh
        int mauCV = MauTheoChucVu(cv);
        string tenCV = TenChucVuNgan(cv);
        string luong = DinhDangTien(danhSach[i]->TinhLuong());   // da hinh

        vector<string> dongTen = ChiaDong(danhSach[i]->getHoTen(), w[2]);

        for (int k = 0; k < (int)dongTen.size(); k++) {
            bool dongDau = (k == 0);

            DoiMau(MAU_VANG); cout << "| ";
            DoiMau(mauCV);    cout << left << setw(w[0]) << (dongDau ? to_string(i + 1) : "");
            DoiMau(MAU_VANG); cout << " | ";
            DoiMau(mauCV);    cout << left << setw(w[1]) << (dongDau ? danhSach[i]->getMaNV() : "");
            DoiMau(MAU_VANG); cout << " | ";
            DoiMau(mauCV);    cout << left << setw(w[2]) << dongTen[k];
            DoiMau(MAU_VANG); cout << " | ";
            DoiMau(mauCV);    cout << left << setw(w[3]) << (dongDau ? danhSach[i]->getNgaySinh() : "");
            DoiMau(MAU_VANG); cout << " | ";
            DoiMau(mauCV);    cout << left << setw(w[4]) << (dongDau ? tenCV : "");
            DoiMau(MAU_VANG); cout << " | ";
            DoiMau(mauCV);    cout << right << setw(w[5]) << (dongDau ? luong : "");
            DoiMau(MAU_VANG); cout << " |" << endl;
        }

        KeDuongNgang(w, soCot);
    }
    ResetMau();
}
