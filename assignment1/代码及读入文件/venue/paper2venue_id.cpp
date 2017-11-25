#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
#define NUM 368

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

int search(char list[NUM][500], const char* s){
	for(int i = 0; i < NUM; ++i){
		if(strcmp(list[i],s) == 0){
			return i;
		}
	}
	return -1;
}

int main(){
	
	ifstream infile("venue_ids.txt");
	char s[500],venue[500],paper[20];
	char list[NUM][500];
	
	int i = 0;
	while(!infile.eof()){
		infile.getline(s,500);
		separate(s,list[i++]);
	}
	infile.close();
	
	infile.open("paper2venue.txt");
	ofstream outfile("paper2venue_id.txt");

	while(!infile.eof()){
		infile.getline(s,500);
		separate(s,venue);
		sscanf(s,"%s",paper);
		outfile<<paper<<"\t"<<search(list,venue)<<endl;
	}
	infile.close();
	outfile.close();


	
	
	
	return 0;
}
