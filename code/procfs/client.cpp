#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ofstream out("/proc/transform");
	
	string str;
	cout<<"user input :";
	while(cin>>str){
		if(str=="quit")break;
		out<<str<<endl;
		ifstream in("/proc/transform");
		in>>str;
		in.close();
		cout<<"kern output:"<<str<<endl;
		cout<<"user input :";
	}
	
	out.close();
	return 0;
}
