#include<iostream>
#include<vector>
#include<string>
#include<algorithm>  // 添加algorithm头文件用于reverse函数
using namespace std;

/*此函数用于去除前导0*/
void trim(vector<int> &a){
    while(a.size() > 1 && a.back() == 0){
        a.pop_back();
    }
}

/*此函数用于比较高精度数的大小*/

bool cmp(vector<int> &a, vector<int> &b){
    //如果a与b位数不同，a位数多返回true否则false
    if(a.size() != b.size()){
        return a.size() > b.size();
    }
    //如果a与b位数相同，比较每一位
    for(int i = a.size() - 1; i >= 0; i--){
        if(a[i] != b[i]){
            return a[i] > b[i];
        }
    }
    return true;
} 

/*此函数用于实现高精度数乘以单精度数的运算*/
vector<int> mul(vector<int> &a, int &b){
    vector<int> c;
    c.resize(a.size() + 1, 0);
    for(int i = 0; i < a.size(); i++){
        c[i] += a[i] * b;
    }
    for(int i = 0; i < c.size(); i++){
        if(c[i] >= 10){
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    trim(c);
    return c;
}
//此函数用于实现a > b时的高精度数减法
void sub(vector<int> &a, vector<int> &b){
    //当a小于b时，返回,不做处理
    if(!cmp(a, b)){
        return;
    }
    //a与b对应位相减
    for(int i = 0; i < a.size(); i++){
        if(i < b.size()){
            a[i] -= b[i];
        }
    }
    //借位
    for(int i = 0; i < a.size() - 1; i++){
        if(a[i] < 0){
            a[i + 1]--;
            a[i] += 10;
        }
    }
    //去除前导0
    trim(a);
}

/*此函数用于实现高精度除法中的模拟试商*/
int div_one(vector<int> &a, vector<int> &b){
    //当b为0或者为空，抛出异常
    if(b.empty() || (b.size() == 1 && b[0] == 0)){
        throw runtime_error("Division by zero");
    }
    //模拟试商
    int ret = 0;
    for(int i = 1; i < 10; i++){
        vector<int> t = mul(b, i);
        if(!cmp(a, t)){
            break;
        }
        ret++;
    }
    //减去试商乘以被除数
    vector<int> c = mul(b, ret);
    sub(a, c);
    return ret;
}
/*此函数用于实现高精度除法*/
vector<int> div(vector<int> &a, vector<int> &b){ 
    //去除前导0
    trim(a);
    trim(b);
    // 除数为0或者为空为0时，异常判断
    if(b.empty() || (b.size() == 1 && b[0] == 0)) {
        throw runtime_error("Division by zero");
    }
    //当a小于b时，返回0
    if(!cmp(a, b)){
        return {0};
    }

    vector<int> c;
    vector<int> t(a.size(), 0); 

    // 构造与被除数对齐的除数
    int offset = a.size() - b.size();
    for(int i = 0; i < b.size(); i++){
        t[offset + i] = b[i];
    }
    // 模拟除法
    for(int i = offset; i >= 0; i--){
        //试商
        int cnt = div_one(a, t);
        //把商记录下来
        c.push_back(cnt);
        if(i > 0){
            // 通过手动移位t
            for(int j = 1; j < t.size(); j++) {
                t[j-1] = t[j];
                t[j] = 0;
            }
            trim(t);
        }
    }
    reverse(c.begin(), c.end());    // 将结果翻转
    trim(c);
    return c;
}

template<typename T>
void inputNumber(T &a){
    string s;
    cin >> s;
    // 增加输入合法性检查
    for(char ch : s) {
        if(!isdigit(ch)) {
            throw invalid_argument("Invalid digit in input");
        }
    }
    for(int i = s.size() - 1; i >= 0; i--){
        a.push_back(s[i] - '0');
    }
}

template<typename T>
void printNumber(const T &a){ 
    for(int i = a.size() - 1; i >= 0; i--){
        cout << a[i];
    }
    cout << endl;
}

int main(){
    try {
        vector<int> a, b;
        inputNumber(a);
        inputNumber(b);
        vector<int> result = div(a, b); 
        printNumber(result);
        printNumber(a);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}