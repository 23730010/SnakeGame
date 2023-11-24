#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <string.h>
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

char capDo = 1;// 1- de, 2 - trung binh, 3 - kho
//int doKho = 300;
int diem = 0;
Point conMoi;
Point gocTraiTren;// góc trái trên
Point gocPhaiDuoi;// góc phải dưới
bool choPhepXuyenTuong = false;

class CONRAN;
void diChuyenCotDong(int cot, int dong);
void choiLai(CONRAN r);
bool ktConMoiTrungConRan(CONRAN r);
void veConMoi(CONRAN r);
void xoaConMoi();
void khiConRanPhamQuy(CONRAN);
Point layDiemTrungTam();
void veGiaoDienChinh();
void veKhungVien();
void veBongDoKhungVien();
void hienThiThongTin();
void capNhatDiem(int diem);
void hienBangThongBao();
void xoaBangThongBao();

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
        gocTraiTren.cot = 17;// tọa độ cột góc trái trên của khung trong chơi
        gocTraiTren.dong = 05;// tọa độ dòng góc trái trên của khung trò chơi
        gocPhaiDuoi.cot = 92;// tọa độ cột góc phải dưới của khung trò chơi
        gocPhaiDuoi.dong = 24;// tọa độ dòng góc phải dưới của khung trò chơi
        // Khoi tao con ran
        khoiTaoThanRan();
    }

    /**
    * Khởi tạo thân rắn
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

    void diChuyen(int Huong)
    {
        for (int i = doDai-1; i>0; i--)
            dotRan[i] = dotRan[i-1];
        if (Huong==0) dotRan[0].cot = dotRan[0].cot + 1;
        if (Huong==1) dotRan[0].dong = dotRan[0].dong + 1;
        if (Huong==2) dotRan[0].cot = dotRan[0].dong - 1;
        if (Huong==3) dotRan[0].cot = dotRan[0].dong - 1;

    }

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

    // ran di chuyen de lai dot cuoi cung
    void xoaDotCuoi()
    {
        /*
        for (int i = 0; i < doDai; i++)
        {
            diChuyenCotDong(dotRan[i].cot, dotRan[i].dong);
            cout<< " ";
        }
        */
        // Cai tien
        diChuyenCotDong(dotRan[doDai-1].cot, dotRan[doDai-1].dong);
        cout<< " ";
    }

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

    bool ktConRanPhamQuy()
    {
        // Khi dau ran trùng -> Cot trai || cot phai || dong tren || dong duoi
        if(dotRan[0].cot == gocTraiTren.cot || dotRan[0].cot == gocPhaiDuoi.cot || dotRan[0].dong == gocTraiTren.dong || dotRan[0].dong == gocPhaiDuoi.dong)
            return true;
        // Dau ran la dot [0] trùng than tu dot [1] den do dai con ran -1
        for (int i = 1; i < doDai; i++)
        {
            if(dotRan[0].cot == dotRan[i].cot && dotRan[0].dong == dotRan[i].dong)
                return true;
        }
        return false;
    }
    /*
    bool ktDauChamVien()
    {
        // Cot trai || cot phai || dong tren || dong duoi
        if(dotRan[0].cot == gocTraiTren.cot || dotRan[0].cot == gocPhaiDuoi.cot || dotRan[0].dong == gocTraiTren.dong || dotRan[0].dong == gocPhaiDuoi.dong)
            return true;
        return false;
    }
    bool ktDauChamThan()
    {
        // Dau la dot [0], than tu dot [1] den do dai con ran -1
        for (int i = 1; i < doDai; i++)
        {
            if(dotRan[0].cot == dotRan[i].cot && dotRan[0].dong == dotRan[i].dong)
                return true;
        }
        return false;
    }
    */

    /**
    * Ăn con mồi
    */
    void anConMoi()
    {
        dotRan[doDai] = dotRan[doDai-1];
        doDai += 1;
        diem += 10;
        lonLen = true;
    }
};

