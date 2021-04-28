#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <assert.h>
#include <vector>

using namespace std;

class Bignumbers
{
protected:
	int NUM_SIZE = 200, VOID_EL = -1;

	int* mas;
	bool NegNumFlag = 0, send = 0, nom;

public:
	Bignumbers()
	{

		mas = new int[NUM_SIZE];
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = VOID_EL;
		//cout << "Create: " << mas << endl;
	}
	~Bignumbers() {
		//cout << "Destruct: " << mas << endl;
		delete[] mas;
	}

	int* extract()
	{
		return mas;
	}

	bool NegNum()
	{
		return NegNumFlag;
	}

protected:
	int kdigit(int* mas)
	{
		int k = 0;
		bool F = 0;
		if (mas[0] != 0) return NUM_SIZE;
		else
		{
			int i = 0;
			for (; i < NUM_SIZE && mas[i] == 0; i++);
			return NUM_SIZE - i;
		}
	}

	int prior(Bignumbers& b)		//Возвращает приоритет данного числа
	{
		int* mas2 = b.extract();
		int r = -1;
		for (int i = 0; i < NUM_SIZE; i++)
		{
			if (mas[i] > mas2[i] && r == -1) r = 1;
			if (mas[i] < mas2[i] && r == -1) r = 0;
		}

		return r;
	}

	int prior(vector <int>& a, vector <int>& b)		//Возвращает приоритет данного числа
	{
		int r = -1;

		if (a.size() > b.size()) return 1;
		if (a.size() < b.size()) return 0;
		if (a.size() == b.size())
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] > b[i])return 1;
				if (a[i] < b[i])return 0;
			}

		return r;
	}

	int prior(Bignumbers& a, Bignumbers& b)		//Возвращает приоритет данного числа
	{
		int r = -1, * mas1 = a.mas, * mas2 = b.mas;

		for (int i = 0; i < NUM_SIZE; i++)
		{
			if (mas1[i] > mas2[i] && r == -1) r = 1;
			if (mas1[i] < mas2[i] && r == -1) r = 0;
		}
		/*if (a.NegNumFlag > b.NegNumFlag && r == 1) r = 0;
		if (a.NegNumFlag < b.NegNumFlag && r == 0) r = 1;
		if (a.NegNumFlag && b.NegNumFlag && r == 1) r = 0;*/

		return r;
	}

	void shift(int* mas)				//Сдвиг массива вправо до края
	{
		int ptr = NUM_SIZE - 1;
		bool F = 1;
		for (int i = NUM_SIZE - 1; i >= 0 && F; i--)
		{
			while (mas[i] == VOID_EL) i--;
			if (ptr != i)
			{
				mas[ptr] = mas[i];
				mas[i] = VOID_EL;
				ptr--;
			}
			else F = 0;
		}
	}

	void normalize(int* mas)
	{
		for (int i = 0; i < NUM_SIZE; i++)			//Преобазование массива к нормальному виду
			if (mas[i] == VOID_EL) mas[i] = 0;
	}

