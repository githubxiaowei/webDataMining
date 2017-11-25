#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

#define VNUM 368
double max(double a,double b){
	return a>b?a:b;
}

void PR(double N[VNUM][VNUM], double* v, double* v1){
	double alpha = 0.85;
	for(int i=0; i<VNUM; ++i){
		v1[i] = 0;
		for(int j=0; j<VNUM; ++j){
			v1[i] += N[j][i]*v[j];//×ªÖÃ
		}
		v1[i] = alpha*v1[i] + (1.0-alpha)/VNUM;
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

void initVID(char** list){
	char s[500];
	ifstream infile;
	infile.open("venue_ids.txt");
	int idx;
	while(!infile.eof()){
		infile.getline(s,500);
		sscanf(s,"%d",&idx);
		separate(s,list[idx]);
	}
	infile.close();
}

int main(){
	
	double vNet[VNUM][VNUM];
	int outcite[VNUM];
	
	for(int i=0; i<VNUM; ++i){
		outcite[i]=0;
		for(int j=0; j<VNUM; ++j){
			vNet[i][j] = 0;
		}
	}
	
	char** list = new char*[VNUM];
	for(int i=0;i<VNUM;++i){
		list[i] = new char[500];
	}
	initVID(list);

	ifstream infile("vcn.txt");
	char s[30];
	int a,b;
	while(!infile.eof()){
		infile.getline(s,30);
		sscanf(s,"%d%*s%d",&a,&b);//cout<<a<<" "<<b<<endl;
		vNet[a][b] += 1;
		++outcite[a];
	}
	for(int i=0; i<VNUM; ++i){
		for(int j=0; j<VNUM; ++j){
			vNet[i][j] = vNet[i][j]/max(1,outcite[i]);
		}
	}
	

	double* r = new double[VNUM];
	double* r1 = new double[VNUM];
	for(int i =0; i < VNUM; ++i ){
		r[i]=1.0/VNUM;
	}

	double e=1.0;
	while(e>1e-7){
		PR(vNet,r,r1);
		PR(vNet,r1,r);
		e = error(r,r1,VNUM);
		cout<<e<<endl;
	}

	int* idx = new int[VNUM];
	for(int i=0;i<VNUM;++i){
		idx[i] = i;
	}
	Quick_sort(idx, r,0,VNUM-1);

	ofstream outfile("venue_pagerank.txt");
	for(int i = 0; i < VNUM ;++i){
		outfile<<list[idx[i]]<<"\t"<<r[i]<<endl;
	}
	outfile.close();

	
	return 0;
}
