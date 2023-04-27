#include <iostream>
#include "Marquee.h"
#include <string>
using namespace std;

/*
 * CHANGELOG:
 * 2023.03.02 Alexi Brooks - Created
 * 2023.03.07 Alexi Brooks - Fixed test function calls
*/

bool test1() {
	try {
		Marquee m{};
		if (m.getSize() != 0) {
			cout << "TEST 1 FAIL: newly constructed Marquee does not have size 0." << endl;
			return false;
		}
		return true;
	} catch(...) {
		cout << "TEST 1 FAIL: unable to construct a Marquee." << endl;
		return false;
	}
}

bool test2() {
	try {
		Marquee m{};
		string s = "one";
		m.playNext(s);
		if (m.getSize() != 1) {
			cout << "TEST 2 FAIL: 1-item Marquee does not have size 1." << endl;
			return false;
		}
		if (s == m.rotate() && s == m.rotate()) {
			return true;
		}
	}
	catch (...) {
		cout << "TEST 2 FAIL: Rotating a 1-item marquee twice crashed." << endl;
		return false;
	}
	cout << "TEST 2 FAIL: Rotating a 1-item marquee twice did not produce"
		<< " the same string twice." << endl;
	return false;
}

bool test3() {
	try {
		Marquee m{};
		string s1 = "first";
		string s2 = "second";
		string s3 = "third";
		m.playNext(s1);
		m.playNext(s2);
		m.playNext(s3);
		if (m.getSize() != 3) {
			cout << "TEST 3 FAIL: 3-item Marquee does not have size 3." << endl;
			return false;
		}
		if (m.rotate() == s3 && m.rotate() == s2 && m.rotate() == s1 &&
			m.rotate() == s3) {
			return true;
		}
	}
	catch (...) {
		cout << "TEST 3 FAIL: Rotating a 3-item marquee 4x crashed." << endl;
		return false;
	}
	cout << "TEST 3 FAIL: Rotating a 3-item marquee 4x did not produce"
		<< " the correct items." << endl;
	return false;
}

bool test4() {
	try {
		Marquee m{};
		string s1 = "first";
		string s2 = "second";
		string s3 = "third";
		m.playNext(s1);
		m.playNext(s2);
		m.playNext(s3);
		string out3 = m.decomission();
		string out2 = m.decomission();
		string out1 = m.decomission();
		if (m.getSize() != 0) {
			cout << "TEST 4 FAIL: 0-item Marquee does not have size 0." << endl;
			return false;
		}
		if (out3 == s3 && out2 == s2 && out1 == s1) {
			return true;
		}
	}
	catch (...) {
		cout << "TEST 4 FAIL: Decomissioning 3 items from a 3-item marquee 4x crashed." << endl;
		return false;
	}
	cout << "TEST 4 FAIL: Decomissioning 3 items from a 3-item marquee 4x did not produce"
		<< " the correct items." << endl;
	return false;
}

//NOTE: In the event of a non-zero exit code with no output... check your destructor!
// Read access violations (common error involving nullptr) do not respect catch() blocks
// and just crash anyway.
int main() { 
	cout << "Running tests of the Marquee class..." << endl;
	if (test1() && test2() && test3() && test4()) {
		cout << "All tests passed!" << endl;
	}
}