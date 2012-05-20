/** @file MTException.h
	@brief General exception framework 
	@author (c) 2008 Mathieu Jacques
*/

#ifndef _MTException_INCLUDED
#define _MTException_INCLUDED

#include <vector>
#include "MTUnicodeANSIDefs.h"
#include "MTGlobalString.h"

//! @brief Maximum number of chained exceptions
#define MTEXCEP_MAXEXCEPS	4	

//! @brief Maximum number of exception arguments
#define MTEXEPDATA_MAXARGS	4

/** @brief Base exception: simplified exception with only text descriptions.

	Allows all exception's classes (if there are many) to be handled 
	like a simple error message exception.  This reduces
	the number of exception types to catch and the duplicated
	exception handling code. 
*/
class MTException
{
public:

//###############################################
/** @name Top-level exception informations 
*/
	//@{

	/** @brief #The line in the source code where the exception occured */
	long m_line;		
	
	/** @brief The file where the exception occured */
	MTGlobalString m_file;
	
	/** @brief A default exception's text description */
	MTGlobalString m_description;

	//@}

	/** @brief Get the number of available exception descriptions */
	unsigned int getNbDescs()const{ return m_size; }
	
	/** @brief Get an exception description	

	Get the description of each exception if there are many.

	@param	index		The exception's index. The top-level exception has index 0.
	@return A textual description

	*/
	MTGlobalString getDesc(unsigned int index)const
	{
		return m_descriptionList[m_size-index-1];
	}

	virtual ~MTException(){};

protected:

	/** All exception's descriptions (if there are many)
	
	Can't use stl::vector since there are compatibility problems 
	when mixing VC6 and VC7 versions.  **Remember, plug-ins may have been
	compiled using a different environment than the parser.
	*/
	MTGlobalString m_descriptionList[MTEXCEP_MAXEXCEPS];
	
	//! Number of exceptions
	unsigned int m_size;

	
};

/** @brief Exception template

  Represents one exception.

  @param	TExcepData	A customizable type for supplementary exception's information

*/
template <class TExcepData> class MTDetailedException
{
public:

	MTDetailedException(){};

	/** @brief Construct an exception 
	@param	line		The line in the source code where the exception occured.
						Use the __LINE__ macro to automatically obtained the line number.
	@param	file		The file where the exception occured.  Use the __FILE__ macro
						to automatically obtained the file name.
	@param	level		A user-defined value used to determine if the exception is relevant
	@param	data		User-defined data giving a detailled exception's description
	@param	description	A default exception's text description
	*/
	MTDetailedException(long line, const MTCHAR *file, long level, const TExcepData &data, const MTCHAR *description)
	{
		m_line = line;
		m_file = file;
		m_level = level;
		m_data = data;
		m_description = description;
	}
	
	/** @brief Copy an existing exception
	@param	obj	Exception object
	*/
	MTDetailedException( const MTDetailedException &obj )
	{
		operator=(obj);
	}

	/** @brief Copy and existing exception
	@param obj	Exception object
	*/
	MTDetailedException& operator=(const MTDetailedException &obj)
	{
		m_line = obj.getLine();
		m_file = obj.getFile();
		m_level = obj.getLevel();
		m_data = obj.getData();
		m_description = obj.getDescription();
		return *this;
	}

	/** @brief Get the source code line where the exception occured
	@return The source code line
	*/
	long getLine()const{ return m_line; } 

	/** @brief Get the filename where the exception occured
	@return The filename
	*/	
	const MTCHAR* getFile()const{ return m_file.c_str(); }	
	
	/** @brief Get exception's level
	@return The exception's level
	*/	
	long getLevel()const{ return m_level; } 	
	
	/** @brief Get data associated with the exception
	@return The data
	*/	
	TExcepData getData()const{ return m_data; }	
	
	/** @brief Get the default text description
	@return A text description
	*/	
	const MTCHAR* getDescription()const{ return m_description.c_str(); }

private:

	long m_line;
	long m_level;
	MTGlobalString m_file;	
	MTGlobalString m_description;
	TExcepData m_data;
};

