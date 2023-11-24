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

char trangThaiDung[17] = "Tạm Dừng... ";
char trangThaiDangChoi[17] = "Đang Chơi...";
char trangThaiKetThuc[17] = "Kết Thúc... ";
int capDo = 1;// 1- de, 2 - trung binh, 3 - kho
int diem = 0;
int diemCao = 0;
Point conMoi;
Point gocTraiTren;// góc trái trên
Point gocPhaiDuoi;// góc phải dưới
bool choPhepXuyenTuong = false;
int doKho = 300;
int luotChoi = 0;
UINT oldcodepage;

class CONRAN;
void diChuyenCotDong(int cot, int dong);
void choiLai(CONRAN r);
bool ktConMoiTrungConRan(CONRAN r);
void veConMoi(CONRAN r);
void xoaConMoi();
void khiConRanPhamQuy(CONRAN);
void manHinhChinh(CONRAN*);
void veLaiDiemVienBiXoa(CONRAN);
void hienTrangThai(char[]);
void thaoTacPhimR(CONRAN*, int&);
void thaoTacPhimM(CONRAN*, int&);
void thaoTacPhimEsc();
void hienThiDiem();
void hienThiDiemCao();
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
        // Dau ran la dot [0] trùng than tu dot [1] den do dai con ran -1
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
        if (choPhepXuyenTuong)
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
// Trả về điểm trung tâm khung viền
Point layDiemTrungTam()
{
    Point diemTT;
    diemTT.cot = (gocTraiTren.cot + gocPhaiDuoi.cot)/2;
    diemTT.dong = (gocTraiTren.dong + gocPhaiDuoi.dong)/2;
    return diemTT;
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
    hienThiDiem();
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
    for (int i = gocTraiTren.cot; i <= gocPhaiDuoi.cot; i++)
    {
        diChuyenCotDong(i, gocTraiTren.dong); // Dòng trên cùng
        cout << (char)205;
        diChuyenCotDong(i + 1, gocPhaiDuoi.dong + 1); // Dòng đổ bóng dưới cùng
        cout << (char)176;
        diChuyenCotDong(i, gocPhaiDuoi.dong); // Dòng dưới cùng
        cout << (char)205;
    }
    for (int i = gocTraiTren.dong; i <= gocPhaiDuoi.dong; i++)
    {
        diChuyenCotDong(gocTraiTren.cot, i); // Cột bên trái
        cout << (char)186;
        diChuyenCotDong(gocPhaiDuoi.cot + 2, i + 1); // Cột đổ bóng bên phải
        cout << (char)176;
        // diChuyenCotDong(gocTraiTren.cot + 7, i + 1); // Cột đổ bóng 2
        // cout << (char)176;
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
    // Vẽ góc đổ bóng
    diChuyenCotDong(gocPhaiDuoi.cot + 2, gocPhaiDuoi.dong + 1);
    cout << (char)176;
    diChuyenCotDong(gocPhaiDuoi.cot + 2, gocPhaiDuoi.dong + 1);
    cout << (char)176;
}

/*
Hàm hiển thị thông tin
*/
void hienThiThongTin()
{
    // Vẽ menu và hướng dẫn cách chơi
    diChuyenCotDong(gocTraiTren.cot + 28, gocTraiTren.dong -4);
    cout << "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    diChuyenCotDong(gocTraiTren.cot + 39, gocTraiTren.dong - 3);
    cout << "oOo";
    diChuyenCotDong(gocTraiTren.cot + 8, gocTraiTren.dong -2);
    cout << "Nhóm SV thực hiện: <23730010><23730024><23730029><23730057><23730030>";
    diChuyenCotDong(gocTraiTren.cot + 2, gocTraiTren.dong -1);
    cout << "<Võ Hùng Cường><Lê Hoàng Kim><Phạm Hoàng Long><Lê Hoàng Vũ><Nguyễn Lê Minh>";
    diChuyenCotDong(gocTraiTren.cot , gocPhaiDuoi.dong+3);
    cout<< "Phím Mũi tên hay <A-X-W-D> để Di chuyển";
    diChuyenCotDong(gocPhaiDuoi.cot - 32, gocPhaiDuoi.dong + 3);
    cout<< "<R> Chơi lại >><< Để gọi Menu <M>";
    diChuyenCotDong(gocTraiTren.cot + 4, gocPhaiDuoi.dong + 4);
    cout<< "Dùng phím <SPACE> để Tạm dừng";
    diChuyenCotDong(gocPhaiDuoi.cot - 28, gocPhaiDuoi.dong + 4);
    cout<< "Dùng phím <ESC> để Thoát";

    // In ra độ khó
    diChuyenCotDong(3, gocTraiTren.dong + 5);
    cout << "ĐỘ KHÓ";
    diChuyenCotDong(2, gocTraiTren.dong + 6);
    switch (capDo)
    {
    case 1:
        cout << "---Dễ---";
        break;
    case 2:
        cout << "Trung Bình";
        break;
    case 3:
        cout << "---Khó---";
        break;
    }
    diChuyenCotDong(1, gocTraiTren.dong + 8);
    cout << "TRẠNG THÁI";
    hienTrangThai(trangThaiDangChoi);
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
    SetConsoleOutputCP(65001);
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
    SetConsoleOutputCP(oldcodepage);
    int tamCot = (gocTraiTren.cot + gocPhaiDuoi.cot) / 2;
    int tamDong = (gocTraiTren.dong + gocPhaiDuoi.dong) / 2;
    int cdBang = 22;
    int crBang = 3;
    for (int i = (tamCot - cdBang/2) + 1; i < tamCot+cdBang/2; i++)
    {
        diChuyenCotDong(i, tamDong - crBang/2); // Dòng trên
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

    SetConsoleOutputCP(65001);
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
void veMenu()
{
    system("cls");
    char x;
    diChuyenCotDong(gocTraiTren.cot + 30, gocTraiTren.dong -4);
    cout<< "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    diChuyenCotDong(gocTraiTren.cot + 35, gocTraiTren.dong -3);
    cout << "Chọn chế độ chơi" << endl;
    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong + 4);
    cout << "Dùng phím số để chọn chế độ chơi";
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong -1);
    cout << "1: Cổ điển" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong);
    cout << "2: Hiện đại" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong + 1);
    do
    {
        x = getch();
    }
    while(x != '1' && x != '2' && x!=27);

    if (x == '2')
    {
        choPhepXuyenTuong = true;
    }
    else if (x == '1')
    {
        choPhepXuyenTuong = false;
    }
    else if (x == 27)
    {
        system("cls");
        exit(0);
    }

    system("cls");
    diChuyenCotDong(gocTraiTren.cot + 30, gocTraiTren.dong -4);
    cout<< "CHƯƠNG TRÌNH RẮN SĂN MỒI";
    diChuyenCotDong(gocTraiTren.cot + 35, gocTraiTren.dong -3);
    cout << "Chọn độ khó" << endl;
    diChuyenCotDong(gocTraiTren.cot + 25, gocPhaiDuoi.dong + 4);
    cout << "Dùng phím số để chọn độ khó";
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong -1);
    cout << "1: Dễ" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong);
    cout << "2: Trung bình" << endl;
    diChuyenCotDong(gocTraiTren.cot + 34, gocTraiTren.dong + 1);
    cout << "3: Khó" << endl;
    diChuyenCotDong(gocTraiTren.cot + 30, gocTraiTren.dong + 2);
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
    char x;
    SetConsoleOutputCP(65001);

    luotChoi = luotChoi + 1;
    if (diem > diemCao)
        diemCao = diem;
    hienThiDiemCao();
    // Lấy tọa độ trung tâm khung viền trò chơi
    Point diemGiua = layDiemTrungTam();
    // Hiện con rắn chết
    r->veConRanChet();
    // Hiện thông báo chơi lại hay về menu chính
    bangThongBao();
    hienTrangThai(trangThaiKetThuc);
    do
    {
        x = getch();
    } while (x != 'r' && x != 'R' && x != 27 && x != 'm' && x != 'M');

    if (x=='r' || x=='R')
    {
        xoaBangThongBao();
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
*   Màn hình chính
*/
void manHinhChinh(CONRAN *r)
{
    system("cls");
    diem = 0;
    veMenu();
    hienThiThongTin();
    hienThiDiem();

    SetConsoleOutputCP(oldcodepage);
    veKhungVienChinh();
    hienThiDiemCao();
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
*
*/
void hienTrangThai(char trangThai[])
{
    diChuyenCotDong(1, gocTraiTren.dong + 9);
    cout << trangThai;
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
    manHinhChinh(r);
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
    oldcodepage = GetConsoleOutputCP();
    // xuất tiếng việt có dấu ra màn hình
    SetConsoleOutputCP(65001);
    // Ẩn con trỏ
    Nocursortype();
    manHinhChinh(&r);
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
            if ((t=='a' || t=='A') && Huong != 0) Huong = 2;
            else if ((t=='w' || t=='W') && Huong != 1) Huong = 3;
            else if ((t=='d' || t=='D') && Huong != 2) Huong = 0;
            else if ((t=='x' || t=='X') && Huong != 3) Huong = 1;
            else if (t == ' ') tamDung(&r, Huong);
            else if (t=='r' || t=='R')
            {
                thaoTacPhimR(&r, Huong);
            }
            else if (t=='m' || t == 'M')
            {
                thaoTacPhimM(&r, Huong);
            } else if (t==27)
            {
                thaoTacPhimEsc();
            }

        }
        if (r.ktDungConMoi())
        {
            r.anConMoi();
            veConMoi(r);
            hienThiDiem();
            if (r.tocDo >= 100 && diem > 0 && diem%50 == 0)
            {
                r.tocDo -= 20;
            }
        }
        r.diChuyen(Huong);
    }

    return 0;
}
