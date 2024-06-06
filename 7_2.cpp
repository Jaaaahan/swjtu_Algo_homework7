/*
一个人在一个由方格组成的矩形区域中按上、下、左、右四个方向移动（每次移动记为一步），区域内可能存在障碍物，每个障碍物占用一个方格
，无法通行。计算人从起点方格移动终点方格所需的最少步数。
输入要求：
测试数据的第一行包含 7 个整数 n、 m、k、x0、y0、x1、y1，分别表示矩形区域的行、列方格数（n和m），区域内障碍物的数量（k），
人的起点方格坐标（行列号，x0和y0），终点方格坐标（行列号，x1和y1）。之后的 k 行，每行包含两个整数，分别表示障碍物所占用的
方格的行列号。
输入用例：
4 3 3 3 1 1 1
1 3
2 1
4 1
*/


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int direction[4][4]={{1,0},{0,1},{-1,0},{0,-1}};
vector<vector<int> > block;
typedef struct
{
    int x0,y0;
    int distance;
}node;
int n,m;
int MIN_DIS=0xffff;
bool meetblock(int x,int y)
{
    for (int i = 0; i < block.size(); i++)
    {
        if (x==block[i][0]&&y==block[i][1])
        {
            return true;
        }
        
    }
    return false;
}
bool overboundary(int x,int y)
{
    if (x>n||y>m||x<1||y<1)
    {
        return true;
    }else return false;
}
vector<vector<bool> > visited;
void BFS(node current,int x1,int y1)
{
    queue<node> nodelist;
    nodelist.push(current);
    while (!nodelist.empty())
    {
        current=nodelist.front();
        nodelist.pop();
        if (current.x0==x1&&current.y0==y1)
        {
            // MIN_DIS=min(current.distance,MIN_DIS);
            // continue;
            MIN_DIS=current.distance;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (meetblock(current.x0+direction[i][0],current.y0+direction[i][1])
                ||overboundary(current.x0+direction[i][0],current.y0+direction[i][1])
                ||visited[current.x0+direction[i][0]][current.y0+direction[i][1]])
            {
                continue;
            }
            visited[current.x0+direction[i][0]][current.y0+direction[i][1]]=true;
            nodelist.push({current.x0+direction[i][0],current.y0+direction[i][1],current.distance+1});
        }
    }
    return;  
}

int main()
{
    int k,x0,y0,x1,y1;
    cin>>n>>m>>k>>x0>>y0>>x1>>y1;
    block.resize(k,vector<int>(2));
    for (int i = 0; i < k; i++)
    {
        cin>>block[i][0]>>block[i][1];
    }
    node start({x0,y0,0});
    visited.resize(n+1,vector<bool>(m+1,false));
    BFS(start,x1,y1);
    if (MIN_DIS!=0xffff)
    {
        cout<<MIN_DIS<<endl;
    }else
    cout<<"Impossible"<<endl;
    
}