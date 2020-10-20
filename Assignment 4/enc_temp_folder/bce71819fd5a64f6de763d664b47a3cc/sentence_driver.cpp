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
	sentence();
	sentence(const string &line);
	sentence(const sentence& lineS);
	~sentence();
	bool isEmpty() { return front == 0; };
	int length() {	return len;	};
	//void addBack(string& line);
	friend ostream& operator<<(ostream& out, const sentence& lineS);
	//void operator=(const string& line);
	//sentence& operator=(sentence& lineS);
	//void operator+(const string& line);
	//bool isEqual(const sentence& lineS);
	//void remove(const string& line);
private:
	word* front;
	word* back;
	int num_of_terms, len;
};

sentence::sentence() {
	front = back = 0;
	num_of_terms = len = 0;
}

sentence::sentence(const string& line) {
	front = back = 0;
	num_of_terms = 0;
	len = 0;
	int wordStart, wordEnd, search = 0;
	for (int i = 0; i < line.size(); i++) {		
		//if first word, initialize wordStart to first character in string
		if (search == 0) {
			wordStart = 0;
			search = 1;
		} 
		if (line[i] == ' ') {
			if (line[i-1] != ' ') {
				//add previous word
				wordEnd = i;
				word* temp = new word;
				temp->term = line.substr(wordStart, wordEnd - wordStart);
				temp->next = NULL;
				len += temp->term.size();
				cout << temp->term << endl;
				if (front == NULL) {
					back = temp;
				}
				else {
					while (back->next != NULL) {
						back = back->next;
					}
				}
				num_of_terms++;

				//add space
				word* space = new word;
				space->term = "_";
				space->next = NULL;
				len += space->term.size();
				cout << space->term << endl;
				if (front == NULL) {
					back = space;
				}
				else {
					while (back->next != NULL) {
						back = back->next;
					}
				}
				num_of_terms++;
				wordStart = i+1;
			}
			else {
				word* temp = new word;
				temp->term = "_";
				temp->next = NULL;
				len += temp->term.size();
				cout << temp->term << endl;
				if (front == NULL) {
					back = temp;
				}
				else {
					while (back->next != NULL) {
						back = back->next;
					}
				}
				num_of_terms++;
				wordStart = i;
			}
		}		
	}
}

sentence::sentence(const sentence& lineS) {
	num_of_terms = lineS.num_of_terms;
	len = lineS.len;
	//new sentence front word = lineS front word
	front = 0;
	back = 0;
	word* current = new word;
	current->term = lineS.front->term;
	current->next = back;
	front = current;
	for (int i = 0; i < num_of_terms-1; i++) {
		word* current = new word;
		current = lineS.front->next;
		current->term = lineS.front->term;
		current->next = back;
		front->next = current;		
	}
	word* final = new word;
	final->term = lineS.back->term;
	final->next = 0;
	back = final;
	/*
	//new currentWord as pointer to new sentence word position
	word* currentWord = new word;
	//currentWord pointer = new sentence next word
	currentWord->next = back;
	//new word temp stores pointers to copy sentence
	word* temp = new word;
	//temp current word points to the next term after first word in copy sentence
	temp->next = lineS.front->next;
	for (int i = 0; i < num_of_terms-2; i++) {
		//new sentence back term = temp term
		back->term = temp->term;
		//new back word creates a new word for new sentence back to point to
		word* emptyBack = new word;
		//emptyBack next value set to null
		emptyBack->next = 0;
		//new sentence back points to the null back
		back->next = emptyBack;
		//current word pointer points to the next 
		currentWord->next = currentWord->next->next;		
		//set temp to next word in copy sentence
		temp->next = temp->next->next;
	}
	//set last back value for new sentence
	back->term = lineS.back->term;
	back->next = lineS.back->next;
	*/
}

sentence::~sentence() {
	for (int i = 0; i < num_of_terms; i++) {
		delete[]front;
		delete[]back;
		num_of_terms = 0;
	}
}

ostream& operator<<(ostream& out, const sentence& lineS) {
	word* p;
	int i = 0;
	for (p = lineS.front; i < lineS.num_of_terms; i++, p = p->next) {
		out << p->term;
	}
	return out;
}

