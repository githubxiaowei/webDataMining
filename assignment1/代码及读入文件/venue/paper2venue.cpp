#include<iostream>
#include<fstream>
using namespace std;

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

int main(){
	

	ifstream infile("acl-metadata.txt");
	ofstream outfile("paper2venue.txt");
	char s[500],paper[200],venue[200];
	
	int i = 1;
	while(!infile.eof()){
		infile.getline(s,500);
		if(i%6==1){
			separate(s,paper);
		}
		
		if(i%6==4){
			separate(s,venue);
			outfile<<paper<<"\t{"<<venue<<'}'<<endl;
		}

		++i;
	}
	infile.close();
	outfile.close();
	
	return 0;
}
