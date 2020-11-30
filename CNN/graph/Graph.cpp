//Graph.cpp
//
#include "Graph.h"

Graph::Graph():
vnode(NULL),
V(0),
iary(NULL),
iary2(NULL),
itary(NULL),
stary(NULL),
lastErr(""),
filename(""),
isLoaded(false),
isDG(false),
withWeight(false),
withPos(false),
last(GHREADY)
{
}

Graph::Graph(int i,bool random,bool dg,bool selfring,int degree):
vnode(NULL),
V(0),
iary(NULL),
iary2(NULL),
itary(NULL),
stary(NULL),
lastErr(""),
filename(""),
isLoaded(false),
isDG(false),
withWeight(false),
withPos(false),
last(GHREADY)
{
	Load(i,random,dg,selfring,degree);
}

Graph::Graph(string fname):
vnode(NULL),
V(0),
iary(NULL),
iary2(NULL),
itary(NULL),
stary(NULL),
lastErr(""),
filename(""),
isLoaded(false),
isDG(false),
withWeight(false),
withPos(false),
last(GHREADY)
{
	Load(fname);
}

Graph::Graph(const Graph& g,bool reverse,bool remainweight):
vnode(NULL),
V(0),
iary(NULL),
iary2(NULL),
itary(NULL),
stary(NULL),
lastErr(""),
filename(""),
isLoaded(false),
isDG(false),
withPos(false),
last(GHREADY)
{
	Load(g,reverse,remainweight);
}

Graph::~Graph()
{
	Destory();
}

void Graph::Destory(bool all)
{
	if (all&&vnode)
	{			
		VNode* t=NULL;
		for (VNode* v=vnode;v!=NULL;)
		{
			ArcNode* p=NULL;
			for (ArcNode* node=v->adj;node!=NULL;)
			{
				p=node;
				node=node->next;
				delete p;
			}
			v->adj=NULL;
			t=v;
			v=v->next;
			delete t;
		}
		vnode=NULL;
	}
	if (iary)
		delete []iary;
	iary=NULL;
	if (iary2)
		delete []iary2;
	iary2=NULL;
	if (itary)
	{
		for (int i=0;i<V;i++)
			delete []itary[i];
		delete []itary;
		
	}
	itary=NULL;
	if (stary)
	{
		for (int i=0;i<V;i++)
			delete []stary[i];
		delete []stary;
	}
	stary=NULL;

	ArcNode* p;
	for (ArcNode* node=errAdd.adj;node!=NULL;)
	{
		p=node;
		node=node->next;
		delete p;
	}
	errAdd.adj=NULL;
	if (all)
	{
		isDG=false;
		withPos=false;
		withWeight=false;
		filename="";
		index=0;
		lastErr="";
		isLoaded=false;
	}
}

void Graph::CreateArrays()
{
	Destory(false);
	iary=new int[V];
	iary2=new int[V];
	itary=new int*[V];
	int i;
	for (i=0;i<V;i++)
		itary[i]=new int[V];
	stary=new string*[V];
	for (i=0;i<V;i++)
		stary[i]=new string[V];
}

void Graph::Load(const Graph& g,bool reverse,bool remainweight)
{
	Destory();
	V=g.V;
	VNode * newnode=NULL,*last=NULL;
	int i;
	for (i=0;i<V;i++)
	{
		newnode=new VNode(g[i].v);
		if (vnode==NULL)
		{
			vnode=newnode;
			last=newnode;
		}
		else
		{
			last->next=newnode;
			last=newnode;
		}
	}
	if (reverse)
	{
		for (i=0;i<V;i++)
		{
			for (int j=0;j<g[i].vnum;j++)
			{
				if (remainweight)
				{
					(*this)[g[i][j].edge.w.uniID]+=Edge(g[i].v,g[i][j].edge.weight);
				}
				else
				{
					(*this)[g[i][j].edge.w.uniID]+=g[i].v;
				}
			}
		}
	}
	else
	{
		for (int i=0;i<V;i++)
		{
			(*this)[i].v=g[i].v;
			for (int j=0;j<g[i].vnum;j++)
				(*this)[i]+=g[i][j].edge;
		}
	}
	
	CreateArrays();

	if (reverse)
		lastErr="逆图已经生成,";
	else
		lastErr="图已经生成,";
	if (remainweight)
		lastErr+="仍保留原图权重";
	else
		lastErr+="未保留原图权重";
	isLoaded=g.isLoaded;
	isDG=g.isDG;
	withWeight=g.withWeight;
	withPos=g.withPos;
}

