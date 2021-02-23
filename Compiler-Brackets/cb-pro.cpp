#include<iostream>
#include<string>
#include<vector>
using namespace std;


int main()
{
	string str;
	while (cin >> str)
	{
		int a = 0, b = 0, c = 0, d = 0, e = 0,flag=0;
		
		for (int i = 0; i < str.size(); i++)
		{
			if (a >= 0 && b >= 0 && c >= 0 && d >= 0 && e >= 0)
			{
				if (str[i] == '(')
				{
					if (str[i + 1] == '*')
					{
						str[i + 1] = '~';
						b++;
						//i++;
					}
					else
					{
						a++;
					}
				}
				else if (str[i] == '[')
					c++;
				else if (str[i] == '{')
					d++;
				else if (str[i] == '<')
					e++;
				else if (str[i] == ')')
				{
					a--;
				}
				else if (str[i] == '*')
				{
					if (str[i + 1] == ')')
					{
						b--;
						i++;
					}
					else if (str[i - 1] == '(')
					{					}
					else
						flag = 1;
				}
				else if (str[i] == ']')
					c--;
				else if (str[i] == '}')
					d--;
				else if (str[i] == '>')
					e--;
				else if(str[i]=='~')
				{ }
				else
					flag = 1;
			}
			else
				break;
		}
		if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0&&flag==0)
			cout << "YES"<<endl;
		else
			cout << "NO"<<endl;
		str = "";
	}
}
