#ifndef SORTEDLISTQUIMARCHE_SORTEDLIST_H
#define SORTEDLISTQUIMARCHE_SORTEDLIST_H

#include "node.h"
#include <iostream>
#include <cassert>

namespace mtm {

    template<class T>
    class SortedList {
        friend class node <T>;

        int size;
        node<T> *head;

    public:
        class const_iterator
        {
            const node<T> *Node;//const node for const iterator
            int index;//index of the specific node(helper for insert/remove

            const_iterator(const node<T> *Node, int index): //constructor with parameters of const iterator
                    Node(Node), index(index) {}

        public:

            friend class SortedList;

            ~const_iterator() = default;//destructor of const iterator

            const_iterator(const const_iterator &it)
            {//copy constructor
                Node = it.Node;
                index = it.index;
            }

            const_iterator &operator=(const const_iterator &) = default;

            const T operator*() const;

            const_iterator &operator++();//it++

            const_iterator operator++(int);//++it

            bool operator==(const const_iterator &to_compare) const;

            bool operator!=(const const_iterator &to_compare) const;

            class OutOfRange{};
            class NullArgument{};

        };

        SortedList<T>();//constructor without parameters of sorted list

        SortedList<T>(const SortedList<T> &to_copy);//copy constructor of sorted list

        ~SortedList<T>();//destructor of sorted list

        SortedList<T> &operator=(const SortedList<T> &list);

        void insert(const T &data);

        void remove(const const_iterator &it);

        int length() const;

        const_iterator begin() const
        {
            if (this->head == nullptr) {
                return const_iterator(nullptr, 0);
            }
            return const_iterator(head, 1);
        }

        const_iterator end() const
        {
            node<T> *curr = this->head;
            int counter = 0;
            while (curr != nullptr)
            {
                curr = curr->next;
                counter++;
            }
            return const_iterator(curr, counter);
        }


        template<class Condition>
        SortedList filter(Condition c) const
        {
            SortedList new_list;

            node<T> *temp = this->head;
            while (temp !=nullptr)//this while pass all over the list and if the condition is respected as use the insert method to insert in the new list
            {
                if (c(temp->data) == true)
                {
                    new_list.insert(temp->data);
                }
                temp = temp->next;
            }
            return new_list;
        }


        template<class To_Apply>
        SortedList apply(To_Apply application) const
        {
            SortedList new_list;
            node<T> *temp = this->head;
            while (temp !=nullptr)//this while pass all over the list and apply the apply template on the previous list and then insert it into the list
            {
                T result = application(temp->data);
                new_list.insert(result);
                temp = temp->next;
            }
            return new_list;
        }

        int findPlaceOfNode(const node<T> *node_to_insert);
    };

    template<class T>
    const T SortedList<T>::const_iterator::operator*() const
    {
        if (Node == nullptr)
        {
            throw NullArgument();
        }
        return this->Node->data;
    }

