//
// Created by sacha on 21/06/2021.
//

#ifndef TO_SORT_NODE_H
#define TO_SORT_NODE_H


    template<class T>
    class node {
        friend class SortedList;

    public:
        T data;
        node<T> *next;

        node() = default;

        ~node() = default;

        node(const T &data_node_to_copy) : data(data_node_to_copy), next(nullptr) {
        }

        bool operator<(const node &first_node) const {
            if (this->data < first_node.data) {
                return true;
            }
            return false;
        }

        T getData() {
            return data;
        }

        node &operator=(const node &) = default;

    };

#endif //TO_SORT_NODE_H
