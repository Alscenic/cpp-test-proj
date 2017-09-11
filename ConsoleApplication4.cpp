#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include "crypto.h"
// I figured out when to use quotes for these inclusions. You use "quotes" when you're calling
// a header file (declarations for functions and variables) from the current project and
// <angle brackets> when you're calling a system file (eg string, iostream)

// Multiple functions with the same name example
// This can be useful for:
//  - Multiple variable types
//     - One for floats, one for ints, etc
//  - Default values
//     - You have a function to spawn an enemy. Its arguments are the enemy's name, health, and attack damage.
//     - You make a function that accepts all of those: enemy_spawn("Bad guy", 100, 4)
//     - Now you make another function that runs the first one with a default: enemy_spawn("Bad guy",4)

void enemy_spawn(std::string name,float health, float damage) {
	// Spawns the enemy.
}

void enemy_spawn(std::string name,float damage) { // 
	enemy_spawn(name,100.0f,damage); // Takes this function's input, but supplements a certain value to make it easier in some situations.
	// Say normal enemies start at 100 health, so you would only user the first function for bosses. Instead of typing 100.0f for all of them,
	// just use this function. Plus if you want to change it later, you don't have to go through 20 different enemies to change 100.0f to whatever.
}


// ---------
// These functions are essentially just different versions of "main()" - I change out the function that the real main() runs so I can run a different test.

// Cryptography prototype test test
void main_crypt_iha1() {
	std::string s = "";
	std::cout << "String to 'encrypt': ";
	std::cin >> s;
	std::cout << "'Encrypted' string:  " << crypt::iha1(s) << std::endl;
}

// Testing random string operations
void main_stringtest1() {
	std::string s = "This is the ORIGINAL string. 22Numbers&other.CHARacters:n'stuff";
	std::cout << s;
	std::cout << std::endl << std::endl;
	std::cout << "Uppercase: " << std::endl << str::toupper(s);
	std::cout << std::endl << std::endl;
	std::cout << "Lowercase: " << std::endl << str::tolower(s);
	std::cout << std::endl << std::endl;
	std::cout << "Togglecase: " << std::endl << str::togglecase(s);
	std::cout << std::endl << std::endl;
	std::cout << "Word case: " << std::endl << str::wordcase(s);
	std::cout << std::endl << std::endl;
}

// Testing a basic search function
void main_strcontains() {
	std::string haystack = "This is a haystack. It's not that large, but it's there."; // Make the haystack (what we're searching in)
	std::string needle = "it's not that large"; // Make the needle (what we're searching for)
	std::cout << "Haystack: " << std::endl << haystack; // What the haystack is
	std::cout << std::endl << std::endl;
	std::cout << "Needle: " << std::endl << needle; // What the needle is
	std::cout << std::endl << std::endl;
	std::cout << "containslit: ";
	if (str::containslit(haystack,needle)) // Does haystack literally contain needle?
		std::cout << "true"; // yep
	else
		std::cout << "false"; // nope
}

void main_rot() {
	std::string s = "";
	std::cout << "Rotn:" << std::endl;
	std::cin >> s;
	int n = 0;
	std::cout << "n:" << std::endl;
	std::cin >> n;
	std::cout << str::rotn(s,n);
}

void main_speedtest1() {
	int times = 500000000;
	clock_t time = clock();
	std::cout << "Starting if/else test..." << std::endl;
	for (int i = 0; i < times; i++) {
		if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else if (1 == 2) {
			std::cout << "???";
		} else {
			i = i;
		}
	}
	std::cout << "If/else test took " << clock() - time << " ticks. Starting switch test..." << std::endl;
	time = clock();
	for (int i = 0; i < times; i++) {
		switch (1) {
			case 2:
				std::cout << "???";
				break;
			case 3:
				std::cout << "???";
				break;
			case 4:
				std::cout << "???";
				break;
			case 5:
				std::cout << "???";
				break;
			case 6:
				std::cout << "???";
				break;
			case 7:
				std::cout << "???";
				break;
			case 8:
				std::cout << "???";
				break;
			default:
				i = i;
				break;
		}
	}
	std::cout << "Switch test took " << clock() - time << " ticks." << std::endl;
}

void main_main() {
	// Initialize list
	basics::list<int> l;

	// Add stuff
	l.add(42);
	l.add(533);
	l.add(2);
	l.add(99991);

	// Use the stuff
	std::cout << "The list has " << l.get_count() << " items." << std::endl;
	std::cout << "Item 0: " << l.get(0) << std::endl;
	std::cout << "Item 1: " << l.get(1) << std::endl;
	std::cout << "Item 2: " << l.get(2) << std::endl;
	std::cout << "Item 3: " << l.get(3) << std::endl;
	std::cout << std::endl;
	std::cout << "Looping:" << std::endl;

	// Use the stuff... recursively!
	// That tostring() function sure came in handy
	for (int i = 0; i < l.get_count(); i++)
		std::cout << "Item " + str::tostring(i) + ": " + str::tostring(l.get(i)) << std::endl;
	std::cout << std::endl;

	vector2<float> v1 = vector2<float>(10.0f,5.0f);
	std::cout << "v1 x: " << v1.x << "; v1 y: " << v1.y << std::endl;
	std::cout << "angle: " << v1.angle() << std::endl;
	std::cout << "normalized x: " << v1.normalize().x << std::endl;
	std::cout << "normalized y: " << v1.normalize().y << std::endl;
	std::cout << std::endl;

	vector2<float> v2 = vector2<float>(-15.0f,3.0f);
	std::cout << "v2 x: " << v2.x << "; v2 y: " << v2.y << std::endl;
	std::cout << "angle: " << v2.angle() << std::endl;
	std::cout << "normalized x: " << v2.normalize().x << std::endl;
	std::cout << "normalized y: " << v2.normalize().y << std::endl;
	std::cout << std::endl;

	vector2<float> v3 = v1 + v2;
	std::cout << "v1+v2 x: " << v3.x << "; v1+v2 y: " << v3.y << std::endl;
	std::cout << "angle: " << v3.angle() << std::endl;
	std::cout << "normalized x: " << v3.normalize().x << std::endl;
	std::cout << "normalized y: " << v3.normalize().y << std::endl;
	std::cout << std::endl;
}

int main() {
	main_crypt_iha1();
	std::cout << std::endl << std::endl;
	main();
	return 0;
}