#pragma once
#include <cstring>
#include <iostream>

template <typename T>
class Vector
{
	T* _data;
	size_t _size;
	size_t _capacity;

public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector&);
	Vector& operator=(const Vector&);

	Vector(Vector&&) noexcept;
	Vector& operator=(Vector&&) noexcept;

	~Vector();

	void pushBack(const T&);
	void pushBack(T&&);

	void popBack();
	void removeAt(size_t);

	void setAt(const T&, size_t);
	void setAt(T&&, size_t);

	size_t getSize() const;

	const T& operator[](size_t) const;
	T& operator[](size_t);
private:
	void free();
	void copyFrom(const Vector&);
	void moveFrom(Vector&&);

	void resize(size_t);
};


template <typename T>
Vector<T>::Vector(size_t capacity)
{
	_data = new T[capacity];
	_capacity = capacity;
	_size = _capacity;
}

template <typename T>
void Vector<T>::copyFrom(const Vector& other)
{
	_size = other._size;
	_capacity = other._capacity;

	_data = new T[_capacity];

	for (size_t i = 0; i < _capacity; i++)
	{
		_data[i] = other._data[i];
	}
}

template <typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	_size = other._size;
	_capacity = other._capacity;

	_data = other._data;
	other._data = nullptr;
}

template <typename T>
void Vector<T>::free()
{
	//for (size_t i = 0; i < _size; i++)
	//	delete _data[i];

	delete[] _data;
}


template <typename T>
Vector<T>::Vector() : _size(0), _capacity(8)
{
	_data = new T[_capacity];
}

template <typename T>
Vector<T>::Vector(const Vector& other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	free();
}

template <typename T>
void Vector<T>::resize(size_t newCapacity)
{
	T* newData = _data;

	_data = new T[newCapacity];
	//T* newData = new T[newCapacity] {nullptr};

	for (size_t i = 0; i < _size; i++)
		_data[i] = newData[i];

	_capacity = newCapacity;
	delete[] newData;
}

template <typename T>
void Vector<T>::pushBack(const T& current)
{
	if (_size >= _capacity)
		resize(_capacity * 2);

	_data[_size++] = current;
}

template <typename T>
void Vector<T>::pushBack(T&& current)
{
	if (_size >= _capacity)
		resize(_capacity * 2);

	_data[_size++] = std::move(current);
}

template <typename T>
void Vector<T>::removeAt(size_t index)
{
	if (index >= _size)
		throw std::invalid_argument("Invalid index!");

	delete _data[index];
	_data[index] = nullptr;
	_size--;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	//if (index >= _size)
	//	throw std::length_error("No such index!");

	return _data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	//if (index >= _size)
	//	throw std::length_error("No such index!");

	return _data[index];
}

template <typename T>
void Vector<T>::popBack()
{
	if (_size == 0)
		throw std::logic_error("No elements available!");

	_size--;
}

template <typename T>
void Vector<T>::setAt(const T& obj, size_t index)
{
	if (index >= _size)
		throw std::length_error("No such index!");

	_data[index] = obj;
	//if (_data[index] != nullptr)
	//	*_data[index] = obj;
	//else
	//{
	//	_data[index] = new T(obj);
	//	_size++;
	//}
}

template <typename T>
void Vector<T>::setAt(T&& obj, size_t index)
{
	if (index >= _size)
		throw std::length_error("No such index!");

	_data[index] = std::move(obj);
	/*if (_data[index] != nullptr)
		*_data[index] = obj;
	else
	{
		_data[index] = new T(std::move(obj));
		_size++;
	}*/
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return _size;
}

