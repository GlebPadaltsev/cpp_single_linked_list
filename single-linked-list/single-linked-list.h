#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <iostream>
#include <iterator> 

using namespace std;



template <typename Type>
class SingleLinkedList {
    // Узел списка
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };

public:

    SingleLinkedList() {
        size_ = 0;

        head_.next_node = nullptr;

    }
    ~SingleLinkedList() {
        this->Clear();
    }

    // Возвращает количество элементов в списке за время O(1)
    [[nodiscard]] size_t GetSize() const noexcept {
        // Заглушка. Реализуйте метод самостоятельно

        return size_;
    }

    // Сообщает, пустой ли список за время O(1)
    [[nodiscard]] bool IsEmpty() const noexcept {
        // Заглушка. Реализуйте метод самостоятельно
        return size_ == 0 ? true : false;

    }
    void PushFront(const Type& value) {
        head_.next_node = new Node(value, head_.next_node);
        size_++;
        // Реализуйте метод самостоятельно
    }

    // Очищает список за время O(N)
    void Clear() noexcept {
        while (head_.next_node != nullptr)
        {
            Node* this_node = head_.next_node;
            head_.next_node = this_node->next_node;
            delete this_node;
            --size_;
        }
        // Реализуйте метод самостоятельно
    }

    //------------Iterator----------------------
    template <typename ValueType>
    class BasicIterator {

        friend class SingleLinkedList;

        // Конвертирующий конструктор итератора из указателя на узел списка
        explicit BasicIterator(Node* node) {
            node_ = node;

            // Реализуйте конструктор самостоятельно
        }

    public:

        using iterator_category = std::forward_iterator_tag;
        // Тип элементов, по которым перемещается итератор
        using value_type = Type;
        // Тип, используемый для хранения смещения между итераторами
        using difference_type = std::ptrdiff_t;
        // Тип указателя на итерируемое значение
        using pointer = ValueType*;
        // Тип ссылки на итерируемое значение
        using reference = ValueType&;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept {

            node_ = other.node_;
            // Реализуйте конструктор самостоятельно
        }

        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return this->node_ == rhs.node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            return this->node_ != rhs.node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return this->node_ == rhs.node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return this->node_ != rhs.node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        BasicIterator& operator++() noexcept {
            node_ = node_->next_node;
            return *this;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        BasicIterator operator++(int) noexcept {
            auto old_node = *this;
            node_ = node_->next_node;
            return old_node;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        [[nodiscard]] reference operator*() const noexcept {
            return node_->value;
            // Не реализовано
            // Заглушка. Реализуйте оператор самостоятельно
        }

        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &node_->value;
            // Заглушка. Реализуйте оператор самостоятельно
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    [[nodiscard]] Iterator begin() noexcept {
        return Iterator{ head_.next_node };
        // Реализуйте самостоятельно

    }

    [[nodiscard]] Iterator end() noexcept {
        return Iterator{ nullptr };
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator{ head_.next_node };
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator{ nullptr };
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept {
        return ConstIterator{ head_.next_node };
    }

    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator{ nullptr };
    }
    //------------end iterator--------------------------
     // Возвращает итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator before_begin() noexcept {
        // Реализуйте самостоятельно
        return Iterator{ &head_ };
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
        // Реализуйте самостоятельно

        return ConstIterator(const_cast<Node*>(&head_));
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator before_begin() const noexcept {
        // Реализуйте самостоятельно
        return ConstIterator(const_cast<Node*>(&head_));
    }

    /*
     * Вставляет элемент value после элемента, на который указывает pos.
     * Возвращает итератор на вставленный элемент
     * Если при создании элемента будет выброшено исключение, список останется в прежнем состоянии
     */
    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        if (pos.node_ == nullptr) {
            throw std::out_of_range("Error iterator");
        }
        pos.node_->next_node = new Node(value, pos.node_->next_node);
        ++size_;
        return Iterator(pos.node_->next_node);
    }

    void PopFront() noexcept {
        // Реализуйте метод самостоятельно
        Node* remove_node = this->head_.next_node;
        this->head_.next_node = remove_node->next_node;
        delete remove_node;

    }

    /*
     * Удаляет элемент, следующий за pos.
     * Возвращает итератор на элемент, следующий за удалённым
     */
    Iterator EraseAfter(ConstIterator pos) noexcept {
        Node* pos_node = pos.node_->next_node;
        pos.node_->next_node = pos_node->next_node;
        delete pos_node;
        return Iterator(pos.node_->next_node);
    }

    SingleLinkedList(std::initializer_list<Type> values) {
        SingleLinkedList<Type> temp;
        temp.Init(values.begin(), values.end());
        swap(temp);
    }


    SingleLinkedList(const SingleLinkedList<Type>& other) : SingleLinkedList() {
        SingleLinkedList<Type> temp;
        temp.Init(other.begin(), other.end());
        swap(temp);
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        // Реализуйте присваивание самостоятельно
        if (this != &rhs) {
            auto tmp(rhs);
            this->Clear();
            swap(tmp);
        }
        return *this;
    }

    // Обменивает содержимое списков за время O(1)
    void swap(SingleLinkedList& other) noexcept {
        // Реализуйте обмен содержимого списков самостоятельно
        std::swap(this->head_.next_node, other.head_.next_node);
        std::swap(size_, other.size_);
    }
private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    size_t size_;
    template <typename Iter>
    void Init(Iter begin, Iter end);

};
template <typename Type>
template <typename Iter>
void SingleLinkedList<Type>::Init(Iter begin, Iter end) {
    Node* p = &head_;
    for (auto it = begin; it != end; ++it) {
        p->next_node = new Node(*it, nullptr);
        p = p->next_node;
        ++size_;
    }
}
template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    // Реализуйте обмен самостоятельно
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ? true : false;

}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !(lhs == rhs) ? true : false;
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ? true : false;
}
template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !(lhs < rhs || lhs == rhs);
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return (lhs < rhs || lhs == rhs);
}
template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !(lhs < rhs);
}
