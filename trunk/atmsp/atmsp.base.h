/** *********************************************************************** **
 **                                                                         **
 ** Copyright (C) 1989-2012 Heinz van Saanen                                **
 **                                                                         **
 ** This file may be used under the terms of the GNU General Public         **
 ** License version 3 or later as published by the Free Software Foundation **
 ** and appearing in the file LICENSE.GPL included in the packaging of      **
 ** this file.                                                              **
 **                                                                         **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE **
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR        **
 ** PURPOSE.                                                                **
 **                                                                         **
 ** Verson: 1.0.4                                                           **
 **                                                                         **
 ** *********************************************************************** **/

#ifndef _ATMSP_BASE_H_INCLUDED_
#define _ATMSP_BASE_H_INCLUDED_


/// Determine maximum sizes for stack and var/val/num/con arrays.
/// Note that sizes may have chache-effects e.g. Play here for tuning 
#define ATMSP_SIZE 64                 // Stack, values-array and bytecode-operators
#define ATMSP_MAXNUM ATMSP_SIZE/4     // Numeric-array. Holds all numbers
#define ATMSP_MAXVAR ATMSP_SIZE/8     // Variables-array. Holds all variables
#define ATMSP_MAXCON ATMSP_SIZE/16    // Constants-array. Holds all constants


/** *********************************************************************** **
 ** Templatized stack, minimalistic version without overhead. Spare all     **
 ** error checks as these are done in the parser anyhow                     **
 ** *********************************************************************** **/
template <typename T>
class ATMSP_STACK {

	T stack[ATMSP_SIZE];    // Stack grows from left (position 0) to right
	long sp;                // Stack-pointer (-1 for empty stack)

public:

	/// Constructor and clear
	ATMSP_STACK() : sp(-1) {}
	void clear() { sp = -1; }

	/// Usual push/pop operations
	void push(T const &elem) { stack[++sp] = elem; }
	T pop() { return stack[sp--]; }

	/// Get/set stack top without push-operation
	T top() { return stack[sp]; }
	void setTop(T const &elem) { stack[sp] = elem; }
};


/** *********************************************************************** **
 ** Templatized list, minimalistic version without overhead                 **
 ** *********************************************************************** **/
template <typename T, size_t maxSize>
class ATMSP_LIST {

	size_t num;         // Current number of list objects
	T list[maxSize];    // Storage

public:

	/// Constructor, clear, size and array-operator
	ATMSP_LIST() : num(0) {}
	void clear() { num = 0; }
	size_t size() { return num; }
	T &operator [] (const size_t index) { return list[index]; }

	/// Add new list entry
	bool push(T const &elem) {
		if ( num < maxSize ) { list[num++] = elem; return true; }
		return false;
	}

	/// Search entry and set list index
	bool find(T const &elem, size_t &index) {
		for (size_t i=0; i<num; i++)
			if ( list[i] == elem ) { index = i; return true; }
		return false;
	}
};

#endif    // _ATMSP_BASE_H_INCLUDED_
