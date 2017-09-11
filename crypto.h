#pragma once // Makes it so this header file can only be included in compilation once
// It may seem like bad practice, but it's nice to be able to include the same header file from any
// cpp files that need it
#include "stdafx.h" // Visual Studio stuff
#include <iostream> // iostream
#include <Windows.h> // Windows.h
#include <string.h> // Strings (std::string)

// Definitions are neat, you use them to declare keyword constant things, in this case PI
#define PI 3.14159265359f // The "f" just makes sure it's a float
// Note that there isn't a semicolon at the end of a #definition


// Make your own namespaces - using them is the same as using std:: (so here it would be math::)

// Also worth noting that it's appearently a better programming habit not to use "using namespace x;"
// so we instead reference libraries like std:: the long way - you can look it up more but I agree,
// you'll have more freedom naming functions since you don't have to worry about which ones already
// exist for one thing

namespace math {
	// The three slashes with the <summary> tags is a visual studio thing that shows up as an
	// autocomplete tooltip. When writing out a function name, it shows the <summary> as a message. Try it.

	///<summary>Used to get the number of digits/characters in an integer n.</summary>
	int places(int n) {
		int p = max(floor(log10(abs(n))) + 1,1);
		return p;
	}

	///<summary>Returns each individual digit of an integer n as an array pointer.</summary>
	int* clip(int n) {
		const int maxdigits = 10;
		int p = places(n);
		int digits[maxdigits];
		for (int i = 0; i < maxdigits; i++) {
			digits[i] = -1;
		}
		for (int i = 0; i < p; i++) {
			digits[p-i-1] = n % maxdigits;
			n = floor(n / maxdigits);
		}

		return digits;
	}

	///<summary>Gives the nth digit index in an integer n.</summary>
	int clip(int n,int index) { // Two of the same functions? How? All you have to do is change the arguments between them.
		// Example in ConsoleApplication4.cpp.
		int* digits = clip(n);
		return digits[index];
	}

	///<summary>Adds n to val, looping it between min and max.</summary>
	int shift(int val,int min,int max,int n) {
		val += n;
		int diff = max - min;

		if (min > max) {
			int oldmin = min;
			min = max;
			max = oldmin;
		}
		if (min == max)
			return min;

		while (val < min)
			val += abs(diff);
		while (val > max)
			val -= abs(diff);
		return val;
	}

	///<summary>Adds n to val, looping it between 0 and max.</summary>
	int shift(int val,int max,int shift) {
		return math::shift(val,0,max,shift);
	}

	///<summary>Rounds off an integer n to tol points of precision. (eg 2,953 to 2,900)</summary>
	int deadzone(int n,int tol) {
		if (tol == 0)
			return n;
		return round(n / log10(tol)) * log10(tol);
	}

	///<summary>Rounds off a float n to tol points of precision. Good for getting rid of -1.1526052e07.</summary>
	float deadzone(float n,int tol) {
		if (tol == 0)
			return n;
		int t = log10(tol);
		return round(n * t) / t;
	}

	///<summary>Returns true if value n is at least min and under max.</summary>
	bool inrange(float n,float min,float max) {
		return n < max && n >= min;
	}

	///<summary>Returns true if value n is at least min and at most max.</summary>
	bool inrange(int n,int min,int max) {
		return n <= max && n >= min;
	}
}

namespace basics {
	// This is a class. It's an object. Objects hold information (variables) and can do things (functions.)
	// Usually their functions only matter to the classes themselves. 

	template <class T> // This line basically says that this class can be of any variable type
	// (we don't want to copy and paste this entire thing just to be able to use more than one variable type.)
	class list {
	public:
		list(T v) {
			add(v);
		}
		list() { }

		// I'll go through each line in this, but I can't guaruntee it'll make sense.
		///<summary>Automagically adds a new int value to the list.</summary>
		void add(T i) { // Function declaration
			listitem* item = new listitem; // [see struct under "private:" declarations]
			item->val = i; // Notice the arrow thing. This is what's used to get parts from a pointer.
			// (Read into pointers, they're pretty important)
			if (first == NULL) {
				first = item;
			} else {
				prev->next = item;
			}
			prev = item;
			count++;
		}

		///<summary>Returns the nth index's value from the list.</summary>
		int get(T index) {
			int i = 0;
			listitem* item = first;
			while (i < count && item != NULL) {
				if (i == index) {
					return item->val;
				} else {
					item = item->next;
					i++;
				}
			}
			return NULL;
		}

		///<summary>Returns the number of values.</summary>
		int get_count() {
			return count;
		}
	private:
		struct listitem {
			T val = NULL;
			listitem* next;
		};

		int count = 0;
		listitem* prev;
		listitem* first;
	};
}

namespace str {
	///<summary>Gets the length of string s.</summary>
	int len(std::string s) {
		int i = 0;
		while (s[i])
			i++;
		return i;
	}

