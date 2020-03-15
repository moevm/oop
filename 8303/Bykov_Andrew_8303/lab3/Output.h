#pragma once
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ostream>
#include <stdexcept>
/*
class file {
public:
	file(const char* filename) : m_file_handle(std::fopen(filename, "w+"))
	{
		if (!m_file_handle)
			throw std::runtime_error("file open failure");
	}
	~file()
	{
		if (!m_file_handle.is_open())
		{
			// fclose() может вернуть ошибку при записи на диск последних изменений
		}
	}
	void write(const char* str)
	{
		m_file_handle << str;
	}
	std::ofstream * stream()
	{
		return &m_file_handle;
	}
private:
	std::ofstream  m_file_handle;

	//  опирование и присваивание не реализовано.  ѕредотвратим их использование,
	// объ€вив соответствующие методы закрытыми.
	file(const file &);
	file & operator=(const file &);
	
};

class Output
{
protected:
	std::ofstream * stream;
	void setStream(std::ofstream * Stream)
	{
		stream = Stream;
	}
	std::ofstream out("out.txt"); 
	std::streambuf *coutbuf = std::cout.rdbuf(); 
	std::cout.rdbuf(out.rdbuf()); 
	

	std::cout.rdbuf(coutbuf);
};

class FileOutputProxy : public Output
{
	FileOutputProxy(file * f)
	{
		if (f)
			setStream(f->stream());
	}
};
class StdOutputProxy : public Output
{
	StdOutputProxy()
	{
		setStream(&std::cout);
	}
};
class NoOutputProxy : public Output
{

};*/