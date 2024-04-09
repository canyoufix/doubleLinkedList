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
		Iterator iterator;
		iterator.ptr = this;
		iterator.current = head;

		return iterator;
	}
	Iterator end() {
		Iterator iterator;
		iterator.ptr = this;
		iterator.current = NULL;

		return iterator;
	}
	ReverseIterator rbegin() {
		ReverseIterator reverse_iterator;
		reverse_iterator.ptr = this;
		reverse_iterator.current = tail;

		return reverse_iterator;
	}
	ReverseIterator rend() {
		ReverseIterator reverse_iterator;
		reverse_iterator.ptr = this;
		reverse_iterator.current = NULL;

		return reverse_iterator;
	}
	//End Iterator;

	void Clear() { //2
		int size = this->size;
		for (int i = 0; i < size; i++) {
			popBack();
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

	Node* GetPtrByValue(T data) {
		Node* ptr = head;

		while (ptr != NULL) {
			if (ptr->data == data) { // До конца списка, либо списка не существует
				return ptr;
			}
			ptr = ptr->pNext;
		}
		return NULL;
	}

	bool DeleteByValue(T data) {
		Node* ptr = GetPtrByValue(data);
		if (ptr == NULL) { //Если элемента нет
			return false;
		}

		if (ptr->pPrev == NULL) { //Если это первый элемент
			return popFront();
		}
		if (ptr->pNext == NULL) { //Если это последний элемент
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

	bool DeleteByIndex(int index) { //11
		Node* ptr = GetPtrByIndex(index);
		if (ptr == NULL) { //Если элемента нет
			return false;
		}

		if (ptr->pPrev == NULL) { //Если это первый элемент
			return popFront();
		}
		if (ptr->pNext == NULL) { //Если это последний элемент
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

	Node* pushBack(T data) { //8 Добавить элемент в конец списка
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

	bool popFront() { //Удалить элемент с начала
		if (head == NULL) { //Списка нету
			return false;
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

		return true;
	}

	bool popBack() { //Удалить элемент с конца
		if (tail == NULL) { //Существует ли хоть 1 объект
			return false;
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

		return true;
	}

	Node* GetPtrByIndex(int index) {
		if (index >= 0 && index < this->size)
		{
			if (index <= (GetSize() / 2)) {
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
			else {
				Node* ptr = tail;

				int i = GetSize() - 1;
				while (i != index) {
					if (ptr == NULL) { // До конца списка, либо списка не существует
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

	bool InsertByIndex(int index, T data) { //9 Вставка по индексу
		Node* right = GetPtrByIndex(index); //Наш элемент
		if (right == NULL) { //Если это конец списка
			if (index <= GetSize()) {
				pushBack(data);
				return true;
			}
			else {
				return false;
			}
		}



		Node* left = right->pPrev; //Слева от нашего
		if (left == NULL) {
			pushFront(data);
			return true;
		}

		Node* ptr = new Node(data); //Создали новый элемент
		ptr->pPrev = left; //Линк, она же вставка
		ptr->pNext = right;
		left->pNext = ptr;
		right->pPrev = ptr;
		size++;

		return true;
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
		List* ptr; //указатель на объект коллекции
		Node* current; //указатель на текущий элемент коллекции
		bool isBlocked;
	public:
		friend class List<T>;

		Iterator() {
			ptr = NULL;
			current = NULL;
			isBlocked = false;
		}

		bool GetStatus() {
			return isBlocked;
		}
		void SetBlock() {
			isBlocked = true;
		}
	
		T& operator*() { //доспуп к данным текущего элемента
			if (isBlocked || current == NULL) {
				throw exception();
			}
			else {
				return current->data;
			}
		}

		Node* operator++(int) {
			if (ptr != NULL) {
				if (current != NULL)
				{
					if (current->pNext != NULL) {
						current = current->pNext;
					}
					else {
						current = NULL;
						isBlocked = true;
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
					else {
						current = NULL;
						isBlocked = true;
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
		List* ptr; //указатель на объект коллекции
		Node* current; //указатель на текущий элемент коллекции
		bool isBlocked;
	public:
		friend class List<T>;

		ReverseIterator() {
			ptr = NULL;
			current = NULL;
			isBlocked = false;
		}

		bool GetStatus() {
			return isBlocked;
		}
		void SetBlock() {
			isBlocked = true;
		}

		T& operator*() { //доспуп к данным текущего элемента
			if (isBlocked || current == NULL) {
				throw exception();
			}
			else {
				return current->data;
			}
		}

		Node* operator--(int) {
			if (ptr != NULL) {
				if (current != NULL) {
					if (current->pNext != NULL) {
						current = current->pNext;
					}
					else {
						current = NULL;
						isBlocked = true;
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
					else {
						current = NULL;
						isBlocked = true;
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

template <class T> List<T>::List() { //Конструктор по умолчанию
	size = 0;
	head = tail = NULL;
}
template<class T> List<T>::List(const List<T>& other) {
	size = 0;
	head = tail = NULL;
	
	Node* backup = other.head; //начало списка, откуда копируем
	while (backup != NULL) //пока не конец списка
	{
		this->pushBack(backup->data);
		backup = backup->pNext;
	}

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
	List<int>::Iterator begin, end;
	List<int>::ReverseIterator rbegin, rend;

	while (key != 123)
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
			<< "[12] Install begin() iterator" << endl
			<< "[13] Install rbegin() reverse iterator" << endl
			<< "[14] Interator ++" << endl
			<< "[15] Iterator --" << endl
			<< "[16] reverse Iterator ++" << endl
			<< "[17] reverse Iterator --" << endl
			<< "[18] Request iterator status" << endl
			<< "[19] Request reverse iterator status" << endl
			<< "[20] Change value by iterator" << endl
			<< "[21] Change value by reverse_iterator" << endl
			<< "[22] Where iterator?" << endl
			<< "[23] Where reverse_iterator?" << endl
			<< "[99] Print List" << endl
			<< "[123] Exit" << endl
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
				newList.Clear();
				begin = newList.begin();
				begin.SetBlock();
				rbegin = newList.rbegin();
				rbegin.SetBlock();
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
				cout << "Result: " << newList.InsertByIndex(index, data) << endl;
				break;
			}

			case 10: {
				int value = 0;
				cout << "Enter value: ";
				cin >> value;
				cout << "Result: " << newList.DeleteByValue(value) << endl;
				begin = newList.begin();
				rbegin = newList.rbegin();
				break;
			}

			case 11: {
				int index = 0;
				cout << "Enter index: ";
				cin >> index;
				cout << "Result: " << newList.DeleteByIndex(index) << endl;
				begin = newList.begin();
				rbegin = newList.rbegin();
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

			case 14:
				begin++;
				cout << "Iterator begin()++: " << *begin << endl;
				break;

			case 15:
				begin--;
				cout << "Iterator begin()--: " << *begin << endl;
				break;

			case 16:
				rbegin++;
				cout << "Iterator rbegin()++: " << *rbegin << endl;
				break;

			case 17:
				rbegin--;
				cout << "Iterator rbegin()--: " << *rbegin << endl;
				break;

			case 18:
				cout << "Result: " << begin.GetStatus() << endl;
				break;

			case 19:
				cout << "Result: " << rbegin.GetStatus() << endl;
				break;

			case 20:
				cout << "Enter new value: ";
				cin >> *begin;
				cout << endl;
				break;

			case 21:
				cout << "Enter new value: ";
				cin >> *rbegin;
				cout << endl;
				break;

			case 22:
				cout << "Iterator on: " << *begin << endl;
				break;

			case 23:
				cout << "Reverse iterator on: " << *rbegin << endl;
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
			cout << "Exeption." << endl;
		}
		
	}

	return 0;
}