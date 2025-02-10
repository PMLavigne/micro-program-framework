/**
 * List.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <utility>

namespace mpf::core {

    template<class ListItemT>
    class List {
    public:
        class Iterator;

        class Item {
            friend class List;

            ListItemT *nextItem = nullptr;

        protected:
            Item() noexcept = default;

        public:
            virtual ~Item() = default;
        };

        class Iterator {
        public:
            using value_type = ListItemT;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

            Iterator(value_type * const currentItem,
                     size_t const currentItemIndex)
                    : m_currentItem(currentItem), m_currentItemIndex(currentItemIndex) {}

            Iterator(Iterator const &) = default;

            Iterator(Iterator &&) noexcept = default;

            ~Iterator() = default;

            Iterator &operator=(Iterator const &) = default;

            Iterator &operator=(Iterator &&) noexcept = default;

            [[nodiscard]]
            reference operator*() const {
                return *m_currentItem;
            }

            [[nodiscard]]
            pointer operator->() const {
                return m_currentItem;
            }

            Iterator &operator++() {
                if (m_currentItem != nullptr) {
                    m_currentItem = m_currentItem->nextItem;
                    m_currentItemIndex++;
                }
                return *this;
            }

            Iterator operator++(int) &{ // NOLINT(cert-dcl21-cpp)
                Iterator const returnValue = {m_currentItem, m_currentItemIndex};
                if (m_currentItem != nullptr) {
                    m_currentItem = m_currentItem->nextItem;
                    m_currentItemIndex++;
                }
                return returnValue;
            }

            [[nodiscard]]
            bool operator==(Iterator const &other) const {
                return m_currentItem == other.m_currentItem &&
                       (m_currentItemIndex == other.m_currentItemIndex || m_currentItem == nullptr);
            }

            [[nodiscard]]
            auto operator<=>(Iterator const & other) const {
                if (operator==(other)) {
                    return std::weak_ordering::equivalent;
                }
                return m_currentItemIndex <=> other.m_currentItemIndex;
            }

        private:
            pointer m_currentItem = nullptr;
            size_t m_currentItemIndex = 0;
        };

        class ConstIterator {
        public:
            using value_type = ListItemT;
            using difference_type = ptrdiff_t;
            using pointer = value_type const *;
            using reference = value_type const &;

            ConstIterator(value_type const * const currentItem,
                     size_t const currentItemIndex)
                    : m_currentItem(currentItem), m_currentItemIndex(currentItemIndex) {}

            ConstIterator(ConstIterator const &) = default;

            ConstIterator(ConstIterator &&) noexcept = default;

            ~ConstIterator() = default;

            ConstIterator &operator=(ConstIterator const &) = default;

            ConstIterator &operator=(ConstIterator &&) noexcept = default;

            [[nodiscard]]
            reference operator*() const {
                return *m_currentItem;
            }

            [[nodiscard]]
            pointer operator->() const {
                return m_currentItem;
            }

            ConstIterator &operator++() {
                if (m_currentItem != nullptr) {
                    m_currentItem = m_currentItem->nextItem;
                    m_currentItemIndex++;
                }
                return *this;
            }

            ConstIterator operator++(int) &{ // NOLINT(cert-dcl21-cpp)
                ConstIterator const returnValue = {m_currentItem, m_currentItemIndex};
                if (m_currentItem != nullptr) {
                    m_currentItem = m_currentItem->nextItem;
                    m_currentItemIndex++;
                }
                return returnValue;
            }

            [[nodiscard]]
            bool operator==(ConstIterator const &other) const {
                return m_currentItem == other.m_currentItem &&
                       (m_currentItemIndex == other.m_currentItemIndex || m_currentItem == nullptr);
            }

            [[nodiscard]]
            auto operator<=>(ConstIterator const & other) const {
                if (operator==(other)) {
                    return std::weak_ordering::equivalent;
                }
                return m_currentItemIndex <=> other.m_currentItemIndex;
            }

        private:
            pointer m_currentItem = nullptr;
            size_t m_currentItemIndex = 0;
        };

    private:
        ListItemT *firstItem = nullptr;
        size_t size = 0;

    public:
        List() noexcept = default;

        List(std::initializer_list<ListItemT *> const & addToList) {
            addAll(addToList);
        }

        virtual ~List() = default;

        [[nodiscard]]
        ListItemT *first() const {
            return firstItem;
        }

        ListItemT *removeFirst() volatile {
            if (firstItem == nullptr) {
                return nullptr;
            }
            ListItemT *temp = firstItem;
            firstItem = firstItem->nextItem;
            temp->nextItem = nullptr;
            size_t const tempSize = size - 1;
            size = tempSize;
            return temp;
        }

        [[nodiscard]]
        bool isEmpty() const {
            return firstItem == nullptr;
        }

        void addAll(std::initializer_list<ListItemT *> const &list) {
            for (ListItemT * const item : list) {
                addItem(item);
            }
        }

        void addItem(ListItemT *const item) volatile {
            if (firstItem == nullptr) {
                firstItem = item;
                size_t const tempSize = size + 1;
                size = tempSize;
                return;
            }

            // Detect if this is already in the collection, and it's the first object
            if (item == firstItem) {
                return;
            }

            ListItemT *currentItem = firstItem;

            while (currentItem->nextItem != nullptr) {
                currentItem = currentItem->nextItem;
                // Detect if this is already in the collection
                if (currentItem == item) {
                    return;
                }
            }

            currentItem->nextItem = item;
            item->nextItem = nullptr;
            size_t const tempSize = size + 1;
            size = tempSize;
        }

        [[nodiscard]]
        size_t getSize() const {
            return size;
        }

        [[nodiscard]]
        Iterator begin() const {
            return {first(), 0};
        }

        [[nodiscard]]
        Iterator end() const {
            return {nullptr, getSize()};
        }

        [[nodiscard]]
        ConstIterator cbegin() const {
            return {first(), 0};
        }

        [[nodiscard]]
        ConstIterator cend() const {
            return {nullptr, getSize()};
        }
    };

}
