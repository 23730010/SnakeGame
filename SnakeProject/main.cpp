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

class CONRAN;
void diChuyenCotDong(int cot, int dong);
void choiLai(CONRAN r);
bool ktConMoiTrungConRan(CONRAN r);
void veConMoi(CONRAN r);
void xoaConMoi();
void khiConRanPhamQuy(CONRAN);
Point layDiemTrungTam();

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
        gocTraiTren.cot = 10;// tọa độ cột góc trái trên của khung trong chơi
        gocTraiTren.dong = 04;// tọa độ dòng góc trái trên của khung trò chơi
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
        if (Huong == 0) dotRan[0].cot = dotRan[0].cot + 1;
        if (Huong == 1) dotRan[0].dong = dotRan[0].dong + 1;
        if (Huong == 2) dotRan[0].cot = dotRan[0].cot - 1;  // Fix hướng đi
        if (Huong == 3) dotRan[0].dong = dotRan[0].dong - 1;  // Fix hướng đi

        // Điều chỉnh tọa độ nếu rắn đi qua tường
        if(choPhepQuaTuong)
            ranDiChuyenQuaTuong(dotRan[0]);
    }

    // Hàm điều chỉnh tọa độ khi rắn đi qua tường
    void ranDiChuyenQuaTuong(Point& head)
    {
    // Kiểm tra xem đầu rắn có ra khỏi màn hình không
        if (head.cot < gocTraiTren.cot)
        {
            head.cot = gocPhaiDuoi.cot - 1;  // Nếu đi ra khỏi bên trái, đặt lại ở bên phải
        }
        else if (head.cot >= gocPhaiDuoi.cot)
        {
            head.cot = gocTraiTren.cot;  // Nếu đi ra khỏi bên phải, đặt lại ở bên trái
        }
        else if (head.dong < gocTraiTren.dong)
        {
            head.dong = gocPhaiDuoi.dong - 1;  // Nếu đi ra khỏi phía trên, đặt lại ở phía dưới
        }
        else if (head.dong >= gocPhaiDuoi.dong)
        {
            head.dong = gocTraiTren.dong;  // Nếu đi ra khỏi phía dưới, đặt lại ở phía trên
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
// Trả về điểm trung tâm khung viền
Point layDiemTrungTam()
{
    Point diemTT;
    diemTT.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
    diemTT.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
    return diemTT;
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

void khiConRanPhamQuy(CONRAN r)
{
    // Lấy tọa độ trung tâm khung viền trò chơi
    Point diemGiua = layDiemTrungTam();
    // Hiện con rắn chết
    r.veConRanChet();
    // Hiện thông báo chơi lại hay về menu chính
    diChuyenCotDong(diemGiua.cot -15, diemGiua.dong);
    cout << "Ran chet! Choi lai hay ve Menu chinh!";
    Sleep(-1);
}

/**
* Hiển thị điểm
*/
void hienThiDiem()
{
    diChuyenCotDong(0, 0);
    cout << "Diem: " << diem;
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

// Ẩn con trỏ
void Nocursortype()
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

    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
    // Ẩn con trỏ
    Nocursortype();
    veConMoi(r);
    while (1)
    {
        if (kbhit())
        {
            // Đọc phím vừa nhấn
            char t = getch();
            if (t=='a' && Huong != 0) Huong = 2;
            if (t=='w' && Huong != 1) Huong = 3;
            if (t=='d' && Huong != 2) Huong = 0;
            if (t=='x' && Huong != 3) Huong = 1;
            // Các hướng mũi tên
            if (t == 72 && Huong != 1) Huong = 3;  // Mũi tên lên
            if (t == 80 && Huong != 3) Huong = 1;  // Mũi tên xuống
            if (t == 75 && Huong != 0) Huong = 2;  // Mũi tên sang trái
            if (t == 77 && Huong != 2) Huong = 0;  // Mũi tên sang phải
        }
        r.diChuyen(Huong);
        r.veConRan();
        Sleep(300);
        r.xoaDotCuoi();
        // Kiểm tra nếu rắn đụng biên hay cắn thân
        if (r.ktConRanPhamQuy())
            khiConRanPhamQuy(r);
    }

    return 0;
}
