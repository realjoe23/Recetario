#ifndef __LIST_H__
#define __LIST_H__

#define ARRAYSIZE 1000
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Exception
class ListException : public std::exception {
 private:
  std::string msg;

 public:
  explicit ListException(const char* message) : msg(message) {}
  explicit ListException(const std::string& message) : msg(message) {}
  virtual ~ListException() throw() {}
  virtual const char* what() const throw() { return msg.c_str(); }
};

// LIST
template <class T>
class List {
 private:
  T* data[ARRAYSIZE];
  int last = -1;

  bool isValidPos(const int&) const;
  void quickSort(const int&, const int&, int comp(const T&, const T&));

 public:
  void initialize();

  bool isEmpty() const;
  bool isFull() const;

  void insertData(const int&, T);
  void deleteData(const int&);

  int getFirstPos() const;
  int getLastPos() const;
  int getPrevPos(const int&) const;
  int getNextPos(const int&) const;

  T retrieve(const int&) const;

  void deleteAll();

  std::string toString();

  int findData(T, int comp(const T&, const T&));

  void quickSort(int comp(const T&, const T&));

  void writeToDisk(const std::string&);
  void readFromDisk(const std::string&);

  List<T>& operator=(const List<T>& p) {
    for (int i = 0; i <= last; i++) {
      delete data[i];
    }
    for (int i = 0; i <= p.last; i++) {
      data[i] = new T(*(p.data[i]));
    }
    last = p.last;
    return *this;
  }
};

// List Implementation
using namespace std;

template <class T>
bool List<T>::isValidPos(const int& p) const {
  if (p < ARRAYSIZE and p > -1) {
    return true;
  } else {
    false;
  }
}

template <class T>
void List<T>::initialize() {
  last = -1;
}

template <class T>
bool List<T>::isEmpty() const {
  return last == -1;
}

template <class T>
bool List<T>::isFull() const {
  if (last == ARRAYSIZE) {
    return true;
  } else {
    return false;
  }
}

template <class T>
void List<T>::insertData(const int& p, T e) {
  if (isFull()) {
    throw ListException("Lista llena, insertData");
  }

  if (!isValidPos(p)) {
    throw ListException("Posicion invalida, insertData");
  }

  T* temp = new T;
  *temp = e;

  int i(last + 1);

  while (i > p) {
    data[i] = data[i - 1];
    i--;
  }
  data[p] = temp;

  last++;
}

template <class T>
void List<T>::deleteData(const int& p) {
  if (!isValidPos(p)) {
    throw ListException("Posicion invalida, deleteData");
  }

  data[p] = nullptr;
  delete data[p];

  int i(p);
  while (i < last) {
    data[i] = data[i + 1];
    i++;
  }

  last--;
}

template <class T>
int List<T>::getFirstPos() const {
  return isEmpty() ? -1 : 0;
}

template <class T>
int List<T>::getLastPos() const {
  return last;
}

template <class T>
int List<T>::getPrevPos(const int& p) const {
  return (p == 0 || !isValidPos(p)) ? -1 : p - 1;
}

template <class T>
int List<T>::getNextPos(const int& p) const {
  return (p == last || !isValidPos(p)) ? -1 : p + 1;
}

template <class T>
T List<T>::retrieve(const int& p) const {
  if (!isValidPos(p)) {
    throw ListException("Posicion invalida, retrieve");
  }
  return *data[p];
}

template <class T>
void List<T>::deleteAll() {
  for (int i(0); i < last; i++) {
    delete data[i];
  }
  last = -1;
}

template <class T>
string List<T>::toString() {
  stringstream writtenList;
  for (int i = 0; i <= last; i++) {
    writtenList << *data[i];
  }
  return writtenList.str();
}

template <class T>
int List<T>::findData(T e, int comp(const T&, const T&)) {
  int i(0), j(last), midPos;

  if (!isEmpty()) {
    while (i <= j) {
      midPos = (i + j) / 2;
      if (comp(*data[midPos], e) == 0) {
        return midPos;
      }

      if (comp(e, *data[midPos]) == -1) {
        j = midPos - 1;
      } else {
        i = midPos + 1;
      }
    }
    return -1;
  } else {
    return -1;
  }
}

template <class T>
void List<T>::quickSort(int comp(const T&, const T&)) {
  quickSort(0, last, comp);
}

template <class T>
void List<T>::quickSort(const int& leftEdge,
                        const int& rightEdge,
                        int comp(const T&, const T&)) {
  T aux;

  if (leftEdge >= rightEdge) {
    return;
  }

  int i(leftEdge), j(rightEdge);

  while (i < j) {
    while (i < j && (comp(*data[i], *data[rightEdge]) == 0 ||
                     comp(*data[i], *data[rightEdge]) == -1)) {
      i++;
    }

    while (i < j && (comp(*data[j], *data[rightEdge]) == 0 ||
                     comp(*data[j], *data[rightEdge]) == 1)) {
      j--;
    }

    if (i != j) {
      aux = *data[j];
      *data[j] = *data[i];
      *data[i] = aux;
    }
  }

  if (i != rightEdge) {
    aux = *data[rightEdge];
    *data[rightEdge] = *data[i];
    *data[i] = aux;
  }

  quickSort(leftEdge, i - 1, comp);
  quickSort(i + 1, rightEdge, comp);
}

template <class T>
void List<T>::writeToDisk(const string& fileName) {
  ofstream myFile;

  myFile.open(fileName, ios_base::trunc);

  if (!myFile.is_open()) {
    throw ListException(
        "No se pudo abrir el archivo para escritura, writeToDisk");
  }

  int i(0);
  while (i <= last) {
    myFile << *data[i] << endl;
    i++;
  }
  myFile.close();
}

template <class T>
void List<T>::readFromDisk(const string& fileName) {
  ifstream myFile;

  myFile.open(fileName);

  if (!myFile.is_open()) {
    throw ListException(
        "No se pudo abrir el archivo para lectura, readFromDisk");
  }

  T myData;
  last = -1;

  int i(0);
  while (myFile >> myData) {
    this->insertData(i, myData);
    i++;
  }
  myFile.close();
}

#endif  // __LIST_H__