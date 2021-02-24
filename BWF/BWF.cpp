//لطفا توجه شود در این برنامه ورودی ها به فرمت زیر است
//Best Fit
//Worst Fit
//First Fit
#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;
#pragma warning(disable:4996)
struct node {
	string name;
	int start;
	int end;
	struct node* next;
	struct node* left;
};

struct node* head, * tail, * temp, * ltail, * it;
int type;
string strg;

void allocate(string arg1, string arg2)
{
	int c = stoi(arg1);
	if (type == 1)//first fit
	{
		for (it = head; it->next != NULL && c!=0; it = it->next)
		{
			if (it->next->start - it->end >=c)
			{
				if (it->next->start - it->end > c)
				{
					temp = new struct node();
					temp->name = arg2;
					temp->start = it->end + 1;
					temp->end = it->end + c;
					temp->next = it->next;
					it->next = temp;
					temp->left = it;
					it->next->next->left = temp;
					break;
				}
				else
				{
					temp = new struct node();
					temp->start = it->end + 1;
					temp->end = it->next->start - 1;
					temp->next = it->next;
					it->next = temp;
					temp->left = it;
					it->next->left = temp;
					c = c - (it->next->start - it->end);
				}
			}
		}
	}
	else if (type == 2)//worst fit
	{
		map<int,string> wmap;
		for (it = head; it->next != NULL; it = it->next)
		{
			if (it->next->start - it->end > 0)
			{
				pair<int,string> s;
				s.first= (it->next->start - it->end);
				s.second = it->name;
				wmap.insert(s);
			}
		}
		string s = wmap.crbegin()->second;
		for (it = head; it->next != NULL; it = it->next)
		{
			if (it->name == s)
			{
				temp = new struct node();
				temp->name = arg2;
				temp->start = it->end + 1;
				temp->end = it->end + c;
				temp->next = it->next;
				it->next = temp;
				temp->left = it;
				it->next->next->left = temp;
				break;
			}
		}
	}
	else if (type == 3)//best fit
	{
		int min = stoi(strg);
		string name;
		for (it = head; it->next != NULL; it = it->next)
		{
			if (it->next->start - it->end >= c && (it->next->start - it->end) <= min)
			{
				min = it->next->start - it->end;
				name = it->name;
			}
		}
		for (it = head; it->next != NULL; it = it->next)
		{
			if (it->name == name)
			{
				temp = new struct node();
				temp->name = arg2;
				temp->start = it->end + 1;
				temp->end = it->end + c;
				temp->next = it->next;
				it->next = temp;
				temp->left = it;
				it->next->next->left = temp;
				break;
			}
		}
	}
}
void free_(string arg)
{
	for (it = head; it->next != NULL; it = it->next)
	{
		if (it->name == arg)
		{
			it->left->next = it->next;
			it->next->left = it->left;
			break;
		}
	}
}


int main()
{
	std::fstream fs;
	fs.open("in.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	getline(fs,strg);
	head =new struct node();
	head->name = "first";
	head->start = 0;
	head->end = 0;
	head->next = NULL;
	head->left = NULL;

	tail = new struct node();
	tail->name = "end";
	tail->start = stoi(strg);
	tail->end = stoi(strg);
	tail->next = NULL;
	tail->left = NULL;

	head->next = tail;
	tail->left = head;
	while (!fs.eof())
	{
		string str;
		char arg1[10], arg2[10];
		char arg[20];
		int index;
		getline(fs,str);
		if (str.find("allocate") != std::string::npos)
		{
			int i, j, k;
			for (i = 0; str[i] != '('; i++);
			for (j = (i + 1); str[j] != ','; j++)
				arg1[j - (i + 1)] = str[j];
			arg1[j - (i + 1)] = '\0';
			for (k = (j + 1); str[k] != ')'; k++)
				arg2[k - (j + 1)] = str[k];
			arg2[k - (j + 1)] = '\0';
			allocate(arg1, arg2);
		}
		if (str.find("free") != std::string::npos)
		{
			int i, j;
			for (i = 0; str[i] != '('; i++);
			for (j = i + 1; str[j] != ')'; j++)
				arg[j-(i+1)] = str[j];
			arg[j - (i + 1)] = '\0';
			free_(arg);
		}
		if (str.find("First Fit") != std::string::npos)
			type=1;
		if (str.find("Worst Fit") != std::string::npos)
			type=2;
		if (str.find("Best Fit") != std::string::npos)
			type=3;
	}


	std::fstream os;
	os.open("out.txt", std::fstream::out | std::fstream::app);

	os << "allocated:" << endl;
	for (it = head->next; it->next != NULL; it = it->next)
	{
		os << it->name << "(" << it->start << "," << it->end << ")" << endl;
	}
	os << "free:" << endl;
	for (it = head; it->next != NULL; it = it->next)
	{
		if ((it->end) + 1 == it->next->start)
			;
		else
		{
			if(it->next->next==NULL)
				os << it->end + 1 << "-" << it->next->start << endl;
			else
				os << it->end + 1 << "-" << it->next->start - 1 << endl;

		}
	}
	os.close();
}