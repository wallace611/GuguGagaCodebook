#define ll long long
int extgcd(int a, int b, int &x, int &y) {
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int GCD=extgcd(b, a%b, y, x);
    y -= a / b * x;
    return GCD;
}

int main(){
    int a, b, x, y;
    cin >> a >> b;
    int GCD = extgcd(a, b, x, y);
}