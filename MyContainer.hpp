//taliyarial1@gmail.com
#pragma once
#include <iostream>
#include <concepts>
#include <ostream>
#include <type_traits>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>

//This concept ensures that the type U supports equality comparison (operator== and operator!=), as well as all four relational comparison operators: <, >, <=, and >=.
//Each relational operator must return a value convertible to bool.
template<typename U>
concept TotallyOrderedWith = std::equality_comparable<U> && requires(U a, U b) {
        { a < b } -> std::convertible_to<bool>;
        { a > b } -> std::convertible_to<bool>;
        { a <= b } -> std::convertible_to<bool>;
        { a >= b } -> std::convertible_to<bool>;
    };

namespace con{
    template<typename T = int >
    requires TotallyOrderedWith<T>
    //MyContainer class represent a generic cottainer that cat contain comperable objects, support add, remove and print operator.
    class MyContainer{
        static_assert(TotallyOrderedWith<T>, "T must support ==, <, >, <=, >= operators (totally ordered)");
        private:
            T* data;
            int c_size = 0;
            int capacity = 5;

            //when container 75% full, capacity is doubled
            void increasCapacity(){
                if(c_size > 0.75 * capacity){
                    capacity = 2 * capacity;
                    copyData();
                }
            }

            //when container is only 25% full, capacity is crossed in two
            void decreasCapacity(){
                if(c_size <= 0.25 * capacity){
                    capacity = 0.5 * capacity;
                    copyData();
                }
            }

            //Copies the objects to a new container of appropriate size
            void copyData(){
                T* newData = new T[capacity];
                for(int i = 0; i < capacity; i++){
                    if(i < c_size){
                        newData[i] = data[i];
                    }
                    else{
                        newData[i] = T{};
                    }
                }
                delete[] data;
                data = newData;
            }

            //Copies the objects to a new container so that there are no breaks in the sequence of objects in the container.
            void copyNewData(){
                T* newData = new T[capacity];
                //Resets the newData array
                for (int i = 0; i < capacity; ++i)
                    newData[i] = T();

                int index = 0;
                for(int i = 0; i < capacity; i++){
                    if(data[i] == T{}) continue;
                    else{
                        newData[index] = data[i];
                        index++;
                    }
                }
                delete[] data;
                data = newData;
            }
            
        public:
            //Constractor that allocates a new array with capacity 5 and resets it
            MyContainer(){
                data = new T[capacity];
                for(int i = 0; i < capacity; i++){
                    data[i] = T{};
                }
            }

            //Distractor free data array memory
            ~MyContainer(){delete[] data;}

            //Adding new object to the container and increas capacity
            void add(T& newObj){
                if(c_size < capacity){
                    data[c_size] = newObj;
                    c_size++;
                }
                increasCapacity();
            }

            //Remove object from container, if object appears multiple times, all of its occurrences are removed. 
            //Decreas capacity.
            void remove(T& obj){
                int counter = 0;
                for(int i = 0; i < c_size; i++){
                    if(data[i] == obj){
                        data[i] = T{};
                        counter++;
                    }
                }
                if(counter == 0){
                    throw std::invalid_argument("Container don't contain " + std::to_string(obj));
                }
                copyNewData();
                c_size -= counter;
                decreasCapacity();
            }

            //Returns the number of objects contained in the container.
            int size()const{return c_size;}

            //Return the object at index i.
            T get(int i) const{
                if(i >= c_size || i < 0){
                    throw std::invalid_argument("index is not in container range");
                }
                return data[i];
            }

            //Prints the contents of the container.
            friend std::ostream& operator<< (std::ostream& os, const MyContainer& m){
                std::operator<<(os, "MyContainer:\n");
                for(int i = 0; i < m.size(); i++){
                    os << std::fixed << std::setprecision(3) << m.get(i);
                    std::operator<<(os, " ");
                }
                return os;
            }

            //Return capacity, use onlly for testing
            int getCapacity(){return capacity;}

            //Order iterator: goes through the container in the order it was filled.
            class Order{
                private:
                    T* current;
                public:
                    //Constractor
                    Order (T* ptr):current(ptr){}
                    //Returns a reference to the element currently pointed to by the iterator.
                    T& operator*() const {
                        return *current;
		            }
                    //Advances the iterator to the next element in the container.
                    Order& operator++(){
                        current++;
                        return *this;
                    }
                    //Compares two iterators for inequality.
                    bool operator!=(const Order& other){
                        return current != other.current;
                    }
            };
            //Return Order Iterator pointing to the first element in the container.
            Order begin_order(){
                return Order(data);
            }
            //Return Order Iterator pointing one past the last element in the container.
            Order end_order(){
                return Order(data + c_size);
            }