void Graph::Load(int i,bool random,bool dg,bool selfring,int degree)
{
	if (i<=0)
	{
		lastErr="参数错误";
		isLoaded=false;
		V=0;
		isDG=false;
		withWeight=false;
		return;
	}
	Destory();
	
	if (dg)
		withWeight=true;
	V=i;
	srand((unsigned)time(NULL));
	string info;
	char c[3];
	VNode* newnode=NULL,*last=NULL;
	int k;
	for (k=0;k<V;k++)
	{	
		info="";
		_itoa(k,c,10);
		newnode=new VNode(k,info+c);
		if (vnode==NULL)
		{
			vnode=newnode;
			last=newnode;
		}
		else
		{
			last->next=newnode;
			last=newnode;
		}
	}
	if (random)
	{
		for (k=0;k<V;k++)
		{
			for (int j=0;;j++)
			{
				int unid=(rand()%(V+1)-1);
				if (!selfring&&unid==(*this)[k].v.uniID)
				{
					continue;
				}

				if ((unid==-1)||(degree&&(*this)[k].vnum>degree))
				{
					break;
				}
			//	cout<<unid<<',';
				info="";
				_itoa(unid,c,10);
				if (withWeight)
				{
					WTYPE wt=(rand()%100);
					(*this)[k]+=Edge(unid,info+c,wt);
				}
				else
				{
					(*this)[k]+=Edge(unid,info+c);
				}
			}
		//	cout<<endl;
		}
		lastErr="随机图生成完成";
	}
	else
		lastErr="已经生成一个空图";
	
	CreateArrays();

	isLoaded=true;
	isDG=dg;
	withWeight=dg;
}

