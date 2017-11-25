#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


#define PNUM 24628
#define VNUM 368

int search(char list[PNUM][10], char* s){
	for(int i = 0; i < PNUM; ++i){
		if(strcmp(list[i],s) == 0){
			return i;
		}
	}
	return -1;
}

int main(){
	

	char plist[PNUM][10],s[30];
	
	int i=0;
	ifstream infile("pid.txt");
	while(!infile.eof()){
		infile.getline(s,30);
		sscanf(s,"%*d%s",plist[i++]);
	}

	infile.close();
	
	int v,p2v[PNUM];
	for(i=0;i<PNUM;++i){
		p2v[i]=-1;
	}
	char p[10];
	infile.open("paper2venue_id.txt");
	while(!infile.eof()){
		infile.getline(s,30);
		sscanf(s,"%s%d",p,&v);
		p2v[search(plist,p)] = v;
	}
	infile.close();
	
	char s1[10],s2[10];
	infile.open("paper-citation-network.txt");
	ofstream outfile("vcn.txt");
	i=0;
	while(!infile.eof()){
		infile.getline(s,30);
		sscanf(s,"%s%*s%s",s1,s2);
		cout<<i++<<'\t';
		cout<<p2v[search(plist,s1)]<<" ==> "<<p2v[search(plist,s2)]<<endl;
		outfile<<p2v[search(plist,s1)]<<" ==> "<<p2v[search(plist,s2)]<<endl;
	}
	infile.close();
	outfile.close();

	
	return 0;
}
