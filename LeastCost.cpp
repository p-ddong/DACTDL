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
    int x[MAX][MAX]={0};// ma trận chuyển hàng
    int value=0;// mức độ ưu tiên
    int tongcung=0;// tổng số hàng cung
    int tongcau=0;// tổng số hàng cầu
};
class LeastCost{
    struct MT *mtr1;
public:
    void ThietLapMT(MT *mtr1);
    void Chiahang(MT *mtr1);
    void TongCuocPhi(MT mtr1);
    void Hienthi(MT mtr1);
};
//ThietLapMT sẽ làm nhiệm vụ nhập dữ liệu và cân bằng cung cầu
void LeastCost::ThietLapMT(MT *mtr1){
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
       mtr1->tongcung = mtr1->tongcung + mtr1->a[i];
    };
    
    cout<<"Nhập số hàng cần nhận :"<<endl;
    for (int i = 0; i <  mtr1->n; i++) {
        cout << "Trạm cầu " << i+1 << ": ";
        cin >> mtr1->b[i];
        mtr1->tongcau = mtr1->tongcau + mtr1->b[i];
    }; 
    // cân bằng cung cầu
    if (mtr1->tongcung > mtr1->tongcau){
        mtr1->value = 1;
    } else if (mtr1->tongcung < mtr1->tongcau){
        mtr1->value = 2;
    }else{
        return;
    }
    int count = abs(mtr1->tongcung-mtr1->tongcau);
    switch(mtr1->value){
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
            mtr1->b[mtr1->n-1]=count; 
            break;
        case 2:
            mtr1->m = mtr1->m + 1;
            // sao chép ma trận cũ sang ma trận mới c2 và thêm hàng mới
            for (int i = 0; i < mtr1->m-1; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    c2[i][j] = mtr1->c[i][j];
                };
            };
            for (int j = 0; j < mtr1->n; j++) {
                c2[mtr1->m-1][j] = 0;
            };
            // gán ma trận mới thiết lập vào ma trận cũ
            for (int i = 0; i < mtr1->m; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    mtr1->c[i][j] = c2[i][j];
                };
            };
            mtr1->a[mtr1->m-1]=count; 
            break;
        default:
            break;
            
    } 
}
//ChiaHang sẽ làm nhiệm vụ chia hàng từ cung tới cầu 
void LeastCost::Chiahang(MT *mtr1)
{
struct MT *mtr2 = mtr1;
int smallest = 1000; // khởi tạo giá trị nhỏ nhất cho biến smallest
while(mtr2->tongcung != 0 || mtr2->tongcau !=0){
    int m,n;
    for(int i=0; i<mtr2->m; i++) {
        for(int j=0; j<mtr2->n; j++) {
            if(mtr2->c[i][j] != 0 && mtr2->c[i][j] < smallest) { // nếu phần tử khác 0 và nhỏ hơn smallest
                smallest = mtr2->c[i][j];
                m=i-1;
                n=j-1;
            }
        }
    }
if(mtr2->a[m] == 0 || mtr2->b[n] == 0 ){
    mtr2->c[m][n]=0;
}else if (mtr2->a[m]>mtr2->b[n]){
    mtr2->x[m][n]=mtr2->b[n];
    mtr2->tongcung=mtr2->tongcung-mtr2->a[m]; 
    mtr2->tongcau=mtr2->tongcau-mtr2->b[n];
    mtr2->a[m]=mtr2->a[m]-mtr2->b[n];
    mtr2->b[n]=0;
    mtr2->c[m][n]=0;
    return;
}else if(mtr2->a[m]<mtr2->b[n]){
    mtr2->x[m][n]=mtr2->a[m];
    mtr2->tongcung=mtr2->tongcung-mtr2->a[m]; 
    mtr2->tongcau=mtr2->tongcau-mtr2->b[n];
    mtr2->b[n]=mtr2->b[n]-mtr2->a[m];
    mtr2->a[m]=0;
    mtr2->c[m][n]=0;
    return;
}else if (mtr2->a[m]==mtr2->b[n]){
    mtr2->x[m][n]=mtr2->a[m];
    mtr2->tongcung=mtr2->tongcung-mtr2->a[m]; 
    mtr2->tongcau=mtr2->tongcau-mtr2->b[n];
    mtr2->a[m]=0;
    mtr2->b[n]=0;
    mtr2->c[m][n]=0;
    return;
}else {
    return;
};

}
if (mtr2->tongcung == 0 && mtr2->tongcau == 0){
    return;
}else if ( mtr2->tongcung == 0 && mtr2->tongcau != 0){
for ( int i = 0; i < mtr2->n; i++)
{
  mtr2->x[mtr2->m-1][i]=mtr2->b[i];
  mtr2->b[i]=0;  
}
return;
}else if (mtr2->tongcung != 0 && mtr2->tongcau == 0){
    for ( int i = 0; i < mtr2->m; i++)
{
  mtr2->x[i][mtr2->n-1]=mtr2->a[i];
  mtr2->a[i]=0;  
}
return;
}else{ 
return;
}
for (int i = 0; i < mtr1->m; i++) {
                for (int j = 0; j < mtr1->n; j++) {
                    mtr1->x[i][j] = mtr2->x[i][j];
                };
};
}

void LeastCost::TongCuocPhi(MT mtr1)
{
    int tongcp = 0;
    for (int i = 0; i < mtr1.m; i++) {
        for (int j = 0; j < mtr1.n; j++) {
            if (mtr1.x[i][j] > 0) { // nếu có hàng được vận chuyển từ cung i đến cầu j
                tongcp += mtr1.x[i][j] * mtr1.c[i][j]; // tính tổng chi phí
            }
        }
    }
    cout << "Tổng chi phí là: " << tongcp << endl;
}
void LeastCost::Hienthi(MT mtr1)
{
    cout << "Ma tran van tai:\n";
    cout << "cung/cau ";
    for (int j = 0; j < mtr1.n; j++) {
        cout << "b" << j+1 << " ";
    }
    cout << endl;
    for (int i = 0; i < mtr1.m; i++) {
        cout << "a" << i+1 << "      ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.c[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nMa tran phan bo:\n";
    cout << "cung/cau ";
    for (int j = 0; j < mtr1.n; j++) {
        cout << "b" << j+1 << " ";
    }
    cout << endl;
    for (int i = 0; i < mtr1.m; i++) {
        cout << "a" << i+1 << "      ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.a[i*mtr1.n+j] << " ";
        }
        cout << endl;
    }
}
int main() {
    MT mtr;
    LeastCost lc;
    lc.ThietLapMT(&mtr);
    lc.Chiahang(&mtr);
    lc.Hienthi(mtr);
    lc.TongCuocPhi(mtr);
    return 0;
}