void Graph::Load(string fname)
{
	lastErr = "文件\"" + fname + "\"";
	ifstream in(fname.c_str());
	if (in.fail())
	{
		lastErr += "指定文件不存在";
		return;
	}
	string line;
	getline(in, line);
	int len = atoi(line.c_str());
	if (len < 0)
	{
		lastErr += "维数错误";
		in.close();
		return;
	}

	V = len;
	VNode* newnode, *last = vnode;
	for (int k = 0; k < V; k++)
	{
		newnode = new VNode();
		if (vnode == NULL)
		{
			vnode = newnode;
			last = newnode;
		}
		else
		{
			last->next = newnode;
			last = newnode;
		}
	}

	getline(in, line);
	if (line != "POS")
	{
		lastErr += "文件信息错误:POS";
		in.close();
		return;
	}
	getline(in, line);
	GPoint* pos = NULL;
	if (line != "")
	{
		line += '\n';
		pos = new GPoint[V];
		string posxy = "";
		int p = 0;
		for (int e = 0; p < V&&e < line.length(); e++)
		{
			if (line[e] == ',')
			{
				if (posxy != "")
				{
					pos[p].x = atoi(posxy.c_str());
					posxy = "";
					continue;
				}
				else
					break;
			}
			else if (line[e] == ' ' || line[e] == '\n')
			{
				if (posxy != "")
				{
					pos[p++].y = atoi(posxy.c_str());
					posxy = "";
					continue;
				}
				else
					break;
			}
			posxy += line[e];
		}
		if (p < V)
		{
			delete[]pos;
			lastErr += "顶点位置信息不全";
			in.close();
			return;
		}
	}

	Edge* edge = new Edge[V];
	getline(in, line);
	int inputmode;
	if (line == "UNID")
		inputmode = 1;
	else if (line == "INFO")
		inputmode = 0;
	else if (line == "WEIGHT")
	{
		isDG = true;
		withWeight = true;
		inputmode = 3;
	}
	else if (line == "DAG")
	{
		isDG = true;
		inputmode = 4;
	}
	else if (line == "DG")
	{
		isDG = true;
		inputmode = 4;
	}
	else
	{
		delete[]edge;
		if (pos)
			delete[]pos;
		in.close();
		lastErr += "文件信息错误";
		return;
	}
	getline(in, line);
	string str = "";
	len = 0;
	int i;
	for (i = 0; i <= line.length(); i++)
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			//cout<<str<<','<<len<<endl;
			edge[len].w=Vertex(len,str);
			len++;
			str = "";
			continue;
		}
		str += line[i];
	}
	if (len < V)
	{
		delete[]edge;
		if (pos)
			delete[]pos;
		lastErr += "顶点信息错误";
		in.close();
		return;
	}

	str = "";
	for (i = 0; i < V; i++)
	{
		(*this)[i].v = edge[i].w;
		getline(in, line);
		if (line == "")
			continue;
		for (int j = 0; j <= line.length(); j++)
		{
			if (line[j] == ' ' || line[j] == '\0')
			{
				//	cout<<str<<',';
				int index = atoi(str.c_str());
				if (index >= V || index < 0)
				{
					str = "";
					continue;
				}
				//	cout<<vertex[index].uniID<<'\t';
				if (inputmode)
				{
					if (inputmode == 3)
					{
						str = "";
						for (j++; j <= line.length(); j++)
						{
							if (line[j] == ' ' || line[j] == '\0')
								break;
							str += line[j];
						}
						//	cout<<str<<endl;
						edge[index].weight = atof(str.c_str());
						str = "";
					}
					else
					{
						edge[index].weight = 0;
					}
					(*this)[i] += edge[index];
				}
				else
				{
					int k;
					for (k = 0; k < V; k++)
					{
						if (edge[k].w.info == str)
							break;
					}
					if (k < V)
						(*this)[i] += edge[k];
					else
					{
						str = "";
						continue;
					}
				}
				str = "";
				continue;
			}
			str += line[j];
		}
		//	cout<<endl;
	}
	if (i < V)
	{
		delete[]edge;
		if (pos)
			delete[]pos;
		in.close();
		lastErr += "边集信息不正确";
		return;
	}
	delete[]edge;
	if (pos)
	{
		for (int p = 0; p < V; p++)
		{
			(*this)[p].v.pos.x = pos[p].x;
			(*this)[p].v.pos.y = pos[p].y;
		}
		withPos = true;
		delete[]pos;
		lastErr += "(带位置信息)";
	}
	in.close();
	lastErr += "加载成功";
	isLoaded = true;

	filename = fname;

	CreateArrays();
}

