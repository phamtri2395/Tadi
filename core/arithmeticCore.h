/** arithmeticCore.h

    An arithmetic processing core for converting and calculating an expression

	@docdate 11/14/2015
    @author phamtri2395@gmail.com
*/
#pragma once
#define RESULT_MAX_LENGTH 501



class Expression {
private:
	char* str;
	char* result; // Contains result of polynomial
	void split(void);
	void calc(void);

public:
	/* Constructor */
	Expression(const char*);
	/* Functions */
	char* verify(void);
	const char* toString(void);
	double at(double);
};