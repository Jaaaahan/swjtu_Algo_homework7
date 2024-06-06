#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;
typedef struct 
{
    int x0,y0;
    int step;
    int distance;
}snake;
int exit_x,exit_y;
int direction[4][4]={{1,0},{0,1},{-1,0},{0,-1}};
int MIN_DIS=100000;
vector<vector<int> > block;
vector<vector<bool> > visited;
int n,m;
// void countdistance(snake s1)
// {
    
//     s1.distance= ;
// }
bool meetblock(int x,int y,vector<snake> current)
{
    for (int i = 0; i < block.size(); i++)
    {
        if (x==block[i][0]&&y==block[i][1])
        {
            return true;
        }
    }
    for (int i = 1; i < current.size(); i++)  //吃到自己
    {
        if (x==current[i].x0&&y==current[i].y0)
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
void moveforward(vector<snake> &current,vector<snake> tempsnake)
{
    for (int i = 1; i < current.size(); i++)
    {
        current[i].x0=tempsnake[i-1].x0;
        current[i].y0=tempsnake[i-1].y0;
    }
}
void BFS(vector<snake> current,int x1,int y1)
{
    queue<vector<snake> > snakelist;  
    snakelist.push(current);  //列表中存储的应该是状态
    while (!snakelist.empty())
    {
        current=snakelist.front();  //取蛇的状态
        snakelist.pop();
        if (current[0].x0==x1&&current[0].y0==y1)
        {
            // MIN_DIS=min(current.distance,MIN_DIS);
            // continue;
            MIN_DIS=current[0].step;
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (meetblock(current[0].x0+direction[i][0],current[0].y0+direction[i][1],current)
                ||overboundary(current[0].x0+direction[i][0],current[0].y0+direction[i][1])
                ||visited[current[0].x0+direction[i][0]][current[0].y0+direction[i][1]])
            {
                continue;
            }
            visited[current[0].x0+direction[i][0]][current[0].y0+direction[i][1]]=true;
            vector<snake> tempsnake1=current;
            vector<snake> tempsnake2=current;
            tempsnake1[0].x0=current[0].x0+direction[i][0];
            tempsnake1[0].y0=current[0].y0+direction[i][1];
            tempsnake1[0].step++;
            moveforward(tempsnake1,tempsnake2);
            snakelist.push(tempsnake1);
        }
    }
    return;  
}

int main()
{
    int k,x0,y0,l;
    cin>>n>>m>>l;
    vector<snake> snakes;
    snakes.resize(l,{0,0,0,10000});
    for (int i = 0; i < l; i++)
    {
        cin>>snakes[i].x0>>snakes[i].y0;
    }
    cin>>k;
    block.resize(k,vector<int>(2));
    for (int i = 0; i < k; i++)
    {
        cin>>block[i][0]>>block[i][1];
    }
    visited.resize(n+1,vector<bool>(m+1,false));
    auto start = high_resolution_clock::now();
    BFS(snakes,1,1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<MIN_DIS<<endl;
    cout << "Execution time: " << duration.count() << " microseconds" << endl;


}