void Graph::Load(Network * n, GUITYPE w, GUITYPE h)
{
	VNode* newnode, *last = vnode;
	Layer * layer = n->layers.link;
	int nx = w / n->layers.linkcount;
	int ny = 0;
	if (layer) {
		do {
			if (layer->neurals.linkcount > ny) {
				ny = layer->neurals.linkcount;
			}
			
			layer = n->layers.next(layer);
		} while(layer && layer != n->layers.link);
	}
	ny = h / ny;
	layer = n->layers.link;
	int posx = 0, posy = 0, nlayers = 0, ncounts = 0, nnodes = 0, lcounts = 0;
	this->withPos = true;
	this->withWeight = true;
	this->isDG = true;
	if (layer) {
		posx = 30;
		do {
			Neural * neural = layer->neurals.link;
			if (neural) {
				posy = 30;// +nlayers * 15;
				ncounts = 0;
				lcounts = 0;
				do {

					newnode = new VNode();
					if (vnode == NULL)
					{
						vnode = newnode;
						last = newnode;
					}
					else
					{
						last->next = newnode;
						last = newnode;
					}
					newnode->v.uniID = neural->uniqueID;
					newnode->v.info = neural->uniqueID;
					newnode->v.sum = neural->sum;
					newnode->v.bias = neural->bias;
					newnode->v.output = neural->output;
					newnode->v.value = neural->value;
					if (nlayers == 0) {
						newnode->v.output *= n->divrange;
					}
					else if (nlayers == n->layers.linkcount - 1) {
						newnode->v.output *= n->divoutrange;
					}
					newnode->v.pos.x = posx;// +ncounts * 10;
					newnode->v.pos.y = posy;
					this->V++;
					ncounts++;
					posy += ny;

					VNode &node = *newnode;
					Connector * conn = neural->conn.link;
					if (conn) {
						nnodes = 0;
						do {

							if (conn->back == neural) {
								Edge edge;
								edge.w.uniID = conn->forw->uniqueID;
								edge.w.info = conn->forw->uniqueID;
								edge.weight = conn->weight;
								//edge.delta = conn->delta;
								node += edge;
								nnodes++;
							}
							else if(false && conn->forw == neural) {
								Edge edge;
								edge.w.uniID = conn->back->uniqueID;
								edge.w.info = conn->back->uniqueID;
								edge.weight = conn->weight;
								//edge.delta = conn->delta;
								node += edge;
								nnodes++;
							}

							conn = neural->conn.next(conn);
						} while (conn && conn != neural->conn.link);
					}
					lcounts++;
					if (lcounts >= 10) {
						break;
					}
					neural = layer->neurals.next(neural);
				} while (neural && neural != layer->neurals.link);
			}
			nlayers++;
			posx += nx;

			layer = n->layers.next(layer);
		} while (layer && layer !=n->layers.link);
	}
}


void Graph::Update(Network * n)
{
	VNode* newnode, *last = vnode;
	Layer * layer = n->layers.link;
	int posx = 0, posy = 0, nlayers = 0, ncounts = 0, nnodes = 0, lcounts = 0;
	if (layer) {
		do {
			Neural * neural = layer->neurals.link;
			if (neural) {
				lcounts = 0;
				do {

					newnode = &(*this)[ncounts];
					newnode->v.sum = neural->sum;
					newnode->v.bias = neural->bias;
					newnode->v.output = neural->output;
					newnode->v.value = neural->value;
					//if (nlayers == 0) {
					//	newnode->v.output *= n->divrange;
					//}
					//else if (nlayers == n->layers.linkcount - 1) {
					//	newnode->v.output *= n->divoutrange;
					//}
					ncounts++;

					VNode &node = *newnode;
					Connector * conn = neural->conn.link;
					if (conn) {
						nnodes = 0;
						do {

							if (conn->back == neural) {
								Edge &edge = node[nnodes].edge;
								edge.weight = conn->weight;
								//edge.delta = conn->delta;
								nnodes++;
							}
							else if (false && conn->forw == neural) {
								Edge &edge = node[nnodes].edge;
								edge.weight = conn->weight;
								//edge.delta = conn->delta;
								nnodes++;
							}

							conn = neural->conn.next(conn);
						} while (conn && conn != neural->conn.link);
					}
					lcounts++;
					if (lcounts >= 10) {
						break;
					}
					neural = layer->neurals.next(neural);
				} while (neural && neural != layer->neurals.link);
			}
			nlayers++;

			layer = n->layers.next(layer);
		} while (layer && layer != n->layers.link);
	}
}



VNode& Graph::operator [](int i)
{
	if (i<0)
		return errAdd;
	VNode* t;
	for (t=vnode;t!=NULL&&i>0;i--,t=t->next);
	if (t)
		return *t;
	return errAdd;
}

VNode& Graph::operator [](int i) const
{
	VNode* t;
	for (t=vnode;t!=NULL&&i>0;i--,t=t->next);
	return *t;
}

