#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<cmath>
#include <fstream>
#include <vector>
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
    #include<iostream>
#include<stdio.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<cmath>
#include <fstream>
#include <vector>
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
    struct MT mtr1;
public:
    void ThietLapMT(MT *mtr1);
    void Chiahang(MT *mtr1);
    friend void TongCuocPhi(MT mtr1);
    friend void Hienthi(MT mtr1);
    friend void DonHinh(MT *mtr1);
    friend void GocTayBac(MT &mtr1);
    friend void InMT(int arr[MAX][MAX],int m ,int n);
    friend int TimChuTrinh(MT mtr1,int &m,int &n,int x[MAX],int y[MAX] );
};
//ThietLapMT sẽ làm nhiệm vụ nhập dữ liệu và cân bằng cung cầu
void LeastCost::ThietLapMT(MT *mtr1){
    int c2[MAX][MAX]; // khai báo ma trận mới c2 để lưu trữ ma trận cũ và thêm hàng hoặc cột mới
    fstream file;
    string filename = "data.txt";   
    // Mở file để đọc dữ liệu
    file.open(filename, ios::in);
    // Kiểm tra xem file có tồn tại không
    if (!file) {
    cout << "Khong the mo file!" << endl;
    cout<<" Số trạm cung ứng : ";
    cin >> mtr1->m;
    cout<<" Số trạm nhận hàng : ";
    cin >> mtr1->n;
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
        return ;
    };
    }
    // Đọc dữ liệu từ file
        file >> mtr1->m;
        file >> mtr1->n;
        for(int i=0; i<mtr1->m;i++){
            for(int j = 0; j < mtr1->n; j++){
                int value;
                file >> value;
                mtr1->c[i][j]=value;
            }
        }
        for (int i = 0; i <  mtr1->m; i++) {
        file >> mtr1->a[i];
       mtr1->tongcung = mtr1->tongcung + mtr1->a[i];
    }
    for (int i = 0; i <  mtr1->n; i++) {
        file >> mtr1->b[i];
        mtr1->tongcau = mtr1->tongcau + mtr1->b[i];
    }; 
    file.close();
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
void LeastCost::Chiahang(MT *mtr1) {
    struct MT mtr2 = *mtr1;
    while(true) {
        int m = -1, n = -1;
        int smallest = 1000; 
        for(int i=0; i<mtr2.m; i++) {
            for(int j=0; j<mtr2.n; j++) {
                if(mtr2.c[i][j] != 0 && mtr2.c[i][j] < smallest) {
                    smallest = mtr2.c[i][j];
                    // lấy vị trí của cước phí nhỏ nhất
                    m=i;
                    n=j;
                }
            }
        }
        if (m==-1 || n==-1) {
            break;
        }
        if(mtr2.a[m] == 0 || mtr2.b[n] == 0 ) {
            mtr2.c[m][n]=0;
        } else if (mtr2.a[m]>mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.b[n];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.a[m]=mtr2.a[m]-mtr2.b[n];
            mtr2.b[n]=0;
            mtr2.c[m][n]=0;
        } else if(mtr2.a[m]<mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.a[m];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.b[n]=mtr2.b[n]-mtr2.a[m];
            mtr2.a[m]=0;
            mtr2.c[m][n]=0;
        } else if (mtr2.a[m]==mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.a[m];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.a[m]=0;
            mtr2.b[n]=0;
            mtr2.c[m][n]=0;
        }       
    }
    if (mtr2.tongcung == 0 && mtr2.tongcau == 0) {
            return;
        } else if ( mtr2.tongcung == 0 && mtr2.tongcau != 0) {
            for ( int i = 0; i < mtr2.n; i++) {
                mtr2.x[mtr2.m-1][i]=mtr2.b[i];
                mtr2.b[i]=0;  
            }
        } else if (mtr2.tongcung != 0 && mtr2.tongcau == 0) {
            for ( int i = 0; i < mtr2.m; i++) {
                mtr2.x[i][mtr2.n-1]=mtr2.a[i];
                mtr2.a[i]=0;  
            }
        }
    //chuyển ma trận chuyển hàng từ mtr2 sang mtr1 
    for (int i = 0; i < mtr1->m; i++) {
        for (int j = 0; j < mtr1->n; j++) {
            mtr1->x[i][j] = mtr2.x[i][j];
        }
    }
}
void TongCuocPhi(MT mtr1)
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
void Hienthi(MT mtr1)
{
    cout << "Ma Trận cước phí:"<<endl;
    cout << "Cung/Cầu ";
    for (int j = 0; j < mtr1.n; j++) {
        cout <<"("<<mtr1.b[j]<<") ";
    }
    cout << endl;

    for (int i = 0; i < mtr1.m; i++) {
        cout <<"("<<mtr1.a[i]<<")    ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.c[i][j] <<"  ";
        }
        cout << endl;
    }
    cout << "Ma trận chuyển hàng:"<<endl;
    cout << "cung/cau ";
    for (int j = 0; j < mtr1.n; j++) {
        cout <<"("<< mtr1.b[j]<<") ";
    }
    cout << endl;
    for (int i = 0; i < mtr1.m; i++) {
        cout << mtr1.a[i] << "      ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.x[i][j] << " ";
        }
        cout << endl;
    }
}
// Hàm InMT để in ma trận ra màn hình
void InMT(int arr[MAX][MAX],int m ,int n){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
}
}
//hàm GocTayBac dùng để chia hàng theo phương pháp góc Tây Bắc
void GocTayBac(MT &mtr1)
{
    struct MT mtr2 = mtr1;
    int i = 0; 
    int j = 0;
while (true){   
    
    if (mtr2.a[i]<mtr2.b[j]){
    mtr2.x[i][j]= mtr2.a[i];
    mtr2.b[j]=abs(mtr2.a[i]-mtr2.b[j]);
    mtr2.a[i]=0;
    i = i+1;
    }
    if (mtr2.a[i]>mtr2.b[j]){
    mtr2.x[i][j]=mtr2.b[j];
    mtr2.a[i]=abs(mtr2.a[i]-mtr2.b[j]);
    mtr2.b[j]=0;
    j = j+1;
    }
    if(mtr2.a[i]==mtr2.b[j]){
    mtr2.x[i][j]=mtr2.a[i];
    mtr2.b[j]=0;
    mtr2.a[i]=0;
    i = i+1;
    j = j+1;
    }
if (i==mtr1.m && j==mtr1.n ){
     break;
}
}
for (int i = 0; i < mtr1.m; i++) {
        for (int j = 0; j < mtr1.n; j++) {
            mtr1.x[i][j] = mtr2.x[i][j];
        }
    }
}
bool AskToContinue() {
    char choice;
    while (true) {
        cout << "Bạn có muốn tiếp tục ? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            cout << "Nhập sai." << endl;
        }
    }
}
int TimChuTrinh(MT mtr1,int &m,int &n,int x[MAX],int y[MAX] ){
    int z=1;
    for(int i=0; i<mtr1.m;i++){
        for(int j=0;j<mtr1.n;j++){
            if((mtr1.x[i][j] !=0 && m==i)||(mtr1.x[i][j] !=0 && n==j)){
                m=i;
                n=j;
                x[z]=i;
                y[z]=j;
                z=z+1;
            }
        }
    }
    for(int i;i<z;i++){
        cout<<"step "<<i+1<<" x["<<x[i]<<"]["<<y[i]<<"]"<<endl;
    }
}
void DonHinh(MT *mtr1)
{
// tính số thế vị
int u[MAX]={0};
int v[MAX]={0};
int o[MAX][MAX]={0};// để đánh dấu vị trí ô chọn
int d=0; // dùng để kiểm tra suy biến
int delta[MAX][MAX];// delta 
for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            if(mtr1->x[i][j]!=0){ 
                o[i][j]=1;
                d=d+1;
            }}}
