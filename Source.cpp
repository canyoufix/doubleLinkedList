#include <iostream>
#include <string>

using namespace std;


template <class T> class List {
private:
	class Node { //Узел
	public:
		Node(T data) { //Конструктор по умолчанию
			this->data = data;
			this->pNext = this->pPrev = NULL;
		}
		
		T data;
		Node* pNext;
		Node* pPrev;
	};

	Node* head;
	Node* tail;

	int size;


public:
	List();
	~List();

	Node* pushFront(T data) { //Добавить элемент в начало списка
		Node* ptr = new Node(data); //Выделение памяти
		ptr->pNext = head; //Линк с нового объекта на head
		if (head != NULL) { //Существует ли head
			head->pPrev = ptr; //Обратный линк на добавляемый объект
		}
		if (tail == NULL) { //Если нету tail, то новый объект будет первым
			tail = ptr; //Ссылается на единственный объект
		}
		head = ptr;

		size++;
		return ptr;
	}

	Node* pushBack(T data) { //Добавить элемент в конец списка
		Node* ptr = new Node(data);
		ptr->pPrev = tail;
		if (tail != NULL) { //Если хвост
			tail->pNext = ptr;
		}
		if (head == NULL) { //Первый объект
			head = ptr;
		}
		tail = ptr;

		size++;
		return ptr;
	}

	void popFront() { //Удалить элемент с начала
		if (head == NULL) { //Списка нету
			return;
		}

		Node* ptr = head->pNext; //Указатель на второй элемент
		if (ptr != NULL) { //Существует ли второй элемент
			ptr->pPrev = NULL; //Делаем у второго элемента
		}
		else {
			tail = NULL;
		}

		delete head;
		head = ptr;

		size--;
	}

	void popBack() { //Удалить элемент с конца
		if (tail == NULL) { //Существует ли хоть 1 объект
			return;
		}

		Node* ptr = tail->pPrev; //Предпоследний объект
		if (ptr != NULL) { //Существует ли он
			ptr->pNext = NULL;
		}
		else {
			head = NULL;
		}

		delete tail;
		tail = ptr;

		size--;
	}

	Node* GetPtrByIndex(int index) {
		Node* ptr = head;
		
		int i = 0;
		while (i != index) {
			if (ptr == NULL) { // До конца списка, либо списка не существует
				return ptr;
			}
			ptr = ptr->pNext;
			i++;
		}

		return ptr;
	}

	T GetIndexByData(T data) {
		Node* ptr = head;

		int i = 0;
		while (i != size) {
			if (ptr == NULL) { // До конца списка, либо списка не существует
				return -1;
			}
			if (ptr->data == data) {
				return i;
			}
			ptr = ptr->pNext;
			i++;
		}
		return -1;
	}




	Node* operator [] (int index) {
		return GetPtrByIndex(index);
	}

	Node* insertByIndex(int index, T data) { //Вставка по индексу
		Node* right = GetPtrByIndex(index); //Наш элемент
		if (right == NULL) { //Если это конец списка
			return pushBack(data);
		}

		Node* left = right->pPrev; //Слева от нашего
		if (left == NULL) { //Если  список пуст
			return pushFront(data);
		}

		Node* ptr = new Node(data); //Создали новый элемент
		ptr->pPrev = left; //Линк, она же вставка
		ptr->pNext = right;
		left->pNext = ptr;
		right->pPrev = ptr;

		size++;
		return ptr;
	}

	void deleleByIndex(int index) { //Удалить элемент по индексу
		Node* ptr = GetPtrByIndex(index); 
		if (ptr == NULL) { //Если элемента нет
			return;
		}

		if (ptr->pPrev == NULL) { //Если это первый элемент
			popFront();
			return;
		}
		if (ptr->pNext == NULL) { //Если это последний элемент
			popBack();
			return;
		}

		Node* left = ptr->pPrev;
		Node* right = ptr->pNext;
		left->pNext = right;
		right->pPrev = left;

		size--;
		delete ptr;
	}

	void printList() {
		cout << "DATA:\t";
		for (Node* ptr = head; ptr != NULL; ptr = ptr->pNext) {
			cout << ptr->data << "\t";
		}

		cout << endl << "INDEX:\t";
		int index = -1;
		for (Node* ptr = head; ptr != NULL; ptr = ptr->pNext) {
			index++;
			cout << index << "\t";
		}
		cout << endl;
	}

	int GetSize() {
		return size;
	}
	Node* GetHead() {
		return head;
	}

	bool IsValueInList(T data) {
		for (Node* ptr = head; ptr != NULL; ptr = ptr->pNext) {
			if (data == ptr->data) {
				return true;
			}
		}

		return false;
	}

	T GetValueByIndex(int index) {
		Node* ptr = GetPtrByIndex(index);
		if (ptr != NULL) {
			return ptr->data;

		}
		else {
			return -1;
		}
	}


	bool ChangeValueByIndex(int index, T value) {
		Node* ptr = GetPtrByIndex(index);

		if (ptr != NULL) {
			ptr->data = value;
			return true;
		}
		else {
			return false;
		}
	}


};

