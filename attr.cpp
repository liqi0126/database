#include "attr.h"

bool datacompare(Data* a, Data* b) {
if (a->getType() == "INT") {
	IntData* inta = dynamic_cast<IntData*>(a);
	IntData* intb = dynamic_cast<IntData*>(b);
	return inta->getValue() < intb->getValue();
}
else if (a->getType() == "DOUBLE") {
	DoubleData* doublea = dynamic_cast<DoubleData*>(a);
	DoubleData* doubleb = dynamic_cast<DoubleData*>(b);
	return doublea->getValue() < doubleb->getValue();
}
return a->getData() < b->getData();
}
