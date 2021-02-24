#include<iostream>
#include<string>
using namespace std;
#pragma warning(disable:4996)
class train_list;
class skip_list;
class train_node;
class skip_node;
class traveler_list;
class stack;
class traveler_node;
train_node* skipFunc(int stn, skip_node* it);
class train_node {
	friend train_list;
public:
	int station;
	int n_traveler = 0;
	int sum = 0;
	traveler_node* dlink;
	train_node* next;
};
class train_list {
public:
	train_node* first = NULL;
	train_node* rear = NULL;
	train_list(int arr[50])
	{
		train_node* temp;
		for (int i = 0; i < 50; i++)
		{
			temp = new train_node();
			temp->next = NULL;
			temp->station = arr[i];
			temp->dlink = NULL;
			if (first == NULL)
			{
				first = temp;
				rear = temp;
			}
			else {
				rear->next = temp;
				rear = temp;
			}
		}
	}
	void insert_traveler1(skip_node* sk, int station, traveler_node* first_traveler, int size)
	{
		train_node* i = skipFunc(station, sk);
		i->dlink = first_traveler;
		i->n_traveler = size;
	}
	void insert_traveler2(int station, traveler_node* first_traveler, int size)
	{
		for (train_node* it = first; it!= NULL; it = it->next)
		{
			if (it->station == station)
			{
				it->dlink = first_traveler;
				it->n_traveler = size;
				break;
			}
		}
	}
};
class skip_node {
public:
	int skip_station;
	train_node* slink;
	skip_node* next;
};
class skip_list {
public:
	friend skip_node;
	skip_node* first = NULL;
	skip_node* rear = NULL;
	skip_list(train_node* it)
	{
		for (train_node* i = it; i->station <= 43; i = i->next)
		{
			if (i->station % 7 == 1)
			{
				skip_node* j = new skip_node();
				j->next = NULL;
				j->slink = i;
				j->skip_station = i->station;
				if (first == NULL)
				{
					first = j;
					rear = j;
				}
				else {
					rear->next = j;
					rear = j;
				}
			}
		}
	}
};
train_node* skipFunc(int stn, skip_node* it)
{
	train_node* r = NULL;
	for (skip_node* i = it; i != NULL; i = i->next)
	{
		if ((i->skip_station <= stn && i->next == NULL) || (i->skip_station <= stn && i->next->skip_station > stn))
		{
			for (train_node* j = i->slink; j != NULL; j = j->next)
			{
				if (j->station == stn)
				{
					r = j;
					break;
				}
			}
			break;
		}
	}
	return r;
}
class stack_node {
public:
	friend stack;
	int value;
	stack_node* next;
	stack_node(int _val) {
		next = NULL;
		value = _val;
	}
};
class stack {
public:
	stack_node* top;
	stack() {
		top = NULL;
	}
	void push(int _val) {
		stack_node* x = new stack_node(_val);
		if (top == NULL)
			top = x;
		else {
			x->next = top;
			top = x;
		}
	}
	void pop() {
		stack_node* t, *temp;
		for (t = top; t->next != top; t = t->next);
		temp = top;
		top = t;
		top->next = NULL;
		delete(temp);
	}
};
class traveler_node {
public:
	friend traveler_list;
	string ID;
	stack food;
	traveler_node* next;
};
class traveler_list {
public:
	int size;
	traveler_node* first = NULL;
	traveler_node* rear = NULL;
	void insert(string _ID) {
		traveler_node* i = new traveler_node;
		i->next = NULL;
		i->ID = _ID;
		if (first == NULL) {
			first = i;
			rear = i;
		}
		else {
			rear->next = i;
			rear = i;
		}
		size++;
	}
};
int traveler_num(train_node* first1, train_node* first2, int length)
{
	int sum1 = 0, sum2 = 0;
	for (train_node* it = first1; it != NULL; it = it->next)
		sum1 += it->n_traveler;
	for (train_node* it = first2; it != NULL; it = it->next)
		sum2 += it->n_traveler;
	return (length + sum2 - sum1);
}
void setTrain2(int stn, train_node* f, string id, stack s)
{
	train_node* r = NULL;
	traveler_node* t = NULL;
	for (train_node* i = f; i != NULL; i = i->next)
	{
		if (stn == i->station)
		{
			r = i;
			break;
		}
	}
	for (traveler_node* i = r->dlink; i != NULL; i = i->next)
	{
		if (i->ID == id)
		{
			t = i;
			break;
		}
	}
	t->food = s;
}
void setTrain1(int stn, train_node* f, skip_node* sk, string id, stack s)
{
	train_node* h = skipFunc(stn, sk);
	traveler_node* t = NULL;
	for (traveler_node* i = h->dlink; i != NULL; i = i->next)
	{
		if (i->ID == id)
		{
			t = i;
			break;
		}
	}
	t->food = s;
}
void getTrain1(train_node* f)
{
	for (train_node* i = f; i != NULL; i = i->next)
	{
		int st = i->station;
		for (traveler_node* j = i->dlink; j != NULL; j = j->next)
		{
			cout << st << ":" << "[" << j->ID << ":" << "{";
			for (stack_node* k = j->food.top; k != NULL; k = k->next)
			{
				cout << k->value;
				if (k->next != NULL)
					cout << ",";
			}
			cout << "}]" << endl;
		}
	}
}
void getTrain2(train_node* f)
{
	int count = 1;
	while (count != 51)
	{
		for (train_node* i = f; i != NULL; i = i->next)
		{
			if (i->station == count)
			{
				int st = i->station;
				for (traveler_node* j = i->dlink; j != NULL; j = j->next)
				{
					cout << st << ":" << "[" << j->ID << ":" << "{";
					for (stack_node* k = j->food.top; k != NULL; k = k->next)
					{
						cout << k->value;
						if (k->next != NULL)
							cout << ",";
					}
					cout << "}]" << endl;
				}

				count++;
				break;
			}
		}
	}
}
void getFood1(train_node* f)
{
	for (train_node* i = f; i != NULL; i = i->next)
	{
		int st = i->station;
		for (traveler_node* j = i->dlink; j != NULL; j = j->next)
		{
			cout << j->ID << ":" << "{";
			for (stack_node* k = j->food.top; k != NULL;)
			{
				cout << k->value;
				j->food.pop();
				if (k->next != NULL)
					cout << ",";
			}
			cout << "}" << endl;
		}
	}
}
void getFood2(train_node * f)
{
	int count = 1;
	while (count != 51)
	{
		for (train_node* i = f; i != NULL; i = i->next)
		{
			int st = i->station;
			for (traveler_node* j = i->dlink; j != NULL; j = j->next)
			{
				cout << j->ID << ":" << "{";
				for (stack_node* k = j->food.top; k != NULL;)
				{
					cout << k->value;
					j->food.pop();
					if (k->next != NULL)
						cout << ",";
				}
				cout << "}" << endl;
			}

			count++;
			break;
		}
	}
}
void SUM(train_node* first1, train_node* first2, skip_node*fs)
{
	for (train_node* i = first2; i != NULL; i = i->next)
	{
		train_node* j = skipFunc(i->station, fs);
		int sum = i->n_traveler + j->n_traveler;
		i->sum = sum;
		j->sum = sum;
	}
}
void print_sum(train_node* first) {
	int sta = 1;
	for (train_node* it = first; it != NULL; it = it->next, sta++)
		cout << "Number of moving traveller in station " << sta << ": " << it->sum << endl;
}
int main()
{
	int arr1[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50 };
	int arr2[50] = { 9,5,8,1,4,7,3,2,6,10,19,15,18,11,14,17,13,12,16,20,29,25,28,21,24,27,23,22,26,30,39,35,38,31,34,37,33,32,36,40,49,45,48,41,44,47,43,42,46,50 };
	train_list train1(arr1);
	train_list train2(arr2);
	skip_list sk(train1.first);
	int n1, n2;
	int counter1 = 0, counter2 = 0;
	cin >> n1 >> n2;
	char e = getchar();
	string station1, station2;
	string x, xx;
	bool flag = false;
	int t1 = 0, t2 = 0;
	int sta;
	getline(cin, station1);
	getline(cin, station2);
	for (int i = 0; i < station1.length(); i++)
		if (station1[i] == '-')
			t1++;
	for (int i = 0; i < station2.length(); i++)
		if (station2[i] == '-')
			t2++;
	//reading travelers
	for (int i = 0; i <= t1; i++) {
		getline(cin, x);
		traveler_list tra;
		for (int j = 0; j < x.length(); j++) {
			if (x[j] == ':') {
				flag = true;
				sta = stoi(xx);
				xx = "";
			}
			else if (!flag)
				xx.push_back(x[j]);

			else {
				if (x[j] != ' ' && x[j] != ',')
					xx.push_back(x[j]);
				if (x[j] == ',' || j == x.length() - 1) {
					tra.insert(xx);
					counter1++;
					xx = "";
				}
			}
		}
		train1.insert_traveler1(sk.first, sta, tra.first, tra.size);
	}
	x = "";
	xx = "";
	flag = false;
	for (int i = 0; i <= t2; i++) {
		getline(cin, x);
		traveler_list tra;
		for (int j = 0; j < x.length(); j++) {
			if (x[j] == ':') {
				flag = true;
				sta = stoi(xx);
				xx = "";
			}
			else if (!flag)
				xx.push_back(x[j]);
			else {
				if (x[j] != ' ' && x[j] != ',')
					xx.push_back(x[j]);
				if (x[j] == ',' || j == x.length() - 1) {
					tra.insert(xx);
					counter2++;
					xx = "";
				}
			}
		}
		train2.insert_traveler2(sta, tra.first, tra.size);
	}
	SUM(train1.first, train2.first, sk.first);
	//reading orders
	x = "";
	xx = "";
	flag = false;
	char flag1 = ' ';
	string ID;
	for (int i = 0; i < counter1; i++) {
		getline(cin, x);
		stack s;
		for (int j = 0; j < x.length(); j++) {
			if (x[j] == ':' && flag1 == ' ') {
				flag1 = ':';
				sta = stoi(xx);
				xx = "";
			}
			else if (x[j] == ':' && flag1 != ' ') {
				ID = xx;
				xx = "";
			}
			else if (x[j] == ',') {
				s.push(stoi(xx));
				xx = "";
			}
			else if (x[j] == '}') {
				s.push(stoi(xx));
				xx = "";
			}
			else if (isalnum(x[j]))
				xx.push_back(x[j]);
		}
		setTrain1(sta, train1.first, sk.first, ID, s);
		flag1 = ' ';
	}
	x = "";
	xx = "";
	flag = false;
	flag1 = ' ';
	ID = "";
	for (int i = 0; i < counter2; i++) {
		getline(cin, x);
		stack s;
		for (int j = 0; j < x.length(); j++) {
			if (x[j] == ':' && flag1 == ' ') {
				flag1 = ':';
				sta = stoi(xx);
				xx = "";
			}
			else if (x[j] == ':' && flag1 != ' ') {
				ID = xx;
				xx = "";
			}
			else if (x[j] == ',') {
				s.push(stoi(xx));
				xx = "";
			}
			else if (x[j] == '}') {
				s.push(stoi(xx));
				xx = "";
			}
			else if (isalnum(x[j]))
				xx.push_back(x[j]);
		}
		setTrain2(sta, train2.first, ID, s);
		flag1 = ' ';
	}
	//Output
	cout << endl << "***Output***" << endl;
	print_sum(train1.first);
	cout << "number of traveller in first train: " << traveler_num(train1.first, train2.first, n1) << endl;
	cout << "number of traveller in second train: " << traveler_num(train2.first, train1.first, n2) << endl;
	getTrain1(train1.first);
	getTrain2(train2.first);
	return 0;
}