	///<summary>Converts an integer n into a string.</summary>
	std::string tostring(int n) {
		int p = math::places(n);
		std::string f = "";
		for (int i = 0; i < p; i++) {
			int digit = math::clip(n,i);
			f += digit + 48;
		}

		return f;
	}

	///<summary>Converts a string s into... a string.</summary>
	std::string tostring(std::string s) {
		return s;
	}

	///<summary>Converts a character c into a string.</summary>
	std::string tostring(char c) {
		return "" + c;
	}
	

	// https://en.wikipedia.org/wiki/ROT13
	char rotn(char c,int n) {
		if (math::inrange((int)c,65,90))
			return (char)math::shift(c,65,90,n);
		else if (math::inrange((int)c,97,122))
			return (char)math::shift(c,97,122,n);
		else return c;
	}

	std::string rotn(std::string s,int n) {
		for (int i = 0; i < str::len(s); i++) {
			s[i] = rotn(s[i],n);
		}
		return s;
	}

	char rot13(char c) {
		return rotn(c,13);
	}

	std::string rot13(std::string s) {
		return rotn(s,13);
	}

	// Uses our fancy custom list function to separate a string into lots
	// Take for example some kind of data string: userdata = "Kyle Lamothe;kyle@alscenic.com;Google Chrome;Windows 10";
	// Splitting that with the divider ";" will give you a list<std::string> that contains each entry.
	// You can split each of the strings with a data string like this: playerdata = "name:Alscenic;coins:172;health:46";
	// Split it with ";" then taking the outputted list, split each entry with ":"
	///<summary>Returns a list of each part of a string divided by string d.</summary>
	basics::list<std::string> split(std::string s,std::string d) {
		return NULL; // slightly unfinished and forgotten about
		/* Initialize last-minute pseudocode:

		list<int> indices;
		for (times d appears in s) {
			add index (position) of occurance to indices
		}

		list<string> pieces;
		for (length of indices) {
			add the characters between one index and another to pieces
		}

		return pieces;

		*/
		// If you don't know what this means that's okay, it's not important
	}

	///<summary>Returns a list of each part of a string divided by char d.</summary>
	basics::list<std::string> split(std::string s,char d) {
		return split(s,str::tostring(d)); // In case someone uses ';' instead of ";"
	}

	///<summary>Returns true if string haystack contains string needle. Takes inputs literally. Does not accept wildcards.</summary>
	bool containslit(std::string haystack,std::string needle) {
		int hlen = str::len(haystack);
		int nlen = str::len(needle);
		if (nlen > hlen)
			return false;

		for (int h = 0; h < hlen; h++) {
			if (haystack[h] == needle[0]) {
				for (int n = 1; n < nlen; n++) {
					if (h + n > hlen)
						return false;
					/*if (n < nlen - 1)
						if (needle[n] == '\\' && needle[n + 1] == '*')
							n++;*/
					if (haystack[h + n] == needle[n]) {
						if (n == nlen - 1)
							return true;
					} else {
						break;
					}
				}
			}
		}

		return false;
	}

	///<summary>Returns true if string haystack contains string needle. Accepts *wildcards. Asterisks may be taken literally with \*.</summary>
	bool contains(std::string haystack,std::string needle) {
		basics::list<std::string> l();
		return NULL;
	}

	///<summary>Is char c a letter?</summary>
	bool isletter(char c) {
		return math::inrange(c,65,90) || math::inrange(c,97,122);
	}

	///<summary>Converts a character to lowercase.</summary>
	char tolower(char c) {
		if (math::inrange(c,65,90))
			c += 32;
		return c;
	}

	///<summary>Converts a character to uppercase.</summary>
	char toupper(char c) {
		if (math::inrange(c,97,122))
			c -= 32;
		return c;
	}

	///<summary>Toggles a character's case.</summary>
	char togglecase(char c) {
		if (math::inrange(c,97,122))
			c -= 32;
		else if (math::inrange(c,65,90))
			c += 32;
		return c;
	}

	///<summary>Converts an entire string to lowercase.</summary>
	std::string tolower(std::string s) {
		int len = str::len(s);
		for (int i = 0; i < len; i++) {
			s[i] = str::tolower(s[i]);
		}
		return s;
	}

	///<summary>Converts an entire string to uppercase.</summary>
	std::string toupper(std::string s) {
		int len = str::len(s);
		for (int i = 0; i < len; i++) {
			s[i] = str::toupper(s[i]);
		}
		return s;
	}

	///<summary>Toggles a string's case.</summary>
	std::string togglecase(std::string s) {
		int len = str::len(s);
		for (int i = 0; i < len; i++) {
			s[i] = str::togglecase(s[i]);
		}
		return s;
	}

