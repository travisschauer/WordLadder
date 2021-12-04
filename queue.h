#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

const int QUEUE_SIZE = 16;

template <typename QueueType>
class Queue {
 public:
  Queue(void) { 

    capacity = QUEUE_SIZE;
    count = tail = 0;
    head = QUEUE_SIZE - 1;

    data = new QueueType[capacity];
  }
  ~Queue(void) {

    delete[] data;
  }

  void clear(void) { count = tail = 0; head = capacity - 1; }
  int size(void) { return count; }
  bool isEmpty(void) { return count == 0; }

  void enqueue(const QueueType &d) {

    if (count == capacity) {
      int
        tmpCap = 2 * capacity;
      QueueType
        *tmpData = new QueueType[tmpCap];

      if (tmpData == nullptr)
        throw std::overflow_error("Queue is full");

      for (int i=0;i<capacity;i++)
        tmpData[i] = data[(head+i+1)%capacity];

      delete[] data;

      data = tmpData;

      tail = capacity;
      head = tmpCap - 1;

      capacity = tmpCap;
    }

    data[tail] = d;

    tail = ++tail % capacity;

    count++;
  }

  QueueType dequeue(void) {

    if (!count)
      throw std::underflow_error("Queue is empty");

    count--;

    head = ++head % capacity;

    return data[head];

  }

 private:
  QueueType
   *data;
  int
   count,head,tail,capacity;
};

#endif