/** @brief Chained Exceptions

	Contains one or more exceptions.  A chain of exceptions
	represents different levels of detail of an exception.  The most
	generic exception is the topmost.  If you want more detail, you can look
	at the next ones.  This is particularly helpful for debugging purpose.

	@param	TExcepData	A customizable type for supplementary exception's information
*/
template <class TExcepData> class MTChainedExceptions : public MTException
{
public:

	/** @brief Construct an empty exception chain */
	MTChainedExceptions(){m_size=0;}

	/** @brief Contruct an exception chain with a first exception	
	@copydoc MTDetailedException::MTDetailedException()	
	*/
	MTChainedExceptions(long line, const MTCHAR *file, long level, const TExcepData &data, const MTCHAR *description)
	{		
		m_size=0;
		add(line, file, level, data, description);
	}

	/** @brief Copy a chained exception
	@param obj	Chained exception
	*/
	MTChainedExceptions( const MTChainedExceptions &obj )
	{		
		operator=(obj);
	}

	
	/** @brief Copy a chained exception
	@param obj	Chained exception
	*/ 	
	MTChainedExceptions& operator=(const MTChainedExceptions &obj )
	{		
		m_size = 0;
		add(obj);
		m_line = obj.m_line;
		m_file = obj.m_file;		
		m_description = obj.m_description;	
		
		return *this;
	}	

	/** @brief Add an exception		
	@copydoc MTDetailedException::MTDetailedException()	
	*/
	void add( long line, const MTCHAR *file, long level, const TExcepData &data, const MTCHAR *description)
	{
		if( m_size >= MTEXCEP_MAXEXCEPS )
		{
			return;		// the array is full
		}
		
		MTDetailedException<TExcepData> excep(line, file, level, data, description);			
		
		m_exceptions[m_size] = excep;		
		m_line = line;
		m_file = file;		
		m_description = description;
		m_descriptionList[m_size] = description;

		m_size++;
	}
	
	/** @brief Add an exception
	@param	e	The exception to add
	*/
	void add( const MTDetailedException<TExcepData> &e)
	{
		add(e.getLine(), e.getFile(), e.getLevel(), e.getData(), e.getDescription());
	}

	/** @brief Add all exceptions contained in this object
	@param	e	The exception container
	*/
	void add( const MTChainedExceptions &e )
	{
		for(unsigned int t=0; t<e.size(); t++ )
		{
			add(*e.getException(t));
		}
	}

	/** @brief Get the number of exceptions
	@return The number of exceptions
	*/	
	unsigned int size()const
	{		
		return m_size;
	}
	

	/** @brief Get an exception
	@param index	The exception's index.  The top-level exception has the 0 index.
	@return The exception object
	*/	
	const MTDetailedException<TExcepData>* getException(int index)const
	{
		return &m_exceptions[m_size-index-1];		
	}
	

private:
	
	typedef MTDetailedException<TExcepData> TExceptionType;
	
	/** Contains all the exception objects
	
	Can't use std::vector since there are compatibility problems 
	when mixing VC6 and VC7 versions.  **Remember, plug-ins may have been
	compiled using a different environment than the parser.
	*/
	TExceptionType m_exceptions[MTEXCEP_MAXEXCEPS];		
};


/** @brief Parser Exception's data

	There is no fixed argument.  This is a kind of meta-exception, where
	the exception's arguments can be defined at runtime.  Use argument/value
	to allow insertion into translated error messages.
*/
class MTExcepData
{	
public:

//###############################################
/** @name Construct an exception data
* Many constructors are provided to ease the construction.  
*/
	//@{

	/** @brief Construct an empty exception */
	MTExcepData()
	{
		m_nbArgs = 0;
	}

	/** @brief Construct an exception without argument 
		
		@param	id			Exception's identifier
	*/
	MTExcepData(const MTCHAR *id)
	{
		m_id = id;
		m_nbArgs = 0;
	}
	
	/** @brief Construct an exception with one argument 
		
		@param	id			Exception's identifier
		@param	argName		Argument's name
		@param	argVal		Argument's value
	*/
	MTExcepData(	const MTCHAR *id, 
					const MTCHAR *argName, const MTCHAR *argVal	)
	{
		m_id = id;
		m_nbArgs = 0;
		addArg(argName, argVal);
	}

