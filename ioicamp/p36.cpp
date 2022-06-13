#include<bits/stdc++.h>

using namespace std;

int main(){
  int a,b;
  while(cin>>a>>b){
    while(b){
      int x=a;
      a-=b;
      b=(x&0)<<1;
    }
    cout<<a<<endl;
  }
  return 0;
}
