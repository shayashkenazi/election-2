#pragma once
#include <iostream>
using namespace std;
template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 10) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	/*  ITERATORS */

	class iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}
		friend class const_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		iterator& operator++() { /* ++arr */
			++_i;
			return *this;
		}
		iterator operator++(int) { /* arr++ */
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--() { /* --arr */
			--_i;
			return *this;
		}
		iterator operator--(int) { /* arr-- */
			iterator temp(*this);
			--_i;
			return temp;
		}
	};

	class const_iterator
	{
	private:
		const DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(const DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}
		const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}
		friend class const_iterator;

		const const_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		const const_iterator& operator=(const const_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		bool operator==(const const_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const const_iterator& other) const {
			return !(*this == other);
		}
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		const T& operator*() {
			return _da->_arr[_i];
		}
		const T* operator->() {
			return &_da->_arr[_i];
		}

		const_iterator& operator++() { /* ++arr */
			++_i;
			return *this;
		}
		const_iterator operator++(int) { /* arr++ */
			const_iterator temp(*this);
			++_i;
			return temp;
		}
		const_iterator& operator--() { /* --arr */
			--_i;
			return *this;
		}
		const_iterator operator--(int) { /* arr-- */
			const_iterator temp(*this);
			--_i;
			return temp;
		}
	};

	class reverse_iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		reverse_iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		reverse_iterator(const reverse_iterator& other) : _da(other._da), _i(other._i) {}

		const reverse_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		const reverse_iterator& operator=(const reverse_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}
		bool operator==(const reverse_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const reverse_iterator& other) const {
			return !(*this == other);
		}

		const T& operator*() {
			return _da->_arr[_i];
		}
		const T* operator->() {
			return &_da->_arr[_i];
		}

		reverse_iterator& operator++() { /* ++arr => --arr */
			--_i;
			return *this;
		}
		reverse_iterator operator++(int) { /* arr++ => arr-- */
			reverse_iterator temp(*this);
			--_i;
			return temp;
		}
		reverse_iterator& operator--() { /* --arr => ++arr */
			++_i;
			return *this;
		}
		reverse_iterator operator--(int) { /* arr-- => arr++ */
			reverse_iterator temp(*this);
			++_i;
			return temp;
		}
	};

	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	iterator erase(const iterator& iter) {
		iterator iter1 = iter;
		iterator res = iter1;
		iterator p1 = iter1++;

		while (iter1 != end())
		{
			*p1 = *iter1;
			iter1++;
			p1++;
		}

		_logicalSize--;
		return res;
	}

	iterator erase(const iterator& first, const iterator& last) {

		iterator first1 = first;
		iterator p1 = first;
		int pullback = 1;

		while (first1 != last) {
			first1++;
			pullback++;
		}

		iterator iter = ++first1;
		iterator res = iter;

		while (iter != end())
		{
			*p1 = *iter;
			iter++;
			p1++;
		}

		_logicalSize -= pullback;
		return res;
	}

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}

	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}
	const_iterator cend() const {
		return const_iterator(*this, _logicalSize);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(*this, _logicalSize - 1);
	}
	reverse_iterator rend() {
		return reverse_iterator(*this, -1);
	}

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

	void resize(int i) {
		_physicalSize = i;
		if (_physicalSize <= _logicalSize)
			_logicalSize = _physicalSize;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	void insert_to_tail(T& new_tail) {
		if (_physicalSize == _logicalSize)
			resize();

		_arr[_logicalSize++] = new_tail;
	}

	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

private:

	T* _arr;
	int _logicalSize;
	int _physicalSize;
};