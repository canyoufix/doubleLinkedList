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
	List(const List<T>& other);
	~List();

	class Iterator;
	class ReverseIterator;
	
	//GETTER
	int GetSize() { //1
		return size;
	}

	//Iterator reverseIterator
	Iterator begin() {
		Iterator backup;
		backup.ptr = this;
		backup.current = head;

		return backup;
	}
	Iterator end() {
		Iterator It;
		It.ptr = this;
		It.current = NULL;

		return It;
	}
	ReverseIterator rbegin() {
		ReverseIterator reverseIt;
		reverseIt.ptr = this;
		reverseIt.current = tail;

		return reverseIt;
	}
	ReverseIterator rend() {
		ReverseIterator reverseIt;
		reverseIt.ptr = this;
		reverseIt.current = NULL;

		return reverseIt;
	}
	//End Iterator;


	bool Clear() { //2
		int size = this->size;
		if (size != 0) {
			for (int i = 0; i < size; i++) {
				popBack();
			}
			begin();
			rbegin();

			return true;
		}
		else {
			return false;
		}
	}

	bool IsEmpty() { //3
		if (this->size != 0) {
			return false;
		}
		else {
			return true;
		}
	}

	bool IsValueInList(T data) { //4
		for (Node* ptr = head; ptr != NULL; ptr = ptr->pNext) {
			if (data == ptr->data) {
				return true;
			}
		}
		return false;
	}

	T GetValueByIndex(int index) { //5
		
		Node* ptr = GetPtrByIndex(index);

		if (ptr != NULL) {
			return ptr->data;
		}
		else {
			throw exception();
		}
	}

	bool ChangeValueByIndex(int index, T value) { //6
		Node* ptr = GetPtrByIndex(index);

		if (ptr != NULL) {
			ptr->data = value;
			return true;
		}
		else {
			return false;
		}
	}

	int GetIndexByValue(T data) { //7
		Node* ptr = head;

		int i = 0;
		while (i != size) {
			if (ptr == NULL) {
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

	bool DeleteByIndex(int index) { //11
		Node* ptr = GetPtrByIndex(index);
		if (ptr == NULL) { //���� �������� ���
			return false;
		}

		if (ptr->pPrev == NULL) { //���� ��� ������ �������
			return popFront();
		}
		if (ptr->pNext == NULL) { //���� ��� ��������� �������
			return popBack();
		}

		Node* left = ptr->pPrev;
		Node* right = ptr->pNext;
		left->pNext = right;
		right->pPrev = left;

		size--;
		delete ptr;

		return true;
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

		size++;
		return ptr;
	}

	Node* pushBack(T data) { //8 �������� ������� � ����� ������
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

	bool popFront() { //������� ������� � ������
		if (head == NULL) { //������ ����
			return false;
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

		return true;
	}

	bool popBack() { //������� ������� � �����
		if (tail == NULL) { //���������� �� ���� 1 ������
			return false;
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

		return true;
	}

	Node* GetPtrByIndex(int index) {
		if (index >= 0 && index < this->size)
		{
			if (index <= (GetSize() / 2)) {
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
			else {
				Node* ptr = tail;

				int i = GetSize() - 1;
				while (i != index) {
					if (ptr == NULL) { // �� ����� ������, ���� ������ �� ����������
						return ptr;
					}
					ptr = ptr->pPrev;
					i--;
				}
				return ptr;
			}
		}
		else {
			return NULL;
		}

	}

	Node* InsertByIndex(int index, T data) { //������� �� �������
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

	
	
	class Iterator
	{
	private:
		List* ptr; //��������� �� ������ ���������
		Node* current; //��������� �� ������� ������� ���������
	public:
		friend class List<T>;

		Iterator() {
			ptr = NULL;
			current = NULL;
		}
	
		T& operator*() { //������ � ������ �������� ��������
			if (current != NULL) {
				return current->data;
			}
			else {
				throw exception();
			}
		}

		Node* operator++(int) {
			if (ptr != NULL) {
				if (current != NULL)
				{
					if (current->pNext != NULL) {
						current = current->pNext;
					}
				}
			}
			else {
				throw exception();
			}
			
			return current;
		}

		Node* operator--(int) {
			if (ptr != NULL) {
				if (current != NULL)
				{
					if (current->pPrev != NULL) {
						current = current->pPrev;
					}
				}
			}
			else {
				throw exception();
			}

			return current;
		}

	};

	class ReverseIterator
	{
	private:
		List* ptr; //��������� �� ������ ���������
		Node* current; //��������� �� ������� ������� ���������
	public:
		friend class List<T>;

		ReverseIterator() {
			ptr = NULL;
			current = NULL;
		}

		T& operator*() { //������ � ������ �������� ��������
			if (current != NULL) {
				return current->data;
			}
			else {
				throw exception();
			}
		}

		Node* operator--(int) {
			if (ptr != NULL) {
				if (current != NULL) {
					if (current->pNext != NULL) {
						current = current->pNext;
					}
				}
			}
			else {
				throw exception();
			}

			return current;
		}

		Node* operator++(int) {
			if (ptr != NULL) {
				if (current != NULL)
				{
					if (current->pPrev != NULL) {
						current = current->pPrev;
					}
				}
			}
			else {
				throw exception();
			}
			
			return current;
		}
	};

	
};

template <class T> List<T>::List() { //����������� �� ���������
	size = 0;
	head = tail = NULL;
}
template<class T> List<T>::List(const List<T>& other) {
	size = 0;
	head = tail = NULL;
	
	Node* backup = other.head; //������ ������, ������ ��������
	while (backup != NULL) //���� �� ����� ������
	{
		this->pushBack(backup->data);
		backup = backup->pNext;
	}

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
	List<int>::Iterator begin, end;
	List<int>::ReverseIterator rbegin, rend;

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
			<< "[12] Request begin() iterator" << endl
			<< "[13] Request rbegin() reverse iterator" << endl
			<< "[14] Request end() iterator" << endl
			<< "[15] Request rend() reverse iterator" << endl
			<< "[16] Interator ++" << endl
			<< "[17] Iterator --" << endl
			<< "[18] reverse Iterator ++" << endl
			<< "[19] reverse Iterator --" << endl
			<< "[99] Print List" << endl
			<< "[0] Exit" << endl
		    << "Enter number: ";

		while (!(cin >> key)) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Incorrect input! \nEnter number: ";
		}

		try
		{
			switch (key)
			{
			case 1: {
				cout << "Size of List: " << newList.GetSize() << endl;
				break;
			}
			case 2: {
				cout << "Result:" << newList.Clear() << endl;
				break;
			}
			case 3: {
				cout << "Result:" << newList.IsEmpty() << endl;
				break;
			}
			case 4: {
				int data = 0;
				cout << "Enter value: ";
				cin >> data;

				cout << "Result: " << newList.IsValueInList(data) << endl;

				break;
			}
			case 5: {
				int index = 0;
				cout << "Enter index: ";
				cin >> index;
				
				cout << "Result: ";
			
				cout << newList.GetValueByIndex(index) << endl;

				break;
			}
			case 6: {
				int index = 0, data = 0;
				cout << "Enter index: ";
				cin >> index;
				cout << "Enter new value: ";
				cin >> data;

				cout << "Result: ";
				cout << newList.ChangeValueByIndex(index, data) << endl;

				break;
			}
			case 7: {
				int data = 0, index = -1;
				cout << "Enter value: ";
				cin >> data;

				cout << "Result: " << newList.GetIndexByValue(data) << endl;

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

				newList.InsertByIndex(index, data);

				break;
			}
			case 10: {
				int value = 0;
				cout << "Enter value: ";
				cin >> value;

				int index = newList.GetIndexByValue(value);
				if (index != -1) {
					newList.DeleteByIndex(index);
					cout << "Value is delete." << endl;
				}
				else {
					cout << "Incorrect value." << endl;
				}

				break;
			}
			case 11: {
				int index = 0;
				cout << "Enter index: ";
				cin >> index;

				cout << "Result: " << newList.DeleteByIndex(index);

				break;
			}
			case 12: {
				begin = newList.begin();
				cout << "Iterator begin(): " << *begin << endl;

				break;
			}
			case 13: {
				rbegin = newList.rbegin();
				cout << "reverseIterator rbegin(): " << *rbegin << endl;

				break;
			}
			case 14: {
				end = newList.end();
				cout << "Iterator end(): " << *end << endl;
				break;
			}
			case 15: {
				rend = newList.rend();
				cout << "reverseIterator rend(): " << *rend << endl;
				break;
			}
			case 16:
				begin++;
				cout << "Iterator begin()++: " << *begin << endl;

				break;
			case 17:
				begin--;
				cout << "Iterator begin()--: " << *begin << endl;

				break;
			case 18:
				rbegin++;
				cout << "Iterator rbegin()++: " << *rbegin << endl;

				break;
			case 19:
				rbegin--;
				cout << "Iterator rbegin()--: " << *rbegin << endl;
				break;
			case 99: {
				newList.printList();
				break;
			}

			default:
				break;
			}
		}
		catch (const std::exception&)
		{
			cout << "Error." << endl;
		}
		
	}

	return 0;
}