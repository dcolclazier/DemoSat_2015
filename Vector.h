﻿#pragma once
#include <stdlib.h>
#include "string.h"
#include <Arduino.h>

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
	bool contains(T const &thing) {
		for (int i = 0; i < d_size; i++) {
			if (d_data[i] == thing) return true;
			Serial.print("d_data[i]: ");
			Serial.println((uint16_t)d_data[i], HEX);
			Serial.print("thing: ");
			Serial.println((uint16_t)thing,HEX);
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
	 
	void push_back(T const &x) {

		if (d_capacity == d_size) resize();
		d_data[d_size++] = x;
	}; // Adds new value. If needed, allocates more space

	long unsigned int size() const {

		return d_size;
	}; // Size getter
	void remove(T const &thing) {
		for (int x = 0; x < d_size; x++){
			if(d_data[x] == thing) {
				Serial.println("deleting.");
				delete d_data[x];
				for (int y = x + 1; y < d_size; y++) {
					d_data[x++] = d_data[y];
				}
				d_data[--d_size] = NULL;

			}
			else Serial.println("couldn't find...");
		}
	}
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