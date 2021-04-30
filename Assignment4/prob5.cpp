#include <iostream>
#include <string.h>

using namespace std;

class String {
	int len;
	char *s;
	int *pc;
public:
	String(const char* temp = "\0")
	{
		len = 0;
		while (temp[len] != '\0')
			++len;
		s = new char[len + 1];
		char* ss = new char[len + 1];
		strcpy(ss, temp);
		strcpy(s, ss);
		delete[] ss;
		pc = new int;
		*pc = 1;
	}
	String(String& a)
	{
		len = a.len;
		s = a.s;
		pc = a.pc;
		(*pc)++;
	}
	void operator=(const String& a)
	{
		if (s != NULL) {
			(*pc)--;
			if (*pc == 0) {
				delete pc;
				delete[] s;
			}
		}
		s = a.s;
		len = a.len;
		pc = a.pc;
		(*pc)++;
	}
	friend String operator+(String& a, String& b)
	{
		char* temp;
		temp = new char[a.len + b.len + 1];
		int i = 0;
		while (i < a.len) {
			temp[i] = a.s[i];
			++i;
		}
		int j = 0;
		while (j < b.len) {
			temp[i] = b.s[j];
			++i;
			++j;
		}
		temp[i] = '\0';
		String c(temp);
		delete[] temp;
		return c;
	}
	friend bool operator<(String& a, String& b)
	{
		if (strcmp(a.s, b.s) < 0)
			return true;
		return false;
	}
	friend bool operator>(String& a, String& b)
	{
		if (strcmp(a.s, b.s) > 0)
			return true;
		return false;
	}
	friend bool operator<=(String& a, String& b)
	{
		if (strcmp(a.s, b.s) <= 0)
			return true;
		return false;
	}
	friend bool operator>=(String& a, String& b)
	{
		if (strcmp(a.s, b.s) >= 0)
			return true;
		return false;
	}
	friend bool operator==(String& a, String& b)
	{
		if (strcmp(a.s, b.s) == 0)
			return true;
		return false;
	}
	friend ostream& operator<<(ostream& out, String& a)
	{
		out << a.s;
		return out;
	}
	~String()
	{
		(*pc)--;
		if (*pc == 0) {
			delete pc;
			delete[] s;
		}
	}
};

signed main() {

	char s1[] = "hello ", s2[] = "world";
	String a(s1);
	String b(s2);
	cout << a << b << "\n";
	String c;
	c = a + b;
	cout << c << "\n";
	String d = b;
	cout << d << "\n";
	if (d == b) {
		cout << "Equal\n";
	}

	String S1(s2);	// world
	String S3(s1);	// hello
	cout << S1;	// world
	String S2(S1);	// world
	cout << S2;	// worl
	S1 = S3;
	cout << S1;
	cout << S2;


	return 0;
}