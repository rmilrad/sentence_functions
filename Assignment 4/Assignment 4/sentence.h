/***********************************PROGRAM HEADER*****************************************************************************************************
Name: Ryan Milrad
TOTAL POINTS:  25
DUE DATE:  10/2/2020
COURSE:  COP 3530
Assignment Name:  Assignment#4
Professor:  Dr. Bullard

Description:  header for the string class assignment
******************************************************************************************************************************************************/

#pragma once
#ifndef SENTENCE_H
#define SENTENCE_H
#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
#include <string>
using namespace std;

class word {
public:
	string term;
	word* next = 0;
};

class sentence {
public:
	sentence(); //default constructor
	sentence(const string& line); //explicit value constructor
	sentence(const sentence& lineS); //copy constructor
	~sentence(); //deconstructor
	bool isEmpty() { return front == 0; }; //checks if sentence is empty
	int length() { return len; }; //returns length of sentence
	friend ostream& operator<<(ostream& out, const sentence& lineS); //overload << operator as friend
	void operator=(const string& line); //overload = operator
	void operator+(const sentence& lineS); //overload + operator
	bool isEqual(const sentence& lineS); //checks if two sentences are equal
	void remove(const string& line); //remove a word from a sentence
private:
	word* front; //pointer to first node in sentence
	word* back; //pointer to last node in sentence
	int num_of_terms, len; //integer values for the number of nodes and length of the sentence
};

#endif SENTENCE_H