int main() {
	cout << "****Test#1: default constructor, length, and operator<<***\n\n";
	sentence you;
	cout << "\"" << you << "\"" <<" : length = "<< you.length() << endl;
	cout<<"\n****End of Test#1*******************************************\n";
	cout<<endl;

	cout << "****Test#2: explicit-value constructor, length, and operator<<***\n\n";
	sentence me("Today is a wonderful day!   ");//sentence with 3 spaces at end
	cout << "me is "<< "\"" << me << "\"" << " =  " << "\"" << "Today is a wonderful day!   " << "\"" << "\n";
	cout << "The length of me is " << me.length() << "\n\n";
	//sentence me_to("");
	//cout << "me_to is " << "\"" << me_to << "\"" << " = " << "\""<< "\""<<"\n"; //sentence should be empty string
	//cout << "The length of me_to is " << me_to.length() << "\n\n";
	//sentence you_to(" ");
	//cout << "you_to is " << "\"" << you_to << "\"" << " =  "<<"\"" <<" "<< "\"" << "\n";//sentence is one space
	//cout << "The length of you_to is " << you_to.length() << "\n\n";
	//cout << "****End of Test#2*******************************************\n";
	//cout << endl;

	//cout << "****Test#3: copy constructor, length, isEqual, and operator<<***\n\n";
	//sentence them = me;
	//cout<<"them is "<<"\""<<them<<"\""<<"\n";
	//cout << "The length of me is " << me.length()
	//     << " = The length of them is " << them.length()<<"\n";
	//cout <<"isEqual should equal 1 = "<< them.isEqual(me) << endl<<endl;
	//cout << "****End of Test#3*******************************************\n";
	//cout<<endl;

	//cout<<"****TEST#4: overloaded operator= with string, and operator<<*******************\n\n";
	//sentence us;
	//us = "There are five racoons in the palm tree.";
	//cout<<"Testing operator = by assigning the value of "<<
	//	"\""<<"There are five racoons in the palm tree."<<"\""<<"\n";
	//cout<<"The sentence us is "<< "\""<<us<<"\""<<endl<<endl;
	//cout<<"****End of Test#4*********************************************\n";
	//cout<<endl;

	//cout<<"****TEST#5: overloaded operator= with string, isEqual, and operator<<*********\n\n";
	//sentence her, him;

	//her = "I am very happy";
	//him = "They are very happy";
	//cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;
	//
	//her = "";
	//him = "";
	//cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	//her = " ";
	//him = " ";
	//cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	//her = "";
	//him = " ";
	//cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	//her = "        ";
	//him = "        ";
	//cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	//her = "       ";
	//him = "        ";
	//cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	//cout << "****End of Test#5*********************************************\n";
	//cout << endl;

	//cout<<"****TEST#6: operator= with a string, operator+ with a sentence, and operator<<*****\n\n";
	//cout<<"Adding 2 sentences by adding us to the back of their.  Their is the current object \n";
	//sentence their("Everything ");
	//us = "will be okay.";
	//cout << "us = " <<"\""<< us <<"\""<<" and length = "<<us.length()<< endl;
	//cout << "their = " <<"\""<< their <<"\""<<" and length = "<<their.length()<< endl;
	//their + us;
	//cout<<"their followed by us is "<< "\""<<their<< "\""<<" and length = " << their.length() << endl;

	//cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	//cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	//us + their;
	//cout << "us followed by their is " << "\"" << us << "\"" <<" and length = "<< us.length()<< endl;
	//cout<<"*************************************************\n";
	//cout<<endl<<endl;

	//us = "123 456";
	//their = "123";
	//cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	//cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	//us + their;
	//cout << "us followed by their is " << "\"" << us << "\"" << "and length = " << us.length() << endl;

	//us = "123 456";
	//their = "";
	//cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	//cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	//their + us;
	//cout << "their followed by us is " << "\"" << their << "\"" << "and length = " << their.length() << endl<<endl;
	//cout << "****End of Test#6*********************************************\n\n";

	//cout<<"****TEST#7: remove with a string without spaces, and operator<<*****\n\n";
	//them = "";
	//them.remove("123");
	//cout << "\"" << them << "\"" << " length of them = " << them.length() << endl;
	//them = "123";
	//them.remove("123");
	//cout <<"\""<< them<< "\"" << " length of them = "<<them.length()<<endl;
	//them = "123 abc 124 abc 123 4567";
	//them.remove("123");
	//cout << "\""<<them <<"\""<< " length of them = " << them.length() << endl;
	//them = "123 abc 124 abc 123 4567";
	//them.remove("4567");
	//cout <<"\""<< them <<"\"" " length of them = " << them.length() << endl;
	//them = "123 abc 124 abc 123 4567";
	//them.remove("124");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	//them.remove(" ");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	//them.remove(" ");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	//them.remove(" ");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	//them.remove(" ");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	//them.remove(" ");
	//cout << "\"" << them << "\"" " length of them = " << them.length() << endl<<endl;
	//cout << "****End of Test#7*********************************************\n";
	//cout << endl;
	//cout << "****TEST#8: operator= with a sentence object and operator<<*****\n\n";
	//sentence h("123 456 780");
	//them = h;
	//cout << "right object = " << h << endl;
	//cout << "them = "<<them << endl<<endl;
	//cout << "****End of TEST#8****************************************\n\n";
	//cout << "****End of Program*********************************************\n";

	return 0;
}