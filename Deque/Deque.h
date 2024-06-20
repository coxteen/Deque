#pragma once
#include <iostream>

template<typename dataType >
class Deque {

public:
	Deque();
	void push_front(dataType value);
	void push_back(dataType value);
	void pop_front();
	void pop_back();
	void erase(int index);
	void insert(dataType value, int index);
	dataType front() const;
	dataType back() const;
	void print() const;
	bool empty() const;
	int size() const;
	void clear();
	dataType& operator [] (int index);

private:
	int dim;
	dataType** adressBlock;
	int leftBlock, rightBlock;
	int beginIndex, endIndex;
	const int blockSize = 8;
	const int startIndex = 3;
	const int startBlock = 1;
	const int multiplyValue = 3;
};

template<typename dataType>
inline Deque<dataType>::Deque() {
	dim = 3;
	leftBlock = startBlock;
	rightBlock = startBlock;
	beginIndex = startIndex;
	endIndex = startIndex;
	adressBlock = new dataType * [dim];
	for (int i = 0; i < dim; ++i) {
		adressBlock[i] = new dataType[blockSize];
	}
}

template<typename dataType>
inline void Deque<dataType>::push_front(dataType value) {
	if (beginIndex == 0) {
		if (leftBlock == 0) {
			dataType** newAdressBlock = new dataType * [dim * multiplyValue];
			for (int i = 0; i < dim; ++i) {
				newAdressBlock[dim + i] = adressBlock[i];
			}
			delete[] adressBlock;
			adressBlock = newAdressBlock;
			leftBlock += dim;
			rightBlock += dim;
			dim *= multiplyValue;
		}
		leftBlock--;
		adressBlock[leftBlock] = new dataType[blockSize];
		beginIndex = blockSize;
	}
	beginIndex--;
	adressBlock[leftBlock][beginIndex] = value;
}

template<typename dataType>
inline void Deque<dataType>::push_back(dataType value) {
	if (endIndex == blockSize) {
		if (rightBlock == dim - 1) {
			dataType** newAdressBlock = new dataType * [dim * multiplyValue];
			for (int i = 0; i < dim; ++i) {
				newAdressBlock[dim + i] = adressBlock[i];
			}
			delete[] adressBlock;
			adressBlock = newAdressBlock;
			leftBlock += dim;
			rightBlock += dim;
			dim *= multiplyValue;
		}
		rightBlock++;
		adressBlock[rightBlock] = new dataType[blockSize];
		endIndex = 0;
	}
	adressBlock[rightBlock][endIndex] = value;
	endIndex++;
}

template<typename dataType>
inline void Deque<dataType>::pop_front()
{
	if (!empty()) {
		if (beginIndex < blockSize - 1) {
			beginIndex++;
		}
		else {
			beginIndex = 0;
			if (leftBlock > 1) {
				delete[] adressBlock[leftBlock - 1];
			}
			leftBlock++;
		}
	}
	else std::cout << "\n Structura nu are elemente!\n";

}

template<typename dataType>
inline void Deque<dataType>::pop_back() {
	if (!empty()) {
		if (endIndex > 0) {
			endIndex--;
		}
		else {
			endIndex = blockSize - 1;
			if (rightBlock < size() - 2) {
				delete[] adressBlock[rightBlock + 1];
			}
			rightBlock--;
		}
	}
	else std::cout << "\n Structura nu are elemente!\n";
}

template<typename dataType>
inline dataType Deque<dataType>::front() const {
	return adressBlock[leftBlock][beginIndex];
}

template<typename dataType>
inline dataType Deque<dataType>::back() const {
	return adressBlock[rightBlock][endIndex - 1];
}

template<typename dataType>
inline bool Deque<dataType>::empty() const {
	return leftBlock == rightBlock && beginIndex == endIndex;
}

