#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ofstream out("/proc/transform");
	
	string str;
	while(cin>>str){
		if(str=="quit")break;
		out<<str<<endl;
		ifstream in("/proc/transform");
		in>>str;
		in.close();
		cout<<str<<endl;
	}
	
	out.close();
	return 0;
}
