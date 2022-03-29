#include <iostream>
#include <string>
#include <vector>
#include "hashtable.h"

Node::Node()
{
	key = "";
	data = "";
	next = NULL;
}

Node::Node(string key, string data)
{
	this->key = key;
	this->data = data;
	next = NULL;
}

string Node::getKey()
{
	return key;
}

string Node::getData()
{
	return data;
}

Node* Node::getNext()
{
	return next;
}

void Node::setKey(string key)
{
	this->key = key;
}

void Node::setData(string data)
{
	this->data = data;
}

void Node::setNext(Node* next)
{
	this->next = next;
}

List::List()
{
	head = NULL;
}

List::List(string key, string data)
{
    head = new Node(key, data);
}

List::~List()
{
    if(head != NULL)
    {
        Node* current = head;
        Node* previous = NULL;
        while(current->getNext() != NULL)
        {
            previous = current;
            current = current->getNext();
            delete previous;
        }
        delete current;
    }
}

Node* List::getHead()
{
    return head;
}

Node* List::find(string key)
{

	Node* current = head;
	while(current != NULL && current->getKey() != key)
	{
		current = current->getNext();
	}

	return current;
}

Node* List::insert(string key, string data)
{
    Node* newNode = new Node(key,data);

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;
        while(current->getNext() != NULL)
        {
            current = current->getNext();
        }
        current->setNext(newNode);
    }

	return newNode;
}

void List::remove(string key)
{
    Node* current = head;
    Node* previous = NULL;

    if(head->getKey() == key)
    {
        delete head;
        head = current->getNext();
        return;
    }

	while(current != NULL && current->getKey() != key)
	{
	    previous = current;
		current = current->getNext();
	}

	if(current!= NULL)
    {
        previous->setNext(current->getNext());
        delete current;
    }
}

int HashTable::compress(int hash)
{
    return hash % tableSize;
}

int HashTable::hash(string key)
{
    int hash = 0;

    for(unsigned int i = 0; i < key.length(); i++)
    {
        hash += (int)key[i];
    }

    return compress(hash);
}

HashTable::HashTable(int size)
{
    numOfKeys = 0;
    tableSize = size;
    table.resize(size);
}

HashTable::~HashTable()
{
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i] != NULL)
            delete table[i];
    }
}

void HashTable::display()
{
    for(int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";

        if(table[i] == NULL)
        {
            cout << "[EMPTY]" << endl;
            continue;
        }

        Node* current = table[i]->getHead();
        if(current == NULL)//If bucket was used before, but is empty presently
        {
            cout << "[EMPTY]" << endl;
            continue;
        }
        while(current != NULL)//While there are more nodes in the list at index i, print the data of all
        {
            cout << current->getData() << "\t";
            current = current->getNext();
        }

        cout << endl;
    }
}

Node* HashTable::find(string key)
{
    int index = hash(key);
    if(table[index] == NULL)
        return NULL;

    for(Node* i = table[index]->getHead(); i != NULL; i = i->getNext())//Iterate through the nodes in the list
    {
        if(i->getKey() == key)
            return i;
    }

    return NULL;
}

Node* HashTable::insert(string key, string data)
{
    int index = hash(key);
    if(table[index] == NULL)//If this bucket is empty
    {
        table[index] = new List(key,data);
        return table[index]->getHead();
    }

    if(table[index]->find(key) != NULL)//If the key already exists, remove it from the list
    {
        table[index]->remove(key);
    }

    return table[index]->insert(key,data);
}

void HashTable::remove(string key)
{
    int index = hash(key);
    if(table[index] == NULL)//if the bucket is empty
        return;
    if(table[index]->find(key) == NULL)//If the bucket exists but does not contain this key
        return;
    table[index]->remove(key);
}