            //Reverse Order iterator: Goes over the container in the opposite way from when the container was filled.
            class ReverseOrder {
                private:
                    T* current;
                public:
                    //Constractor
                    ReverseOrder(T* ptr):current(ptr){}
                    //Returns a reference to the element currently pointed to by the iterator.
                    T operator*()const{
                        return *current;
                    }
                    //Advances the iterator to the next element in the container.
                    ReverseOrder operator++(){
                        current--;
                        return *this;
                    }
                    //Compares two iterators for inequality.
                    bool operator!=(const ReverseOrder& other){
                        return current != other.current;
                    }
            };
            //Return Reverse Order Iterator pointing to the first element in the container.
            ReverseOrder begin_reverse_order(){
                return ReverseOrder(data + c_size - 1);
            }
            //Return Reverse Order Iterator pointing one past the last element in the container.
            ReverseOrder end_reverse_order(){
                return ReverseOrder(data - 1);
            }

            //Ascending Order iterator: Goes over the container from the smallest object to the largest.
            class AscendingOrder{
                private:
                    T* current;
                    T* start;
                    int size;
                    T* max;
                    bool end = false;
                    std::vector<bool> visit;
                public:
                    //Constractor
                    AscendingOrder(T* ptr, T* data, int c_size): current(ptr), start(data), size(c_size), visit(c_size, false){
                        //Finding max object in container
                        max = start;
                        int index = 0;
                        for(int i = 0; i < size; i++){
                            //Find max object
                            if(*(start + i) > *max)
                                max = start + i;
                            //Find min object
                            if(start + i == current)
                                index = i;
                        }
                        visit[index] = true;

                    }
                    //Returns a reference to the element currently pointed to by the iterator.
                    T operator*(){
                        return *current;
                    }

                    //Advances the iterator to the next element in the container.
                    AscendingOrder operator++(){
                        T* next = max;
                        int index = 0;
                        //Finding next object in container
                        for(int i = 0; i < size; i++){
                            if(*(start + i) >= *current && *(start + i) <= *next && !visit[i]){
                                next = start + i;
                                index = i;
                            }
                        }
                        current = next;
                        visit[index] = true;
                        //If max allredy reached once, no more iterations
                        if(end){
                            current = start + size + 1;
                        }
                        //First time that max reached, returnt it, and turn the flag for finish next iteration
                        if(current == max && !end){
                            end = true;
                        }
                        return *this;
                    }

                    //Compares two iterators for inequality.
                    bool operator!=(const AscendingOrder& other){
                        return current != other.current;
                    }
            };
            //Return AscendingOrder Iterator pointing to the first element in the container- min object.
            AscendingOrder begin_ascending_order(){
                //Finding min object
                T* min = data;
                for(int i = 0; i < c_size; i++){
                    if(*(data + i) < *min)
                        min = data + i;
                }
                return AscendingOrder(min, data, c_size);
            }
            //Return AscendingOrder Iterator pointing one past the last element in the container.
            AscendingOrder end_ascending_order(){
                return AscendingOrder(data + c_size + 1, data, c_size);
            }
            //Descending Order iterator: Goes over the container from the largest object to the smallest.
            class DescendingOrder {
                private:
                    T* current;
                    T* start;
                    int size;
                    T* min;
                    std::vector<bool> visit;

                public:
                    //Constractor initilaize all filds
                    DescendingOrder(T* ptr, T* data, int c_size): current(ptr), start(data), size(c_size), visit(c_size, false) {
                        //Find minimum object and mark it as visited
                        min = start;
                        int index = 0;
                        for (int i = 0; i < size; i++) {
                            if (*(start + i) < *min)
                                min = start + i;
                            if (start + i == current)
                                index = i;
                        }
                        visit[index] = true;
                    }

                    //Returns a reference to the element currently pointed to by the iterator.
                    T operator*() {
                        return *current;
                    }

                    //Advances the iterator to the next element in the container.
                    DescendingOrder operator++() {
                        T* next = min;
                        int index = -1;
                        //Find the next object that less than current and larger then the other objects
                        for (int i = 0; i < size; i++) {
                            //Check if object is less-then-equal current object and larger then other objects and not visited yet
                            if (*(start + i) <= *current && *(start + i) >= *next && !visit[i]) {
                                next = start + i;
                                index = i;
                            }
                        }
                        // No next element, go to end
                        if (index == -1) { 
                            current = start + size + 1;
                        } else {
                            current = next;
                            visit[index] = true;
                        }

                        return *this;
                    }
                    //Compares two iterators for inequality.
                    bool operator!=(const DescendingOrder& other) const {
                        return current != other.current;
                    }
            };
            //Return DescendingOrder Iterator pointing to the first element in the container - max object.
            DescendingOrder begin_descending_order(){
                //Finding max object
                T* max = data;
                for(int i = 0; i < c_size; i++){
                    if(*(data + i) > *max)
                        max = data + i;
                }
                return DescendingOrder(max, data, c_size);
            }
            //Return DescendingOrder Iterator pointing one past the last element in the container.
            DescendingOrder end_descending_order(){
                return DescendingOrder(data + c_size + 1, data, c_size);
            }

