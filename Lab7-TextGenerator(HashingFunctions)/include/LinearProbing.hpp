#pragma once
#include "ArrayList.hpp"
#include <functional>
#include <utility>
#include <stdexcept>
#include <optional>

template <typename Key, typename Value>
class LinearProbing {
public:
    LinearProbing(size_t initialCapacity = 101);

    void insert(const Key& key, const Value& value);

    bool remove(const Key& key);

    Value* find(const Key& key);

    Value& operator[](const Key& key);

    size_t size() const;

    size_t capacity() const;

private:
    enum class SlotStatus { EMPTY, OCCUPIED, DELETED };

    struct Slot {
        std::optional<Key> key;
        std::optional<Value> value;
        SlotStatus status = SlotStatus::EMPTY;
    };

    ArrayList<Slot> table_;
    size_t count_;
    size_t capacity_;
    static constexpr double LOAD_FACTOR = 0.7;

    size_t hash(const Key& key) const;
    void rehash();
};

// Implementation

template <typename Key, typename Value>
LinearProbing<Key, Value>::LinearProbing(size_t initialCapacity)
    : table_(initialCapacity), count_(0), capacity_(initialCapacity) {}

template <typename Key, typename Value>
size_t LinearProbing<Key, Value>::hash(const Key& key) const {
    // TODO: implement hash function
    return std::hash<Key>{}(key) % capacity_;
}

template <typename Key, typename Value>
void LinearProbing<Key, Value>::insert(const Key& key, const Value& value) {
    // TODO: implement insert
    // rehash if load factor exceeded
    if ((double)(count_ + 1) / capacity_ > LOAD_FACTOR) {
        rehash();
    }

    size_t insertIndex = hash(key);
    int firstDeletedIndex = -1;

    for(size_t i = 0; i < capacity_; ++i){
        size_t currIndex = (insertIndex + i) % capacity_;
        Slot& slot = table_.get(currIndex);

        if(slot.status == SlotStatus::OCCUPIED && slot.key.value() == key){
            slot.value = value;
            return;
        }
        else if(slot.status == SlotStatus::DELETED){
            if(firstDeletedIndex == -1){
                firstDeletedIndex = currIndex;
            }
        }
        else if(slot.status == SlotStatus::EMPTY){
            size_t insertIndex2;
            if(firstDeletedIndex != -1){
                insertIndex2 = firstDeletedIndex;
            }
            else{
                insertIndex2 = currIndex;
            }
            table_.get(insertIndex2).key = key;
            table_.get(insertIndex2).value = value;
            table_.get(insertIndex2).status = SlotStatus::OCCUPIED;
            count_++;
            return;
        }
    }
}

template <typename Key, typename Value>
bool LinearProbing<Key, Value>::remove(const Key& key) {
    // TODO: implement remove
    size_t removeIndex = hash(key);

    for(size_t i = 0; i < capacity_; ++i){
        size_t currIndex = (removeIndex + i) % capacity_;
        Slot& slot = table_.get(currIndex);

        if(slot.status == SlotStatus::EMPTY){
            return false;
        }
        if(slot.status == SlotStatus::OCCUPIED && slot.key == key){
            slot.status = SlotStatus::DELETED;
            slot.key = std::nullopt;
            slot.value = std::nullopt;
            count_--;
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
Value* LinearProbing<Key, Value>::find(const Key& key) {
    // TODO: implement find
    size_t findIndex = hash(key);

    for(size_t i = 0; i < capacity_; ++i){
        size_t currIndex = (findIndex + i) % capacity_;
        Slot& slot = table_.get(currIndex);

        if(slot.status == SlotStatus::EMPTY){
            return nullptr;
        }
        if(slot.status == SlotStatus::OCCUPIED && slot.key == key){
            return &(*slot.value);
        }
    }
    return nullptr;
}

template <typename Key, typename Value>
Value& LinearProbing<Key, Value>::operator[](const Key& key) {
    // TODO: implement operator[] to return reference to value associated with key
    // if key not found, insert default-constructed Value and return its reference
    Value* foundValue = find(key);

    if(foundValue){
        return *foundValue;
    }

    insert(key, Value());

    return *find(key);
}

template <typename Key, typename Value>
size_t LinearProbing<Key, Value>::size() const {
    return count_;
}

template <typename Key, typename Value>
size_t LinearProbing<Key, Value>::capacity() const {
    return capacity_;
}

template <typename Key, typename Value>
void LinearProbing<Key, Value>::rehash() {
    // TODO: Implement rehashing by doubling capacity and reinserting all items
     ArrayList<Slot> oldTable = table_;
    size_t oldCapacity = capacity_;

    capacity_ *= 2;
    table_ = ArrayList<Slot>(capacity_);

    for(size_t i = 0; i < capacity_; i++){
        table_.add(Slot());
    }

    count_ = 0;

    for(size_t i = 0; i < oldCapacity; ++i){
        Slot& slot = oldTable.get(i);
        if(slot.status == SlotStatus::OCCUPIED){
            insert(*slot.key, *slot.value);
        }
    }

}