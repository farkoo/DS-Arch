#include<iostream>
using namespace std;
#pragma warning(disable:4996)
int main()
{
	int m, n, c;
	cin >> m  >> n;
	int** a = new int* [m];
	for (int i = 0; i < m; ++i)
		a[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	int l;
	cin >> l;
	int* b = new int[l];
	for (int i = 0; i < l; i++)
		cin >> b[i];
	for (int i = 0; i < m; i++)
	{
		int p = 0, q = 0, flag = 0, s = 0;
		while (q < l && p<n)
		{
			if (a[i][p] == b[q])
			{
				if (flag == 0)
				{
					flag = 1;
					s = p;
				}
				p++;
				q++;
			}
			else
			{
				q = 0;
				p = ++s;
				flag = 0;
			}
			if (p == (n))
				break;
		}
		if (flag == 1 && q==(l))
		{
			cout << i << ' ' << s << ' ' << i << ' ' << (s+l-1) << '\n';
			return 0;
		}
	}
	for (int i = 0; i < n; i++)
	{
		int p = 0, q = 0, flag = 0, s=0;
		while (q < l)
		{
			if (a[p][i] == b[q])
			{
				if (flag == 0)
				{
					flag = 1;
					s = p;
				}
				p++;
				q++;
			}
			else
			{
				q = 0;
				p = ++s;
				flag = 0;
			}
			if (p == m)
				break;
		}
		if (flag == 1)
		{
			cout << s << ' ' << i << ' ' << (s+l-1) << ' ' << i << '\n';
			return 0;
		}
	}
	if (m == 0 && n == 0)
		cout <<"0 0 0 0";
	return 0;
}