if(d == ((mtr1->m) + (mtr1->n) - 1)){
    cout<<"Phương án cơ bản không suy biến"<<endl;
    InMT(o, mtr1->m, mtr1->n);
}else if(d < ((mtr1->m) + (mtr1->n) - 1)){
cout<<"Phương án cơ bản suy biến";
    while(true){
    if(AskToContinue()){
        int smallest;
        int c,d;
        for(int i=0; i<mtr1->m;i++){
            for(int j=0; j<mtr1->n;j++){
                if (mtr1->c[i][j]<smallest && mtr1->x[i][j]==0){
                    smallest=mtr1->c[i][j];
                    c=i;
                    d=j;
                }
            }
        }
        o[c][d]=1;
         InMT(o, mtr1->m, mtr1->n);
        break;
    }else{
        break;
    }
}
}
//tính u[i] và v[j]
int sopheptinh=0;
while(true){
    for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            if(mtr1->x[i][j]!=0){
            if(u[i]==0 && i !=0 && v[j]!=0){
                u[i]=mtr1->c[i][j]-v[j];
                sopheptinh = sopheptinh+1;
            }
            if(v[j]==0 && u[i] == 0 && i == 0 ){              
                v[j]=mtr1->c[i][j]-u[i];
                sopheptinh = sopheptinh+1;
                }else if (v[j]==0 && u[i] !=0 && i!=0){               
                v[j]=mtr1->c[i][j]-u[i];
                sopheptinh = sopheptinh+1;
                }
                }
            }
            }
    if(sopheptinh ==((mtr1->m) + (mtr1->n) - 1)){
        break;
    }            
}
for(int i=0; i<mtr1->m;i++){
            cout<<"u["<<i<<"] :"<<u[i]<<endl;
       }