public:
	void print_num()
	{
		//for (int i = 0; i < NUM_SIZE; i++)     //Полный вывод массива
		//	cout << mas[i];

		if (NegNumFlag == 1) cout << '-';
		int f;
		if (kdigit(mas)) f = kdigit(mas);
		else f = 1;
		for (int i = NUM_SIZE - f; i < NUM_SIZE; i++)		//Вывод без нулей в начале

			cout << mas[i];
	}

	string print_numstr()
	{
		string tmp = "";
		//for (int i = 0; i < NUM_SIZE; i++)     //Полный вывод массива
		//	cout << mas[i];

		if (NegNumFlag == 1) tmp+="-";
		int f;
		if (kdigit(mas)) f = kdigit(mas);
		else f = 1;
		for (int i = NUM_SIZE - f; i < NUM_SIZE; i++)		//Вывод без нулей в начале

			tmp+=char(mas[i]+48);
		return tmp;
	}

	void clear()
	{
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = VOID_EL;
	}

	void clear_to_null()
	{
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = 0;
	}

	void copy(Bignumbers& b)
	{
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = b.mas[i];
		NegNumFlag = b.NegNumFlag;
		NUM_SIZE = b.NUM_SIZE;
		VOID_EL = b.VOID_EL;
		NegNumFlag = b.NegNumFlag;
		send = b.send;
		nom = b.nom;
	}

	void copyUk(Bignumbers& b)
	{
		mas = b.mas;
		NegNumFlag = b.NegNumFlag;
	}

	void assign_int(int num)						//Заполнение массива из переменной
	{
		if (num < 0) NegNumFlag = 1;
		num = abs(num);
		for (int i = NUM_SIZE - 1; i >= 0; i--)
		{
			mas[i] = num % 10;
			num /= 10;
		}
	}

	void assign_direct()
	{
		for (int i = 0; i < NUM_SIZE; i++)			//Ручное заполнение массива
		{
			while (!_kbhit())
			{
				Sleep(5);
			}
			int key = _getch();
			if (key == '-') { NegNumFlag = 1; cout << '-'; }
			if (key == 13) break;
			if (key == 8)
			{
				system("cls");
				if (i != 0) i--;
				else { NegNumFlag = 0; }
				mas[i] = VOID_EL;
				if (NegNumFlag) cout << '-';
				for (int j = 0; j < i; j++)
					cout << mas[j];
				i--;
			}
			else
			{
				if (key >= 48 && key <= 57)
				{
					mas[i] = key - 48;
					cout << key - 48;
				}
				else
				{
					i--;
					continue;
				}
			}
		}

		shift(mas);				//Сдвиг массива вправо до края

		normalize(mas);			//Преобазование массива к нормальному виду

		cout << endl;
	}

	void sub(int b)
	{
		Bignumbers bn;
		bn.assign_int(b);
		sub(bn);
	}

	void sub(Bignumbers& b)
	{
		bool priority = prior(b), priority2 = !priority;
		Bignumbers tmp, tmpb, a;

		nom = 0; b.nom = 1;
		tmpb.copy(b);

		a.mas = mas;
		a.NegNumFlag = NegNumFlag;
		if (priority < priority2)
		{
			tmp.copy(b);
			b.copy(a);
			copy(tmp);
			nom = !nom;
			b.nom = !b.nom;
		}

		a.mas = 0;
		//if (priority < priority2) { tmp.mas = b.mas; tmp.NegNumFlag = b.NegNumFlag; b.NegNumFlag = NegNumFlag; b.mas = mas; mas = tmp.mas; NegNumFlag = tmp.NegNumFlag; nom = !nom; b.nom = !b.nom; }  //Swap

		if (((!NegNumFlag && b.NegNum()) || (NegNumFlag && !b.NegNum())) && !b.send) { b.NegNumFlag = !b.NegNumFlag; sum(b); b.copy(tmpb); tmpb.mas = 0; if (nom) NegNumFlag = !NegNumFlag; return; }

		int* mas2 = b.extract();

		int ptr;

		for (int i = NUM_SIZE - 1; i >= 0; i--)
		{
			if (mas[i] < mas2[i])
			{
				ptr = i;
				do
				{
					ptr--;
					assert(ptr >= 0);
				} while (mas[ptr] == 0);
				mas[ptr]--;
				ptr++;

				while (ptr != i) { mas[ptr] = 9; ptr++; }
				mas[i] += 10;
			}
			mas[i] -= mas2[i];
		}
		if (nom) NegNumFlag = !NegNumFlag;

		b.copy(tmpb);
		mas2 = nullptr;
	}

	void sum(int b)
	{
		Bignumbers bn;
		bn.assign_int(b);
		sum(bn);
	}

	void sum(Bignumbers& b)
	{
		bool priority = prior(b), priority2 = !priority;
		Bignumbers tmp, tmpb, a;

		tmpb.copy(b);

		a.mas = mas;
		a.NegNumFlag = NegNumFlag;
		if (priority < priority2)
		{
			tmp.copy(b);
			b.copy(a);
			copy(tmp);
		}
		a.mas = 0;
		//if (priority < priority2) { tmp.mas = b.mas; tmp.NegNumFlag = b.NegNumFlag; b.NegNumFlag = NegNumFlag; b.mas = mas; mas = tmp.mas; NegNumFlag = tmp.NegNumFlag; }  //Swap

		if (NegNumFlag != b.NegNum()) { b.send = 1; sub(b); b.copy(tmpb); return; }

		int* mas2 = b.extract();
		assert(((mas[0] + mas2[0]) / 10) == 0);
		for (int i = NUM_SIZE - 1; i >= 1; i--)
		{
			mas[i - 1] += (mas[i] + mas2[i]) / 10;
			mas[i] = (mas[i] + mas2[i]) % 10;
		}

		b.copy(tmpb);
		mas2 = nullptr;
	}

	void mlp(int b)
	{
		Bignumbers bn;
		bn.assign_int(b);
		mlp(bn);
	}

	void mlp(Bignumbers& b)
	{
		int* mas2 = b.extract();
		assert(((kdigit(mas) + kdigit(mas2) - 1) <= NUM_SIZE) && (mas[0] * mas2[NUM_SIZE - 1] < 10));

		int* tmp = new int[NUM_SIZE + kdigit(mas2)];
		for (int i = 0; i < NUM_SIZE + kdigit(mas2); i++) tmp[i] = 0;
		int ptr = 0;

		for (int j = NUM_SIZE - 1; j >= 0 && j != NUM_SIZE - kdigit(mas2) - 2; j--)
		{
			for (int i = NUM_SIZE - 1; i >= 0; i--)
			{
				tmp[i - ptr + kdigit(mas2) - 1] += (mas2[j] * mas[i]) / 10;
				tmp[i - ptr + kdigit(mas2)] += (mas2[j] * mas[i]) % 10;

				if (tmp[i - ptr + kdigit(mas2)] / 10 > 0)
				{
					tmp[i - ptr + kdigit(mas2) - 1] += tmp[i - ptr + kdigit(mas2)] / 10;
					tmp[i - ptr + kdigit(mas2)] = tmp[i - ptr + kdigit(mas2)] % 10;
				}
			}
			ptr++;
		}

		for (int i = 0; i < NUM_SIZE; i++)
			mas[i] = tmp[i + kdigit(mas2)];
		NegNumFlag = (NegNumFlag + b.NegNum()) % 2;
		mas2 = nullptr;
	}

	void div_chld(Bignumbers& b)
	{
		if (b.NegNumFlag) b.NegNumFlag = 0;

		Bignumbers res, E;
		E.assign_int(1);
		res.assign_int(0);

		while (prior(b) && !NegNumFlag)
		{
			sub(b);
			res.sum(E);
		}
		copy(res);
	}

	void div(int b)
	{
		Bignumbers bn;
		bn.assign_int(b);
		div(bn);
	}

	void div(Bignumbers& b)
	{
		Bignumbers res, tmp, tmptmp;
		vector <int> resvec, tmpvec, masvec, bvec;
		bool NNF = b.NegNumFlag;

		for (int i = NUM_SIZE - 1; i >= NUM_SIZE - kdigit(mas); i--) masvec.push_back(mas[i]);
		for (int i = NUM_SIZE - kdigit(b.mas); i < NUM_SIZE; i++) bvec.push_back(b.mas[i]);

		while (prior(tmpvec, bvec) == 0)		// Дополнение tmp
		{
			if (masvec.empty())
			{
				clear_to_null();
				if (resvec.empty())	return;
				else
				{
					for (int i = NUM_SIZE - 1; i >= NUM_SIZE - resvec.size(); i--) { mas[i] = resvec[resvec.size() - 1]; resvec.pop_back(); }
					return;
				}
			}

			tmpvec.push_back(masvec[masvec.size() - 1]);
			masvec.pop_back();
		}

		masvec.push_back(tmpvec[tmpvec.size() - 1]);
		tmpvec.pop_back();

		while (!masvec.empty())
		{
			tmpvec.push_back(masvec[masvec.size() - 1]);
			masvec.pop_back();

			tmp.clear_to_null();
			for (int i = NUM_SIZE - 1; !tmpvec.empty(); i--) { tmp.mas[i] = tmpvec[tmpvec.size() - 1]; tmpvec.pop_back(); }

			tmptmp.copy(tmp);
			tmptmp.div_chld(b);
			resvec.push_back(tmptmp.mas[NUM_SIZE - 1]);
			tmptmp.mlp(b);
			tmp.sub(tmptmp);

			while (tmpvec.size() != 0) tmpvec.pop_back();
			for (int i = NUM_SIZE - kdigit(tmp.mas); i < NUM_SIZE; i++) tmpvec.push_back(tmp.mas[i]);
		}

		clear_to_null();
		for (int i = NUM_SIZE - 1; !resvec.empty(); i--) { mas[i] = resvec[resvec.size() - 1]; resvec.pop_back(); }
		b.NegNumFlag = NNF;
		NegNumFlag = (NegNumFlag + b.NegNum()) % 2;
	}

	void fc(int fc)
	{
		assign_int(1);
		if (fc == 0) return;
		Bignumbers tmp;
		for (int i = 1; i <= fc; i++)
		{
			tmp.assign_int(i);
			mlp(tmp);
		}
	}

	void st(int x)
	{
		Bignumbers a, b;

		a.mas = mas;
		a.NegNumFlag = NegNumFlag;

		b.copy(a);

		if (x == 0) { assign_int(1); return; }
		if (x > 1)
			for (int i = 2; i <= x; i++)
				mlp(b);
		a.mas = 0;
	}

	Bignumbers& operator= (Bignumbers& other)
	{
		copy(other);
		return *this;
	}

	Bignumbers& operator= (Bignumbers&& other)
	{
		copy(other);
		return *this;
	}

	Bignumbers& operator= (int x)
	{
		assign_int(x);
		return *this;
	}

	Bignumbers operator- ()
	{
		Bignumbers tmp = *this;
		tmp.NegNumFlag = !tmp.NegNumFlag;
		return tmp;
	}

	Bignumbers& operator++ ()
	{
		this->sum(1);
		return *this;
	}

	Bignumbers operator++ (int)
	{
		Bignumbers tmp = *this;
		this->sum(1);
		return tmp;
	}

	Bignumbers& operator-- ()
	{
		this->sub(1);
		return *this;
	}

	Bignumbers operator-- (int)
	{
		Bignumbers tmp = *this;
		this->sub(1);
		return tmp;
	}

	Bignumbers operator+ (Bignumbers& other)
	{
		Bignumbers tmp = *this;
		tmp.sum(other);
		return tmp;
	}

	Bignumbers operator- (Bignumbers& other)
	{
		Bignumbers tmp = *this;
		tmp.sub(other);
		return tmp;
	}

	Bignumbers operator* (Bignumbers& other)
	{
		Bignumbers tmp = *this;
		tmp.mlp(other);
		return tmp;
	}

	Bignumbers operator/ (Bignumbers& other)
	{
		Bignumbers tmp = *this;
		tmp.div(other);
		return tmp;
	}

	Bignumbers operator+ (Bignumbers&& other)
	{
		Bignumbers tmp = *this;
		tmp.sum(other);
		return tmp;
	}

	Bignumbers operator- (Bignumbers&& other)
	{
		Bignumbers tmp = *this;
		tmp.sub(other);
		return tmp;
	}

	Bignumbers operator* (Bignumbers&& other)
	{
		Bignumbers tmp = *this;
		tmp.mlp(other);
		return tmp;
	}

	Bignumbers operator/ (Bignumbers&& other)
	{
		Bignumbers tmp = *this;
		tmp.div(other);
		return tmp;
	}

	Bignumbers& operator+= (Bignumbers& other)
	{
		this->sum(other);
		return *this;
	}

	Bignumbers& operator-= (Bignumbers& other)
	{
		this->sub(other);
		return *this;
	}

	Bignumbers& operator*= (Bignumbers& other)
	{
		this->mlp(other);
		return *this;
	}

	Bignumbers& operator/= (Bignumbers& other)
	{
		this->div(other);
		return *this;
	}

	Bignumbers& operator+= (Bignumbers&& other)
	{
		this->sum(other);
		return *this;
	}

	Bignumbers& operator-= (Bignumbers&& other)
	{
		this->sub(other);
		return *this;
	}

	Bignumbers& operator*= (Bignumbers&& other)
	{
		this->mlp(other);
		return *this;
	}

	Bignumbers& operator/= (Bignumbers&& other)
	{
		this->div(other);
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, Bignumbers&& num)
	{
		num.print_num();
		return out;
	}

	friend std::ostream& operator<< (std::ostream& out, Bignumbers& num)
	{
		num.print_num();
		return out;
	}

	friend std::istream& operator>> (std::istream& in, Bignumbers& num)
	{
		num.assign_direct();
		return in;
	}

	Bignumbers(Bignumbers& other)
	{
		mas = new int[NUM_SIZE];
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = VOID_EL;
		copy(other);
	}

	Bignumbers(Bignumbers&& other)
	{
		mas = new int[NUM_SIZE];
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = VOID_EL;
		copy(other);
	}


	Bignumbers(int value)
	{
		mas = new int[NUM_SIZE];
		for (int i = 0; i < NUM_SIZE; i++) mas[i] = VOID_EL;
		assign_int(value);
	}

};