	///<summary>Converts an entire string to Word Case.</summary>
	std::string wordcase(std::string s) {
		int len = str::len(s);
		for (int i = 0; i < len; i++) {
			if (i > 0) {
				//std::string chars = " .,`~|/\\<>()[]{}!?@#$%^&*-_+=0123456789\"\'";
				//str::containslit(chars,str::tostring(s[i]))
				if (!str::isletter(s[i - 1])) {
					s[i] = str::toupper(s[i]);
				} else {
					s[i] = str::tolower(s[i]);
				}
			} else {
				s[i] = str::toupper(s[i]);
			}
		}
		return s;
	}
}

namespace crypt {
	float seed = 57;
	float randomness = 100000;
	float size = 127;

	///<summary>Inscure Hash Algorithm 1 - 'encrypts' data based on rules I made up.</summary>
	unsigned char iha1(float val,float offset) {
		return (sin((val * crypt::randomness) + (crypt::seed * val) + offset) + 1) * 0.5f * 255;
	}

	///<summary>Inscure Hash Algorithm 1 - 'encrypts' data based on rules I made up.</summary>
	unsigned char iha1(float val) {
		return crypt::iha1(val,0.0f);
	}

	///<summary>Inscure Hash Algorithm 1 - 'encrypts' data based on rules I made up.</summary>
	unsigned char iha1(int val) {
		return crypt::iha1((float)val);
	}

	///<summary>Inscure Hash Algorithm 1 - 'encrypts' data based on rules I made up.</summary>
	unsigned char iha1(char val) {
		return crypt::iha1((float)val);
	}

	std::string iha1(std::string s) {
		if (s == "")
			return "ZERO LENGTH STRING";
		std::string n = "";
		float total = str::len(s);
		for (int i = 0; i < str::len(s); i++) {
			total += (s[i] * i) / str::len(s);
		}
		for (int i = 0; i < str::len(s); i++) {
			n += iha1(s[i],total + str::len(s) + i);
		}
		return n;
	}
}

///<summary>Holds and does operations with a point in 2D space.</summary>
template <class T>
class vector2 {
public:
	T x = 0;
	T y = 0;

	vector2(T _x,T _y) {
		x = _x;
		y = _y;
	}

	vector2() { }

	///<summary>Gets the angle of the point from (0,0).</summary>
	float angle() {
		return math::deadzone((-(atan2(y,x) * midang) / PI) + midang,deadzone);
	}

	///<summary>Returns the normalized vector2.</summary>
	vector2 normalize() {
		vector2 v;
		float len = 1.0f;
		v.x = (-sin((angle() / midang) * PI + (PI / 2))) * len;
		v.y = sin((angle() / midang) * PI) * len;

		return v;
	}
private:
	const float maxang = 360;
	const float midang = 180;
	const int deadzone = 6;
};

class vector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	vector3() {

	}
};

// These functions make it so you can perform arithmetic on vector2s (pretty cool imo)
vector2<float> operator +(vector2<float> &lhs,vector2<float> &rhs) {
	vector2<float> result = lhs;
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

vector2<float> operator -(vector2<float> &lhs,vector2<float> &rhs) {
	vector2<float> result = lhs;
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

vector2<float> operator *(vector2<float> &lhs,vector2<float> &rhs) {
	vector2<float> result = lhs;
	result.x *= rhs.x;
	result.y *= rhs.y;
	return result;
}

vector2<float> operator /(vector2<float> &lhs,vector2<float> &rhs) {
	// Quick note: division is slow, you should always try to multiply (i.e. x * 0.5f) vs (x / 2)
	vector2<float> result = lhs;
	result.x /= rhs.x;
	result.y /= rhs.y;
	return result;
}

// Make it so you can use numbers too (adding and subtracting are pretty pointless, so I didn't include them)
vector2<float> operator *(vector2<float> &lhs,float &rhs) { // vector2 * float
	vector2<float> result = lhs;
	result.x *= rhs;
	result.y *= rhs;
	return result;
}

vector2<float> operator /(vector2<float> &lhs,float &rhs) { // vector2 / float
	vector2<float> result = lhs;
	result.x /= rhs;
	result.y /= rhs;
	return result;
}

vector2<float> operator *(vector2<float> &lhs,int &rhs) { // vector2 * int
	vector2<float> result = lhs;
	result.x *= rhs;
	result.y *= rhs;
	return result;
}

vector2<float> operator /(vector2<float> &lhs,int &rhs) { // vector2 / int
	vector2<float> result = lhs;
	result.x /= rhs;
	result.y /= rhs;
	return result;
}

vector2<float> operator *(vector2<float> &lhs,double &rhs) { // vector2 * double
	vector2<float> result = lhs;
	result.x *= rhs;
	result.y *= rhs;
	return result;
}

vector2<float> operator /(vector2<float> &lhs,double &rhs) { // vector2 / double
	vector2<float> result = lhs;
	result.x /= rhs;
	result.y /= rhs;
	return result;
}