for(int j=0; j<mtr1->n;j++){             
            cout<<"v["<<j<<"] :"<<v[j]<<endl;
         }
//tính số kiểm tra 
    for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            delta[i][j]=u[i]+v[j]-mtr1->c[i][j];
            cout<<"delta["<<i<<"]["<<j<<"]:"<<delta[i][j]<<endl;
        }
    }
int m,n,a=0;
int biggest=0;
int x[MAX],y[MAX];//tạo mảng để lưu trữ các bước đi của chu trình
   for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            if (delta[i][j]>0){
                cout<<"Bài toán chưa tối ưu"<<endl;
                a=a+1;
                if (delta[i][j]>0 && delta[i][j]>biggest){
                delta[i][j]=biggest;
                //lấy vị trí có delta dương lớn nhất
                m=i;
                n=j;
                }
            }
        }
    }
x[0]=m; y[0]=n;//gán vị trí đầu tiên trong chu trình và tìm kiếm chu trình
int z=1;
if (a>0){
if(AskToContinue()){
while(true){
        for(int i=0; i<mtr1->m;i++){
        for(int j=0;j<mtr1->n;j++){
            if((mtr1->x[i][j] !=0 && m==i)||(mtr1->x[i][j] !=0 && n==j)){
                m=i;
                n=j;
                x[z]=i;
                y[z]=j;
                z=z+1;
            }
        }
        }
            for(int i=0;i<z+1;i++){
        cout<<"step "<<i+1<<" x["<<x[i]<<"]["<<y[i]<<"]"<<endl;
    } 
        int smallest=1000;
        for(int l=1; l<z;l++){
            if((l+1)%2==0){
                 if(mtr1->x[x[l]][y[l]]<smallest){
                    smallest=mtr1->x[x[l]][y[l]];
                 }
                cout<<mtr1->x[x[l]][y[l]]<<endl;
                }
                }
                cout<<smallest<<endl;
        for(int l=0; l<z;l++){
            if((l+1) % 2 != 0){
                mtr1->x[x[l]][y[l]]=mtr1->x[x[l]][y[l]]+smallest;
            }
            if((l+1) % 2 == 0 ){
                mtr1->x[x[l]][y[l]]=mtr1->x[x[l]][y[l]]-smallest;
            }
        }
         Hienthi(*mtr1);
        TongCuocPhi(*mtr1);

    if(AskToContinue()){
        DonHinh(mtr1);
    }else{
        break;
    }
}
}
}
}
int main() {
    MT mtr,mtr3;
    LeastCost lc; 
    lc.ThietLapMT(&mtr);
    mtr3 = mtr;
    lc.Chiahang(&mtr);
    //GocTayBac(&mtr3);
    //cout<<"Phương Pháp LeastCost :"<<endl;
    Hienthi(mtr);
    TongCuocPhi(mtr);
    //cout<<"Phương Pháp North-West Corner :"<<endl;
    //lc.Hienthi(mtr3);
    //lc.TongCuocPhi(mtr3);
    DonHinh(&mtr);
    return 0;
}


