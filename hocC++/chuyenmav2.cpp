#include<bits/stdc++.h>
using namespace std;
//Màu
#define RESET   "\033[0m"   // Đặt lại màu mặc định
#define RED     "\033[31m"  // Màu đỏ
#define ORANGE  "\033[38;5;214m" // Màu cam (đỏ nhạt)
#define YELLOW  "\033[33m"  // Màu vàng
#define BLUE    "\033[34m"  // Màu xanh dương
string thapphan(int t, int d, float a)
{
    if (t != d && t == 1) {
        if (d == 2) { // Chuyển sang nhị phân
            int m = (int)a, y = 0;
            string n = "";
            while (m > 0) {
                n = to_string(m % 2) + n;
                m /= 2;
            }
            if ((int)a == a) {
                return n;
            } else {
                n += ".";
                float x = a - (int)a;
                while (x > 0 && y < 10) {
                    x *= 2;
                    n += to_string((int)x);
                    x -= (int)x;
                    y++;
                }
                if ((int)a == 0) n = "0" + n;
                return n;
            }
        }
        if (d == 3) { // Chuyển sang hệ 16 (hex)
            int m = (int)a, y = 0;
            string n = "";
            while (m > 0) {
                if ((m % 16) < 10)
                    n = to_string(m % 16) + n;
                else if (m % 16 == 10) n = "A" + n;
                else if (m % 16 == 11) n = "B" + n;
                else if (m % 16 == 12) n = "C" + n;
                else if (m % 16 == 13) n = "D" + n;
                else if (m % 16 == 14) n = "E" + n;
                else if (m % 16 == 15) n = "F" + n;
                m /= 16;
            }
            if ((int)a == a) {
                return n;
            } else {
                n += ".";
                float x = a - (int)a;
                while (x > 0 && y < 10) {
                    x *= 16;
                    if ((int)x < 10)
                        n += to_string((int)x);
                    else if ((int)x == 10) n += "A";
                    else if ((int)x == 11) n += "B";
                    else if ((int)x == 12) n += "C";
                    else if ((int)x == 13) n += "D";
                    else if ((int)x == 14) n += "E";
                    else if ((int)x == 15) n += "F";
                    x -= (int)x;
                    y++;
                }
                if ((int)a == 0) n = "0" + n;
                return n;
            }
        }
    }
}
float nhiphan(int t, int d, string a)
{
    float m=0, y = 0;
            for(int i=0;i<a.length();i++)
            if(a[i]!='.') y++;
            else break;
            y--;
            for(int i=0;i<a.length();i++)
            {
                if(a[i]!='.') { m+=pow(2,y)*(a[i]-'0');
                y--;
            }
        }
            return m;
}
float hex(int t, int d, string a)
{
    float m=0, y = 0;
            for(int i=0;i<a.length();i++)
            if(a[i]!='.') y++;
            else break;
            y--;
            for(int i=0;i<a.length();i++)
        {
            if(a[i]!='.') 
            { 
                if(a[i]<='9'&&a[i]>='0') m+=pow(16,y)*(a[i]-'0');
                else m+=pow(16,y)*(a[i]-'7');
                y--;
            }
        }
            return m;
}
int main() {
    cout << BLUE << "Vui lòng nhập chuyển đổi từ ... đến ..." << RESET << endl;
    cout << YELLOW << "Các loại mã: 1. Thập phân / 2. Nhị phân / 3. Hex" << RESET << endl;
    cout << "Cú pháp nhập: " << ORANGE << "[loại mã nguồn] [loại mã đích] [giá trị]" << RESET << endl;
    int t, d;
    string a;
    cin >> t >> d >> a;
    cout << "----------------------------------" << endl;
    cout << BLUE << "Chuyển đổi từ " << t << " sang " << d << ":" << RESET << endl;
    if(t!=d&&t<=3&&d<=3&&t>=0&&d>=0)
    {
    if(t==1&&t!=d) 
    if(d==2) cout<<ORANGE<<thapphan(t,d,stof(a))<<YELLOW<<"(2)"<<RESET<<endl;
    else cout<<ORANGE<<thapphan(t,d,stof(a))<<YELLOW<<"(16)"<<RESET<<endl;
    if(t==3&&t!=d)
    if(d==1) cout<<ORANGE<<hex(t,d,a)<<YELLOW<<"(10)"<<RESET<<endl;
    else if(d==2) cout<<ORANGE<<thapphan(1,2,hex(3,1,a))<<YELLOW<<"(2)"<<RESET<<endl;
    if(t==2&&d==1) cout<<ORANGE<<nhiphan(t,d,a)<<YELLOW<<"(10)"<<RESET<<endl;
    else if(t==2&&d==3)
    cout<<ORANGE<<thapphan(1,3,nhiphan(2,1,a))<<YELLOW<<"(16)"<<RESET<<endl;
    }
    else cout << RED << "Are you kidding me?" << RESET << endl;
    cout << "----------------------------------" << endl;
    return 0;
}
