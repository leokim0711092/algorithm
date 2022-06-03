#include<iostream>
#include<climits>
using namespace std;

struct L_pl_S{
	int len;
	int C[100][100];
	int b[100][100];
};
L_pl_S LCS(int [],int [],int,int);
void print_LCS(int[][100],int[],int,int);
int main(){
	int X[] = {0,6,6,6,0,8,9,4,5,7,9,4,5,3};
	int Y[]= {0,1,6,8,0,4,8,7,5,4,8,7,7,4,1,4};
	//int X[] = {0,1,4,6,2,8,1,5,6};
	//int Y[] = {0,1,6,9,8,5,1,6,3,2};
	
        int m = sizeof X/sizeof X[0];
	cout <<"X: ";
	for(int i=1;i<m;i++){
	cout <<X[i]<<" ";
	}
	cout<<endl;

        int n = sizeof Y/sizeof Y[0];
	cout <<"Y: ";
        for(int i=1;i<n;i++){
        cout <<Y[i]<<" ";
        }
        cout<<endl;

	L_pl_S ans = LCS(X,Y,m,n);
	cout <<"LCS = "<< ans.len<< endl;
	cout <<"Z=";
	print_LCS(ans.b,X,m-1,n-1);
	cout<<endl;
}
L_pl_S LCS(int X[],int Y[],int m,int n){
	L_pl_S ans;
	int C[m+1][n+1];
	int b[m+1][n+1];
	for(int i=0;i<=m;i++) C[i][0] =0;
      	for(int i=0;i<=n;i++) C[0][i] =0;	
	for(int i=1;i<m;i++){
		for(int j=1;j<n;j++){
			if(X[i] == Y[j]){
				C[i][j] = C[i-1][j-1]+1;
				b[i][j] = 0;
			}
			else if(C[i-1][j] < C[i][j-1]){
				C[i][j] = C[i][j-1];
				b[i][j] =1;
			}else{
				C[i][j]=C[i-1][j];
				b[i][j]=2;
			}
		}
	}
	ans.len = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			ans.C[j][i] = C[j][i];
		       	ans.b[j][i] = b[j][i];
			if(C[j][i] > ans.len) ans.len = C[j][i];
		}
	}
	return ans;
}
void print_LCS(int b[][100],int X[],int i,int j){
	if (i == 0 || j==0) return ;
	if(b[i][j] == 0){
		print_LCS(b,X,i-1,j-1);
		cout << X[i]<<" ";
	}else if(b[i][j] == 2){
		print_LCS(b,X,i-1,j);
	}else print_LCS(b,X,i,j-1);
}