int tongcung=0;// tổng số hàng cung
    int tongcau=0;// tổng số hàng cầu
};
class LeastCost{
    struct MT mtr1;
public:
    void ThietLapMT(MT *mtr1);
    void Chiahang(MT *mtr1);
    void TongCuocPhi(MT mtr1);
    void Hienthi(MT mtr1);
    friend void DonHinh(MT *mtr1);
    friend void GocTayBac(MT &mtr1);
    friend bool CheckMang(int arr[MAX],int n);
};
//ThietLapMT sẽ làm nhiệm vụ nhập dữ liệu và cân bằng cung cầu
void LeastCost::ThietLapMT(MT *mtr1){
    int c2[MAX][MAX]; // khai báo ma trận mới c2 để lưu trữ ma trận cũ và thêm hàng hoặc cột mới
    fstream file;
    string filename = "data.txt";   
    // Mở file để đọc dữ liệu
    file.open(filename, ios::in);
    // Kiểm tra xem file có tồn tại không
    if (!file) {
    cout << "Khong the mo file!" << endl;
    cout<<" Số trạm cung ứng : ";
    cin >> mtr1->m;
    cout<<" Số trạm nhận hàng : ";
    cin >> mtr1->n;
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
        return ;
    };
    }
    // Đọc dữ liệu từ file
        file >> mtr1->m;
        file >> mtr1->n;
        for(int i=0; i<mtr1->m;i++){
            for(int j = 0; j < mtr1->n; j++){
                int value;
                file >> value;
                mtr1->c[i][j]=value;
            }
        }
        for (int i = 0; i <  mtr1->m; i++) {
        file >> mtr1->a[i];
       mtr1->tongcung = mtr1->tongcung + mtr1->a[i];
    }
    for (int i = 0; i <  mtr1->n; i++) {
        file >> mtr1->b[i];
        mtr1->tongcau = mtr1->tongcau + mtr1->b[i];
    }; 
    file.close();
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
void LeastCost::Chiahang(MT *mtr1) {
    struct MT mtr2 = *mtr1;
    while(true) {
        int m = -1, n = -1;
        int smallest = 100; 
        for(int i=0; i<mtr2.m; i++) {
            for(int j=0; j<mtr2.n; j++) {
                if(mtr2.c[i][j] != 0 && mtr2.c[i][j] < smallest) {
                    smallest = mtr2.c[i][j];
                    // lấy vị trí của cước phí nhỏ nhất
                    m=i;
                    n=j;
                }
            }
        }
        if (m==-1 || n==-1) {
            break;
        }
        if(mtr2.a[m] == 0 || mtr2.b[n] == 0 ) {
            mtr2.c[m][n]=0;
        } else if (mtr2.a[m]>mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.b[n];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.a[m]=mtr2.a[m]-mtr2.b[n];
            mtr2.b[n]=0;
            mtr2.c[m][n]=0;
        } else if(mtr2.a[m]<mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.a[m];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.b[n]=mtr2.b[n]-mtr2.a[m];
            mtr2.a[m]=0;
            mtr2.c[m][n]=0;
        } else if (mtr2.a[m]==mtr2.b[n]) {
            mtr2.x[m][n]=mtr2.a[m];
            mtr2.tongcung=mtr2.tongcung-mtr2.a[m]; 
            mtr2.tongcau=mtr2.tongcau-mtr2.b[n];
            mtr2.a[m]=0;
            mtr2.b[n]=0;
            mtr2.c[m][n]=0;
        }
        
    }
    if (mtr2.tongcung == 0 && mtr2.tongcau == 0) {
            return;
        } else if ( mtr2.tongcung == 0 && mtr2.tongcau != 0) {
            for ( int i = 0; i < mtr2.n; i++) {
                mtr2.x[mtr2.m-1][i]=mtr2.b[i];
                mtr2.b[i]=0;  
            }
        } else if (mtr2.tongcung != 0 && mtr2.tongcau == 0) {
            for ( int i = 0; i < mtr2.m; i++) {
                mtr2.x[i][mtr2.n-1]=mtr2.a[i];
                mtr2.a[i]=0;  
            }
        }
    //chuyển ma trận chuyển hàng từ mtr2 sang mtr1 
    for (int i = 0; i < mtr1->m; i++) {
        for (int j = 0; j < mtr1->n; j++) {
            mtr1->x[i][j] = mtr2.x[i][j];
        }
    }
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
    cout << "Ma Trận cước phí:"<<endl;
    cout << "Cung/Cầu ";
    for (int j = 0; j < mtr1.n; j++) {
        cout <<"("<<mtr1.b[j]<<") ";
    }
    cout << endl;

    for (int i = 0; i < mtr1.m; i++) {
        cout <<"("<<mtr1.a[i]<<")    ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.c[i][j] <<"  ";
        }
        cout << endl;
    }
    cout << "Ma trận chuyển hàng:"<<endl;
    cout << "cung/cau ";
    for (int j = 0; j < mtr1.n; j++) {
        cout <<"("<< mtr1.b[j]<<") ";
    }
    cout << endl;
    for (int i = 0; i < mtr1.m; i++) {
        cout << mtr1.a[i] << "      ";
        for (int j = 0; j < mtr1.n; j++) {
            cout << mtr1.x[i][j] << " ";
        }
        cout << endl;
    }
}
void GocTayBac(MT &mtr1)
{
    struct MT mtr2 = mtr1;
    int i = 0; 
    int j = 0;
while (true){   
    
    if (mtr2.a[i]<mtr2.b[j]){
    mtr2.x[i][j]= mtr2.a[i];
    mtr2.b[j]=abs(mtr2.a[i]-mtr2.b[j]);
    mtr2.a[i]=0;
    i = i+1;
    }
    if (mtr2.a[i]>mtr2.b[j]){
    mtr2.x[i][j]=mtr2.b[j];
    mtr2.a[i]=abs(mtr2.a[i]-mtr2.b[j]);
    mtr2.b[j]=0;
    j = j+1;
    }
    if(mtr2.a[i]==mtr2.b[j]){
    mtr2.x[i][j]=mtr2.a[i];
    mtr2.b[j]=0;
    mtr2.a[i]=0;
    i = i+1;
    j = j+1;
    }
if (i==mtr1.m && j==mtr1.n ){
     break;
}
}
for (int i = 0; i < mtr1.m; i++) {
        for (int j = 0; j < mtr1.n; j++) {
            mtr1.x[i][j] = mtr2.x[i][j];
        }
    }
}
bool CheckMang(int Arr[MAX], int n) {
    int count=0;
    for (int i = 0; i < n+1; i++) {
        if (Arr[i] != 0) {
            count = count + 1;
        }
    }
    if(count==n){
    return true;
    }
    else{
        return false;
    }
}
bool AskToContinue() {
    char choice;
    while (true) {
        cout << "Bài toán chưa tối ưu bạn có muốn tiếp tục ? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            cout << "Nhập sai." << endl;
        }
    }
}
void DonHinh(MT *mtr1)
{
// tính số thế vị
int u[MAX]={0};
int v[MAX]={0};
while(true){
    for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            if(mtr1->x[i][j]!=0){
            if(u[i]==0 && i !=0 && v[j]!=0){
                u[i]=mtr1->c[i][j]-v[j];
            }
            if(v[j]==0 && u[i] == 0 && i == 0 ){              
                v[j]=mtr1->c[i][j]-u[i];
                }else if (v[j]==0 && u[i] !=0 && i!=0){               
                v[j]=mtr1->c[i][j]-u[i];
                }
                }
            }
            }
    int count=0;
    for (int i = 0; i < mtr1->n; i++) {
        if (v[i] != 0) {
            count = count + 1;
        }
    }
    if(count==mtr1->n){
        break;
    }            
}
for(int i=0; i<mtr1->m;i++){
            cout<<"u["<<i<<"] :"<<u[i]<<endl;
       }
