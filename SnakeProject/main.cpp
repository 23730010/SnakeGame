#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <random>

using namespace std;

#define dotToiDa 500
#define doDaiMacDinh 5
#define tocDoThap 400
#define tocDoTrungBinh 300
#define tocDoCao 150

void diChuyenCotDong(int cot, int dong);
struct Point
{
    int cot, dong;
};
// Hỗ trợ tiện thay đổi ngôn ngữ tại trạng thái
char trangThaiDung[17] = "Tạm Dừng!";
char trangThaiDangChoi[17] = "Đang Chơi!";
char trangThaiKetThuc[17] = "Kết Thúc!";
int capDo = 1;// 1- de, 2 - trung binh, 3 - kho
int diem = 0;
int diemCao = 0;
Point conMoi;
Point gocTraiTren;// góc trái trên
Point gocPhaiDuoi;// góc phải dưới
bool choPhepQuaTuong = false;
int doKho = 300;
int luotChoi = 0;
UINT oldcodepage;

class CONRAN;
void diChuyenCotDong(int cot, int dong);
void choiLai(CONRAN r);
bool ktConMoiTrungConRan(CONRAN r);
void veConMoi(CONRAN r);
void xoaConMoi();
void veGiaoDien(CONRAN*);
void veLaiDiemVienBiXoa(CONRAN);
void thaoTacPhimR(CONRAN*, int&);
void thaoTacPhimM(CONRAN*, int&);
void thaoTacPhimEsc();
void hienThiDiemCao();

void khiConRanPhamQuy(CONRAN);
Point layDiemTrungTam();
void veKhungVien();
void veBongDoKhungVien();
void inGiuaCot1Cot2(int cot1, int cot2, int dong, string noiDung);
void hienThiThongTin();
void capNhatDiem(int diem);
void hienTrangThai(char[]);
void hienBangThongBao(int cdBang, int crBang);
void xoaBangThongBao(int cdBang, int crBang);

class CONRAN
{
public:
    struct Point dotRan[dotToiDa];
    int doDai = doDaiMacDinh;
    int tocDo = tocDoThap;
    bool lonLen = false;
    CONRAN()
    {
        // Khoi tao khung vien gioi han ran di chuyen
        gocTraiTren.cot = 15;// tọa độ cột góc trái trên của khung trong chơi
        gocTraiTren.dong = 06;// tọa độ dòng góc trái trên của khung trò chơi
        gocPhaiDuoi.cot = 97;// tọa độ cột góc phải dưới của khung trò chơi
        gocPhaiDuoi.dong = 24;// tọa độ dòng góc phải dưới của khung trò chơi
        // Khoi tao con ran
        khoiTaoThanRan();
    }

    /**
    *   Khởi tạo thân rắn
    */
    void khoiTaoThanRan()
    {
        // điểm bắt đầu game, trung tam khung vien
        Point diemBatDau = layDiemTrungTam();
        /*
        Point diemBatDau;
        diemBatDau.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
        diemBatDau.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
        */

        // khởi tạo tọa độ cho các đốt của thân rắn, bao gom dau ran
        for(int i = 0; i < doDai; i++)
        {
            dotRan[i].cot = diemBatDau.cot--;
            dotRan[i].dong = diemBatDau.dong;
        }
    }
    /**
    *   Di chuyển
    */
    void diChuyen(int Huong)
    {
        if (!lonLen)
        {
            // xóa hiển thị đốt cuối cùng khi di chuyển
            xoaDotCuoi();
        }
        else
            lonLen = false;

        // vị trí đầu rẵn sẽ là vị trí thân rắn khi di chuyên
        diChuyenCotDong(dotRan[0].cot,dotRan[0].dong);
        cout << "+";

        for (int i = doDai-1; i>0; i--)
            dotRan[i] = dotRan[i-1];
        if (Huong==0) dotRan[0].cot = dotRan[0].cot + 1;// rẽ phải
        if (Huong==1) dotRan[0].dong = dotRan[0].dong + 1;// đi xuống
        if (Huong==2) dotRan[0].cot = dotRan[0].cot - 1;// rẽ trái
        if (Huong==3) dotRan[0].dong = dotRan[0].dong - 1;// đi lên

        // Điều chỉnh tọa độ nếu rắn đi qua tường
        if(choPhepQuaTuong)
            ranDiChuyenQuaTuong();
    }

