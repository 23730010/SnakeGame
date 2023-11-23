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
bool choPhepXuyenTuong = false;
int doKho = 300;

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

/**
Vẽ khung chính cho trò chơi
*/
void veKhungVienChinh()
{
    for (int i = gocTraiTren.cot + 1; i < gocPhaiDuoi.cot; i++)
    {
        diChuyenCotDong(i + 5, gocTraiTren.dong + 1); // Dòng trên cùng
        cout << (char)205;
        diChuyenCotDong(i + 6, gocPhaiDuoi.dong + 1); // Dòng đổ bóng dưới cùng
        cout << (char)176;
        diChuyenCotDong(i + 5, gocPhaiDuoi.dong); // Dòng dưới cùng
        cout << (char)205;
    }
    for (int i = gocTraiTren.dong + 1; i < gocPhaiDuoi.dong; i++)
    {
        diChuyenCotDong(gocTraiTren.cot + 5, i); // Cột bên trái
        cout << (char)186;
        diChuyenCotDong(gocPhaiDuoi.cot + 7, i + 1); // Cột đổ bóng bên phải
        cout << (char)176;
        // diChuyenCotDong(gocTraiTren.cot + 7, i + 1); // Cột đổ bóng 2
        // cout << (char)176;
        diChuyenCotDong(gocPhaiDuoi.cot + 5, i); // Cột phải
        cout << (char)186;
    }
    // Vẽ 4 góc của khung
    diChuyenCotDong(gocTraiTren.cot + 5, gocTraiTren.dong + 1);
    cout << (char)201;
    diChuyenCotDong(gocPhaiDuoi.cot + 5, gocTraiTren.dong + 1);
    cout << (char)187;
    diChuyenCotDong(gocTraiTren.cot +5, gocPhaiDuoi.dong);
    cout << (char)200;
    diChuyenCotDong(gocPhaiDuoi.cot + 5, gocPhaiDuoi.dong);
    cout << (char)188;
    // Vẽ góc đổ bóng
    diChuyenCotDong(gocPhaiDuoi.cot + 6, gocPhaiDuoi.dong + 1);
    cout << (char)176;
    diChuyenCotDong(gocPhaiDuoi.cot + 7, gocPhaiDuoi.dong + 1);
    cout << (char)176;
}

/*
Hàm hiển thị thông tin
*/
void hienThiThongTin()
{
    // Vẽ menu và hướng dẫn cách chơi
    diChuyenCotDong(gocTraiTren.cot + 33, gocTraiTren.dong -3);
    cout << "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    diChuyenCotDong(gocTraiTren.cot + 42, gocTraiTren.dong - 2);
    cout << "oOo";
    diChuyenCotDong(gocTraiTren.cot + 12, gocTraiTren.dong -1);
    cout << "Nhóm SV thực hiện: <23730010><23730024><23730029><23730057><23730030>";
    diChuyenCotDong(gocTraiTren.cot + 10, gocTraiTren.dong);
    cout << "<Võ Hùng Cường><Lê Hoàng Kim><Phạm Hoàng Long><Lê Hoàng Vũ><Nguyễn Lê Minh>";
    diChuyenCotDong(gocTraiTren.cot , gocPhaiDuoi.dong+3);
    cout<< "Phím Mũi tên hay <A-X-W-D> để Di chuyển";
    diChuyenCotDong(gocPhaiDuoi.cot - 32, gocPhaiDuoi.dong + 3);
    cout<< "<R> Chơi lại >><< Để gọi Menu <M>";
    diChuyenCotDong(gocTraiTren.cot, gocPhaiDuoi.dong + 4);
    cout<< "Dùng phím <SPACE> để Tạm dừng";
    diChuyenCotDong(gocPhaiDuoi.cot - 21, gocPhaiDuoi.dong + 4);
    cout<< "Dùng phím <ESC> để Thoát";

    // In ra độ khó
    diChuyenCotDong(3, gocTraiTren.dong + 5);
    cout << "ĐỘ KHÓ";
    diChuyenCotDong(2, gocTraiTren.dong + 6);
    switch (capDo)
    {
    case 1:
        cout << "   Dễ";
        break;
    case 2:
        cout << "Trung Bình";
        break;
    case 3:
        cout << "   Khó";
        break;
    }
    diChuyenCotDong(1, gocTraiTren.dong + 8);
    cout << "TRẠNG THÁI";
    diChuyenCotDong(1, gocTraiTren.dong + 9);
    cout << "Đang dùng...";
    diChuyenCotDong(2, 1);
    cout << "TIGER BẠC";
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
    cout << "ĐIỂM";
    diChuyenCotDong(4, gocTraiTren.dong + 3);
    cout << "   ";
    diChuyenCotDong(4, gocTraiTren.dong + 3);
    cout << " " << diem;
}