//struct Komb
//{
//	char info = ' ';
//	int argN, argK;
//	bool tilda = 0;
//	Bignumbers value;
//};
//
//
//class Stek
//{
//protected:
//	Komb *mass, clear;
//	int StackPointer = -1, N;
//public:
//	Stek() { cin >> N; mass = new Komb[N - 1]; }
//	Stek(int a) { N = a; mass = new Komb[N - 1]; }
//
//	~Stek() { }
//
//	bool IsEmpty() {
//		return (StackPointer == -1);
//	}
//
//	bool IsFull() {
//		return (StackPointer == N);
//	}
//
//	void Push(Komb x) {
//		if (!IsFull()) {
//			StackPointer++;
//			mass[StackPointer].info = x.info;
//			mass[StackPointer].argN = x.argN;
//			mass[StackPointer].argK = x.argK;
//			mass[StackPointer].tilda = x.tilda;
//			mass[StackPointer].value.copyUk(x.value);
//
//		}
//	}
//
//	void Pop() {
//		if (!IsEmpty()) {
//			StackPointer--;
//		}
//	}
//
//	Komb Top() {
//		return mass[StackPointer];
//	}
//};
//
//int prior(char x) {
//	switch (x)
//	{
//	case '+': return 2;
//	case '-': return 2;
//	case '*': return 3;
//	case '/': return 3;
//	case '(': return 1;
//	}
//}
//
//void calkulating(Komb &a, bool F)
//{
//	if (a.info == 'A' && a.tilda == 0)
//	{
//		if (a.argK > a.argN)
//		{
//			cout << "\nНеверные аргументы!\n";
//			system("pause");
//			assert(a.argK <= a.argN);
//		}
//		Bignumbers res, znm;
//		res.fc(a.argN);
//		znm.fc(a.argN - a.argK);
//		res.div(znm);
//		a.value.copy(res);
//	}
//
//	if (a.info == 'C' && a.tilda == 0)
//	{
//		if (a.argK > a.argN)
//		{
//			cout << "\nНеверные аргументы!\n";
//			system("pause");
//			assert(a.argK <= a.argN);
//		}
//		Bignumbers znm;
//		a.value.fc(a.argN);
//		znm.fc(a.argN - a.argK);
//		a.value.div(znm);
//		znm.fc(a.argK);
//		a.value.div(znm);
//	}
//
//	if (a.info == 'P' && a.tilda == 0)
//	{
//		a.value.fc(a.argN);
//	}
//
//	if (a.info == 'A' && a.tilda == 1)
//	{
//		a.value.assign_int(a.argN);
//		a.value.st(a.argK);
//	}
//
//	if (a.info == 'C' && a.tilda == 1)
//	{
//		if (a.argN < 1)
//		{
//			cout << "\nНеверные аргументы!\n";
//			system("pause");
//			assert(a.argN > 0);
//		}
//		Bignumbers res, znm1, znm2;
//
//		a.argN += a.argK - 1;
//
//		res.fc(a.argN);
//		znm1.fc(a.argK);
//		znm2.fc(a.argN - a.argK);
//		znm1.mlp(znm2);
//		res.div(znm1);
//		a.value.copy(res);
//	}
//
//	if (a.info == 'P' && a.tilda == 1)
//	{
//		a.value.assign_int(a.argN);
//		a.value.st(a.argN);
//	}
//
//	if (a.info == '!')
//	{
//		a.value.fc(a.argN);
//	}
//
//	if (a.info == '^')
//	{
//		a.value.assign_int(a.argN);
//		a.value.st(a.argK);
//	}
//	if (F)
//	{
//		cout << "\nРезультат: ";
//		a.value.print_num();
//	}
//
//}
//
//vector <Komb> polskanota(vector <Komb> &vrj)
//{
//	vector <Komb> rez;
//	rez.reserve(vrj.size());
//	Komb tmp;
//
//	Stek *stk = new Stek(vrj.size());
//
//	for (int i = 0; i < vrj.size(); i++)
//	{
//		if (vrj[i].info == 'A' || vrj[i].info == 'C' || vrj[i].info == 'P' || vrj[i].info == '^' || vrj[i].info == '!') rez.push_back(vrj[i]);
//		if (vrj[i].info == '(') stk->Push(vrj[i]);
//		if (vrj[i].info == ')')
//		{
//			while (stk->Top().info != '(')
//			{
//				rez.push_back(stk->Top());
//				stk->Pop();
//			}
//			stk->Pop();
//		}
//		if (vrj[i].info == '+' || vrj[i].info == '-' || vrj[i].info == '*' || vrj[i].info == '/')
//		{
//			if (stk->IsEmpty() || prior(stk->Top().info) < prior(vrj[i].info)) stk->Push(vrj[i]);
//			else if (!(stk->IsEmpty() || prior(stk->Top().info) < prior(vrj[i].info)))
//			{
//				while (!(stk->IsEmpty() || prior(stk->Top().info) < prior(vrj[i].info)))
//				{
//					rez.push_back(stk->Top());
//					stk->Pop();
//				}
//				if (stk->IsEmpty() || prior(stk->Top().info) < prior(vrj[i].info)) stk->Push(vrj[i]);
//			}
//		}
//	}
//
//	while (!stk->IsEmpty())
//	{
//		rez.push_back(stk->Top());
//		stk->Pop();
//	}
//
//	for (int i = 0; i < rez.size(); i++)
//		if (rez.size() == 1) calkulating(rez[i], 1);
//		else calkulating(rez[i], 0);
//
//		return rez;
//}
//
//Bignumbers calcRes(vector <Komb> vrj)
//{
//	Bignumbers res;
//	Stek *stk = new Stek(vrj.size());
//
//	for (int i = 0; i < vrj.size(); i++)
//	{
//		if (vrj[i].info == 'A' || vrj[i].info == 'C' || vrj[i].info == 'P' || vrj[i].info == '^' || vrj[i].info == '!') stk->Push(vrj[i]);
//		if (vrj[i].info == '+' || vrj[i].info == '-' || vrj[i].info == '*' || vrj[i].info == '/')
//		{
//			if (vrj[i].info == '+')
//			{
//				Bignumbers b;
//				Komb a;
//				b.copy(stk->Top().value);
//				stk->Pop();
//				a = (stk->Top());
//				stk->Pop();
//				a.value.sum(b);
//				stk->Push(a);
//				continue;
//			}
//
//			if (vrj[i].info == '-')
//			{
//				Bignumbers b;
//				Komb a;
//				b.copy(stk->Top().value);
//				stk->Pop();
//				a = (stk->Top());
//				stk->Pop();
//				a.value.sub(b);
//				stk->Push(a);
//				continue;
//			}
//
//			if (vrj[i].info == '*')
//			{
//				Bignumbers b;
//				Komb a;
//				b.copy(stk->Top().value);
//				stk->Pop();
//				a = (stk->Top());
//				stk->Pop();
//				a.value.mlp(b);
//				stk->Push(a);
//				continue;
//			}
//
//			if (vrj[i].info == '/')
//			{
//				Bignumbers b;
//				Komb a;
//				b.copy(stk->Top().value);
//				stk->Pop();
//				a = (stk->Top());
//				stk->Pop();
//				a.value.div(b);
//				stk->Push(a);
//				continue;
//			}
//		}
//	}
//
//	Komb t = stk->Top();
//	t.value.copyUk(stk->Top().value);
//	res.copyUk(t.value);
//
//	return res;
//}