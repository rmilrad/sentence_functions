/***********************************PROGRAM HEADER*****************************************************************************************************
Name: Ryan Milrad
TOTAL POINTS:  25
DUE DATE:  10/2/2020
COURSE:  COP 3530
Assignment Name:  Assignment#4
Professor:  Dr. Bullard

Description:  function declarations for the sentence header file
******************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
#include <string>
#include "sentence.h"
using namespace std;

//default constructor, called when sentence is initialized 
sentence::sentence() {
	//set pointer to first and last node equal to NULL
	front = back = 0;
	//set the number of nodes and length of the empty sentence to 0
	num_of_terms = len = 0;
}

//explicit value constructor, called-by-value, called when initialized and declared, takes in a constant string
sentence::sentence(const string& line) {
	//set initial sentence to empty
	front = back = 0;
	num_of_terms = 0;
	len = 0;
	//values for tracking words in string passed through
	int wordStart, wordEnd, search = 0;

	//loop through the string
	for (int i = 0; i < line.size(); i++) {
		//if first word, initialize wordStart to first character in string
		if (search == 0) {
			wordStart = 0;
			search = 1;
		}
		//if the character in the string is a space
		if (line[i] == ' ') {
			//if the word is not the first word and the character previous was not a space
			//i used this to differentiate between multiple spaces and meaningful words separated by one space
			if (i == 0 || line[i - 1] != ' ') {
				//set the end index for the word
				wordEnd = i;
				//create a new pointer
				word* temp = new word;
				//set the value of the term to the string we parsed
				temp->term = line.substr(wordStart, wordEnd - wordStart);
				//set the next value to nothing, ie put the word at the end of the sentence
				temp->next = NULL;
				//tally the length of the sentence for future ease
				len += temp->term.size();
				//if front is empty, set it to back
				if (front == NULL) {
					back = temp;
					front = back;
				}
				//if not empty, set the previous back pointer to new word and set back to new word
				else {
					back->next = temp;
					//set the back value to temp
					back = temp;
				}
				num_of_terms++;

				//add space, same flow as above, given it is a MEANINGFUL space
				word* space = new word;
				space->term = " ";
				space->next = NULL;
				len += space->term.size();
				back->next = space;
				back = space;
				num_of_terms++;
				wordStart = i + 1;
			}
			//if the character is an isolated space
			else {
				//add space, same flow as above
				word* temp = new word;
				temp->term = " ";
				temp->next = NULL;
				len += temp->term.size();
				if (front == NULL) {
					back = temp;
					front = back;
				}
				else {
					back->next = temp;
					back = temp;
				}
				num_of_terms++;
				wordStart = i;
			}
		}
		//if we are at the end of the sentence and it is not a space
		if (i == line.size() - 1 && line[i] != ' ') {
			//add word just as above
			wordEnd = i;
			word* temp = new word;
			temp->term = line.substr(wordStart, wordEnd - wordStart + 1);
			temp->next = NULL;
			len += temp->term.size();
			//cout << temp->term << endl;
			//if front is empty, set it to back
			if (front == NULL) {
				back = temp;
				front = back;
			}
			//if not empty, set the previous back pointer to new word and set back to new word
			else {
				back->next = temp;
				back = temp;
			}
			num_of_terms++;
		}
	}
}

//copy constructor, creates a new sentence identical to the sentence passed through as an argument
sentence::sentence(const sentence& lineS) {
	//creates an empty string
	front = back = 0;
	//number of terms in new sentence equals num of terms in copied sentence
	num_of_terms = lineS.num_of_terms;
	//length of new sentence equal to the length of the old sentence
	len = lineS.len;
	//create a new word
	word* p = new word;
	//set the new word term to the first word
	p->term = lineS.front->term;
	//set the pointer to next node equal to the pointer of the sentence passed second node
	p->next = lineS.front->next;
	//iterate through each word until no more terms
	for (int i = 0; i < num_of_terms; i++) {
		//create a new word
		word* temp = new word;
		//set the word to the current pointed word
		temp->term = p->term;
		//point the word to the next node, ie put to back of the new sentence
		temp->next = NULL;
		//if the sentence is empty, set back and front to same word
		if (front == NULL) {
			back = temp;
			front = back;
		}
		//if not the first word
		else {
			//point the previous last word to the new last word
			back->next = temp;
			//set the back pointer to the new last word
			back = temp;
		}
		//move the pointer to the next node of the copied sentence
		p = p->next;
	}
}

//deconstructor, deletes memory whenever a sentence goes out of scope
sentence::~sentence() {
	//create a new word
	word* temp = new word;
	//loop until the front points to nothing
	while (front != NULL) {
		//point temporary word to front word
		temp = front->next;
		//deletes word
		delete front;
		//set new front word to temporary word
		front = temp;
	}
}

//overload the << operator with chaining, takes in a sentence
ostream& operator<<(ostream& out, const sentence& lineS) {
	//create a word pointer
	word* p;
	//loop through each word in the sentence passed
	//starting at the first word, while the current word is pointed to an existing word, set the pointer to the next word
	for (p = lineS.front; p != 0; p = p->next) {
		//output the word
		out << p->term;
	}
	//return the stream
	return out;
}

//overload the = operator, takes in a constant string 
void sentence::operator=(const string& line) {
	//set up empty sentence
	front = back = 0;
	num_of_terms = 0;
	len = 0;
	//location trackers
	int wordStart, wordEnd, search = 0;
	//if the sentence is empty
	if (line.size() == 0) {
		//create a new word
		word* temp = new word;
		//while there still exists a word and front is pointed to it
		while (front != NULL) {
			//set temp word to the next word
			temp = front->next;
			//delete first word
			delete front;
			//repoint front word
			front = temp;
		}
		front = back = 0;
		return;
	}
	//iterate through each character
	for (int i = 0; i < line.size(); i++) {
		//if first word, initialize wordStart to first character in string
		if (search == 0) {
			wordStart = 0;
			search = 1;
		}
		//if the character is a space
		if (line[i] == ' ') {
			//if the word is the first word and the previous character isnt a space
			if (i == 0 || line[i - 1] != ' ') {
				wordEnd = i;
				//create new temporary word
				word* temp = new word;
				//set the term equal to the string word we parsed
				temp->term = line.substr(wordStart, wordEnd - wordStart);
				//point next to nothing, ie place at the back
				temp->next = NULL;
				len += temp->term.size();
				//if front is empty, set it to back
				if (front == NULL) {
					back = temp;
					front = back;
				}
				//if not empty, set the previous back pointer to new word and set back to new word
				else {
					back->next = temp;
					back = temp;
				}
				num_of_terms++;
				//add space, same flow as above
				word* space = new word;
				space->term = " ";
				space->next = NULL;
				len += space->term.size();
				back->next = space;
				back = space;
				num_of_terms++;
				wordStart = i + 1;
			}
			//if not the first word
			else {
				//add space, same flow as above
				word* temp = new word;
				temp->term = " ";
				temp->next = NULL;
				len += temp->term.size();
				if (front == NULL) {
					back = temp;
					front = back;
				}
				else {
					back->next = temp;
					back = temp;
				}
				num_of_terms++;
				wordStart = i;
			}
		}
		//if the character of the string is the last character and if it is not a space character
		if (i == line.size() - 1 && line[i] != ' ') {
			//same flow as above
			wordEnd = i;
			word* temp = new word;
			temp->term = line.substr(wordStart, wordEnd - wordStart + 1);
			temp->next = NULL;
			len += temp->term.size();
			//if front is empty, set it to back
			if (front == NULL) {
				back = temp;
				front = back;
			}
			//if not empty, set the previous back pointer to new word and set back to new word
			else {
				back->next = temp;
				back = temp;
			}
			num_of_terms++;
		}
	}
}

//overload + operator, takes in a sentence as argument, adds the sentence to the end of the current object
void sentence::operator+(const sentence& lineS) {
	//update length and number of terms to accomodate for the new sentence addition
	len += lineS.len;
	num_of_terms += lineS.num_of_terms;
	//create a new word
	word* p = new word;
	//set the word term to the first word of the sentence to be added
	p->term = lineS.front->term;
	//set the next word to the next word of the sentence to be added
	p->next = lineS.front->next;
	//loop through the sentence for each term it has
	for (int i = 0; i < lineS.num_of_terms; i++) {
		//same flow as above for a copy constructor, except adding sentence word by word
		word* temp = new word;
		temp->term = p->term;
		temp->next = NULL;
		if (front == NULL) {
			back = temp;
			front = back;
		}
		else {
			back->next = temp;
			back = temp;
		}
		p = p->next;
	}
}

//boolean function that checks if two sentences are equal, takes in a sentence as an argument
bool sentence::isEqual(const sentence& lineS) {
	//if the sentences dont share the same number of words or if the lengths of the two sentences are different
	if (num_of_terms != lineS.num_of_terms || len != lineS.len) {
		//sentences not equal
		return false;
	}
	//if both sentences are empty
	if (front == 0 && back == 0 && lineS.front == 0 && lineS.back == 0) {
		//sentences are equal
		return true;
	}
	//create a new word to compare sentence passed
	word* compare = new word;
	//set equal to the first word of sentence passed
	compare->term = lineS.front->term;
	//create a new word to compare current object
	word* current = new word;
	//set equal to the first word of the current object
	current->term = front->term;
	//loop through each word and check if equal
	for (int i = 0; i < num_of_terms; i++) {
		if (compare->term == current->term) {
			compare->next = lineS.front->next;
			current->next = front->next;
		}
		//if we find a term that doesnt match, we can say its not equal and quit
		else {
			return false;
		}
	}
	return true;
}

//remove function, takes in a string and we search the current object for an instance of that string
void sentence::remove(const string& line) {
	//if empty list
	if (front == NULL) {
		return;
	}
	//if first term is a match
	if (front->term == line) {
		//and there follows another node
		if (front->next != NULL) {
			//set front to next node
			len -= front->term.size();
			front = front->next;
			num_of_terms--;
			return;
		}
		//if front is the only node
		else {
			//remove front and set to NULL
			front = NULL;
			len = num_of_terms = 0;
			return;
		}
	}
	//if the current term is not a match and there are no other nodes
	else if (front->term != line && front->next == NULL) {
		//end
		return;
	}
	//prev = head;
	word* current = front;
	word* prev = NULL;

	//while the next to current node is not NULL and there is no match
	while (current->next != NULL && current->term != line) {
		//previous node is now current node and current node moves to next node
		prev = current;
		current = current->next;
	}

	//if the current node matches the key
	if (current->term == line) {
		//previous node skips current node and moves beyond current node
		len -= current->term.size();
		num_of_terms--;
		prev->next = prev->next->next;
		//free current node memory
		delete current;
	}
}
