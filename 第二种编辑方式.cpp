//完成第二种编辑方式的编辑，输出最优对齐和使用最优对齐时所选择的各个编辑步骤
//
#include <iostream>  
#include <stack>
#include <string>
#include <cstring>
using namespace std;

//进行样例序列编辑时要将a_stack, b_stack注释，因为此处两个栈是对应DNA问题代价进行的回溯
//copy,replace,delete,insert,twiddle,kill  
int cost[6] ={ -1,1,2,2,1,1 };     //DNA序列自动编辑代价 注意，这里为代价序列，同理，下面为代价矩阵
//int cost[6] = { 1,2,1,2,2,1 };      //普通序列代价（即样例那个）
int dp[100][100];
int oper[100][100];
enum { cop = 1, replace, del, insert, twi, kill};

//char a[]="algorithm", b[]="altruistic";
char a[] = "GATCGGCAT", b[] = "CAATGTGAATC";

void trackBack(int operMatrix[][100], int len1, int len2)
{
	stack<int > mystack;
	stack <char> a_stack;
	stack <char> b_stack;
	int i = len1;
	int j = len2;
	while (i>0 && j>0) {
		switch (operMatrix[i][j]) {
		case 1://copy  
		{
			mystack.push(cop);
			a_stack.push(a[i - 1]);    
			b_stack.push(b[j - 1]);
			i--; j--;
			break;
		}
		case 2://replace  
		{
			mystack.push(replace);
			a_stack.push(a[i - 1]);
			b_stack.push(b[j - 1]);
			i--; j--;
			break;
		}
		case 3://delete  
		{
			mystack.push(del);
			a_stack.push(a[i - 1]);
			b_stack.push(' ');
			i--;
			break;
		}	
		case 4://insert  
		{
			mystack.push(insert);
			a_stack.push(' ');
			b_stack.push(b[j - 1]);
			j--;
			break;
		}
		case 5:
		{
			mystack.push(twi);
			j -= 2;
			i -= 2;
			break;
		}
		}	
	}
	if (i == 0) {
		for (; j>0; j--) {
			mystack.push(insert);
			a_stack.push(' ');
			b_stack.push(b[j - 1]);
		}
	}
	else {
		for (; i>0; i--) {
			mystack.push(del);
			a_stack.push(a[i - 1]);
			b_stack.push(' ');
		}
	}
	while (!a_stack.empty())
	{
		cout << a_stack.top();
		a_stack.pop();
	}
	cout << '\n';
	while (!b_stack.empty())
	{
		cout << b_stack.top();
		b_stack.pop();
	}
	cout << '\n';
	while (!mystack.empty())
	{
		cout << mystack.top() << " ";
		mystack.pop();
	}
	cout << '\n';
}
void init(int ls, int ld)
{
	int i = 0, j = 0;
	for (i = 0; i <= ls; i++)
	{
		dp[i][0] = i * cost[2];
	}
	for (j = 0; j <= ld; j++)
	{
		dp[0][j] = j * cost[3];
	}
	for (i = 1; i <= ls; i++)
	{
		oper[i][0] = del;
	}
	for (j = 1; j <= ld; j++)
	{
		oper[0][j] = insert;
	}
}

int icopy(int i, int j, char s, char d)
{
	if (s == d)
	{
		int temp = dp[i][j] + cost[0];
		if (temp < dp[i+1][j+1])
		{
			dp[i+1][j+1]= temp;
			oper[i+1][j+1] = cop;
		}
	}
	return dp[i+1][j+1];
}

int ireplace(int i, int j, char s, char d)
{
	if (s != d)
	{
		int temp = dp[i][j] + cost[1];
		if (temp < dp[i+1][j+1])
		{
			dp[i+1][j+1]= temp;
			oper[i+1][j+1] = replace;
		}
	}
	return dp[i+1][j+1];
}

int idelete(int i, int j)
{
	int temp = dp[i][j+1] + cost[2];
	if (temp < dp[i+1][j+1])
	{
		dp[i+1][j+1]= temp;
		oper[i+1][j+1] = del;
	}
	return dp[i+1][j+1];
}

int iinsert(int i, int j)
{
	int temp = dp[i+1][j] + cost[3];
	if (temp < dp[i+1][j+1])
	{
		dp[i+1][j+1]= temp;
		oper[i+1][j+1] = insert;
	}
	return dp[i+1][j+1];
}

int itwiddle(int i, int j, char a, char b, char cc, char d)
{
	if (i && j && a == b && cc == d)
	{
		int temp = dp[i-1][j-1] + cost[4];
		if (temp < dp[i+1][j+1])
		{
			dp[i+1][j+1] = temp;
			oper[i + 1][j + 1] = twi;
		}
	}
	return dp[i+1][j+1];
}
int DP(char a[], char b[])
{
	int i = 0, j = 0;
	int la=strlen(a), lb=strlen(b);
	init(la, lb);
	for (i = 0; i < la; i++)
	{
		for (j = 0; j < lb; j++)
		{
			dp[i+1][j+1] = 10000000;
			dp[i+1][j+1] = icopy(i, j, a[i], b[j]);
			dp[i+1][j+1] = ireplace(i, j, a[i], b[j]);
			dp[i+1][j+1] = idelete(i, j);
			dp[i+1][j+1] = iinsert(i, j);
			dp[i+1][j+1] = itwiddle(i, j, a[i], b[j-1], a[i-1], b[j]);
		}
	}
	int ret = dp[la][lb];
	for (i = 1; i <= la; i++)
		if (dp[i][lb] + cost[5] < ret)
			ret = dp[i][lb] + cost[5];
	return ret;
}		

int main()
{
	int l1 = strlen(a), l2 = strlen(b);
	printf("%d\n", DP(a, b));
	printf("\n");
	
	for (int i = 0; i <= l1; i++)
	{
		for (int j = 0; j <= l2; j++)
		{
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i <= l1; i++)
	{
		for (int j = 0; j <= l2; j++) 
		{
			printf("%d ", oper[i][j]);
		}
		printf("\n");
	}
	cout << '\n';
	trackBack(oper, l1, l2);
	return 0;
}
