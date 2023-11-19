#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
#define dotToiDa 500
#define soDotMacDinh 5
void gotoxy( int column, int line );

int capDo = 1;// 1- de, 2 - trung binh, 3 - kho
int doKhoMacDinh = 300;

struct Point
{
    int x,y;
};
class CONRAN
{
public:
    Point conMoi;
    Point gocTraiTren;// góc trái trên
    Point gocPhaiDuoi;// góc phải dưới
    struct Point dotRan[dotToiDa];
    int DoDai;
    int diem = 0;
    bool lonLen = false;
    CONRAN()
    {
        DoDai = 3;
        dotRan[0].x = 10;
        dotRan[0].y = 10;
        dotRan[1].x = 11;
        dotRan[1].y = 10;
        dotRan[2].x = 12;
        dotRan[2].y = 10;
    }
    void Ve()
    {
        for (int i = 0; i < DoDai; i++)
        {
            gotoxy(dotRan[i].x,dotRan[i].y);
            cout<<"X";
        }
    }
    void DiChuyen(int Huong)
    {
        for (int i = DoDai-1; i>0; i--)
            dotRan[i] = dotRan[i-1];
        if (Huong==0) dotRan[0].x = dotRan[0].x + 1;
        if (Huong==1) dotRan[0].y = dotRan[0].y + 1;
        if (Huong==2) dotRan[0].x = dotRan[0].x - 1;
        if (Huong==3) dotRan[0].y = dotRan[0].y - 1;

    }
    // Khi ran di chuyen xoa anh ran cu tren man hinh (xoa dot cuoi cung)
    void xoaConRan()
    {
        gotoxy(dotRan[DoDai].cot, dotRan[DoDai].dong);
        cout<< " ";
    }

    void veConRanChet()
    {
        // Ve cai minh luc ran chet
        for (int i = 1; i < DoDai; i++)
        {
            gotoxy(dotRan[i].cot, dotRan[i].dong);
            cout<< ".";
        }
        // Ve cai dau khi ran chet
        gotoxy(dotRan[0].cot, dotRan[0].dong);
        cout<< "*";
    }    
    // Khi dau ran cham vao vien ham tra ve <true>
	bool ktDauChamVien()
    {
        if(dotRan[0].cot == gocTrenTrai.cot || dotRan[0].cot == gocDuoiPhai.cot || dotRan[0].dong == gocTrenTrai.dong || dotRan[0].dong == gocDuoiPhai.dong)
            return true;
        return false;
    }
    // Khi dau ran cham phai than cua no thi ham tra ve <true>
    bool ktDauChamThan()
    {
        for (int i = 1; i < doDai; i++)
        {
            if(dotRan[0].cot == dotRan[i].cot && dotRan[0].dong == dotRan[i].dong)
                return true;
        }
        return false;
    }
};

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

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
        system("cls");
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}


void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