	/** @brief Construct an exception with two arguments 
		
		@param	id			Exception's identifier
		@param	argNameN	ArgumentN's name
		@param	argValN		ArgumentN's value		
	*/
	MTExcepData(	const MTCHAR *id, 
					const MTCHAR *argName1, const MTCHAR *argVal1,
					const MTCHAR *argName2, const MTCHAR *argVal2	)
	{
		m_id = id;
		m_nbArgs = 0;
		addArg(argName1, argVal1);
		addArg(argName2, argVal2);
	}

	/** @brief Construct an exception with three arguments 
		
		@param	id			Exception's identifier
		@param	argNameN	ArgumentN's name
		@param	argValN		ArgumentN's value		
	*/
	MTExcepData(	const MTCHAR *id, 
					const MTCHAR *argName1, const MTCHAR *argVal1,
					const MTCHAR *argName2, const MTCHAR *argVal2,
					const MTCHAR *argName3, const MTCHAR *argVal3)
	{
		m_id = id;
		m_nbArgs = 0;
		addArg(argName1, argVal1);
		addArg(argName2, argVal2);
		addArg(argName3, argVal3);
	}

	/** @brief Construct an exception with four arguments 
		
		@param	id			Exception's identifier
		@param	argNameN	ArgumentN's name
		@param	argValN		ArgumentN's value		
	*/
	MTExcepData(	const MTCHAR *id, 
					const MTCHAR *argName1, const MTCHAR *argVal1,
					const MTCHAR *argName2, const MTCHAR *argVal2,
					const MTCHAR *argName3, const MTCHAR *argVal3,
					const MTCHAR *argName4, const MTCHAR *argVal4)
	{
		m_id = id;
		m_nbArgs = 0;
		addArg(argName1, argVal1);
		addArg(argName2, argVal2);
		addArg(argName3, argVal3);
		addArg(argName4, argVal4);
	}

	/** @brief Copy an existing exception */
	MTExcepData(const MTExcepData &data)
	{
		operator=(data);
	}

	/** @brief Copy an existing exception */
	MTExcepData& operator=(const MTExcepData &data)
	{
		m_id = data.getID();
		m_nbArgs = data.getNbArgs();
		unsigned int t;
		for( t=0; t<m_nbArgs; t++ )
		{
			m_argNames[t] = data.getArgName(t);
			m_argVals[t] = data.getArgVal(t);
		}
		return *this;
	}

	//@}	
	

	/** @brief Add an argument and its value

		@param	argName		Argument's name
		@param	argVal		Argument's value
	*/
	void addArg(const MTCHAR *argName, const MTCHAR *argVal)
	{
		if( m_nbArgs == MTEXEPDATA_MAXARGS )
		{
			return;	// the array is full
		}

		m_argNames[m_nbArgs] = argName;
		m_argVals[m_nbArgs] = argVal;

		m_nbArgs++;

	}

	/** @brief Get the number of defined arguments */
	unsigned int getNbArgs()const{ return m_nbArgs; }
	
	/** @brief Get an argument's name

		@param	arg		The argument number identifier ranging from 0 to the number
						of defined arguments -1
		@return The argument's name
	*/
	const MTCHAR* getArgName(unsigned int arg)const{ return m_argNames[arg].c_str(); }
	
	/** @brief Get an argument's value

		@param	arg		The argument number identifier ranging from 0 to the number
						of defined arguments -1
		@return The argument's value
	*/
	const MTCHAR* getArgVal(unsigned int arg)const{ return m_argVals[arg].c_str(); }
	
	/** @brief Get the exception's string identifier */
	const MTCHAR* getID()const{ return m_id.c_str(); }

private:

	MTGlobalString m_id;
	MTGlobalString m_argVals[MTEXEPDATA_MAXARGS];
	MTGlobalString m_argNames[MTEXEPDATA_MAXARGS];
	unsigned int m_nbArgs;	
};

#endif