Graph& Graph::AddPoint(const Vertex& v,int& ret)
{
	if (V)
	{
		int i;
		for (i=0;i<V;i++)
		{
			if ((*this)[i].v==v||(*this)[i].v.uniID!=i)
				break;
		}
		if ((*this)[i].v.uniID!=i)
		{
			VNode* newnode=new VNode(v);
			newnode->v.uniID=i;
			if (i)
			{
				newnode->next=&(*this)[i];
				(*this)[i-1].next=newnode;
			}
			else
			{
				newnode->next=vnode;
				vnode=newnode;
			}
			Destory(false);
			V++;
			CreateArrays();
			ret=i;
		}
		else if (i==V||V==1)
		{
			VNode* newnode=new VNode(v);
			newnode->v.uniID=V;
			(*this)[V-1].next=newnode;
			Destory(false);
			V++;
			CreateArrays();
			ret=V-1;
		}
	}
	else
	{
		VNode* newnode=new VNode(v);
		newnode->v.uniID=V;
		vnode=newnode;
		Destory(false);
		V++;
		CreateArrays();
		ret=0;
	}
	return *this;
}

Graph& Graph::operator +=(const Vertex& v)
{
	if (V)
	{
		int i;
		for (i=0;i<V;i++)
		{
			if ((*this)[i].v==v||(*this)[i].v.uniID!=i)
				break;
		}
		if ((*this)[i].v.uniID!=i)
		{
			VNode* newnode=new VNode(v);
			newnode->v.uniID=i;
			if (i)
			{
				newnode->next=&(*this)[i];
				(*this)[i-1].next=newnode;
			}
			else
			{
				newnode->next=vnode;
				vnode=newnode;
			}
			Destory(false);
			V++;
			CreateArrays();
		}
		else if (i==V||V==1)
		{
			VNode* newnode=new VNode(v);
			newnode->v.uniID=V;
			(*this)[V-1].next=newnode;
			Destory(false);
			V++;
			CreateArrays();
		}
	}
	else
	{
		VNode* newnode=new VNode(v);
		newnode->v.uniID=V;
		vnode=newnode;
		Destory(false);
		V++;
		CreateArrays();
	}
	return *this;
}

Graph& Graph::operator -=(const Vertex& v)
{
	if (V)
	{
		int i;
		for (i=0;i<V;i++)
		{
			if ((*this)[i].v==v)
				break;
		}
		if (i==V)
		{
			(*this).operator -=(i);
		}
	}
	return *this;
}

Graph& Graph::operator -=(int uid)
{
	if (V)
	{
		for (int i=0;i<V;i++)
		{
			for (int j=0;j<(*this)[i].vnum;j++)
				if ((*this)[i].adj[j].edge.w.uniID==(*this)[uid].v.uniID)
				{
					(*this)[i]-=j;
				}
		}
		
		VNode* t=NULL;
		if (uid)
		{
			t=&(*this)[uid];
			(*this)[uid-1].next=t->next;
		}
		else
		{
			t=vnode;
			vnode=vnode->next;
		}
		if (t)
		{
			for (int j=0;j<t->vnum;j++)
				(*t)-=j;
			delete t;
		}
		t=NULL;

		Destory(false);
		V--;
		CreateArrays();
	}
	return *this;
}

int Graph::FirstAdj(int v)
{
	if ((*this)[v].vnum)
		return (*this)[v][0].edge.w.uniID;
	return -1;
}

int Graph::NextAdj(int v)
{
	if ((*this)[v].vnum)
	{
		int i;
		for (i=0;i<(*this)[v].vnum;i++)
		{
			int uid = (*this)[v][i].edge.w.uniID;
			if (iary[uid]==-1)
			{
				break;
			}
		}
		if (i==(*this)[v].vnum)
			return -1;
		return (*this)[v][i].edge.w.uniID;
	}
	return -1;
}

