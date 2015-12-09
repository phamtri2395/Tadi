#include "arithmeticCore.h"
#include "extlib/strLib.h"
#include "extlib/extList.h"
#include <cmath>
#include <sstream>

Queue<char*> Postfix;

/* Monomial class */
class mono {
public:
	double coef;
	double exp;
	mono* next;
	mono* prev;

	/* Constructor */
	mono(double coefficient, double exponent, mono* _prev = nullptr, mono* _next = nullptr) {
		coef = coefficient;
		exp = exponent;
		prev = _prev;
		next = _next;
	}
};



/* Polynomial class */
class poly {
public:
	mono* head;
	mono* tail;

	/* Constructors & Destructors */
	poly(void) {
		head = tail = nullptr;
	}
	poly(double coefficient, double exponent) {
		head = tail = new mono(coefficient, exponent);
	}
	void Dispose(void) {
		mono* current = head;
		head = nullptr;
		while (current != nullptr) {
			mono* next = current->next;
			delete current;
			current = next;
		}
	}

	/* Operator Overloading */
	poly& operator+(const poly&);
	poly& operator-(const poly&);
	poly& operator*(const poly&);

	/* Functions */
	bool isEmpty(void);
	void Clone(poly&);
	double Calc(double);
	double coef(void);
	double exp(void);
};

poly& poly::operator+(const poly& other) {
	poly temp;
	this->Clone(temp);

	mono* curr_other = other.head;
	while (curr_other != nullptr) {
		mono* curr_temp = temp.head;
		while ((curr_temp != nullptr) && (curr_temp->exp < curr_other->exp)) {
			curr_temp = curr_temp->next;
		}

		if (curr_temp != nullptr) {
			if (curr_temp->exp > curr_other->exp) { // Exponent1 > Exponent2
				mono* t = new mono(curr_other->coef, curr_other->exp, curr_temp->prev, curr_temp);
				if (curr_temp->prev != nullptr){
					curr_temp->prev->next = t;
					curr_temp->prev = t;
				}
				else {
					temp.head = t;
					temp.head->next->prev = temp.head;
				}
			}
			else { // Exponent1 == Exponent2
				curr_temp->coef = curr_temp->coef + curr_other->coef;
			}
		}
		else { // Add to last of list
			if (head != nullptr) { // check if list == null
				temp.tail = new mono(curr_other->coef, curr_other->exp, temp.tail, nullptr);
				temp.tail->prev->next = temp.tail;
			}
			else {
				temp.head = temp.tail = new mono(curr_other->coef, curr_other->exp, temp.tail, nullptr);
			}
		}

		curr_other = curr_other->next;
	}

	return temp;
}

poly& poly::operator-(const poly& other) {
	poly temp;
	this->Clone(temp);

	mono* curr_other = other.head;
	while (curr_other != nullptr) {
		mono* curr_temp = temp.head;
		while ((curr_temp != nullptr) && (curr_temp->exp < curr_other->exp)) {
			curr_temp = curr_temp->next;
		}

		if (curr_temp != nullptr) {
			if (curr_temp->exp > curr_other->exp) { // Exponent1 > Exponent2
				mono* t = new mono(0.0 - curr_other->coef, curr_other->exp, curr_temp->prev, curr_temp);
				if (curr_temp->prev != nullptr){
					curr_temp->prev->next = t;
					curr_temp->prev = t;
				}
				else {
					temp.head = t;
					temp.head->next->prev = temp.head;
				}
			}
			else { // Exponent1 == Exponent2
				curr_temp->coef = curr_temp->coef - curr_other->coef;
			}
		}
		else { // Add to last of list
			if (head != nullptr) { // check if list == null
				temp.tail = new mono(0.0 - curr_other->coef, curr_other->exp, temp.tail, nullptr);
				temp.tail->prev->next = temp.tail;
			}
			else {
				temp.head = temp.tail = new mono(0.0 - curr_other->coef, curr_other->exp, temp.tail, nullptr);
			}
		}

		curr_other = curr_other->next;
	}

	return temp;
}

poly& poly::operator*(const poly& other) {
	poly temp;
	
	mono* curr_other = other.head;
	while (curr_other != nullptr) {
		mono* curr_this = this->head;
		while (curr_this != nullptr) {
			temp = temp + poly((curr_this->coef) * (curr_other->coef), (curr_this->exp) + (curr_other->exp));
			curr_this = curr_this->next;
		}

		curr_other = curr_other->next;
	}

	return temp;
}

bool poly::isEmpty() {
	return (head == nullptr);
}

void poly::Clone(poly& oldtmp) {
	if (head != nullptr) {
		mono* curr_this = head;
		poly temp(curr_this->coef, curr_this->exp);
		curr_this = curr_this->next;

		while (curr_this != nullptr) {
			temp.tail = new mono(curr_this->coef, curr_this->exp, temp.tail, nullptr);
			temp.tail->prev->next = temp.tail;
			curr_this = curr_this->next;
		}

		oldtmp.Dispose();
		oldtmp = temp;
	}
}

double poly::Calc(double X) {
	if (head == nullptr) return 0.0;

	mono* curr = head;
	double result = 0.0;
	while (curr != nullptr) {
		result += (curr->coef) * pow(X, curr->exp);
		curr = curr->next;
	}

	return result;
}

double poly::coef() {
	return head->coef;
}

double poly::exp() {
	return head->exp;
}

