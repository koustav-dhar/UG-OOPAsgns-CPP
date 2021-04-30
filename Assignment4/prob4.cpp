#include <iostream>
#include <string.h>

using namespace std;

class String {
	int len;
	char *s;
public:
	String(const char* temp = "")
	{
		len = 0;
		while (temp[len] != '\0')
			++len;
		s = new char[len + 1];
		strcpy(s, temp);
	}
	String(String& a)
	{
		len = a.len;
		s = new char[len + 1];
		strcpy(s, a.s);
	}
	void operator=(const String& a)
	{
		delete[] s;
		len = a.len;
		s = new char[len + 1];
		strcpy(s, a.s);
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
		delete[] s;
	}
};

signed main() {

	char s1[] = "hello ", s2[] = "world";
	String a(s1);
	String b(s2);
	String c;
	c = a + b;
	cout << c << "\n";
	String d = b;
	if (d == b) {
		cout << "Equal\n";
	}

	return 0;
}