    // Hàm điều chỉnh tọa độ khi rắn đi qua tường
    void ranDiChuyenQuaTuong()
    {
        // Kiểm tra xem đầu rắn có ra khỏi màn hình không
        if (dotRan[0].cot == gocTraiTren.cot )
            dotRan[0].cot = gocPhaiDuoi.cot - 1;
        else if (dotRan[0].cot == gocPhaiDuoi.cot )
            dotRan[0].cot = gocTraiTren.cot + 1;
        else if (dotRan[0].dong == gocTraiTren.dong )
            dotRan[0].dong = gocPhaiDuoi.dong - 1;
        else if (dotRan[0].dong == gocPhaiDuoi.dong )
            dotRan[0].dong = gocTraiTren.dong + 1;
    }
    /**
    *   vẽ con rắn
    */
    void veConRan()
    {
        diChuyenCotDong(dotRan[0].cot,dotRan[0].dong);
        cout << "O";
        for (int i = 1; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot,dotRan[i].dong);
            cout<<"+";
        }
    }
    /**
    *   vẽ thân rắn
    */
    void veThanRan()
    {
        for (int i = 1; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot,dotRan[i].dong);
            cout<<"+";
        }
    }
    /**
    *   vẽ đầu rắn
    */
    void veDauRan()
    {
        diChuyenCotDong(dotRan[0].cot,dotRan[0].dong);
        cout << "O";
    }
    /**
    *   xóa đốt cuối cùng
    */
    void xoaDotCuoi()
    {
        diChuyenCotDong(dotRan[doDai-1].cot, dotRan[doDai-1].dong);
        cout<< " ";
    }
    /**
    *   xóa con rắn
    */
    void xoaConRan()
    {
        for (int i = 0; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot,dotRan[i].dong);
            cout<<" ";
        }
    }
    /**
    *   vẽ con rắn chết
    */
    void veConRanChet()
    {
        // Ve minh khi chet
        for (int i = 1; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot, dotRan[i].dong);
            cout<< ".";
        }
        // Ve cai dau khi chet
        diChuyenCotDong(dotRan[0].cot, dotRan[0].dong);
        cout<< "*";
    }
    /**
    *   Kiểm tra con rắn phạm quy
    */
    bool ktConRanPhamQuy()
    {
        if (ktConRanChamKhung())
        {
            return true;
        }
        // Đầu rắn đốt[0] trùng với thân rắn từ đốt[1] đến đốt độ dài con rắn -1
        for (int i = 1; i < doDai; i++)
        {
            if(dotRan[0].cot == dotRan[i].cot && dotRan[0].dong == dotRan[i].dong)
                return true;
        }
        return false;
    }
    /**
    *   Kiểm tra con rắn chạm khung
    */
    bool ktConRanChamKhung()
    {
        if (choPhepQuaTuong)
        {
            return false;
        }
        // Khi dau ran trùng -> Cot trai || cot phai || dong tren || dong duoi
        if(dotRan[0].cot == gocTraiTren.cot || dotRan[0].cot == gocPhaiDuoi.cot || dotRan[0].dong == gocTraiTren.dong || dotRan[0].dong == gocPhaiDuoi.dong)
            return true;
        return false;
    }
    /**
    *   Ăn con mồi
    */
    void anConMoi()
    {
        dotRan[doDai] = dotRan[doDai-1];
        doDai += 1;
        diem += 10;
        lonLen = true;
    }
    /**
    *   Kiểm tra rắn đụng con môi
    */
    bool ktDungConMoi()
    {
        if (dotRan[0].cot == conMoi.cot && dotRan[0].dong == conMoi.dong)
        {
            return true;
        }
        return false;
    }

};