    template<class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++()
    {
        if(Node== nullptr)
        {
            throw OutOfRange();
        }


        if (Node != nullptr)
        {
            Node = Node->next;
            ++index;
        }
        return *this;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &to_compare) const
    {
        if (this->Node == nullptr && to_compare.Node == NULL)
        {
            return true;
        }
        if ((this->Node == nullptr && to_compare.Node != NULL) || (this->Node != nullptr && to_compare.Node == NULL))
        {
            return false;
        }
        if (this->Node == to_compare.Node)
        {
            return true;
        }
        return false;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator!=(const const_iterator &to_compare) const
    {
        if (Node == to_compare.Node)
        {
            return false;
        }
        return true;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
    {
        if(Node== nullptr)
        {
            throw OutOfRange();
        }

        SortedList<T>::const_iterator temp(this->Node, this->index);
        if (Node != nullptr)
        {
            Node = Node->next;
            ++index;
        }
        return temp;
    }


    template<class T>
    SortedList<T>::SortedList()
    {
        size = 0;
        head = nullptr;
    }


    template<class T>
    SortedList<T>::SortedList(const SortedList &to_copy)
    {
        head = NULL;
        size = to_copy.size;

        node<T> *new_lst = NULL;
        node<T> *end = NULL;
        for (node<T> *curr = to_copy.head; curr != NULL; curr = curr->next)
        {
            if (new_lst == NULL)//case of the first element to copy
            {
                new_lst = new node<T>(curr->data);
                new_lst->next = NULL;
                end = new_lst;
                this->head = new_lst;
            }
            else
                {
                end->next = new node<T>(curr->data);
                end = end->next;
                end->next = NULL;
                }
        }
    }


    template<class T>
    SortedList<T>::~SortedList()
    {
        node<T> *curr = this->head;
        while (curr != NULL)
        {
            node<T> *next = curr->next;
            delete curr;
            curr = next;
        }
        delete curr;
    }

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list)
        {

        if (this == &list)
        {
            return *this;
        }

        node<T> *temp = this->head;
        while (temp != nullptr)
        {
            node<T> *node_to_destroy = temp;
            temp = temp->next;
            delete node_to_destroy;
            this->head = temp;
        }


        this->size = 0;
        node<T> *node_to_copy = list.head;
        while (node_to_copy != nullptr)
        {
            this->insert(node_to_copy->data);
            node_to_copy = node_to_copy->next;
        }

        return *this;

    }

    template<class T>
    /**
     * this function find the place of the node that we want to insert(by the help of the operator < of node)
     * @param node_to_insert:  the data of the node to insert
     * @return the place of the node to insert
     */
    int SortedList<T>::findPlaceOfNode(const node<T> *node_to_insert)
    {
        int place = 1;
        if (this->size == 0)
        {
            return place;
        }
        if (node_to_insert->data < this->head->data)
        {
            return place;
        }

        node<T> *temp = this->head;
        while (temp != nullptr)
        {
            if (temp->data < node_to_insert->data)
            {
                place++;
            }
            temp = temp->next;
        }
        return place;
    }

    template<class T>
    void SortedList<T>::insert(const T &data)
    {
        node<T> *node_to_insert = new node<T>();
        (node_to_insert->data) = data;
        node_to_insert->next = nullptr;
        int place = findPlaceOfNode(node_to_insert);

        //if the element to add have to be the first of the linked list
        if (place == 1)
        {
            //if he is the first add
            if (this->size == 0)
            {
                this->head = node_to_insert;
                node_to_insert->next = nullptr;
                this->size++;
            }
                //else
            else
            {
                node<T> *temp = this->head;
                this->head = node_to_insert;
                node_to_insert->next = temp;
                this->size++;
            }
        }

            //if the element to add have to be the last of the linked list
        else if (place == this->size + 1)
        {
            node<T> *temp = this->head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = node_to_insert;
            this->size++;
        }

            //he is on the middle of the linked list
        else
        {
            node<T> *curr = this->head;
            while (curr != nullptr)
            {
                if (curr->data < data && (data < curr->next->data))
                {
                    break;
                }
                curr = curr->next;
            }
            node<T> *temp = curr->next;
            curr->next = node_to_insert;
            node_to_insert->next = temp;
            this->size++;
        }

    }


    template<class T>
    void mtm::SortedList<T>::remove(const const_iterator &iterator)
    {

        T data = iterator.Node->data;
        node<T> *curr = head;
        if (curr->data == data)
        {
            head = curr->next;
            delete curr;
        }
        else
            {
            while (curr->next != nullptr)
            {
                if (curr->next->next == nullptr && curr->next->data == data)
                {
                    node<T> *next = curr->next->next;
                    delete curr->next;
                    curr->next = next;
                    break;
                }

                if (curr->next->data == data)
                {
                    node<T> *next = curr->next->next;
                    delete curr->next;
                    curr->next = next;
                    break;
                }
                curr = curr->next;
            }
        }

    }

    template<class T>
    int mtm::SortedList<T>::length() const
    {
        int counter = 0;
        node<T> *curr = this->head;
        while (curr != nullptr)
        {
            curr = curr->next;
            counter++;
        }
        return counter;
    }
}
#endif //SORTEDLISTQUIMARCHE_SORTEDLIST_H