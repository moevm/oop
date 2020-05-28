#pragma once
#include <iterator>
#include <memory>
#include <cmath>
#include "Base.h"

struct Field {

	struct element {
		element();
		element(element const& a);
		~element() = default;

        std::string ObjName;
		LandscapeTypes type;
        std::shared_ptr<NtrlObj> object;
		std::shared_ptr<Base> base;
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
	std::vector<std::shared_ptr<Base>> ListBases;
private:
	element** field;
};