/**
*   Di chuyển con trỏ tới vị trí dòng và cột
*/
void diChuyenCotDong(int cot, int dong)
{
    COORD coord;
    coord.X = cot;
    coord.Y = dong;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
*   Chơi lại
*   Làm mới các chỉ số của rắn tương ứng với loại trò chơi và độ khó
*/
void lamMoiRan(CONRAN *r)
{
    // làm mới các chỉ số
    r->xoaConRan();
    veLaiDiemVienBiXoa(*r);
    diem = 0;
    r->doDai = doDaiMacDinh;
    r->tocDo = doKho;
    r->khoiTaoThanRan();
    capNhatDiem(diem);
}

/**
* Kiểm tra con mồi được tạo có bị trung với con rắn không
*/
bool ktConMoiTrungConRan(CONRAN r)
{
    for (int i = 0; i < r.doDai; i++)
    {
        if (conMoi.cot == r.dotRan[i].cot && conMoi.dong == r.dotRan[i].dong)
            return true;
    }
    return false;
}

/**
* Vẽ con mồi
*/
void veConMoi(CONRAN r)
{
    srand(time(0));
    while(true)
    {
        // random tọa độ của con mồi
        conMoi.cot = (rand() % (gocPhaiDuoi.cot - gocTraiTren.cot - 1)) + gocTraiTren.cot + 1;
        conMoi.dong = (rand() % (gocPhaiDuoi.dong - gocTraiTren.dong - 1)) + gocTraiTren.dong + 1;

        // kiểm tra nếu tạo độ con mồi trùng với con rắn thì tạo lại
        if (ktConMoiTrungConRan(r))
        {
            continue;
        }

        break;
    }

    // di chuyển con trỏ tới tọa độ của con mồi để vẽ con mồi
    diChuyenCotDong(conMoi.cot, conMoi.dong);
    cout << "x";
}

/**
* xóa con mồi
*/
void xoaConMoi()
{
    diChuyenCotDong(conMoi.cot, conMoi.dong);
    cout << " ";
}

// Trả về điểm trung tâm khung viền
Point layDiemTrungTam()
{
    Point diemTT;
    diemTT.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
    diemTT.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
    return diemTT;
}

/**
In chuổi nội dung giữa cột 1 và 2 của 1 dòng
Nếu tiếng việt có dấu + thêm ký tự trắng cho số lần gõ dấu
*/

void inGiuaCot1Cot2(int cot1, int cot2, int dong, string noiDung)
{
    SetConsoleOutputCP(65001);
    int nuaDoan = round(abs(cot2 - cot1)/2);
    int nuaNoiDung = round(noiDung.length()/2);
    diChuyenCotDong(abs((cot1 + nuaDoan) - nuaNoiDung), dong);
    cout << noiDung;
}

/**
Vẽ cái khung chính cho trò chơi
*/

void veKhungVien(Point gocTrai, Point gocPhai, int netVien)
{
    SetConsoleOutputCP(oldcodepage);
    if(netVien == 1)
    {
        for (int i = gocTrai.cot + 1; i < gocPhai.cot; i++)
        {
            diChuyenCotDong(i, gocTrai.dong); // Dòng trên cùng
            cout << (char)196;
            diChuyenCotDong(i, gocPhai.dong); // Dòng dưới cùng
            cout << (char)196;
        }
        for (int i = gocTrai.dong + 1; i < gocPhai.dong; i++)
        {
            diChuyenCotDong(gocTrai.cot, i); // Cột bên trái
            cout << (char)179;
            diChuyenCotDong(gocPhai.cot, i); // Cột phải
            cout << (char)179;
        }
        // Vẽ 4 góc của khung
        diChuyenCotDong(gocTrai.cot, gocTrai.dong);
        cout << (char)218;
        diChuyenCotDong(gocPhai.cot, gocTrai.dong);
        cout << (char)191;
        diChuyenCotDong(gocTrai.cot, gocPhai.dong);
        cout << (char)192;
        diChuyenCotDong(gocPhai.cot, gocPhai.dong);
        cout << (char)217;
    }
    else if(netVien == 2)
    {
        for (int i = gocTrai.cot + 1; i < gocPhai.cot; i++)
        {
            diChuyenCotDong(i, gocTrai.dong); // Dòng trên cùng
            cout << (char)205;
            diChuyenCotDong(i, gocPhai.dong); // Dòng dưới cùng
            cout << (char)205;
        }
        for (int i = gocTrai.dong + 1; i < gocPhai.dong; i++)
        {
            diChuyenCotDong(gocTrai.cot, i); // Cột bên trái
            cout << (char)186;
            diChuyenCotDong(gocPhai.cot, i); // Cột phải
            cout << (char)186;
        }
        // Vẽ 4 góc của khung
        diChuyenCotDong(gocTrai.cot, gocTrai.dong);
        cout << (char)201;
        diChuyenCotDong(gocPhai.cot, gocTrai.dong);
        cout << (char)187;
        diChuyenCotDong(gocTrai.cot, gocPhai.dong);
        cout << (char)200;
        diChuyenCotDong(gocPhai.cot, gocPhai.dong);
        cout << (char)188;
    }
}

void veBongDoKhungVien()
{
    SetConsoleOutputCP(oldcodepage);
    for (int i = gocTraiTren.cot + 1; i <= gocPhaiDuoi.cot + 2; i++)
    {
        diChuyenCotDong(i, gocPhaiDuoi.dong + 1);  // Dòng đổ bóng dưới cùng
        cout << (char)176;
    }
    for (int i = gocTraiTren.dong + 1; i <= gocPhaiDuoi.dong; i++)
    {
        diChuyenCotDong(gocPhaiDuoi.cot + 1, i); // Cột đổ bóng bên phải 1
        cout << (char)176;
        diChuyenCotDong(gocPhaiDuoi.cot + 2, i); // Cột đổ bóng bên phải 2
        cout << (char)176;
    }
}

/*
Hàm hiển thị thông tin
*/
void hienThiThongTin()
{
    SetConsoleOutputCP(65001);
    // In logo
    inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong -3, "TIGER BẠC");
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong -2, "CN1.2023.1");
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong -1, "11/2023");
    // In giới thiệu
    inGiuaCot1Cot2(gocTraiTren.cot+8, gocPhaiDuoi.cot, gocTraiTren.dong -4, "CHƯƠNG TRÌNH RẮN SĂN MỒI");
    inGiuaCot1Cot2(gocTraiTren.cot, gocPhaiDuoi.cot, gocTraiTren.dong -3, "oOo");
    inGiuaCot1Cot2(gocTraiTren.cot+5, gocPhaiDuoi.cot, gocTraiTren.dong -2, "Nhóm SV thực hiện: <23730010><23730024><23730029><23730057><23730030>");
    inGiuaCot1Cot2(gocTraiTren.cot+16, gocPhaiDuoi.cot, gocTraiTren.dong -1, "[Võ Hùng Cường | Lê Hoàng Kim | Phạm Hoàng Long | Lê Hoàng Vũ | Nguyễn Lê Minh]");
}