for(int j=0; j<mtr1->n;j++){             
            cout<<"v["<<j<<"] :"<<v[j]<<endl;
         }
//tính số kiểm tra 
int biggest=0;
int m,n,a=0;
int delta[MAX][MAX];
    for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            delta[i][j]=u[i]+v[j]-mtr1->c[i][j];
            cout<<"delta["<<i<<"]["<<j<<"]:"<<delta[i][j]<<endl;
        }
    }
   for(int i=0; i<mtr1->m;i++){
        for(int j=0; j<mtr1->n;j++){
            if (delta[i][j]>0){
                cout<<"Bài toán chưa tối ưu"<<endl;
                a=a+1;
                if (delta[i][j]>0 && delta[i][j]>biggest){
                delta[i][j]=biggest;
                //lấy vị trí có delta dương lớn nhất
                i=m;
                j=n;
                }
            }
        }
    }
if (a>0)
    if(AskToContinue()){
        
    }
}
int main() {
    MT mtr,mtr3;
    LeastCost lc; 
    lc.ThietLapMT(&mtr);
    mtr3 = mtr;
    lc.Chiahang(&mtr);
    //GocTayBac(&mtr3);
    //cout<<"Phương Pháp LeastCost :"<<endl;
    lc.Hienthi(mtr);
    lc.TongCuocPhi(mtr);
    //cout<<"Phương Pháp North-West Corner :"<<endl;
    //lc.Hienthi(mtr3);
    //lc.TongCuocPhi(mtr3);
    DonHinh(&mtr);
    return 0;
}