/**
* Di chuyển con trỏ tới vị trí dòng và cột
*/
void diChuyenCotDong(int cot, int dong)
{
    COORD coord;
    coord.X = cot;
    coord.Y = dong;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**
* Chơi lại
* Làm mới các chỉ số của rắn tương ứng với loại trò chơi và độ khó
*/
void choiLai(CONRAN r)
{
    // làm mới các chỉ số
    diem = 0;
    r.doDai = doDaiMacDinh;
    if (capDo == 1)
    {
        r.tocDo = tocDoThap;
    }
    if (capDo == 2)
    {
        r.tocDo = tocDoTrungBinh;
    }
    if (capDo == 3)
    {
        r.tocDo = tocDoCao;
    }

    r.khoiTaoThanRan();
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

/*
Vẽ Menu cho trò chơi
*/

void veMenu(int &doKho)
{
    system("cls");
    int x;
    diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -3);
    cout<< "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    do
    {
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -2);
        cout << "Chọn chế độ chơi" << endl;
        diChuyenCotDong(gocTraiTren.cot + 35, gocPhaiDuoi.dong + 4);
        cout << "Dùng phím số để chọn chế độ chơi";
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -1);
        cout << "1: Cổ điển" << endl;
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong);
        cout << "2: Hiện đại" << endl;
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong + 1);
        x = getch();
        //cin >> x;
    }
    while(x != '1' && x != '2');

    if (x == '2')
        choPhepXuyenTuong = true;
    else
        choPhepXuyenTuong = false;

    system("cls");
    diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -3);
    cout<< "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    do
    {
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -2);
        cout << "Chọn độ khó" << endl;
        diChuyenCotDong(gocTraiTren.cot + 35, gocPhaiDuoi.dong + 4);
        cout << "Dùng phím số để chọn độ khó";
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong -1);
        cout << "1: Dễ" << endl;
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong);
        cout << "2: Trung bình" << endl;
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong + 1);
        cout << "3: Khó" << endl;
        diChuyenCotDong(gocTraiTren.cot + 40, gocTraiTren.dong + 2);
        capDo = getch();
        //cin >> capDo;
    }
    while(capDo != '1' && capDo != '2' & capDo != '3');

    if (capDo == '1')
    {
        doKho = 500;
    }
    if (capDo == '2')
    {
        doKho = 300;
    }
    if (capDo == '3')
    {
        doKho = 150;
    }
    system("cls");
}

/**
* tạm dừng
*/
bool tamDung()
{
    while(true)
    {
        char nhanPhim = getch();
        if (nhanPhim == ' ')
            return true;
        if (nhanPhim == 27) // ESC key
        {
            return false;
        }
    }
}


// Trả về điểm trung tâm của khung viền
Point layDiemTrungTam()
{
    Point diemTT;
    diemTT.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
    diemTT.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
    return diemTT;
}

/**
In chuổi giữa cột 1 và 2 của 1 dòng
*/

void inGiuaCot1Cot2(int cot1, int cot2, int dong, string noiDung)
{
    int nuaDoan = round(abs(cot2 - cot1)/2);
    int nuaNoiDung = round(noiDung.length()/2);
    diChuyenCotDong(abs((cot1 + nuaDoan) - nuaNoiDung), dong);
    cout << noiDung;
}

/**
Vẽ giao diện chính của trò chơi
*/

void veGiaoDienChinh()
{
    UINT oldcodepage = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);
    hienThiThongTin();
    SetConsoleOutputCP(oldcodepage);
    capNhatDiem(diem);
    veKhungVien();
    veBongDoKhungVien();
}

/**
Vẽ cái khung chính cho trò chơi
*/

void veKhungVien()
{
    for (int i = gocTraiTren.cot + 1; i < gocPhaiDuoi.cot; i++)
    {
        diChuyenCotDong(i, gocTraiTren.dong); // Dòng trên cùng
        cout << (char)205;
        diChuyenCotDong(i, gocPhaiDuoi.dong); // Dòng dưới cùng
        cout << (char)205;
    }
    for (int i = gocTraiTren.dong + 1; i < gocPhaiDuoi.dong; i++)
    {
        diChuyenCotDong(gocTraiTren.cot, i); // Cột bên trái
        cout << (char)186;
        diChuyenCotDong(gocPhaiDuoi.cot, i); // Cột phải
        cout << (char)186;
    }
    // Vẽ 4 góc của khung
    diChuyenCotDong(gocTraiTren.cot, gocTraiTren.dong);
    cout << (char)201;
    diChuyenCotDong(gocPhaiDuoi.cot, gocTraiTren.dong);
    cout << (char)187;
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong);
    cout << (char)200;
    diChuyenCotDong(gocPhaiDuoi.cot, gocPhaiDuoi.dong);
    cout << (char)188;
}

void veBongDoKhungVien()
{
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
    inGiuaCot1Cot2(gocTraiTren.cot+8, gocPhaiDuoi.cot, gocTraiTren.dong -4, "CHƯƠNG TRÌNH RẮN SĂN MỒI");
    inGiuaCot1Cot2(gocTraiTren.cot, gocPhaiDuoi.cot, gocTraiTren.dong -3, "oOo");
    inGiuaCot1Cot2(gocTraiTren.cot+5, gocPhaiDuoi.cot, gocTraiTren.dong -2, "Nhóm SV thực hiện: <23730010><23730024><23730029><23730057><23730030>");
    inGiuaCot1Cot2(gocTraiTren.cot+16, gocPhaiDuoi.cot, gocTraiTren.dong -1, "[Võ Hùng Cường | Lê Hoàng Kim | Phạm Hoàng Long | Lê Hoàng Vũ | Nguyễn Lê Minh]");
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong+3);
    cout<< "Phím Mũi tên hay <A-X-W-D> để Di chuyển";
    diChuyenCotDong(gocPhaiDuoi.cot -32, gocPhaiDuoi.dong +3);
    cout<< "<R> Chơi lại >><< Để gọi Menu <M>";
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong +4);
    cout<< "Dùng phím <SPACE> để Tạm dừng";
    diChuyenCotDong(gocPhaiDuoi.cot -23, gocPhaiDuoi.dong +4);
    cout<< "Dùng phím <ESC> để Thoát";
    // In logo
    inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong -3, "TIGER BẠC");
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong -2, "CN1.2023.1");
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong -1, "11/2023");
    // In thông báo điểm - độ khó - trạng thái
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong +2, "ĐIỂM");
    inGiuaCot1Cot2(3, gocTraiTren.cot, gocTraiTren.dong +5, "ĐỘ KHÓ");
    if(capDo == '1')
        inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong +6, "Dễ");
    else if(capDo == '2')
        inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong +6, "Trung Bình");
    else if(capDo == '3')
        inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong +6, "Khó");
    inGiuaCot1Cot2(2, gocTraiTren.cot, gocTraiTren.dong + 8, "TRẠNG THÁI");
    inGiuaCot1Cot2(1, gocTraiTren.cot, gocTraiTren.dong + 9, "Đang...");
}