void hienThiThongTin1()
{
    SetConsoleOutputCP(65001);
    // In thông báo điểm - độ khó - trạng thái
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong +2, "ĐIỂM");
    inGiuaCot1Cot2(3, gocTraiTren.cot, gocTraiTren.dong +5, "ĐỘ KHÓ");
    if(capDo == 1)
        inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong +6, "Dễ");
    else if(capDo == 2)
        inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong +6, "Trung Bình");
    else if(capDo == 3)
        inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong +6, "Khó");
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong + 8, "TRẠNG THÁI");
    hienTrangThai(trangThaiDangChoi);
    // In hướng dẫn
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong+3);
    cout<< "Phím Mũi tên hay <A-X-W-D> để Di chuyển";
    diChuyenCotDong(gocPhaiDuoi.cot -32, gocPhaiDuoi.dong +3);
    cout<< "<R> Chơi lại >><< Để gọi Menu <M>";
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong +4);
    cout<< "Dùng phím <SPACE> để Tạm dừng";
    diChuyenCotDong(gocPhaiDuoi.cot -23, gocPhaiDuoi.dong +4);
    cout<< "Dùng phím <ESC> để Thoát";
}

/**
* Hiển thị điểm hiện có
*/
void capNhatDiem(int diem)
{
    SetConsoleOutputCP(65001);
    // Xóa điểm cũ
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong +3, "    ");
    // Ghi điểm mới
    diChuyenCotDong(5, gocTraiTren.dong + 3);
    cout << " " << diem;
    //inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong +3, (char)diem);
}

/**
*
*/
void hienTrangThai(char trangThai[])
{
    //diChuyenCotDong(1, gocTraiTren.dong + 9);
    //cout << trangThai;
    SetConsoleOutputCP(65001);
    // Xóa trạng thái cũ
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong + 9, "          ");
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong + 9, trangThai);
}

/*
Hàm vẽ bảng thông báo
*/
void hienBangThongBao(int cdBang, int crBang, char *tieuDe, char *noiDung)
{
    Point gocTrai, gocPhai;
    Point diemGiua = layDiemTrungTam();
    gocTrai.cot = diemGiua.cot - cdBang/2;
    gocTrai.dong = diemGiua.dong - crBang/2;
    gocPhai.cot = diemGiua.cot + cdBang/2;
    gocPhai.dong = diemGiua.dong + crBang/2;
    SetConsoleOutputCP(oldcodepage);
    veKhungVien(gocTrai, gocPhai, 1);
    // Thông báo thua với tiêu đề và nội dung
    inGiuaCot1Cot2(gocTrai.cot +6, gocPhai.cot, gocTrai.dong, tieuDe); // Vì tiếng việt có 6 dấu
    // Nội dung trong bảng
    SetConsoleOutputCP(65001);
    diChuyenCotDong(gocTrai.cot +1,  gocTrai.dong +1);
    cout << noiDung;
}

