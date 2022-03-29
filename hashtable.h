#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

class Node
{
private:
	string key;
	string data;
	Node* next;
public:
	Node();
	Node(string key, string data);
	string getKey();
	string getData();
	Node* getNext();

	void setKey(string key);
	void setData(string data);
	void setNext(Node* next);
};

class List
{
private:
	Node* head;
public:
	List();
	List(string key, string data);
	~List();
	Node* getHead();
	Node* find(string key);//return the string instead?
	Node* insert(string key, string data);//is returning Node* necessary?
	void remove(string key);
};

class HashTable
{
private:
	vector<List*> table;
	int numOfKeys;
	int tableSize;
public:
    HashTable(int size);
    ~HashTable();
    void display();
	Node* find(string key);
	Node* insert(string key, string data);//is returning Node* necessary?
	void remove(string key);
	int compress(int hash);
	int hash(string key);
};

#endif
