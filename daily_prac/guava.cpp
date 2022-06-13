#include <iostream>
#include <string>
#include <list>
using namespace std;
int main(){
	int inside_emp, turns;
	cin >> inside_emp >> turns;
	list<string> line;
	list<int> price;
	for(int i = 0; i < turns; i++){
		string opt; cin >> opt;
		if(opt == "Leave"){
			inside_emp ++;
			if(line.size()) {
				line.pop_front();
				price.pop_front();
				inside_emp--;
			}
		}
		else if(opt == "Car"){
			string name;
			int wai, pri;
			cin >> name >> wai >> pri;
			if(inside_emp > 0) inside_emp --;
			else if(line.size() < wai){
				line.push_back(name);
				price.push_back(pri);
			}
		}
		else if(opt == "Price"){
			int cost; cin >> cost;
			while(price.size() && price.back() > cost) {
				line.pop_back();
				price.pop_back();
			}
		}
	}
	bool isfirst = 1;
	if(line.size() == 0){
		cout << "empty" << endl;
	}
	else{
		while(line.size()){
			if(isfirst){
				cout << line.front();
				isfirst = 0;
				line.pop_front();
			}
			else{
				cout << " " << line.front();
				line.pop_front();
			}
		}
		cout << endl; 
	}
}