/*
Xoá bảng thông báo
*/
void xoaBangThongBao(int cdBang, int crBang)
{
    Point diemGiua = layDiemTrungTam();
    for (int i = (diemGiua.dong - crBang/2); i < diemGiua.dong + crBang/2 + 2; i++)
    {
        diChuyenCotDong(diemGiua.cot - cdBang/2,i); // Cột bên trái
        cout<< "                         ";
    }
}

/*
Vẽ Menu cho trò chơi
*/
void veMenu()
{
    char x;
    system("cls");
    hienThiThongTin();
    // Vẽ khung viền nét đôi
    veKhungVien(gocTraiTren, gocPhaiDuoi, 2);
    veBongDoKhungVien();
    hienBangThongBao(22, 5, "Chọn chế độ chơi", "");
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong +9);
    cout << "1: Cổ điển" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong +10);
    cout << "2: Hiện đại" << endl;
    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong +3);
    cout << "Dùng phím số để chọn chế độ chơi";
    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong + 4);
    cout << "Dùng phím <ESC> để thoát chương trình" << endl;
    do
    {
        x = getch();
    }
    while(x != '1' && x != '2' && x!=27);

    if (x == '2')
    {
        choPhepQuaTuong = true;
    }
    else if (x == '1')
    {
        choPhepQuaTuong = false;
    }
    else if (x == 27)
    {
        system("cls");
        exit(0);
    }

    system("cls");
    hienThiThongTin();
    // Vẽ khung viền nét đôi
    veKhungVien(gocTraiTren, gocPhaiDuoi, 2);
    veBongDoKhungVien();
    hienBangThongBao(22, 6, "Chọn độ khó", "");
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong +8);
    cout << "1: Dễ" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong +9);
    cout << "2: Trung bình" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong +10);
    cout << "3: Khó" << endl;

    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong + 3);
    cout << "Dùng phím số để chọn độ khó";
    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong + 4);
    cout << "Dùng phím <ESC> để thoát chương trình" << endl;
    do
    {
        x = getch();
    }
    while(x != '1' && x != '2' & x != '3' && x != 27);

    if (x == '1')
    {
        capDo = 1;
        doKho = tocDoThap;
    }
    else if (x == '2')
    {
        capDo = 2;
        doKho = tocDoTrungBinh;
    }
    else if (x == '3')
    {
        capDo = 3;
        doKho = tocDoCao;
    }
    else if (x == 27)
    {
        system("cls");
        exit(0);
    }
    system("cls");
}
/**
*   vẽ lại điểm viền khung bị thay dổi khi rắn chạm viền
*/
void veLaiDiemVienBiXoa(CONRAN r)
{
    Point dauRan = r.dotRan[0];
    SetConsoleOutputCP(oldcodepage);
    diChuyenCotDong(dauRan.cot, dauRan.dong);
    if(dauRan.cot == gocTraiTren.cot)
    {
        cout << (char)186;
    }
    else if (dauRan.cot == gocPhaiDuoi.cot)
    {
        cout << (char)186;
    }
    else if(dauRan.dong == gocTraiTren.dong)
    {
        cout<< (char)205;
    }
    else if(dauRan.dong == gocPhaiDuoi.dong)
    {
        cout<< (char)205;
    }
    SetConsoleOutputCP(65001);
}
/**
* Khi con rắn phạm quy
*/
void khiConRanPhamQuy(CONRAN *r, int &Huong)
{
    Point diemGiua;
    char x;
    SetConsoleOutputCP(65001);
    luotChoi = luotChoi + 1;
    if (diem > diemCao)
        diemCao = diem;
    hienThiDiemCao();
    // Hiện con rắn chết
    r->veConRanChet();
    // Lấy tọa độ trung tâm khung viền trò chơi
    diemGiua = layDiemTrungTam();
    // Hiện thông báo chơi lại hay về menu chính giua man hinh
    hienBangThongBao(22, 3, "RẮN ĐÃ CHẾT..!", "R(Chơi lại) - M(Menu)");
    hienTrangThai(trangThaiKetThuc);
    do
    {
        x = getch();
    }
    while (x != 'r' && x != 'R' && x != 27 && x != 'm' && x != 'M');

    if (x=='r' || x=='R')
    {
        xoaBangThongBao(22, 3);
        thaoTacPhimR(r, Huong);
    }
    else if (x=='m' || x=='M')
    {
        thaoTacPhimM(r, Huong);
    }
    else if (x = 27)
    {
        system("cls");
        exit(0);
    }
}
/**
*   vẽ giao diện
*/
void veGiaoDien(CONRAN *r)
{
    system("cls");
    diem = 0;
    veMenu();
    hienThiThongTin();
    hienThiThongTin1();
    capNhatDiem(diem);
    hienThiDiemCao();
    //SetConsoleOutputCP(oldcodepage);
    // Vẽ khung viền nét đôi
    veKhungVien(gocTraiTren, gocPhaiDuoi, 2);
    veBongDoKhungVien();
}