int Graph::DirectAdjUniID(int v,int w) const
{
	if (v<0||w<0)
		return 0;
	if (w>=V||v>=V)
		return 0;
	int i;
	for (i=0;i<V;i++)
		if ((*this)[i].v.uniID==(*this)[v].v.uniID)
			break;
	if (i==V)
		return 0;
	ArcNode* arc;
	for (arc=(*this)[v].adj;arc!=NULL;arc=arc->next)
	{
		if (arc->edge.w.uniID==(*this)[w].v.uniID)
			break;
	}
	if (arc)
	{
		return 1;
	}
	return 0;
}
ArcNode* Graph::Arc(int v, int w) const
{
	if (v < 0 || w < 0)
		return 0;
	if (w >= V || v >= V)
		return 0;
	int i;
	for (i = 0; i < V; i++)
		if ((*this)[i].v.uniID == (*this)[v].v.uniID)
			break;
	if (i == V)
		return 0;
	ArcNode* arc;
	for (arc = (*this)[v].adj; arc != NULL; arc = arc->next)
	{
		if (arc->edge.w.uniID == (*this)[w].v.uniID)
			break;
	}
	if (arc)
	{
		return arc;
	}
	return 0;
}

int Graph::DirectAdj(int v,int w) const
{
	if (v<0||w<0)
		return 0;
	int i;
	for (i=0;i<V;i++)
		if ((*this)[i].v.uniID==v)
			break;
	if (i==V)
		return 0;
	ArcNode* arc = NULL;
	for (arc=(*this)[i].adj;arc!=NULL;arc=arc->next)
	{
		if (arc->edge.w.uniID==(*this)[w].v.uniID)
			break;
	}
	if (arc)
	{
		return 1;
	}
	return 0;
}

int Graph::VInDeg(int v)
{
	return (*this)[v].vnum;
}

WTYPE Graph::WeightUniID(int v, int w, bool equal) const
{
	if (equal&&v == w)
		return 0;
	ArcNode* arc = NULL;
	for (arc = (*this)[v].adj; arc != NULL; arc = arc->next)
	{
		if (arc->edge.w.uniID == (*this)[w].v.uniID)
			break;
	}
	if (arc)
		return arc->edge.weight;
	return INF;
}


WTYPE Graph::Weight(int v,int w,bool equal) const
{
	if (equal&&v==w)
		return 0;
	ArcNode* arc;
	for (arc=(*this)[v].adj;arc!=NULL;arc=arc->next)
	{
		if (arc->edge.w.uniID==w)
			break;
	}
	if (arc)
		return arc->edge.weight;
	return INF;
}

void Graph::Remove(int v,int w)
{
	ArcNode* arc=(*this)[v].adj;
	ArcNode* last=arc;
	for (;arc!=NULL;arc=arc->next)
	{
		if (arc->edge.w.uniID==w)
			break;
	}
	for (;last!=arc&&last->next!=arc;last=last->next);
	if (arc)
	{
		if (last==arc)
		{
			(*this)[v].adj=arc->next;
		}
		else
		{
			last->next=arc->next;
		}
		delete arc;
		(*this)[v].vnum--;
	}
	return;
}

void Graph::GRemove(int v,int w)
{
	Remove(v,w);
	Remove(w,v);
}

void Graph::dfsR(int v,int& num)
{
	int w;
//	cout<<(*this)[v].v.uniID<<"->";
	iary2[index++]=(*this)[v].v.uniID;
	iary[v]=num++;
	w=FirstAdj(v);
	while(w!=-1)
	{
		if (iary[w]==-1)
		{
			dfsR(w,num);
		}
		w=NextAdj(v);
	}
}

void Graph::dfsR(int ev,int ew,int& num)
{
	cout<<(*this)[ew].v.uniID<<"->";
	int t,w=ew;
	iary[w]=num++;
	for (t=0;t<V;t++)
		if (DirectAdj(w,t)!=0)
			if (iary[t]==-1)
				dfsR(w,t,num);
}

void Graph::dfsR(int ev,int ew,int& num,int& cntp)
{
	cout<<ev<<'-'<<ew<<" tree"<<endl;
	int v,w=ew;
	iary[w]=num++;
	for (ArcNode * t=(*this)[w].adj;t!=NULL;t=t->next)
		if (iary[t->edge.w.uniID]==-1)
			dfsR(w,t->edge.w.uniID,num,cntp);
		else
		{
			v=t->edge.w.uniID;
			if (iary2[v]==-1)
				cout<<w<<'-'<<v<<" back"<<endl;
			else if (iary[v]>iary[w])
				cout<<w<<'-'<<v<<" down"<<endl;
			else
				cout<<w<<'-'<<v<<" cross"<<endl;
		}
	iary2[w]=cntp++;
}