/*
Hàm vẽ bảng thông báo
*/

void bangThongBao()
{
    int tamCot = (gocTraiTren.cot + gocPhaiDuoi.cot) / 2;
    int tamDong = (gocTraiTren.dong + gocPhaiDuoi.dong) / 2;
    int cdBang = 22;
    int crBang = 3;
    for (int i = (tamCot - cdBang/2) + 1; i < tamCot+cdBang/2; i++)
    {
        diChuyenCotDong(i, tamCot - crBang/2); // Dòng trên
        cout << (char)196;
        diChuyenCotDong(i, tamDong+crBang/2); //Dòng dưới
        cout << (char)196;
    }

    for (int i = (tamDong - crBang/2)+1; i < tamDong + crBang/2; i++)
    {
        diChuyenCotDong(tamCot - cdBang/2,i); // Cột trái
        cout << (char)179;
        diChuyenCotDong(tamCot + cdBang/2, i); // Cột phải
        cout << (char)179;
    }

    // Vẽ 4 góc của khung viền thông báo
    diChuyenCotDong(tamCot - cdBang/2, tamDong- crBang/2);
    cout << (char)218;
    diChuyenCotDong(tamCot + cdBang/2, tamDong - crBang/2);
    cout << (char)191;
    diChuyenCotDong(tamCot - cdBang/2, tamDong + crBang/2);
    cout << (char)192;
    diChuyenCotDong(tamCot + cdBang/2, tamDong + crBang/2);
    cout << (char)217;

    // Thông báo thua
    diChuyenCotDong(tamCot - 6, tamDong - 1);
    cout << "RẮN ĐÃ CHẾT!!!!";
    diChuyenCotDong(tamCot - 10, tamDong);
    cout << "R(Chơi lại) - M(Menu)";
}

/*
Xoá bảng thông báo
*/
void xoaBangThongBao()
{
    int tamCot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
    int tamDong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
    int cdBang = 22, crBang = 3;
    for (int i = (tamDong - crBang/2); i < tamDong + crBang/2 + 2; i++)
    {
        diChuyenCotDong(tamCot - cdBang/2,i); // Cột bên trái
        cout<< "                         ";
    }

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
    {
        choPhepXuyenTuong = true;
    }
    else
    {
        choPhepXuyenTuong = false;
    }

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
void khiConRanPhamQuy(CONRAN r)
{
    SetConsoleOutputCP(65001);
    // Lấy tọa độ trung tâm khung viền trò chơi
    Point diemGiua = layDiemTrungTam();
    // Hiện con rắn chết
    r.veConRanChet();
    // Hiện thông báo chơi lại hay về menu chính
    diChuyenCotDong(diemGiua.cot -15, diemGiua.dong);
    cout << "RẮN ĐÃ CHẾT!!!! R(Chơi lại) - M(Menu)";
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


int main()
{
    CONRAN r;
    int Huong = 0;
    char t;
    UINT oldcodepage = GetConsoleOutputCP();
    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
    veMenu(doKho);
    hienThiThongTin();
    hienThiDiem();
    SetConsoleOutputCP(oldcodepage);
    veKhungVienChinh();
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
        Sleep(300);
        r.xoaDotCuoi();
        r.diChuyen(Huong);
        // Kiểm tra nếu rắn đụng biên hay cắn thân
        if (r.ktConRanPhamQuy())
            khiConRanPhamQuy(r);
    }

    return 0;
}
