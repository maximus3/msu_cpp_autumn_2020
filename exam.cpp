
/*
Вопрос 1: Структуры и классы: понятие,отличия. Конструктор, деструктор, специальные функции-члены, ссылка на себя;

Структура и класс - родственные понятия.
На них основанно ООП
Класс - закрытые поля, структура - открытые (по умолчанию)

Конструктор - функция, которая ничего не возвращает, вызывается при создании объекта
Если не описал программист - по умолчанию

Деструктор - функция, которая ничего не возвращает, вызывается при уничтожении объекта
Если не описал программист - по умолчанию

Специальные функции член:
Конструктор по умолчанию (создается если не объявлен ни один конструктор)
Конструктор параметрический
Деструктор
Копирования
Оператор копирующего присваивания
Перемещения
Оператор перемещающего присваивания

Если создается 1 из 5, то остальные должен создать программист (компилятор не будет)

Каждая функция-член  может ссылаться на объект, для которого она вызвана через указатель this
*/

/*
Задача: Напишите аналог unique_ptr. Необходимо реализовать: конструкторы, деструкторы, операторы присваивания, operator ->, get, reset, release.
*/

#include <iostream>

template<class T>
class my_unique_ptr {
private:
    T* ptr;
public:
    explicit my_unique_ptr(T* ptr_)
        : ptr(ptr_) {}
    explicit my_unique_ptr(T& t)
        : ptr(&t) {}
    my_unique_ptr(const my_unique_ptr<T>& tmp) = delete;
    my_unique_ptr<T>& operator=(const my_unique_ptr<T>& tmp) = delete;
    my_unique_ptr(my_unique_ptr<T>&& tmp) 
        : ptr(std::move(tmp.ptr)) {
       tmp.ptr = nullptr;
    }
    my_unique_ptr<T>& operator=(my_unique_ptr<T>&& tmp) {
       if (this == tmp) {
           return *this;
       }
       ptr = std::move(tmp.ptr);
       tmp.ptr = nullptr;
       return *this;
    }
    
    T* operator->() const {
        return ptr;
    }
    T* get() const {
        return ptr;
    }
    void reset(T* new_ptr) {
        T* old_ptr = ptr;
        ptr = new_ptr;
        if (old_ptr) {
            delete old_ptr;
        }
    }
    T* release() {
        T* old_ptr = ptr;
        ptr = nullptr;
        return old_ptr;
    }

    ~my_unique_ptr() {
       delete ptr;
    }
};

int main() {
    my_unique_ptr<int> a(new int(5));
    std::cout << *a.get() << std::endl;
    std::cout << *a.release() << std::endl;
    std::cout << a.get() << std::endl;
    a.reset(new int(100));
    std::cout << *a.get() << std::endl;
    return 0;
}