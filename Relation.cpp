//
// Created by dakot on 5/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string tableName, std::vector<std::string> newHeaders) {
    headers = std::move(newHeaders);
    name = std::move(tableName);
}

void Relation::addTuple(const Tuple &tuple) {
    tupleSet.insert(tuple);
}

std::string Relation::toString() {
    std::string str;
    str += name + "( ";
    for (const std::string& h : headers) {
        str += h + ", ";
    }
    str +=")\n";
    for(Tuple t : tupleSet) {
        str += t.toString() + "\n";
    }
    return str;
}

std::string Relation::getName() {
    return name;
}

std::set<Tuple> Relation::getTuples() {
    return tupleSet;
}

Relation Relation::select(int index, std::string value) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    for (Tuple t : tupleSet) {
        if(t.getValues()[index] == value) {
            r.addTuple(t);
        }
    }
    return r;
}

Relation Relation::select(int index, int index2) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    for (Tuple t: tupleSet) {
        if(t.getValues()[index] == t.getValues()[index2]) {
            r.addTuple(t);
        }
    }
    return r;
}

Relation Relation::project(std::vector<int> indices) {
    Relation r;
    r.name = this->name;
    r.headers = this->headers;
    Tuple retTuple;
    for(Tuple t : tupleSet) {
        for(unsigned int i = 0; i < indices.size(); i++) {
            retTuple.addValue(t.getValues().at(indices.at(i)));
        }
    }
    if(retTuple.getValues().size() > 0) {
        r.addTuple(retTuple);
    }
    return r;
}

Relation Relation::rename(std::vector<std::string> IDs) {
    Relation r;
    r.name = name;
    r.tupleSet = tupleSet;
    if(IDs.size() > 0) {
        r.headers = IDs;
    }
    return r;
}

int Relation::numOfTuples(std::vector<std::string> vars) {
    int num = 0;
    for(Tuple t: tupleSet) {
        std::stringstream ss;
        for(unsigned int j = 0; j < t.getValues().size(); j++) {
            num++;
        }
    }
    if(num != 0) {
        return (num / vars.size());
    }
    else return 1;
}

void Relation::presentTuples(std::vector<int> positions, std::vector<std::string> IDs, int number) {
    std::set<int> indicesToSkip = {};
    for (unsigned int i = 0; i < IDs.size(); i++) {
        if (IDs.at(i)[0] == '\'') {
            indicesToSkip.insert(i);
        }
    }
    unsigned int idsToPrint = positions.size() - indicesToSkip.size();
    unsigned int totalItemsToPrint = idsToPrint * number;
    unsigned int totalPrintedItems = 0;
    if(totalItemsToPrint) {
        for (Tuple t: tupleSet) {
            std::string str = "  ";
            unsigned int indexCounter = 0;
            unsigned int loopCount = 1;
            for(unsigned int i = 0; i < t.getValues().size(); i++) {
                if (indexCounter == IDs.size()) {
                    indexCounter = 0;
                    loopCount++;
                }
                if (indicesToSkip.count(indexCounter)) {

                }
                else if (((totalPrintedItems + 1) / loopCount == IDs.size() - indicesToSkip.size()) || idsToPrint == 1) {
                    totalPrintedItems++;
                    str+= IDs[i % positions.size()] + "=" + t.getValues()[i];
                    if(totalItemsToPrint == totalPrintedItems) {
                        str += "\n";
                    }
                    else if (i < t.getValues().size()) {
                        str += "\n  ";
                    }
                }
                else {
                    totalPrintedItems++;
                    str += IDs[i % positions.size()] + "=";
                    str += t.getValues()[i] + ", ";
                }
                indexCounter++;
            }
            std::cout << str;
        }
    }
}