            //Side Cross Order iterator: Goes over the container starting with the smallest object, moving from there to the largest, and so on.
            class SideCrossOrder{
                private:
                    T* current;
                    T* start;
                    int size;
                    T* min;
                    T* max;
                    int counter = 0;
                    std::vector<bool> visit;
                public:
                    //Constractor
                    SideCrossOrder(T* ptr, T* data, int c_size):current(ptr), start(data), size(c_size), visit(c_size, false){
                        min = start;
                        int min_i = 0;
                        max = start;
                        for(int i = 0; i < size; i++){
                            //Find min object
                            if(*(start + i) < *min){
                                min = start + i;
                                min_i = i;
                            }
                            //Find max object
                            if(*(start + i) > *max)
                                max = start + i;
                        }
                        visit[min_i] = true;
                    }
                    //Returns a reference to the element currently pointed to by the iterator.
                    T operator*(){
                        return *current;
                    }

                    //Advances the iterator to the next element in the container.
                    SideCrossOrder operator++(){
                        int max_i = -1;
                        int min_i = -1;
                        //Check if current iteration is even
                        if((counter % 2) == 0){
                            //Finds maximum object relative to current maximum that was not visit yet.
                            T* next = min;
                            for(int i = 0; i < size; i++){
                                if(*(start + i) >= *next && *(start + i) <= *max && !visit[i]){   
                                    next = start + i;
                                    max_i = i;
                                }
                            }
                            //If no next founded- go to end, else update max and current object
                            if(min_i == -1 && max_i == -1){
                                current = start + size + 1;
                            }
                            else{
                                max = next;
                                visit[max_i] = true;
                                current = max;
                            }
                        }
                        else{
                            //If current iteration is odd
                            T* nextM = max;
                            //Finds min object relative to current min that was not visit yet.
                            for(int i = 0; i < size; i++){
                                if(*(start + i) <= *nextM && *(start + i) >= *min && !visit[i]){   
                                    nextM = start + i;
                                    min_i = i;
                                }
                            }
                            //If no next founded- go to end, else update min and current object
                            if(min_i == -1 && max_i == -1){
                                current = start + size + 1;
                            }
                            else{
                                min = nextM;
                                visit[min_i] = true;
                                current = min;
                            }
                        }
                        counter++;
                        return *this;
                    }
                    //Compares two iterators for inequality.
                    bool operator!=(const SideCrossOrder& other){
                        return current != other.current;
                    }
            };
            //Return SideCrossOrder Iterator pointing to the first element in the container - min object. 
            SideCrossOrder begin_side_cross_order(){
                //Finding min object
                 T* min = data;
                for(int i = 0; i < c_size; i++){
                    if(*(data + i) < *min)
                        min = data + i;
                }
                return SideCrossOrder(min, data, c_size);
            }
            //Return SideCrossOrder Iterator pointing one past the last element in the container.
            SideCrossOrder end_side_cross_order(){
                return SideCrossOrder(data + c_size + 1, data, c_size);
            }

            //Middle Out Order Order iterator: Goes over the container starting with the middle object, moving to the left then the right and so on
            class MiddleOutOrder{
                private:
                    T* current;
                    T* start;
                    int size;
                    int counter = 0;
                    int left;
                    int right;
                public:
                    //Constractor initializes all fields
                    MiddleOutOrder(T* ptr, T* data, int c_size): current(ptr), start(data), size(c_size){
                        left = size/ 2 - 1;
                        right = size/ 2 + 1;
                    }
                    //Returns a reference to the element currently pointed to by the iterator.
                    T operator*(){
                        return *current;
                    }

                    //Advances the iterator to the next element in the container.
                    MiddleOutOrder operator++(){
                        //Check if current iteration is even
                        if((counter % 2) == 0){
                            current = start + left;
                            left -= 1;
                        }
                        else{
                            //If current iteration is odd
                            current = start + right;
                            right += 1;
                        }
                        //If no iteration in container range- go to end
                        if((current == start - 1 || current == start + size)){
                            current = start + size + 1;
                        }
                        counter++;
                        return *this;
                    }
                    //Compares two iterators for inequality.
                    bool operator!=(const MiddleOutOrder& other){
                        return current != other.current;
                    }
            };
            //Return MiddleOutOrder Iterator pointing to the first element in the container - middle object.
            MiddleOutOrder begin_middle_out_order(){
                int midle = c_size / 2.0;
                return MiddleOutOrder(data + midle, data, c_size);
            }

            //Return MiddleOutOrder Iterator pointing one past the last element in the container.
            MiddleOutOrder end_middle_out_order(){
                    return MiddleOutOrder(data + c_size + 1, data, c_size);
            }

    }; 
} 