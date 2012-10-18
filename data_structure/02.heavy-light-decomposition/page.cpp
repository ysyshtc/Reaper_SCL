#define For(i,n) for(int i=1;i<=n;++i)
#define visedge(k,x) for(int k=first[x];k;k=next[k])
typedef long long ll;
const int inf=1000000000,oo=~0u>>1;
using namespace std;
const int maxn=100010,maxm=maxn*2;
int n;
int first[maxn],next[maxm],en[maxm],tot,S[maxn],T[maxn],W[maxn];
inline void Add(int s,int t)
{
	next[++tot]=first[s],first[s]=tot,en[tot]=t;
}
int deep[maxn],size[maxn],id[maxn],li[maxn];int *Link[maxn];
int up[maxn][20];
struct node{
	node *lc,*rc;
	int mx,same,add;
}Data[maxn*20],*root[maxn];
int L[maxn],R[maxn];
inline node *NewNode()
{
	static int top=0;
	node *p=&Data[top++];
	p->mx=p->add=0;p->same=oo;
	return p;
}
inline void Update(node *k){k->mx=max(k->lc->mx,k->rc->mx);}
void Build(node* &k,int s,int t)
{
	k=NewNode();
	if(s+1==t){k->mx=li[s];return;}
	int m=s+t>>1;
	Build(k->lc,s,m),Build(k->rc,m,t);
	Update(k);
}
int lft,rgt,cc,lx;
inline void MakeSame(node *k,int x){k->mx=k->same=x,k->add=0;}
inline void Add(node *k,int x){k->mx+=x,k->add+=x;}
inline void PushDown(node *k)
{
	if(k->same<oo)
	{
		MakeSame(k->lc,k->same),MakeSame(k->rc,k->same);
		k->same=oo;
	}
	if(k->add)
	{
		Add(k->lc,k->add),Add(k->rc,k->add);
		k->add=0;
	}
}
void Insert(node* k,int s,int t)
{
	if(lft<=s&&t<=rgt)
	{
		lx==0?MakeSame(k,cc):Add(k,cc);
		return;
	}
	int m=s+t>>1;
	PushDown(k);
	if(lft<m)Insert(k->lc,s,m);
	if(rgt>m)Insert(k->rc,m,t);
	Update(k);
}
int Query(node *k,int s,int t)
{
	if(lft<=s&&t<=rgt)return k->mx;
	int m=s+t>>1;
	PushDown(k);
	if(rgt<=m)return Query(k->lc,s,m);
	if(lft>=m)return Query(k->rc,m,t);
	return max(Query(k->lc,s,m),Query(k->rc,m,t));
}
void Init()
{
	static int q[maxn],r=1;
	static bool V[maxn]={};
	q[1]=1,V[1]=1;
	For(i,r)
	{
		int x=q[i],j;size[x]=1;
		visedge(k,x)if(!V[j=en[k]])
		{
			V[j]=1,q[++r]=j;
			deep[j]=deep[x]+1;
			Link[j]=&W[k+1>>1];
			up[j][0]=x;
		}
	}
	for(int j=1;1<<j<=n;++j)For(i,n)if(up[i][j-1])
		up[i][j]=up[up[i][j-1]][j-1];
	for(int i=r;i;--i)size[up[q[i]][0]]+=size[q[i]];size[0]=0;
	for(int i=1;i<=r;++i)
	{
		int x=q[i],p=0;
		if(!id[x])id[x]=x;
		visedge(k,x)if(en[k]!=up[x][0]&&size[en[k]]>size[p])p=en[k];
		if(p)id[p]=id[x];
	}
	memset(V,0,sizeof(V));
	for(int i=r;i;--i)if(!V[q[i]])
	{
		int x=q[i];R[id[x]]=deep[x];
		for(;id[x]!=x;x=up[x][0])li[deep[x]-1]=*Link[x],V[x]=1;
		V[x]=1,L[x]=deep[x];
		if(L[x]<R[x])Build(root[x],deep[x],R[x]);
	}
}
inline int LCA(int a,int b)
{
	if(deep[a]<deep[b])swap(a,b);
	static int log;for(log=1;1<<log<=deep[a];++log);--log;
	for(int i=log;i>=0;--i)if(deep[a]-(1<<i)>=deep[b])a=up[a][i];
	if(a==b)return a;
	for(int i=log;i>=0;--i)if(up[a][i]&&up[a][i]!=up[b][i])
		a=up[a][i],b=up[b][i];
	return up[a][0];
}
inline void Shift(int &a,int lca)
{
	static int x;
	for(;id[a]!=id[lca];a=up[x][0])
	{
		x=id[a];
		lft=L[x],rgt=deep[a];
		if(lft<rgt)Insert(root[x],L[x],R[x]);
		lx==0?(*Link[x])=cc:(*Link[x])+=cc;
	}
}
inline int Ask(int &a,int lca)
{
	int ret=0;static int x;
	for(;id[a]!=id[lca];a=up[x][0])
	{
		x=id[a];
		lft=L[x],rgt=deep[a];
		if(lft<rgt)ret=max(ret,Query(root[x],L[x],R[x]));
		ret=max(ret,*Link[x]);
	}
	return ret;
}
int main()
{
	scanf("%d",&n);
	For(i,n-1)
	{
		int s,t,c;scanf("%d%d%d",&s,&t,&c);
		S[i]=s,T[i]=t,W[i]=c;
		Add(s,t),Add(t,s);
	}
	Init();
	char ctrl[100];int a,b,lca,k;
	while(scanf("%s",ctrl),ctrl[0]!='S')switch(ctrl[0])
	{
		case 'C':
			lx=0;
			if(ctrl[1]=='h')
			{
				scanf("%d%d",&a,&b);
				k=a,cc=b,b=T[a],a=S[a];
				if(up[a][0]==b)swap(a,b);
				W[k]=cc;
				if(id[a]==id[b])
				{
					lft=deep[a],rgt=deep[b];
					Insert(root[id[a]],L[id[a]],R[id[a]]);
				}
				break;
			}
			scanf("%d%d%d",&a,&b,&cc);
			lca=LCA(a,b);
			Shift(a,lca),Shift(b,lca);
			lft=deep[a],rgt=deep[b];
			if(lft>rgt)swap(lft,rgt);
			if(lft<rgt)Insert(root[id[lca]],L[id[lca]],R[id[lca]]);
			break;
		case 'A':
			lx=1;
			scanf("%d%d%d",&a,&b,&cc);
			lca=LCA(a,b);
			Shift(a,lca),Shift(b,lca);
			lft=deep[a],rgt=deep[b];
			if(lft>rgt)swap(lft,rgt);
			if(lft<rgt)Insert(root[id[lca]],L[id[lca]],R[id[lca]]);
			break;
		case 'M':
			scanf("%d%d",&a,&b);
			lca=LCA(a,b);
			int res=max(Ask(a,lca),Ask(b,lca));
			lft=deep[a],rgt=deep[b];
			if(lft>rgt)swap(lft,rgt);
			if(lft<rgt)res=max(res,Query(root[id[lca]],L[id[lca]],R[id[lca]]));
			printf("%d\n",res);
	}
	return 0;
}
