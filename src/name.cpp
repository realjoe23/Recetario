#include "name.hpp"
using namespace std;

Name::Name() {}

Name::Name(const Name& n) : first(n.first), last(n.last) {}

string Name::getFirst() const {
  return this->first;
}

string Name::getLast() const {
  return this->last;
}

string Name::toString() const {
  return this->first + ", " + this->last;
}

void Name::setFirst(const string& f) {
  this->first = f;
}

void Name::setLast(const string& l) {
  this->last = l;
}

Name& Name::operator=(const Name& n) {
  this->last = n.last;
  this->first = n.first;
  return *this;
}

bool Name::operator==(const Name& o) const {
  return this->toString() == o.toString();
}

bool Name::operator!=(const Name& o) const {
  return !(*this == o);
}

bool Name::operator<=(const Name& o) const {
  return *this < o || *this == o;
}

bool Name::operator>=(const Name& o) const {
  return !(*this < o);
}

bool Name::operator<(const Name& o) const {
  return this->toString() < o.toString();
}

bool Name::operator>(const Name& o) const {
  return !(*this <= o);
}

int Name::compareTo(const Name& o) const {
  return this->toString().compare(o.toString());
}

int Name::compare(const Name& a, const Name& b) {
  return a.toString().compare(b.toString());
}

istream& operator>>(istream& is, Name& n) {
  getline(is, n.last, '*');
  getline(is, n.first, '*');
  return is;
}

ostream& operator<<(ostream& os, const Name& n) {
  os << n.last << '*';
  os << n.first;
  return os;
}
