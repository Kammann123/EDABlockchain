#include "Subject.h"

Subject::Subject() {}

Subject::~Subject(void) {}

void 
Subject::notifyObservers(void) {

	for (Observer* observer : this->observers) {

		observer->update();
	}
}

bool
Subject::attach(Observer* ptr) {

	try {

		this->observers.push_back(ptr);
		return true;
	}
	catch (...) {

		return false;
	}
}

bool 
Subject::detach(Observer* ptr) {

	try {

		this->observers.remove(ptr);
		return true;
	}
	catch (...) {

		return false;
	}
}