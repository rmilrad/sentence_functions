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
	void operator=(const string& line);
	//sentence& operator=(sentence& lineS);
	void operator+(const sentence& lineS);
	bool isEqual(const sentence& lineS);
	void remove(const string& line);
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
			if (i==0 || line[i-1] != ' ') {
				//add previous word
				wordEnd = i;
				word* temp = new word;
				temp->term = line.substr(wordStart, wordEnd - wordStart);
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

				//add space, same flow as above
				word* space = new word;
				space->term = " ";
				space->next = NULL;
				len += space->term.size();
					//cout << space->term << endl;
				back->next = space;
				back = space;

				num_of_terms++;
				wordStart = i+1;
			}
			else {
				//add space, same flow as above
				word* temp = new word;
				temp->term = " ";
				temp->next = NULL;
				len += temp->term.size();
					//cout << temp->term << endl;
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
		if (i == line.size() - 1 && line[i] != ' ') {
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

sentence::sentence(const sentence& lineS) {
	front = back = 0;
	num_of_terms = lineS.num_of_terms;
	len = lineS.len;
	word* p = new word;
	p->term = lineS.front->term;
	p->next = lineS.front->next;
	for (int i = 0; i < num_of_terms; i++) {
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

sentence::~sentence() {
	word* temp = new word;
	while (front != NULL) {		
		temp = front->next;
		delete front;
		front = temp;
	}
}

ostream& operator<<(ostream& out, const sentence& lineS) {
	//create a word pointer
	word* p;
	int i = 0;
	if (lineS.len == 0) {
		return out;
	}
	//print out the current word term while there exists a term. set word pointer to next word and increase i counter with each iteration
	for (p = lineS.front; i < lineS.num_of_terms; i++, p = p->next) {
		out << p->term;
	}
	return out;
}

void sentence::operator=(const string& line) {
	front = back = 0;
	num_of_terms = 0;
	len = 0;
	int wordStart, wordEnd, search = 0;
	if (line.size() == 0) {
		word* temp = new word;
		while (front != NULL) {
			temp = front->next;
			delete front;
			front = temp;
		}
		front = back = 0;
		return;
	}
	for (int i = 0; i < line.size(); i++) {
		//if first word, initialize wordStart to first character in string
		if (search == 0) {
			wordStart = 0;
			search = 1;
		}
		if (line[i] == ' ') {
			if (i == 0 || line[i - 1] != ' ') {
				//add previous word
				wordEnd = i;
				word* temp = new word;
				temp->term = line.substr(wordStart, wordEnd - wordStart);
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

				//add space, same flow as above
				word* space = new word;
				space->term = " ";
				space->next = NULL;
				len += space->term.size();
				//cout << space->term << endl;
				back->next = space;
				back = space;

				num_of_terms++;
				wordStart = i + 1;
			}
			else {
				//add space, same flow as above
				word* temp = new word;
				temp->term = " ";
				temp->next = NULL;
				len += temp->term.size();
				//cout << temp->term << endl;
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
		if (i == line.size() - 1 && line[i] != ' ') {
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

void sentence::operator+(const sentence& lineS) {
	if (len == 0) {
		front = lineS.front;
		front->next = lineS.front->next;
		back = lineS.back;
		back->next = NULL;
	}	
	num_of_terms += lineS.num_of_terms;
	len += lineS.len;
	back->next = lineS.front;
	back = lineS.back;
	return;
}

bool sentence::isEqual(const sentence& lineS) {
	if (num_of_terms != lineS.num_of_terms || len != lineS.len) {
		return false;
	}
	if (front == 0 && back == 0 && lineS.front == 0 && lineS.back == 0) {
		return true;
	}
	word* compare = new word;
	compare->term = lineS.front->term;
	word* current = new word;
	current->term = front->term;
	for (int i = 0; i < num_of_terms; i++) {
		if (compare->term == current->term) {
			compare->next = lineS.front->next;
			current->next = front->next;
		}
		else {
			return false;
		}
	}
	return true;
}

void sentence::remove(const string& line) {
	if (line.size() > len) {
		return;
	}
	word* p;
	word* pPrev;
	word* temp;
	int i = 0;
	pPrev = front;
	for (p = front; i < num_of_terms; i++, p = p->next) {
		if (i==0 && p->term==line) {
			if (front->next == back) {
				front = back;
				delete front;
				len = num_of_terms = 0;
			}
			else {
				len -= p->term.size();
				p = front->next;
				delete front;
				front = p;
				num_of_terms--;
			}			
		}
		if (p->term == line) {
			len -= p->term.size();
			temp = p->next;
			delete p;
			p = temp;
			pPrev->next = p;
			pPrev = pPrev->next;
			num_of_terms--;
		}
	}
	return;
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
	sentence me_to("");
	cout << "me_to is " << "\"" << me_to << "\"" << " = " << "\""<< "\""<<"\n"; //sentence should be empty string
	cout << "The length of me_to is " << me_to.length() << "\n\n";
	sentence you_to(" ");
	cout << "you_to is " << "\"" << you_to << "\"" << " =  "<<"\"" <<" "<< "\"" << "\n";//sentence is one space
	cout << "The length of you_to is " << you_to.length() << "\n\n";
	cout << "****End of Test#2*******************************************\n";
	cout << endl;

	cout << "****Test#3: copy constructor, length, isEqual, and operator<<***\n\n";
	sentence them = me;
	cout<<"them is "<<"\""<<them<<"\""<<"\n";
	cout << "The length of me is " << me.length() << " = The length of them is " << them.length()<<"\n";
	cout <<"isEqual should equal 1 = "<< them.isEqual(me) << endl<<endl;
	cout << "****End of Test#3*******************************************\n";
	cout<<endl;

	cout<<"****TEST#4: overloaded operator= with string, and operator<<*******************\n\n";
	sentence us;
	us = "There are five racoons in the palm tree.";
	cout<< "Testing operator = by assigning the value of " << "\"" << "There are five racoons in the palm tree."<<"\""<<"\n";
	cout<<"The sentence us is "<< "\""<<us<<"\""<<endl<<endl;
	cout<<"****End of Test#4*********************************************\n";
	cout<<endl;

	cout<<"****TEST#5: overloaded operator= with string, isEqual, and operator<<*********\n\n";
	sentence her, him;

	her = "I am very happy";
	him = "They are very happy";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;
	
	her = "";
	him = "";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = " ";
	him = " ";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = "";
	him = " ";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	her = "        ";
	him = "        ";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = "       ";
	him = "        ";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	cout << "****End of Test#5*********************************************\n";
	cout << endl;

	cout<<"****TEST#6: operator= with a string, operator+ with a sentence, and operator<<*****\n\n";
	cout<<"Adding 2 sentences by adding us to the back of their.  Their is the current object \n";
	sentence their("Everything ");
	us = "will be okay.";
	cout << "us = " <<"\""<< us <<"\""<<" and length = "<<us.length()<< endl;
	cout << "their = " <<"\""<< their <<"\""<<" and length = "<<their.length()<< endl;
	their + us;
	cout<<"their followed by us is "<< "\""<<their<< "\""<<" and length = " << their.length() << endl;

	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	us + their;
	cout << "us followed by their is " << "\"" << us << "\"" <<" and length = "<< us.length()<< endl;
	cout <<"*************************************************\n";
	cout << endl << endl;

	us = "123 456";
	their = "123";
	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	us + their;
	cout << "us followed by their is " << "\"" << us << "\"" << "and length = " << us.length() << endl;

	us = "123 456";
	their = "";
	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	their + us;
	cout << "their followed by us is " << "\"" << their << "\"" << " and length = " << their.length() << endl<<endl;
	cout << "****End of Test#6*********************************************\n\n";

	cout<<"****TEST#7: remove with a string without spaces, and operator<<*****\n\n";
	them = "";
	them.remove("123");
	cout << "\"" << them << "\"" << " length of them = " << them.length() << endl;
	them = "123";
	cout << them << endl;
	them.remove("123");
	cout <<"\""<< them<< "\"" << " length of them = "<<them.length()<<endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("123");
	cout << "\""<<them <<"\""<< " length of them = " << them.length() << endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("4567");
	cout <<"\""<< them <<"\"" " length of them = " << them.length() << endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("124");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl<<endl;
	cout << "****End of Test#7*********************************************\n";
	cout << endl;
	//cout << "****TEST#8: operator= with a sentence object and operator<<*****\n\n";
	//sentence h("123 456 780");
	//them = h;
	//cout << "right object = " << h << endl;
	//cout << "them = "<<them << endl<<endl;
	//cout << "****End of TEST#8****************************************\n\n";
	//cout << "****End of Program*********************************************\n";

	return 0;
}