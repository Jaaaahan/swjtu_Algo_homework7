/*
小李希望开车到全国各地旅游，他发现旅途中各个城市的汽油价格也不相同，显然如果能够采取合理的加油方式，将会节省整个旅途的费用。
假设汽车开始时油箱为空，汽车每走一个单位的距离将耗费一个单位的汽油。请帮助小李找到一种最省钱的方式完成他的整个自驾游。

输入要求：
输入的第一行包含两个整数n （1 ≤ n ≤ 1000）和m（0 ≤ m ≤ 10000），分别表示城市的数量以及道路的数量。其后的一行包含n个整数，
分别表示n个城市的汽油价格。其后的m行，每一行包含三个整数u,v,d，表示城市u，v之间的距离为d（1 ≤ d ≤ 100）。
最后一行包含三个整数c（ 1 ≤ c ≤ 100）,s,e,分别表示油箱的容量，出发的城市和最后到达的城市。
输出要求：
如果能够帮助小李找到一个最省钱从s到e的路线，则输出对应的费用，否则输出“impossible”。
样例输入：
4  6
8  10  6  7
0  1  8
0  3  12
1  2  10
2  3  7
1  3  9
0  2  10
10  0  3

*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n,m;
vector<int> gas_price;
vector<vector<int> >map;
vector<bool> visited;
typedef struct 
{
    int citylabel;
    // int left_gas;
    // int gas_price;
    vector<int> travel_distance;
    vector<int> citytraveled;
    int cost;
}travel_status;
int MIN_COST=10000;
int count_cost(vector<int> citytraveled,vector<int> travel_distance)
{
    int min_cost=100000;
    for (int i = 0; i < citytraveled.size()-1; i++)
    {
        min_cost=min(min_cost,gas_price[citytraveled[i]]);
    }
    int min_city_label;
    for (int i = 0; i < citytraveled.size()-1; i++)
    {
        if (gas_price[citytraveled[i]]==min_cost)
        {
            min_city_label=citytraveled[i];
        }
    }

    int sum_cost=0;
    for (int i = 0; i < citytraveled.size(); i++)
    {
        if (citytraveled[i]==min_city_label)
        {
            for (int k = i+1; k < travel_distance.size(); k++)
            {
                
                sum_cost=sum_cost+min_cost*travel_distance[k];
            }
            if (i==0)
            {
                return sum_cost;
            }
            vector<int> sub_citytraveled,sub_travel_distance;
            sub_citytraveled.assign(citytraveled.begin(),citytraveled.begin()+i+1);
            sub_travel_distance.assign(travel_distance.begin(),travel_distance.begin()+i+1);

            return sum_cost+count_cost(sub_citytraveled,sub_travel_distance);
        }
        
    }   
}
struct cmp{
    bool operator()(travel_status a,travel_status b)
    {
        return a.cost>b.cost;
    }
};
void BFS(int start,int end,int total_gas)
{
    visited[start]=true;
    priority_queue<travel_status,vector<travel_status>,cmp> status_list;
    travel_status initial_status,next_status;
    initial_status.citylabel=start;
    initial_status.travel_distance.push_back(0);
    initial_status.citytraveled.push_back(start);
    initial_status.cost=count_cost(initial_status.citytraveled,initial_status.travel_distance);
    status_list.push(initial_status);
    while (!status_list.empty())
    {
        travel_status current=status_list.top();
        status_list.pop();
        visited[current.citylabel]=true;
        if (current.citylabel==end)
        {
            MIN_COST = min(MIN_COST,count_cost(current.citytraveled,current.travel_distance));
            return;
        }
        for (int i = 0; i < map[current.citylabel].size(); i++)
        {

            if (map[current.citylabel][i]!=0&&visited[i]==false&&map[current.citylabel][i]<=total_gas)
            {
                next_status.citylabel=i;
                next_status.travel_distance=current.travel_distance;
                next_status.travel_distance.push_back(map[current.citylabel][i]);
                next_status.citytraveled=current.citytraveled;
                next_status.citytraveled.push_back(i);
                next_status.cost=count_cost(next_status.citytraveled,next_status.travel_distance);
                status_list.push(next_status);
            }
            
        }
        
    }
    
}

int main()
{
    cin>>n>>m;
    gas_price.resize(n,0);
    map.resize(n,vector<int>(n,0));
    visited.resize(n,false);
    for (int i = 0; i < n; i++)
    {
        cin>>gas_price[i];
    }
    int a,b,d;
    for (int i = 0; i < m; i++)
    {
        cin>>a>>b;
        cin>>d;
        map[a][b]=map[b][a]=d;
    }
    int total_gas,start,end;
    cin>>total_gas>>start>>end;
    BFS(start,end,total_gas);
    cout<<MIN_COST<<endl;
}
