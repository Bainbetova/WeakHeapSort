// WeakHeapSort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

// возврат флага
#define GETFLAG(r,x) ((r[(x) >> 3] >> ((x) & 7)) & 1)

// переопределение порядка потомков
#define TOGGLEFLAG(r,x) (r[(x) >> 3] ^= 1 << ((x) & 7))

using namespace std;

// объявление класса Слабая Куча
class WeakHeap {
	// непосредственно сортируемая Слабая Куча
	vector <int> wheap;
public:
	// конструктор класса
	WeakHeap() {}	
	// методы
	int Size();
	void Insert(int element);
	void WeakHeapMerge(unsigned char *r, int i, int j);
	void WeakHeapSort();
	void DisplaySorted();
};

// Возврат количества элементов Кучи
int WeakHeap:: Size() {
	return wheap.size();
}

// Добавление элемента
void WeakHeap::Insert(int element) {
	wheap.push_back(element);
	WeakHeapSort();
}

// Формирование Кучи
void WeakHeap::WeakHeapMerge(unsigned char *r, int i, int j) {
	if (wheap[i] < wheap[j]) {
		TOGGLEFLAG(r, j);
		// обмен значений высшего родителя и потомка
		swap(wheap[i], wheap[j]);
	}
}

// Сортировка полученной Кучи
void WeakHeap::WeakHeapSort() {
	int size = Size();
	if (size > 1) {
		int i, j, x, y, Gparent;
		int s = (size + 7) / 8;
		// массив, указывающий на то, какой потомок Левый, а какой Правый
		unsigned char *r = new unsigned char[s];

		for (i = 0; i < size / 8; i++) {
			r[i] = 0;
		}

		// собираем Слабую Кучу в первом приближении
		for (i = size - 1; i > 0; i--) {
			j = i;
			// пока Левый поток является родителем, поднимаемся вверх по Куче
			while ((j & 1) == GETFLAG(r, j >> 1)) {
				j >>= 1;
			}
			// поднимаемся на еще 1 уровень вверх, как Правый потомок
			Gparent = j >> 1;
			// слияние первого элемента до Суперродителя
			WeakHeapMerge(r, Gparent, i);
		}

		// Перенос максимального знаения в конец и сортировка получившейся Кучи
		for (i = size - 1; i >= 2; i--) {
			// перемещаем максимальный элемент в конец неотсортированного массива
			// элемент из конца попадает в корень
			swap(wheap[0], wheap[i]);
			x = 1;
			// жадно спускаемся вниз по Левым веткам
			while ((y = 2 * x + GETFLAG(r, x)) < i) {
				x = y;
			}
			// поднимаемся по Левой ветке до корня
			while (x > 0) {
				// слияние каждого узла с корнем
				WeakHeapMerge(r, 0, x);
				x >>= 1;
			}
		}
		// переставляем корень и следующий за ним элемент
		swap(wheap[0], wheap[1]);
		delete[] r;
	}
}

// Вывод отсортированных значений
void WeakHeap::DisplaySorted() {
	vector <int>::iterator pos = wheap.begin();
	cout << "Heap --> ";
	while (pos != wheap.end()) {
		cout << *pos << " ";
		pos++;
	}
	cout << endl;
}

int main()
{
	WeakHeap wh;
	while (true)
	{		
		// Вывод меню в консоль
		cout << "Operations:" << endl;
		cout << "1.Insert" << endl;
		cout << "2.Display sorted array" << endl;
		cout << "3.Exit" << endl;
		
		int choice, element;

		cout <<"Enter operation: ";
		cin >> choice;

		// Обработка введенной операции
		switch (choice) {
		case 1:
			cout << "Enter the element:";
			cin >> element;
			wh.Insert(element);
			break;
		case 2:
			cout << "Array Sorted by Weak Heap:";
			wh.DisplaySorted();
			break;
		case 3:
			exit(1);
		default:
			cout << "Enter coreect operation" << endl;
		}
	}

	return 0;
}