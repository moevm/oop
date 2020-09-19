#pragma once
#include "UnitFactory.h"
#include <iostream>
#include <iterator>
#include <memory>

struct Point{
    Point(int x, int y);
    Point & operator=(Point const& a);
    Point(Point const& a);
    int x;
    int y;
};


struct Field {

	struct element {
		element();
		element(element const& a);
		~element() = default;
		std::unique_ptr<Unit> unit;
	};

	struct iterator: std::iterator<std::bidirectional_iterator_tag, element>{
	private:
		element** field;
		int height;
		int width;
		int y;
		int x;
	public:
        iterator() = default;

        iterator(iterator const&) = default;

		iterator(element** field_, int height_, int width_, int y_, int x_);

        iterator& operator++();

        iterator operator++(int);

        iterator& operator--();

		iterator operator--(int);

		bool operator==(const iterator& b) const;

		bool operator!=(const iterator& b) const;

		const element& operator*() const;

		element const* operator->() const;
	};
	iterator begin() {
		return {field, height, width, 0, 0};
	}
	iterator end() {
		return {field, height, width, height - 1, width};
	}

	struct SomeStruct {
		explicit SomeStruct(element* a);
		element* arr;
		element& operator[](int a);
	};
	SomeStruct operator[](int a);

	explicit Field(int s = 10, int l = 10);
	Field(Field const& a);
	Field(Field&& a) noexcept;
	~Field();
	void addUnit(Point const& a, char Name);
	void remUnit(Point const &a);
	bool move(Point const& old_p, Point const& new_p );
    void show();

	int height;
	int width;
	int MaxCount;
	int Count;
private:
	element** field;
};