/*Rabin Karp/Rolling Hash algorithm is generally used for finding a pattern in a text in O(mn) time complexity
where m is the length of text and n is the length of pattern*/

//Note: This program works only for characters having +ve ascii value

#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define ll long long
#define pb push_back

void search_pattern(string txt, string patrn){
	/*Here h is number to be multiplied to a single digit to obtain the most significant bit
	like for 234 it is 100 for 2,
	d is the number of charaters and q is prime number i.e.,
	number used to range bound the hash values*/
	int i=0,j=0,h=1,m=txt.length(),n=patrn.length(),d=256,q=101;

	/*Here we are finding the value to be multiplied to obtain the most significant bit place*/
	while(i<n-1){
		h=(h*d)%q;
		++i;
	}

	/*Defining two variables to store the hash values of sliding window and pattern*/
	long hash_win=0, hash_patrn=0;
	i=0;

	/*Running the loop to obatin the hash value of pattern and sliding window*/
	while(j<n){
		hash_patrn=(hash_patrn*d+patrn[j])%q;
		hash_win=(hash_win*d+txt[j])%q;
		++j;
	}

	//sliding window
	for(i=0;i<m-n;++i){
		//cout<<i<<" ";
		if(hash_patrn==hash_win){
			bool flag=false;

			//check if there was a false positive i.e., collision case 
			for(int j=0;j<n;++j){
				if(txt[i+j]!=patrn[j]){
					flag=true;
					break;
				}
			}

			if(flag){continue;}

			cout<<i<<" ";
		}

		//obtain the hash value of next window
		hash_win=(d*(hash_win-txt[i]*h)+txt[n+i])%q;
		if(hash_win<0){hash_win+=q;}
	}
}

int main(){
	ifstream fin;
	fin.open("C:/Users/Aditya Shirude/Desktop/Codes/sample.txt");

	if(!fin.is_open()){
		cerr<<"Error in Opening the File";
		exit(EXIT_FAILURE);
	}

	string text,pattern;
	getline(fin,text);

	cin>>pattern;

	search_pattern(text,pattern);
	fin.close();
}