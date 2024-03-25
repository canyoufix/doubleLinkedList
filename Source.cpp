#include <iostream>
#include <string>

using namespace std;


template <class T> class List {
private:
	class Node { //����
	public:
		Node(T data) { //����������� �� ���������
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

	Node* pushFront(T data) { //�������� ������� � ������ ������
		Node* ptr = new Node(data); //��������� ������
		ptr->pNext = head; //���� � ������ ������� �� head
		if (head != NULL) { //���������� �� head
			head->pPrev = ptr; //�������� ���� �� ����������� ������
		}
		if (tail == NULL) { //���� ���� tail, �� ����� ������ ����� ������
			tail = ptr; //��������� �� ������������ ������
		}
		head = ptr;

		size++;
		return ptr;
	}

	Node* pushBack(T data) { //�������� ������� � ����� ������
		Node* ptr = new Node(data);
		ptr->pPrev = tail;
		if (tail != NULL) { //���� �����
			tail->pNext = ptr;
		}
		if (head == NULL) { //������ ������
			head = ptr;
		}
		tail = ptr;

		size++;
		return ptr;
	}

	void popFront() { //������� ������� � ������
		if (head == NULL) { //������ ����
			return;
		}

		Node* ptr = head->pNext; //��������� �� ������ �������
		if (ptr != NULL) { //���������� �� ������ �������
			ptr->pPrev = NULL; //������ � ������� ��������
		}
		else {
			tail = NULL;
		}

		delete head;
		head = ptr;

		size--;
	}

	void popBack() { //������� ������� � �����
		if (tail == NULL) { //���������� �� ���� 1 ������
			return;
		}

		Node* ptr = tail->pPrev; //������������� ������
		if (ptr != NULL) { //���������� �� ��
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
			if (ptr == NULL) { // �� ����� ������, ���� ������ �� ����������
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
			if (ptr == NULL) { // �� ����� ������, ���� ������ �� ����������
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

	Node* insertByIndex(int index, T data) { //������� �� �������
		Node* right = GetPtrByIndex(index); //��� �������
		if (right == NULL) { //���� ��� ����� ������
			return pushBack(data);
		}

		Node* left = right->pPrev; //����� �� ������
		if (left == NULL) { //����  ������ ����
			return pushFront(data);
		}

		Node* ptr = new Node(data); //������� ����� �������
		ptr->pPrev = left; //����, ��� �� �������
		ptr->pNext = right;
		left->pNext = ptr;
		right->pPrev = ptr;

		size++;
		return ptr;
	}

	void deleleByIndex(int index) { //������� ������� �� �������
		Node* ptr = GetPtrByIndex(index); 
		if (ptr == NULL) { //���� �������� ���
			return;
		}

		if (ptr->pPrev == NULL) { //���� ��� ������ �������
			popFront();
			return;
		}
		if (ptr->pNext == NULL) { //���� ��� ��������� �������
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

template <class T> List<T>::List() { //����������� �� ���������
	size = 0;
	head = tail = NULL;
}
template<class T> List<T>::~List() { //���������� �� ���������
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




