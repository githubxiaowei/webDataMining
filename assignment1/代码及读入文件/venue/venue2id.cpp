#include<iostream>
#include<fstream>
#include<cstring>
#include<set>
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

	set<string> venues;
	ifstream infile("acl-metadata.txt");
	char s[500],n[200];
	int i = 1;
	while(!infile.eof()){
		infile.getline(s,500);
		if(i++%6==4){
			separate(s,n);
			venues.insert(string(n));
		}
	}
	infile.close();
	
	cout<<venues.size();
	
    ofstream outfile("venue_ids.txt");
    i = 0;
	for (set<string>::iterator it = venues.begin(); it != venues.end(); ++it)
    {
        cout << *it << endl;
        outfile<<i++<<"\t{"<<*it<<'}'<<endl;
    }
    outfile.close();

    
    
    

	return 0;
}