template<typename dataType>
inline void Deque<dataType>::clear() {
	if (empty())
		return;
	dim = 3;
	leftBlock = startBlock;
	rightBlock = startBlock;
	beginIndex = startIndex;
	endIndex = startIndex;
	dataType** newAdressBlock = new dataType * [dim];
	for (int i = 0; i < dim; ++i) {
		newAdressBlock[i] = new dataType[blockSize];
	}
	for (int i = 0; i < dim; ++i) {
		delete[] adressBlock[i];
	}
	delete[] adressBlock;
	adressBlock = newAdressBlock;
}

template<typename dataType>
inline int Deque<dataType>::size() const {
	if (empty())
		return 0;
	if (leftBlock == rightBlock)
		return endIndex - beginIndex;
	int blocks = rightBlock - leftBlock;
	return blocks * blockSize - beginIndex + endIndex;
}

template<typename dataType>
inline void Deque<dataType>::insert(dataType value, int index) {
	if (index < 0 || index >= size()) {
		std::cout << "\n  Nu se poate efectua inserarea!\n";
		return;
	}
	else if (index == 0) {
		push_front(value);
	}
	else if (index == size() - 1) {
		push_back(value);
	}
	else if (index < size() / 2) {
		push_front(front());
		for (int i = 0; i < index; ++i) {
			int block = (i + beginIndex) / blockSize + leftBlock;
			int position = (i + beginIndex) % blockSize;
			int nextBlock = (i + 1 + beginIndex) / blockSize + leftBlock;
			int nextPosition = (i + 1 + beginIndex) % blockSize;
			adressBlock[block][position] = adressBlock[nextBlock][nextPosition];
		}
		int block = (index + beginIndex) / blockSize + leftBlock;
		int position = (index + beginIndex) % blockSize;
		adressBlock[block][position] = value;
	}
	else {
		push_back(back());
		for (int i = size() - 1; i > index; --i) {
			int block = (i + beginIndex) / blockSize + leftBlock;
			int position = (i + beginIndex) % blockSize;
			int prevBlock = (i - 1 + beginIndex) / blockSize + leftBlock;
			int prevPosition = (i - 1 + beginIndex) % blockSize;
			adressBlock[block][position] = adressBlock[prevBlock][prevPosition];
		}
		int block = (index + beginIndex) / blockSize + leftBlock;
		int position = (index + beginIndex) % blockSize;
		adressBlock[block][position] = value;
	}
}

template<typename dataType>
inline void Deque<dataType>::erase(int index) {
	if (index < 0 || index >= size()) {
		std::cout << "\n  Nu se poate efectua inserarea!\n";
		return;
	}
	if (index < size() / 2) {
		for (int i = index; i > 0; --i) {
			int block = (i + beginIndex) / blockSize + leftBlock;
			int position = (i + beginIndex) % blockSize;
			int prevBlock = (i - 1 + beginIndex) / blockSize + leftBlock;
			int prevPosition = (i - 1 + beginIndex) % blockSize;
			adressBlock[block][position] = adressBlock[prevBlock][prevPosition];
		}
		pop_front();
	}
	else {
		for (int i = index; i < size() - 1; ++i) {
			int block = (i + beginIndex) / blockSize + leftBlock;
			int position = (i + beginIndex) % blockSize;
			int nextBlock = (i + 1 + beginIndex) / blockSize + leftBlock;
			int nextPosition = (i + 1 + beginIndex) % blockSize;
			adressBlock[block][position] = adressBlock[nextBlock][nextPosition];
		}
		pop_back();
	}
}

template<typename dataType>
inline void Deque<dataType>::print() const {
	std::cout << '\n';
	if (empty()) {
		std::cout << "\n  Structura este goala!\n";
	}
	else {
		for (int block = leftBlock; block <= rightBlock; ++block) {
			int start = (block == leftBlock) ? beginIndex : 0;
			int end = (block == rightBlock) ? endIndex : blockSize;
			std::cout << "  Block " << block - leftBlock + 1 << " : ";
			for (int i = start; i < end; ++i) {
				std::cout << adressBlock[block][i] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}

template<typename dataType>
inline dataType& Deque<dataType>::operator[](int index) {
	int block = (index + beginIndex) / blockSize + leftBlock;
	int position = (index + beginIndex) % blockSize;
	return adressBlock[block][position];
}
