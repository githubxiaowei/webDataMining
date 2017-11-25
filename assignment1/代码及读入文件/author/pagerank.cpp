
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
using namespace std;
#define NUM 22710
double max(double a,double b){
	return a>b?a:b;
}
class BitSet{
	private:
		int size;
		char* array;
		int num;
	public:
		BitSet(int n = NUM){
			size = (n+7)/8;
			array = new char[size];
			for(int i=0;i<size;++i){
				array[i]='\0';
			}
			num = 0;
		}
		~BitSet(){
			delete[] array;
		}
		int insert(int index){
			//if(isElement(index))return 1;
			if(index >= 0 && index>>3 < size ){
				array[index>>3] |= (1 << (index & 07));
				++num;
				return 1;
			}
			return 0;
		}
		int isElement(int index){
			if(index >= 0 && index>>3 < size && (array[index >> 3] & (1<<(index & 07))))
				return 1;
			return 0;
		}
		double operator[](int idx){
			return isElement(idx)*1.0/max(num,1.0);
		}
		int getNum(){
			return num;
		}
};

class Network{
	public:
		int size;
		BitSet* nodes;
		Network(int n = NUM){
			size = n;
			nodes = new BitSet[n];

		}
		~Network(){
			delete[] nodes;
		}
		int addEdge(int a, int b){
			if(a > 0 && a <= size){
				if(nodes[a].insert(b)){
					return 1;
				}
			}
			return 0;
		}
		BitSet& operator[](int a){
			return nodes[a];
		}
		void init(){
			ifstream file;
			char s[50],s1[10];
			int a,b;

			file.open("author_citation_network.txt");
			while(!file.eof()){
				file.getline(s,50);
				sscanf(s,"%d%s%d",&a,s1,&b);
				addEdge(a,b);
			}
			file.close();

		}

};


void PR(Network& N, double* v, double* v1, int size){
	double alpha = 0.85;
	for(int i=0; i<size; ++i){
		v1[i] = 0;
		for(int j=0; j<size; ++j){
			v1[i] += N[j][i]*v[j];//×ªÖÃ
		}
		v1[i] = alpha*v1[i] + (1.0-alpha)/size;
	}
}

double error(double* a, double* b, int size){
	double e=0;
	for(int i=0; i<size; ++i){
		e = max(fabs(a[i]-b[i]),e);
	}
	return e;
}

//Data swop function
template<class T>
void Swap(T &p,T &q)
{
     T temp = p;
       p=q;
       q=temp;
}

//Quick sort
void Quick_sort(int index[], double ArrayInput[],int nLow,int nHigh)
{
    if(nLow < nHigh)
    {
    	//Partition
    	double nTemp=ArrayInput[nHigh];
	    int i = nLow-1, j=nLow;
		for(; j<nHigh; j++)
		{
		      if( ArrayInput[j]>=nTemp )
		      {
		             i++;
		             if(i !=j )
		             {
		                   Swap<double>(ArrayInput[i], ArrayInput[j]);
		                   Swap<int>(index[i], index[j]);
		             }
		      }
		}
		Swap<double>(ArrayInput[i+1],ArrayInput[nHigh]);
		Swap<int>(index[i+1], index[nHigh]);
        int nIndex=i+1;

        Quick_sort(index,ArrayInput , nLow, nIndex-1);
        Quick_sort(index,ArrayInput , nIndex+1, nHigh);
    }
}


void save_vec(double* v, int i){
	ofstream outfile("author_vec.txt");
	outfile<<i<<endl;
	for(int r = 0; r<NUM;++r){
		outfile<<v[r]<<endl;
	}
	outfile.close();
}

#define READVEC 1

void init_vec(double* r, int& n){
	if(READVEC){
		ifstream infile("author_vec.txt");
		infile>>n;
		for(int j = 0; j<NUM;++j){
			infile>>r[j];
		}
		infile.close();
	}else{
		for(int i =0; i < NUM; ++i ){
			r[i]=1.0/NUM;
		}
		n = 0;
	}
}

void separate(const char* s, char* n){
	int i = 0,j=0,flag=0;
	while(s[i]!='\0'){
		if(flag == 1){
			n[j++] = s[i];
		}
		if(s[i]=='{' | s[i] == '}'){
			flag++;
		}
		++i;
	}
	n[j-1] = '\0';
}

void initAID(char** list){
	char s[500];
	ifstream infile;
	infile.open("author_ids.txt");
	int idx;
	while(!infile.eof()){
		infile.getline(s,500);
		sscanf(s,"%d",&idx);
		separate(s,list[idx]);
	}
	infile.close();
}

int main(){

	Network g;
	g.init();

	char** list = new char*[NUM];
	for(int i=0;i<NUM;++i){
		list[i] = new char[200];
		list[i][0] = '+';
		list[i][1] = '+';
		list[i][2] = '\0';
		
	}
	initAID(list);

	double* r = new double[NUM];
	double* r1 = new double[NUM];

	double e=1;
	int i;
	init_vec(r,i);
	while(e>1e-6){
		++i;
		cout<<i<<endl;
		PR(g,r,r1,NUM);
		PR(g,r1,r,NUM);
		e = error(r,r1,NUM);
		cout<<e<<endl;
		save_vec(r,i);
	}


	int* idx = new int[NUM];
	for(int i=0;i<NUM;++i){
		idx[i] = i;
	}
	Quick_sort(idx, r,0,NUM-1);


	ofstream outfile("author_pagerank.txt");
	for(int i = 0; i < NUM ;++i){
		if(strcmp(list[idx[i]],"++"))outfile<<list[idx[i]]<<"\t"<<r[i]<<endl;
	}
	outfile.close();


	return 0;
}
