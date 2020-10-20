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
	//~sentence();
	bool isEmpty() { return front == 0; };
	//int length();
	//void addBack(string& line);
	friend ostream& operator<<(ostream&, const sentence& lineS);
	//void operator=(const string& line);
	//sentence& operator=(sentence& lineS);
	//void operator+(const string& line);
	//bool isEqual(const sentence& lineS);
	//void remove(const string& line);
private:
	word* front;
	word* back;
	int num_of_terms;
};

sentence::sentence() {
	front = 0;
	back = 0;
	num_of_terms = 0;
}

sentence::sentence(const string& line) {
	//empty sentence
	front = back = 0;
	int wordStart, wordEnd, search;
	num_of_terms = wordStart = wordEnd = search = 0;

	//start iterating backwards until either a space or the front of the string is reached
	for (int i = line.size()-1; i > -1; i--) {
		//if we are starting a new term, search = 0
		if (search == 0) {
			//if search = 0, wordEnd = i
			wordEnd = i;
		}
		//if wordEnd has a value
		if (wordEnd != 0) {
			//set search to 1 to stop the redefinition of wordEnd
			search = 1;
		}
		//if the character in the string is a space
		if (line[i] == ' ') {
			//set word start to space position + 1
			wordStart = i + 1;
		}
		//if we have a starting point for a new word
		if (wordStart != 0 && i != 0) {
			//start the transfer of the word into sentence
			word* w = new word;
			w->term = line.substr(wordStart, wordEnd - i);
			w->next = front;
			front = w;
			num_of_terms++;
			//add a term for the space
			word* space = new word;
			w->term = ' ';
			w->next = front;
			front = space;
			num_of_terms++;
			wordStart = 0;
			wordEnd = i-1;
		}
		if (i == 0) {
			//start the transfer of last word
			word* w = new word;
			w->term = line.substr(0, wordEnd + 1);
			w->next = front;
			front = w;
			num_of_terms++;
			break;
		}
	}
}

sentence::sentence(const sentence& lineS) {
	num_of_terms = lineS.num_of_terms;
	//new sentence front word = lineS front word
	front->term = lineS.front->term;
	front->next = back;
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
}

ostream& operator<<(ostream& out, const sentence& lineS) {
	out << lineS;
	return out;
}

int main() {
	cout << "****Test#1: default constructor, length, and operator<<***\n\n";
	sentence you;
	cout<<"\""<<you << "\"" /*<<" : length = "<<you.length()*/<< endl;
	cout<<"\n****End of Test#1*******************************************\n";
	cout<<endl;

	cout << "****Test#2: explicit-value constructor, length, and operator<<***\n\n";
	sentence me("Today is a wonderful day!   ");//sentence with 3 spaces at end
	cout<<"me is "<<"\""<<me<<"\""<<" =  "<<"\""<<"Today is a wonderful day!   "<<"\""<<"\n";
	//cout << "The length of me is " << me.length() << "\n\n";
	sentence me_to("");
	cout << "me_to is " << "\"" << me_to << "\"" << " = " << "\""<< "\""<<"\n"; //sentence should be empty string
	//cout << "The length of me_to is " << me_to.length() << "\n\n";
	sentence you_to(" ");
	cout << "you_to is " << "\"" << you_to << "\"" << " =  "<<"\"" <<" "<< "\"" << "\n";//sentence is one space
	//cout << "The length of you_to is " << you_to.length() << "\n\n";
	cout << "****End of Test#2*******************************************\n";
	cout<<endl;

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