/* Miscellaneous functions */
int type(char c) { // Return type of character
	if (((c >= '0') && (c <= '9')) || (c == '.')) return 1;
	if ((c == '+') || (c == '-') || (c == '*')) return 2;
	if ((c == '(') || (c == ')')) return 3;
	if ((c == 'x') || (c == '^')) return 4;

	return -1;
}
int type(char* s) {
	if ((s[0] >= '0') && (s[0] <= '9')) return 1;
	if ((s[0] == '+') || (s[0] == '-')) return 2;
	if ((s[0] == '*') || (s[0] == '/')) return 3;
	if (s[0] == 'x') {
		if (s[1] == '^') return 5;
		else return 4;
	}
	if ((s[0] == '(') || (s[0] == ')')) return 6;
}

Queue<char*> toPoly(Queue<char*> queue) {
	Queue<char*> postfix;
	Stack<char*> stack;

	while (!queue.isEmpty()) {
		char* sub = queue.dequeue();

		// if Operands
		if (type(sub) == 1) {
			postfix.enqueue(sub);
			continue;
		}

		// if Operators
		if ((type(sub) >= 2) && (type(sub) <= 5)) {
			if ((!stack.isEmpty()) && (type(stack.peek()) >= type(sub)) && (type(stack.peek()) != 6)) {
				postfix.enqueue(stack.pop());
			}

			if (type(sub) == 4) {
				// if it's just x
				if ((postfix.isEmpty()) || (type(postfix.peek()) != 1))
					postfix.enqueue("1");

				postfix.enqueue("1");
				stack.push("x^");
				continue;
			}

			stack.push(sub);

			continue;
		}

		// if ( or )
		if (type(sub) == 6) {
			if (sub[0] == '(') {
				stack.push(sub);
			}
			else {
				while ((!stack.isEmpty()) && (stack.peek()[0] != '('))
					postfix.enqueue(stack.pop());

				stack.pop();
			}
			continue;
		}
	}

	/* Pop out all element in stack */
	while (!stack.isEmpty()) {
		postfix.enqueue(stack.pop());
	}

	return postfix;
}





poly polyResult;

Expression::Expression(const char* string) {
	/* Copy string */
	str = new char[length(string) + 1];
	int pos = 0;
	while (string[pos] != '\0') {
		str[pos] = string[pos];
		pos++;
	}
	str[pos] = string[pos];
}

/* String processing functions */
char* Expression::verify(void) {
	removeSpace(str);

	/* Call split function*/
	split();

	return ("OK");
}

void Expression::split() {
	Queue<char*> queue;

	int last_state = 0;
	int curr_state = 0;
	last_state = type(str[0]);

	int last_pos = 0;
	int pos = 1;
	while (str[pos] != '\0') {
		curr_state = type(str[pos]);

		if (((curr_state != last_state) && (last_state != 0)) || (curr_state == 3)) {
			/* Enqueue substring */
			char* sub = new char[pos - last_pos + 1];
			int count = 0;
			while (count < pos - last_pos) {
				sub[count] = str[last_pos + count];
				count++;
			}
			sub[count] = '\0';
			queue.enqueue(sub);

			/* Go to next position */
			last_pos = pos;
			last_state = type(str[pos++]);
			continue;
		}

		pos++;
	}

	/* Add last substring */
	char* sub = new char[pos - last_pos + 1];
	int count = 0;
	while (count < pos - last_pos) {
		sub[count] = str[last_pos + count];
		count++;
	}
	sub[count] = '\0';
	queue.enqueue(sub);

	/* Call toPoly function */
	Postfix = toPoly(queue);

	/* Call calc function*/
	calc();
}

void Expression::calc() {
	Stack<poly> stk_result;

	while (!Postfix.isEmpty()) {
		char* sub = Postfix.dequeue();

		/* if Operands */
		if (type(sub) == 1) {
			stk_result.push(poly(stod(sub), 0.0));
			continue;
		}

		poly poly2 = stk_result.pop();
		poly poly1 = stk_result.pop();
		poly temp;

		/* if + or - or * */
		if ((type(sub) == 2) || (type(sub) == 3)) {
			switch (sub[0]) {
			case '+':
				temp = poly1 + poly2;
				stk_result.push(temp);
				break;
			case '-':
				temp = poly1 - poly2;
				stk_result.push(temp);
				break;
			case '*':
				temp = poly1 * poly2;
				stk_result.push(temp);
				break;
			}
		}

		/* if x^ */
		if ((type(sub) == 4) || (type(sub) == 5)) {
			stk_result.push(poly(poly1.coef(), poly2.coef()));
			continue;
		}
	}



	/* Write out result to string */
	polyResult = stk_result.pop();
	mono* curr = polyResult.tail;
	std::stringstream stream;
	std::string s;

	while (curr != nullptr)
	{
		/* Won't print monomial with coefficient == 0 */
		if (curr->coef == 0) {
			curr = curr->prev;
			continue;
		}

		/* negative and positive coefficient */
		if (curr->coef >= 0) {
			if (curr->next != nullptr) // for first element
				stream << " + ";
			if (curr->coef !=1 ) stream << curr->coef;
		}
		else
			stream << " - " << 0.0 - curr->coef;

		/* print x or not */
		if (curr->exp > 1)
			stream << "x" << "^" << curr->exp;
		else if (curr->exp == 1)
			stream << "x";

		curr = curr->prev;
	}

	/* Copy to result */
	s = stream.str();
	const char* temp = s.c_str();
	result = new char[length(temp) + 1];
	int pos = 0;
	while (temp[pos] != '\0') {
		result[pos] = temp[pos];
		pos++;
	}
	result[pos] = '\0';
}

const char* Expression::toString() {
	return result;
}

double Expression::at(double x) {
	return polyResult.Calc(x);
}