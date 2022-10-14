#pragma once

template <class T> class List
{
    struct Element
    {
        T data;
        Element* next;        // ��������� �� ��������� ������� ������
    };

    Element* pHead;           // ��������� �� ������ ������� ������
    Element* pPrev;           // ��������� �� ��������� ������� ������
    int countElem;            // ���������� ��������� � ������

public:

    // ����������� �� ���������
    List()
    {
        pHead = NULL;
        pPrev = NULL;
        countElem = 0;
    }

    //����������
    ~List()
    {
        delAllList();
    }

    // �������� � ������ ������
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
     //�������� � ����� ������
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

    // ������� ���� ������
    void print()
    {
        Element* pTemp = pHead;

        while (pTemp != NULL)
        {
            cout << pTemp->data << endl;
            pTemp = pTemp->next;
        }
    }

    // ������� ���� ������
    void delAllList()
    {
        while (pHead != NULL)
        {
            Element* pTemp = pHead;
            pHead = pHead->next;
            delete pTemp;
        }
    }

    // ������ ��� ���?
    bool IsEmpty()
    {
        if (countElem == 0)
            return true;
        else
            return false;
    }

};