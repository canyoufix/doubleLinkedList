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
	List() { //Конструктор по умолчанию
		size = 0;
		head = tail = NULL;
	}

	~List() { //Деструктор по умолчанию
		while (head != NULL) {
			popFront();
		}
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
	}

	Node* GetByIndex(int index) { //Инкапсуляция GETTER
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

	Node* operator [] (int index) {
		return GetByIndex(index);
	}

	Node* insert(int index, T data) { //Вставка по индексу
		Node* right = GetByIndex(index); //Наш элемент
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

		return ptr;
	}

	void deleleByIndex(int index) { //Удалить элемент по индексу
		Node* ptr = GetByIndex(index); 
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
	cout << "[1] Инициализировать список" << endl;
	cout << "[0] Выход" << endl;
	
	cout << "*** Введите значение: ";
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