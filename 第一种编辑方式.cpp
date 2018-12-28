#include <iostream> 
#include <cstring>
#include <algorithm>
using namespace std;
char s1[1000], s2[1000];
int d[1001][1001];
int mmin(int a, int b, int c) {
	int t = a < b ? a : b;
	return t < c ? t : c;
}

void minEditDistance(int len1, int len2) {
	if (len1==0||len2==0) { 
		printf("%d\n", max(len1, len2));
		return;
	}
	int i, j;
	for (i = 0; i <= len1; i++)
		d[i][0] = i;
	for (j = 0; j <= len2; j++)
		d[0][j] = j;
	for (i = 1; i <= len1; i++)
		for (j = 1; j <= len2; j++) {
			int cost=s1[i-1] == s2[j-1] ? 0 : 1;
			d[i][j] = mmin(d[i-1][j] + 1, d[i][j-1] + 1, d[i-1][j-1]+cost);
		}
	printf("%d\n", d[len1][len2]);
}
int main() 
{
	while (cin>>s1>>s2) {
		int l1 = strlen(s1), l2 = strlen(s2);
		minEditDistance(l1, l2);
		for (int i = 0; i <= l1; i++)
		{
			for (int j = 0; j <= l2; j++)
			{
				printf("%d ", d[i][j]);
			}
			printf("\n");
		}
	}
	
}


/*#include <iostream> 
#include <cstring>
using namespace std;
char s1[1000], s2[1000];
//int dp[1001][1001];
int mmin(int a, int b, int c) {
	int t = a < b ? a : b;
	return t < c ? t : c;
}
void editDistance(int len1, int len2) {
	int** d=new int*[len1+1];
	for (int k=0; k<=len1; k++)
		d[k]=new int[len2+1];
	int i, j;
	for (i = 0; i <= len1; i++)
		d[i][0] = i;
	for (j = 0; j <= len2; j++)
		d[0][j] = j;
	for (i = 1; i <= len1; i++)
		for (j = 1; j <= len2; j++) {
			int cost = s1[i] == s2[j] ? 0 : 1;
			d[i][j] = mmin(d[i-1][j] + 1, d[i][j-1] + 1, d[i-1][j-1] + cost);
		}
	printf("%d\n", d[len1][len2]);
	for (int k=0; i<=len1; k++)
		delete[] d[k];
	delete[] d;
}
int main() {
	while (cin>>s1>>s2)
		editDistance(strlen(s1), strlen(s2));
}*/
