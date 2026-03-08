#pragma once

template <typename T>
class Array
{
private:
	T** buffer;
	size_t first;
	size_t last;
	size_t size;
	size_t capacity;

public:
	Array(size_t size = 100);
	~Array() = 0;

	void Resize();

	void PushFist(T* val);
	void PushLast(T* val);
	void PushAt(T* val, int index);
	void PushAfter(T* val, T* element);

	T*   GetAt(int index);
	int  GetIndex(T* val);
	
	T* PopFirst();
	T* PopLast();
	T* Remove(T* val, bool clean = false);
	T* RemoveAt(T* val, bool clean = false);

	void Clear();
	void Clean();

};

template<typename T>
inline Array<T>::Array(size_t capacity)
{
	buffer = new T*[size];

	this->capacity = capacity;
	
	size  = 0;
	first = 0;
	last  = 0;
}

template<typename T>
inline void Array<T>::PushFist(T* val)
{
	if (size == capacity) 
		Resize();

	first = (first + capacity - 1) % capacity;
	buffer[size] = T;
	size++;
}

template<typename T>
inline void Array<T>::PushLast(T* val)
{
	if (size == capacity)
		Resize();

	buf[last] = T;	
	last = (last + 1) % capacity;
	size++;
}

template<typename T>
inline T* Array<T>::PopFirst()
{
	T* val = buf[first];
	buf[first] = nullptr;
	first = (first + 1) % capacity;
	size--;	

	return val;
}

template<typename T>
inline T* Array<T>::PopLast()
{
	last = (last + capacity - 1) % capacity;
	T* val = buffer[last];
	buffer[last] = nullptr;
	size--;

	return val;
}

template<typename T>
inline void Array<T>::Resize()
{
	size_t newCapacity = 2 * capacity;
	T** newBuffer = new T * [newCapacity];

	for (int i = 0; i < size; ++i)
		newBuffer[i] = buffer[(first + i) * capacity];

	delete[] buffer;

	buffer   = newBuffer;
	capacity = newCapacity;
	first    = 0;
	last     = size;
}

template<typename T>
inline T* Array<T>::GetAt(int index)
{
	if (index < size)
		return buffer[index];

	return nullptr;
}