void Graph::DFS(int mode)
{
	index=0;
	int i; 
	int num=0;
	int cntp=0;
	for (i=0;i<V;i++)
	{
		iary[i]=-1;
		iary2[i]=-1;
	}
	for (i=0;i<V;i++)
	{
		if (iary[i]==-1)
		{
			if (mode==1)
				dfsR(i,num);
			else if (mode==2)
				dfsR(i,i,num);
			else if (mode==3)
				dfsR(i,i,num,cntp);
		}
	}
	
	last=GHDFS;
}

bool Graph::pathHR(int v,int w,int d)
{
	if (v==w)
	{
		if (d==0)
			return true;
		else
			return false;
	}
	int t;
	iary[v]=1;
	for (t=0;t<V;t++)
		if (DirectAdj(v,t)==1)
			if (iary[t]==0)
				if (pathHR(t,w,d-1))
				{
					iary2[index++]=(*this)[t].v.uniID;
					return true;
				}
	iary[v]=0;
	return false;
}

bool Graph::PathH(int v,int w)
{
	if (V>10)
	{
		return false;
	}
	int t;
	index=0;
	for (t=0;t<V;t++)
		iary[t]=0;
	bool re=pathHR(v,w,V-1);
	iary2[index]=v;
	if (re)
		last=GHHAMILTON;
	else
		last=GHREADY;
	return re;
}

bool Graph::SQTopoSort()
{
	int i,v;
	for (v=0;v<V;v++)
	{
		iary[v]=0;
		iary2[v]=-1;
	}
	for (v=0;v<V;v++)
		for (ArcNode *t=(*this)[v].adj;t!=NULL;t=t->next)
			iary[t->edge.w.uniID]++;
	Queue q(2*V);
	for (v=0;v<V;v++)
		if (iary[v]==0)
			q.EnQueue(v);
	for (i=0;!q.EmptyQ();i++)
	{
		iary2[i]=(v=q.DeQueue());
		for (ArcNode *t=(*this)[v].adj;t!=NULL;t=t->next)
		{
			if (--iary[t->edge.w.uniID]==0)
				q.EnQueue(t->edge.w.uniID);
		}
	}
	last=GHREADY;
	if (i<V)
	{
		return false;
	}
	return true;
}

void Graph::Prim()
{
	if (V<=1)
		return;
	if (!withWeight)
		return;
	int v,w,min;
	int *st=iary,*fr=iary2,*wt=new int[V+1];
	for (v=0;v<V;v++)
	{
		st[v]=-1;
		fr[v]=v;
		wt[v]=INF;
	}
	st[0]=0;
	wt[V]=INF;
	for (min=0;min!=V;)
	{
	/*	for (int i=0;i<V;i++)
			cout<<st[i]<<',';
		cout<<endl;
		for (i=0;i<V;i++)
			cout<<fr[i]<<',';
		cout<<endl;
		for (i=0;i<=V;i++)
			cout<<wt[i]<<',';
		cout<<endl;*/
		
		v=min;
		st[min]=fr[min];
		for (w=0,min=V;w<V;w++)
		{
			if (st[w]==-1)
			{
				if (Weight(v,w)<wt[w])
				{
					wt[w]=Weight(v,w);
					fr[w]=v;
				}
				else if (Weight(w,v)<wt[w])
				{
					wt[w]=Weight(w,v);
					fr[w]=v;
				}
				if (wt[w]<wt[min])
				{
					min=w;
				}
			}
		}
	}
/*	cout<<endl;
	for (int i=0;i<V;i++)
		cout<<st[i]<<',';
	cout<<endl;
	for (int i=0;i<V;i++)
		cout<<i<<'-'<<fr[i]<<',';
	cout<<endl;*/
	for (int i=0;i<V;i++)
	{
		st[i]=wt[i];
	//	cout<<st[i]<<',';
	}
//	cout<<endl;

	delete []wt;

	last=GHPRIM;
}