/**
* tạm dừng
*/
void tamDung(CONRAN *r, int &Huong)
{
    SetConsoleOutputCP(65001);
    hienTrangThai(trangThaiDung);
    while(true)
    {
        char nhanPhim = getch();
        if (nhanPhim == ' ')
        {
            hienTrangThai(trangThaiDangChoi);
            return;

        }
        else if (nhanPhim=='r' || nhanPhim=='R')
        {
            thaoTacPhimR(r, Huong);
            return;
        }
        else if (nhanPhim=='m' || nhanPhim=='M')
        {
            thaoTacPhimM(r, Huong);
            return;
        }
        else if (nhanPhim = 27)
        {
            thaoTacPhimEsc();
        }
    }
}

/**
*   thao tác phím R
*/
void thaoTacPhimR(CONRAN *r, int &Huong)
{
    lamMoiRan(r);
    r->veThanRan();
    xoaConMoi();
    veConMoi(*r);
    Huong = 0;
    hienTrangThai(trangThaiDangChoi);
}
/**
*   Thao tác phím M
*/
void thaoTacPhimM(CONRAN *r, int &Huong)
{
    Huong = 0;
    lamMoiRan(r);
    veGiaoDien(r);
    r->tocDo = doKho;
    veConMoi(*r);
    r->veThanRan();
}
/**
*   thao tác phím Esc
*/
void thaoTacPhimEsc()
{
    system("cls");
    exit(0);
}
/**
*   hiện điểm cao nhât
*/
void hienThiDiemCao()
{
    SetConsoleOutputCP(65001);
    diChuyenCotDong(gocPhaiDuoi.cot + 4, 1);
    cout << "Điểm cao: " << diemCao << "/" << luotChoi;
}
/**
*   Ẩn con trỏ
*/
void anConTro()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
int main()
{
    CONRAN r;
    int Huong = 0;
    char t;
    oldcodepage = GetConsoleOutputCP();
    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
    // Ẩn con trỏ
    anConTro();
    veGiaoDien(&r);
    r.tocDo = doKho;
    veConMoi(r);
    r.veThanRan();
    while (1)
    {
        r.veDauRan();
        // Kiểm tra nếu rắn đụng biên hay cắn thân
        if (r.ktConRanPhamQuy())
        {
            khiConRanPhamQuy(&r, Huong);
        }
        Sleep(r.tocDo);
        if (kbhit())
        {
            t = getch();
            if ((t=='a' || t=='A' || t==75) && Huong != 0) Huong = 2;
            else if ((t=='w' || t=='W' || t==72) && Huong != 1) Huong = 3;
            else if ((t=='d' || t=='D' || t==77) && Huong != 2) Huong = 0;
            else if ((t=='s' || t=='S' || t==80) && Huong != 3) Huong = 1;
            else if (t == ' ') tamDung(&r, Huong);
            else if (t=='r' || t=='R')
            {
                thaoTacPhimR(&r, Huong);
            }
            else if (t=='m' || t == 'M')
            {
                thaoTacPhimM(&r, Huong);
            }
            else if (t==27)
            {
                thaoTacPhimEsc();
            }

        }
        if (r.ktDungConMoi())
        {
            r.anConMoi();
            veConMoi(r);
            capNhatDiem(diem);
            if (r.tocDo >= 100 && diem > 0 && diem%50 == 0)
            {
                r.tocDo -= 20;
            }
        }
        r.diChuyen(Huong);
    }
    return 0;
}
