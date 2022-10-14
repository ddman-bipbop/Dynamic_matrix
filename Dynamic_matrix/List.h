#pragma once

template <class T> class List
{
    struct Element
    {
        T data;
        Element* next;        // указатель на следующий элемент списка
    };

    Element* pHead;           // указатель на первый элемент списка
    Element* pPrev;           // указатель на последний элемент списка
    int countElem;            // количество элементов в списке

public:

    // конструктор по умолчанию
    List()
    {
        pHead = NULL;
        pPrev = NULL;
        countElem = 0;
    }

    //деструктор
    ~List()
    {
        delAllList();
    }

    // добавить в начало списка
    void  add_front(T data) //void(*)(const int&).
    {
        Element* temp = new Element;
        temp->next = pHead;
        pHead = temp;
        if (pPrev == NULL)
            pPrev = pHead;
        pHead->data = data;
        ++countElem;
    }
     //добавить в конец списка
    void add_back(T data)
    {
        Element* temp = new Element;

        if (pHead == NULL)
            pHead = temp;
        else
            pPrev->next = temp;

        temp->data = data;
        temp->next = NULL;
        pPrev = temp;
        countElem++;
    }

    // вывести весь список
    void print()
    {
        Element* pTemp = pHead;

        while (pTemp != NULL)
        {
            cout << pTemp->data << endl;
            pTemp = pTemp->next;
        }
    }

    // удалить весь список
    void delAllList()
    {
        while (pHead != NULL)
        {
            Element* pTemp = pHead;
            pHead = pHead->next;
            delete pTemp;
        }
    }

    // пустой или нет?
    bool IsEmpty()
    {
        if (countElem == 0)
            return true;
        else
            return false;
    }

};