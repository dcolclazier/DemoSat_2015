#pragma once
#include <stdlib.h>
#include "string.h"

template<typename T>
class Vector {
	long unsigned int d_size; // Stores no. of actually stored objects
	long unsigned int d_capacity; // Stores allocated capacity
	T *d_data; // Stores data
public:
	Vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor

	Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) {

		d_data = (T *)malloc(d_capacity*sizeof(T));
		memcpy(d_data, other.d_data, d_size*sizeof(T));
	}; // Copy constuctor

	~Vector() {
		delete[] d_data;
		//free(d_data);
	}; // Destructor
	bool contains(T thing) {
		for (int i = 0; i < d_size; i++) {
			if (d_data[i] == thing) return true;
		}
		return false;
	}
	Vector &operator=(Vector const &other) {
		//free(d_data); 
		delete[] d_data;
		d_size = other.d_size;
		d_capacity = other.d_capacity;
		d_data = static_cast<T*>(malloc(d_capacity*sizeof(T)));
		memcpy(d_data, other.d_data, d_size*sizeof(T));
		return *this;
	}; // Needed for memory management
	   /*void remove(int index) {
	   memmove(d_data + index, d_data + 3, (d_size - index - 1) * sizeof(T));
	   d_size--;
	   d_capacity--;
	   }*/
	void push_back(T const &x) {

		if (d_capacity == d_size) resize();
		d_data[d_size++] = x;
	}; // Adds new value. If needed, allocates more space

	long unsigned int size() const {

		return d_size;
	}; // Size getter

	T const &operator[](long unsigned int idx) const {

		return d_data[idx];
	}; // Const getter
	T &operator[](long unsigned int idx) {

		return d_data[idx];
	}; // Changeable getter

private:
	void resize() {
		d_capacity = d_capacity ? d_capacity * 2 : 1;
		T *newdata = (T *)malloc(d_capacity*sizeof(T));
		memcpy(newdata, d_data, d_size * sizeof(T));
		//delete[] d_data;
		free(d_data);
		d_data = newdata;
	};// Allocates double the old space
};