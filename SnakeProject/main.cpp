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

int capDo = 1;// 1- de, 2 - trung binh, 3 - kho
int diem = 0;
Point conMoi;
Point gocTraiTren;// góc trái trên
Point gocPhaiDuoi;// góc phải dưới

class CONRAN
{
public:
    struct Point dotRan[dotToiDa];
    int doDai = doDaiMacDinh;
    int tocDo = tocDoThap;
    bool lonLen = false;
    CONRAN()
    {
        gocTraiTren.cot = 10;// tọa độ cột góc trái trên của khung trong chơi
        gocTraiTren.dong = 04;// tọa độ dòng góc trái trên của khung trò chơi
        gocPhaiDuoi.cot = 92;// tọa độ cột góc phải dưới của khung trò chơi
        gocPhaiDuoi.dong = 24;// tọa độ dòng góc phải dưới của khung trò chơi

        khoiTaoThanRan();
    }

    /**
    * Khởi tạo thân rắn
    */
    void khoiTaoThanRan()
    {
        // điểm bắt đầu game
        Point diemBatDau;
        diemBatDau.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
        diemBatDau.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;

        // khởi tạo tọa độ cho các đốt của thân rắn
        for(int i=0; i<doDai; i++)
        {
            dotRan[i].cot = diemBatDau.cot--;
            dotRan[i].dong = diemBatDau.dong;
        }
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
    void diChuyen(int Huong)
    {
        for (int i = doDai-1; i>0; i--)
            dotRan[i] = dotRan[i-1];
        if (Huong==0) dotRan[0].cot = dotRan[0].cot + 1;
        if (Huong==1) dotRan[0].dong = dotRan[0].dong + 1;
        if (Huong==2) dotRan[0].cot = dotRan[0].dong - 1;
        if (Huong==3) dotRan[0].cot = dotRan[0].dong - 1;

    }
};

/**
Vẽ khung chính cho trò chơi
*/
void veKhungVienChinh()
{
    for (int i = gocTraiTren.cot + 1; i < gocPhaiDuoi.cot; i++)
    {
        diChuyenCotDong(i, gocTraiTren.dong + 1); // Dòng trên cùng
        cout << (char)205;
        diChuyenCotDong(i + 1, gocPhaiDuoi.dong + 1); // Dòng bóng đỏ
        cout << (char)176;
        diChuyenCotDong(i, gocPhaiDuoi.dong); // Dòng dưới cùng
        cout << (char)205;
    }
    for (int i = gocTraiTren.dong + 1; i < gocPhaiDuoi.dong; i++)
    {
        diChuyenCotDong(gocTraiTren.cot, i); // Cột bên trái
        cout << (char)186;
        diChuyenCotDong(gocPhaiDuoi.cot + 1, i + 1); // Cột bóng đỏ 1
        cout << (char)176;
        diChuyenCotDong(gocTraiTren.cot + 2, i + 1); // Cột bóng đỏ 2
        cout << (char)176;
        diChuyenCotDong(gocPhaiDuoi.cot, i); // Cột phải
        cout << (char)186;
    }
    // Vẽ 4 góc của khung 
    diChuyenCotDong(gocTraiTren.cot, gocTraiTren.dong + 1);
    cout << (char)201;
    diChuyenCotDong(gocPhaiDuoi.cot, gocTraiTren.dong + 1);
    cout << (char)187;
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong);
    cout << (char)200;
    diChuyenCotDong(gocPhaiDuoi.cot, gocPhaiDuoi.dong);
    cout << (char)188;
    // Vẽ góc bóng đỏ
    diChuyenCotDong(gocPhaiDuoi.cot + 1, gocPhaiDuoi.dong + 1);
    cout << (char)176;
    diChuyenCotDong(gocPhaiDuoi.cot + 2, gocPhaiDuoi.dong + 1);
    cout << (char)176;

    // Vẽ menu và hướng dẫn cách chơi
    diChuyenCotDong(gocTraiTren.cot + 24, gocTraiTren.dong -3);
    cout << "CHUONG TRINH RAN SAN MOI";
    diChuyenCotDong(gocTraiTren.cot + 35, gocTraiTren.dong - 2);
    cout << "oOo";
    diChuyenCotDong(gocTraiTren.cot + 4, gocTraiTren.dong -1);
    cout << "Nhom SV thuc hien: <23730010><23730024><23730029><23730057><23730030>";
    diChuyenCotDong(gocTraiTren.cot + 2, gocTraiTren.dong);
    cout << "<Vo Hung Cuong><Le Hoang Kim><Pham Hoang Long><Le Hoang Vu><Nguyen Le Minh>";
    diChuyenCotDong(gocTraiTren.cot , gocPhaiDuoi.dong+3);
    cout<< "Phim Mui ten hay <A-X-W-D> de Di chuyen";
    diChuyenCotDong(gocPhaiDuoi.cot - 32, gocPhaiDuoi.dong + 3);
    cout<< "<R> Choi lai  >><<  De goi Menu <M>";
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong + 4);
    cout<< "Dung phim <SPACE> de Tam dung";
    diChuyenCotDong(gocPhaiDuoi.cot - 21, gocPhaiDuoi.dong + 4);
    cout<< "Dung phim <ESC> de Thoat";

    // In ra độ khó
    diChuyenCotDong(3, gocTraiTren.dong + 5);
    cout << "DO KHO";
    diChuyenCotDong(2, gocTraiTren.dong + 6);
    switch (capDo)
    {
    case 1:
        cout << "   De";
        break;
    case 2:
        cout << "Trung Binh";
        break;
    case 3:
        cout << "   Kho";
        break;
    }
    diChuyenCotDong(2, gocTraiTren.dong + 8);
    cout << "TRANG THAI";
    diChuyenCotDong(1, gocTraiTren.dong + 9);
    cout << "Dang dung...";
    diChuyenCotDong(3, 1);
    cout << "TIGER BAC";
    diChuyenCotDong(1, 2);
    cout << "CN1.2023.1";
    diChuyenCotDong(3, 3);
    cout << "11/2023";
}

/*
 Hàm hiển thị điểm
*/

void hienThiDiem()
{
    diChuyenCotDong(4, gocTraiTren.dong + 2);
    cout << "DIEM";
    diChuyenCotDong(4, gocTraiTren.dong + 3);
    cout << "   ";
    diChuyenCotDong(4, gocTraiTren.dong + 3);
    cout << " " << diem;
}

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
void choiLai(CONRAN r) {
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
int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
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
        r.diChuyen(Huong);
        Sleep(300);
    }

    return 0;
}
