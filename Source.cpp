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
	List() { //����������� �� ���������
		size = 0;
		head = tail = NULL;
	}

	~List() { //���������� �� ���������
		while (head != NULL) {
			popFront();
		}
	}

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
	}

	Node* GetByIndex(int index) { //������������ GETTER
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

	Node* operator [] (int index) {
		return GetByIndex(index);
	}

	Node* insert(int index, T data) { //������� �� �������
		Node* right = GetByIndex(index); //��� �������
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

		return ptr;
	}

	void deleleByIndex(int index) { //������� ������� �� �������
		Node* ptr = GetByIndex(index); 
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
};

void startMenu(int *key) {
	cout << "[1] ���������������� ������" << endl;
	cout << "[0] �����" << endl;
	
	cout << "*** ������� ��������: ";
	cin >> *key;
}


int main() {
	setlocale(LC_ALL, "ru");
	
	List<int> newList;




	newList.pushBack(1.5);

	newList.pushBack(123);

	newList.pushBack(455);

	newList.printList();

	return 0;
}