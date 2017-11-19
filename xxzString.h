#ifndef XXZ_STRING
#include<iostream>
#define XXZ_STRING
#define isSpace(x) ((x)=='\n'||(x)==' '||(x)=='\t')
class xxzString{

private :
	char* __str;
	int size;
	int length;
	void expand(){
		size <<= 2;
		auto tmp = new char[size];
		memcpy(tmp, __str, size >> 2);
		delete[] __str;
		__str = tmp;
	}
public :
	xxzString() :__str(new char[16]), size(16), length(0){}

	xxzString(const xxzString& other){
		__str = new char[other.size];
		memcpy(__str, other.__str, other.size);
	}

	xxzString& operator=(xxzString& other){
		delete[] __str;
		size = other.size;
		length = other.length;
		__str = new char[other.size];
		memcpy(__str, other.__str, other.size);
		return *this;
	}

	xxzString& operator=(const char* other){
		delete[] __str;
		__str = new char[16];
		size = 16;
		int i = length = 0;
		while (other[i] != 0){
			__str[length++] = other[i++];
			if (length >= size - 2){
				expand();
			}
			__str[length] = 0;
		}
		return *this;
	}


	int operator==(const xxzString& other)const{
		return strcmp(__str, other.__str);
	}

	int operator==(const char* c)const{
		return strcmp(__str, c);
	}

	char* getStr(){
		return __str;
	}

friend std::istream& operator>>(std::istream& cin, xxzString& xxz);
friend std::ostream& operator<<(std::ostream& cout, xxzString& xxz);

};

std::ostream& operator<<(std::ostream& cout, xxzString& xxz){
	return cout << xxz.__str;
}




std::istream& operator>>(std::istream& cin, xxzString& xxz){
	char c;
	while (isSpace(cin.peek())){
		cin >> c;
	}
	do{
		cin >> c;
		if (xxz.size <= xxz.length - 2) 
			xxz.expand();
		xxz.__str[xxz.length++] = c;
	} while (!isSpace(cin.peek()));
	xxz.__str[xxz.length] = 0;
	return cin;
}



#endif