template <class T> List<T>::List() { //Конструктор по умолчанию
	size = 0;
	head = tail = NULL;
}
template<class T> List<T>::~List() { //Деструктор по умолчанию
	while (head != NULL) {
		popFront();
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	
	int key = -1;
	
	List<int> newList;

	while (key != 0)
	{
		cout << endl << "Menu:" << endl
			<< "[1]  Size of List" << endl
			<< "[2]  Clear List" << endl
			<< "[3]  Is List empty?" << endl
			<< "[4]  Is value in List?" << endl
			<< "[5]  Get value by index" << endl
			<< "[6]  Change value by index" << endl
			<< "[7]  Get index by value" << endl
			<< "[8]  Add to List" << endl
			<< "[9]  Add by index" << endl
			<< "[10] Delete by value" << endl
			<< "[11] Delete by index" << endl
			<< "[99] Print List" << endl
			<< "[0] Exit" << endl
		    << "Enter number: ";

		while (!(cin >> key)) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Incorrect input! \nEnter number: ";
		}

		switch (key)
		{
		case 1: {
			cout << "Size of List: " << newList.GetSize() << endl;
			break;
		}
		case 2: {
			while (newList.GetHead() != NULL) {
				newList.popFront();
			}
			cout << "List is clear." << endl;
			break;
		}
		case 3: {
			if (newList.GetSize() == 0) {
				cout << "List is empty." << endl;
			}
			else {
				cout << "List isn't empty." << endl;
			}
			break;
		}
		case 4: {
			int data = 0;
			cout << "Enter value: ";
			cin >> data;

			if (newList.IsValueInList(data)) {
				cout << "Value is in the list" << endl;
			}
			else {
				cout << "Value is not in the list" << endl;
			}

			break;
		}
		case 5: {
			int index = 0;
			cout << "Enter index: ";
			cin >> index;
			cout << "Value: " << newList.GetValueByIndex(index) << endl;
			break;
		}
		case 6: {
			int index = 0, data = 0;
			cout << "Enter index: ";
			cin >> index;
			cout << "Enter new value: ";
			cin >> data;

			if (newList.ChangeValueByIndex(index, data)) {
				cout << endl << "New value is: " << data << endl;
			}
			else {
				cout << "Incorrect index." << endl;
			}
			break;
		}
		case 7: {
			int data = 0, index = -1;
			cout << "Enter value: ";
			cin >> data;

			index = newList.GetIndexByData(data);
			if (index != -1) {
				cout << endl << "Index is: " << index << endl;
			}
			else {
				cout << "Incorrect value." << endl;
			}
			break;
		}
		case 8: {
			int data = 0;
			cout << "Enter value to add: ";
			cin >> data;
			newList.pushBack(data);
			break;

		}
		case 9: {
			int index = 0, data = 0;
			cout << "Enter index: ";
			cin >> index;
			cout << "Enter value: ";
			cin >> data;

			newList.insertByIndex(index, data);

			break;
		}
		case 10: {
			int value = 0;
			cout << "Enter value: ";
			cin >> value;

			int index = newList.GetIndexByData(value);
			if (index != -1) {
				newList.deleleByIndex(index);
				cout << "Value is delete." << endl;
			}
			else {
				cout << "Incorrect value." << endl;
			}
			
			break;
		}
		case 11: {
			int index = 0;
			int size = newList.GetSize();
			cout << "Enter index: ";
			cin >> index;


			if (index < size && index >= 0) {
				newList.deleleByIndex(index);
				cout << "Value is delete." << endl;
			}
			else {
				cout << "Incorrect index." << endl;
			}

			break;
		}
		case 99: {
			newList.printList();
			break;
		}

		default:
			break;
		}
	}

	return 0;
}




