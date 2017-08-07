/*
ID: suzyzha1
PROG: schlnet
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 102;

int n;
bool g[maxn][maxn];

int top=0,stack[maxn];
bool in_satck[maxn];
int idx=0,dfn[maxn],low[maxn];

int tot=0,color[maxn];
int in_degree[maxn],out_degree[maxn];

void tarjan(int cur)
{
	idx++;
	dfn[cur]=low[cur]=idx;

	top++;
	stack[top]=cur;
	in_satck[cur]=true;

	for(int i=1;i<=n;i++)
		if(g[cur][i])
		{
			if(dfn[i]==0)
			{
				tarjan(i);
				low[cur]=min(low[cur],low[i]);
			}
			else
			if(in_satck[i])
				low[cur]=min(low[cur],dfn[i]);
		}

	if(low[cur]==dfn[cur])
	{
		tot++;
		int j;
		do{
			j=stack[top];
			color[j]=tot;
			in_satck[j]=false;
			top--;
		}while(j!=cur);
	}
}

int main()
{
	fstream fin("schlnet.in",ios::in);
	fstream fout("schlnet.out",ios::out);

	fin>>n;
	int t;
	for(int i=1;i<=n;i++)
		while(true)
		{
			fin>>t;
			if(t==0) break;
			g[i][t]=true;
		}

	for(int i=1;i<=n;i++)
		if(dfn[i]==0)
			tarjan(i);

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(g[i][j] && color[i]!=color[j])
			{
				in_degree[color[j]]++;
				out_degree[color[i]]++;
			}

	int ans1=0,ans2=0;
	for(int i=1;i<=tot;i++)
	{
		if(in_degree[i]==0) ans1++;
		if(out_degree[i]==0) ans2++;
	}

	fout<<ans1<<endl;
	if(tot==1)
		fout<<0<<endl;
	else
	{
		ans2=ans2>ans1 ? ans2:ans1;
		fout<<ans2<<endl;
	}

	fin.close();
	fout.close();
	return 0;
}