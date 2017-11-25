#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

#define NUM 25000

int search(char list[NUM][20], char* s){
	for(int i = 0; i < NUM; ++i){
		if(strcmp(list[i],s) == 0){
			return i;
		}
	}
	return -1;
}

void init(char list[NUM][20]){
	char s[500],n[20];
	ifstream infile;
	infile.open("paper_ids.txt");
	int i = 0;
	while(!infile.eof()){
		infile.getline(s,500);
		sscanf(s,"%s",list[i++]);
	}
	infile.close();
}

void writePID(char list[NUM][20]){
	ofstream outfile("pid.txt");
	for(int i = 0; i < NUM; ++i){
		outfile<<i<<'\t'<<list[i]<<endl;
	}
	outfile.close();
}

void writePCN(char list[NUM][20]){
	
	ifstream infile("paper-citation-network.txt");
	ofstream outfile("pcn.txt");
    char a[20],b[20],s[500];
    int i = 0;
	while(!infile.eof()){
		infile.getline(s,500);
		sscanf(s,"%s%*s%s",a,b);
		outfile<<search(list,a)<<" ==> "<<search(list,b)<<endl;
		cout<<i++<<endl;
	}
	infile.close();
	outfile.close();
}

int main(){
	
	char list[NUM][20];
	
	init(list);

	writePID(list);

	return 0;
}
