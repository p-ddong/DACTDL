#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<cmath>
#define MAX 50
using namespace std;

struct MT // ma trận bài toán vận tải
{
    int m;// số trạm cung
    int n;// số trạm cầu
    int a[MAX];// các điểm cung
    int b[MAX];// các điểm cầu
    int c[MAX][MAX];// cước phí
    int x[MAX][MAX];// lượng hàng cần vận chuyển
};

class LeastCost{
    struct MT *mtr1;
public:
    void ThietLapMT(MT *mtr1);

};

void LeastCost::ThietLapMT(MT *mtr1){
    int cung = 0;
    int cau = 0;
    int sosanh;
    cout<<" Số trạm cung ứng : ";
    cin >> mtr1->m;
    cout<<" Số trạm nhận hàng : ";
    cin >> mtr1->n;
    int c2[MAX][MAX]; // khai báo ma trận mới c2 để lưu trữ ma trận cũ và thêm hàng hoặc cột mới
    for (int i = 0; i < mtr1->m; i++) {
        cout << "Nhập cước phí hàng " << i+1 << " : ";
        for (int j = 0; j < mtr1->n; j++) {
            int value;
            cin >> value;
            mtr1->c[i][j] = value;
        };
    };
    
    cout<<"Nhập số hàng cần vận chuyển :"<<endl;
    for (int i = 0; i <  mtr1->m; i++) {
        cout << "Trạm cung " << i+1 << ": ";
        cin >> mtr1->a[i];
        cung = cung + mtr1->a[i];
    };
    
    cout<<"Nhập số hàng cần nhận :"<<endl;
    for (int i = 0; i <  mtr1->n; i++) {
        cout << "Trạm cầu " << i+1 << ": ";
        cin >> mtr1->b[i];
        cau = cau + mtr1->b[i];
    }; 
    
    if (cung > cau){
        sosanh = 1;
    } else if (cung < cau){
        sosanh = 2;
    } else {
        return; // nếu không có hàng cần vận chuyển hoặc hàng cần nhận thì thoát khỏi hàm
    }
    int count = abs(cung-cau);
    switch(sosanh){
        case 1:
            mtr1->n = mtr1->n + 1;
            // sao chép ma trận cũ sang ma trận mới c2 và thêm cột mới
            for (int i = 0; i < mtr1->m; i++) {
                for (int j = 0; j < mtr1->n-1; j++) {
                    c2[i][j] = mtr1->c[i][j];
                }
                c2[i][mtr1->n-1] = 0;
            }
            // gán ma trận mới thiết lập vào ma trận cũ 
            for (int i = 0; i < mtr1->m; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    mtr1->c[i][j] = c2[i][j];
                }
            }
            mtr1->b[mtr1->n-1]=count   
            break;
        case 2:
            mtr1->m = mtr1->m + 1;
            // sao chép ma trận cũ sang ma trận mới c2 và thêm hàng mới
            for (int i = 0; i < mtr1->m-1; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    c2[i][j] = mtr1->c[i][j];
                }
            }
            for (int j = 0; j < mtr1->n; j++) {
                c2[mtr1->m-1][j] = 0;
            }
            // gán ma trận mới thiết lập vào ma trận cũ
            for (int i = 0; i < mtr1->m; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    mtr1->c[i][j] = c2[i][j];
                }
            }
            mtr1->a[mtr1->m-1]=count 
            break;
        default:
            break;
    } 
}
int main() {
    MT mtr;
    LeastCost lc;
    lc.ThietLapMT(&mtr);
    return 0;
}
