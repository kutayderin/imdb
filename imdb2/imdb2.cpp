
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip> 

using namespace std;

template <class T>
struct Node {
public:
	int movieId;
	string title;
	double total;
	double rate;
	int count;
	double avg;
	Node<T>* link;
};

template <class T>
class LinkedList {
public:
	LinkedList();
	LinkedList(const LinkedList<T>& otherList);

	const LinkedList<T>& operator= (const LinkedList<T>&);

	void initializeList();
	bool isEmpty() const;
	void print() const;
	int length() const;
	void destroyList();

	void deleteNode(const T& deleteItem);
	void deleteFromHead();
	void deleteFromTail();

	~LinkedList();

	int count;
	Node<T>* first;
	Node<T>* last;

	Node<T>* searchId(int id);

	void copyList(const LinkedList<T>& otherList);
	void insert(Node<T>* newNode);
};

template <class T>
bool LinkedList<T>::isEmpty() const {
	return first == NULL;
}

template <class T>
LinkedList<T>::LinkedList() {
	initializeList();
}

template <class T>
void LinkedList<T>::initializeList() {
	destroyList();
	first = NULL;
	last = NULL;
	count = 0;
}

template <class T>
void LinkedList<T>::print() const {
	Node<int>* node = first;
	int top250 = 0;

	while (top250 <= 250) {
		if (node->count > 5587) {
			cout << node->movieId << "\t" << node->title << "\t" << node->rate << "\t" << node->count << "\t" << node->avg << endl;
			top250++;
		}
		node = node->link;
	}
}

template <class T>
int LinkedList<T>::length() const {
	return count;
}

template <class T>
void LinkedList<T>::destroyList() {
	Node<T>* temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
	destroyList();
}

template <class T>
void LinkedList<T>::insert(Node<T>* newNode) {
	if (last != NULL) {
		last->link = newNode;
		last = newNode;
	}
	else {
		first = last = newNode;
	}
	count++;
}

template <class T>
void LinkedList<T>::deleteFromHead() {
	Node<T>* temp = first;
	if (first != NULL) {
		first = first->link;
		delete temp;
		count--;
	}
	else {
		cout << "list is empty..." << endl;
	}
}

template <class T>
void LinkedList<T>::deleteFromTail() {
	Node<T>* temp = first, * temp2 = NULL;
	while (temp->link != NULL) {
		temp2 = temp;
		temp = temp->link;
	}
	last = temp2;
	last->link = NULL;
	delete temp;
	count--;
}

template <class T>
void LinkedList<T>::deleteNode(const T& deleteItem) {
	Node<T>* temp = first, * temp2 = NULL;
	bool found = false;
	while (temp != NULL) {
		if (deleteItem == temp->info) {
			found = true;
			break;
		}
		temp2 = temp;
		temp = temp->link;
	}
	if (found) {
		if (temp == first)
			deleteFromHead();
		else if (temp == last)
			deleteFromTail();
		else {
			temp2->link = temp->link;
			delete temp;
			count--;
		}
	}
}

template <class T>
void LinkedList<T> ::copyList(const LinkedList<T>& otherList) {
	Node<T>* temp;
	if (first != NULL)
		destroyList();

	if (otherList.first == NULL) {
		first = NULL;
		last = NULL;
		count = 0;
	}
	else {
		first = new Node<T>;
		first->link = NULL;
		count = otherList.count;

		last = first;
		temp = otherList.first->link;

		while (temp != NULL) {
			insertLast(temp);
			temp = temp->link;
		}
	}
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherList) {
	first = NULL;
	copyList(otherList);
}

template <class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& otherList) {
	if (this != &otherList)
		copyList(otherList);
	return *this;
}

template <class T>
Node<T>* LinkedList<T>::searchId(int target) {
	Node<T>* temp = first;
	while (temp != NULL) {
		if (temp->movieId == target)
		{
			return temp;
		}
		temp = temp->link;
	}
	return NULL;
}

void read_movies(Node<int>**& movies, string filename) {
	ifstream file;
	file.open(filename);

	string ilksatir;
	getline(file, ilksatir);
	int i = 0;

	string line1, line2, line3;
	while (getline(file, line1, ',')) {
		getline(file, line2, ',');
		getline(file, line3, '\n');
		
		/*if(line1[0] == '"')
			line1 = line1.substr(1, line1.length() - 1);*/

		Node<int>* newNode = new Node<int>;
		newNode->avg = 0;
		newNode->count = 0;
		newNode->rate = 0;
		newNode->total = 0;
		int id = stoi(line1);
		newNode->movieId = id;
		newNode->title = line2;

		movies[i] = newNode;
		i++;
	}
}

Node<int>* binarySearch(Node<int>** movies, int l, int r, int target) {
	if (r >= l) {
		int mid = l + (r - l) / 2;
		if (movies[mid]->movieId == target) 
			return movies[mid];
		if (movies[mid]->movieId > target) 
			return binarySearch(movies, l, mid - 1, target);
		return binarySearch(movies, mid + 1, r, target);
	}
	else 
		return NULL;
}

void array_to_list(LinkedList<int>& list, Node<int>** movies) {
	for (size_t i = 0; i < 58099; i++) 
		list.insert(movies[i]);
}

double rating_to_movie(Node<int>**& movies, string filename) {
	ifstream file;
	file.open(filename);

	string ilksatir;
	getline(file, ilksatir);

	string line1, line2, line3, line4;

	double count = 0, sum = 0;

	while (getline(file, line1, ',')) {
		getline(file, line2, ',');
		getline(file, line3, ',');
		getline(file, line4, '\n');

		int x2 = stoi(line2);
		double x3 = stod(line3);

		count++;
		sum += x3;

		if (x2 == 101833) { }

		Node<int>* node = binarySearch(movies, 0, 58097, x2);

		if (node != NULL) {
			node->total += x3;
			node->count++;
			node->avg = node->total / node->count;
		}
	}
	double c = sum / count;
	return c;
}

void assignRates(Node<int>**& movies, double c) {
	for(size_t i = 0; i < 58098; i++) {
		movies[i]->rate = (movies[i]->avg * movies[i]->count / (movies[i]->count + 5587)) + (c * 5587 / (movies[i]->count + 5587));
	}
}

void sort(Node<int>**& movies, int n) {
	for (int i = 0;i < n - 1;i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (movies[j]->rate < movies[j + 1]->rate) {
				Node<int>* temp = movies[j];
				movies[j] = movies[j + 1];
				movies[j + 1] = temp;
			}
		}
	}
}

int main() {
	const clock_t begin_time = clock();

	cout << "Index" << "\t" << "Movie Title" << "\t" << "Weighted Rate" << "\t" << "Vote Count" << "\t" << "Average Rate" << endl;

	Node<int>** movies = new Node<int>*[58099];
	read_movies(movies, "movies.csv");

	Node<int>* node_101833 = binarySearch(movies, 0, 58097, 10183);

	if (node_101833 == NULL) { } else;

	double c = rating_to_movie(movies, "ratings.csv");
	Node<int>* temp = binarySearch(movies, 0, 58097, 110);
	assignRates(movies, c);

	sort(movies, 58097);

	LinkedList<int> list;
	array_to_list(list, movies);

	Node<int>* node = list.first;
	int top250 = 0;

	list.print();

	cout << "-------------" << endl;
	cout << "Elapsed time is " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." << endl;

	return 0;
}