/**
* Hiển thị điểm hiện có
*/

void capNhatDiem(int diem)
{
    // Xóa điểm cũ
    //diChuyenCotDong(4, gocTraiTren.dong +3);
    //cout << "   ";
    inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong +3, "    ");
    // Ghi điểm mới
    diChuyenCotDong(5, gocTraiTren.dong + 3);
    cout << " " << diem;
    //inGiuaCot1Cot2(0, gocTraiTren.cot, gocTraiTren.dong +3, (char)diem);
}

/*
Hàm vẽ bảng thông báo
*/

void hienBangThongBao()
{
    Point diemGiua = layDiemTrungTam();
    int cdBang = 22;
    int crBang = 3;
    for (int i = (diemGiua.cot - cdBang/2) + 1; i < diemGiua.cot+cdBang/2; i++)
    {
        diChuyenCotDong(i, diemGiua.cot - crBang/2); // Dòng trên
        cout << (char)196;
        diChuyenCotDong(i, diemGiua.dong+crBang/2); //Dòng dưới
        cout << (char)196;
    }

    for (int i = (diemGiua.dong - crBang/2)+1; i < diemGiua.dong + crBang/2; i++)
    {
        diChuyenCotDong(diemGiua.cot - cdBang/2,i); // Cột trái
        cout << (char)179;
        diChuyenCotDong(diemGiua.cot + cdBang/2, i); // Cột phải
        cout << (char)179;
    }

    // Vẽ 4 góc của khung viền thông báo
    diChuyenCotDong(diemGiua.cot - cdBang/2, diemGiua.dong- crBang/2);
    cout << (char)218;
    diChuyenCotDong(diemGiua.cot + cdBang/2, diemGiua.dong - crBang/2);
    cout << (char)191;
    diChuyenCotDong(diemGiua.cot - cdBang/2, diemGiua.dong + crBang/2);
    cout << (char)192;
    diChuyenCotDong(diemGiua.cot + cdBang/2, diemGiua.dong + crBang/2);
    cout << (char)217;

    // Thông báo thua
    diChuyenCotDong(diemGiua.cot - 6, diemGiua.dong - 1);
    cout << "RẮN ĐÃ CHẾT!!!!";
    diChuyenCotDong(diemGiua.cot - 10, diemGiua.dong);
    cout << "R(Chơi lại) - M(Menu)";
}

/*
Xoá bảng thông báo
*/
void xoaBangThongBao()
{
    Point diemGiua = layDiemTrungTam();
    int cdBang = 22, crBang = 3;
    for (int i = (diemGiua.dong - crBang/2); i < diemGiua.dong + crBang/2 + 2; i++)
    {
        diChuyenCotDong(diemGiua.cot - cdBang/2,i); // Cột bên trái
        cout<< "                         ";
    }

}

void khiConRanPhamQuy(CONRAN r)
{
    SetConsoleOutputCP(65001);
    // Lấy tọa độ trung tâm khung viền trò chơi đẻ xuất thông báo
    Point diemGiua = layDiemTrungTam();
    // Hiện con rắn chết
    r.veConRanChet();
    // Hiện thông báo chơi lại hay về menu chính
    diChuyenCotDong(diemGiua.cot -15, diemGiua.dong);
    hienBangThongBao();
}

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;
    int doKho = 300;
    // xuất tiếng việt có dấu ra màn hình
    UINT oldcodepage = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);
    veMenu(doKho);
    SetConsoleOutputCP(oldcodepage);
    veGiaoDienChinh();
    veConMoi(r);
    while (1)
    {
        if (kbhit())
        {
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='x') Huong = 1;
        }
        r.veConRan();
        Sleep(doKho);
        r.xoaDotCuoi();
        r.diChuyen(Huong);
        // Kiểm tra nếu rắn đụng biên hay cắn thân
        if (r.ktConRanPhamQuy())
        {
            khiConRanPhamQuy(r);
            Sleep(-1);
        }
    }

    return 0;
}
