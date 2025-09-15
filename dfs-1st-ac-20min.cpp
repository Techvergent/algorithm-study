#include<iostream>
using namespace std;


bool mark[6][6] = {false};
int path[26][3];
const int n = 5;
int cnt = 0;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
void my_cout(int k){
    cnt++;
    for(int i = 1; i <= k; i++){
        cout << cnt << ": ";
        if(i != k){
            cout << "(" <<path[i][1] << "," << path[i][2] << ") " << "-> ";
        }else{
            cout << "(" <<path[i][1] << "," << path[i][2] << ")" << endl;
        }
    }
}

bool judge(int x, int y){
    if(x > n || y > n || x < 1 || y < 1 || mark[x][y]){
        return false;
    }
    return true;
}

void dfs(int x, int y, int k){
    //记录当前路径
    path[k][1] = x;
    path[k][2] = y;
    //到了终点就输出
    if(x == n && y == n){
        //输出路径
        my_cout(k);
        //结束函数
        return;
    }
    for(int i = 0; i < 4; i++){
        //模拟右下左上四种运动 
        int nx = x + dx[i];
        int ny = y + dy[i];
        //如果可以走到
        if(judge(nx, ny)){
            //标记下一个节点
            mark[nx][ny] = true;
            //继续往下走输出结果
            dfs(nx, ny, k + 1);
            //一条路径输出完之后回到这里
            //清空格子的标记
            mark[nx][ny] = false;
        }
    }
}






