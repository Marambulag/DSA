#ifndef QUEUE_HPP
#define QUEUE_HPP

class Queue {
private:
    int front, rear, size, capacity;
    int* queueArray;

public:
    Queue(int capacity);      // Constructor para inicializar la cola con capacidad fija
    ~Queue();                 // Destructor para liberar la memoria

    void enqueue(int value);  // Inserta un elemento al final de la cola
    void dequeue();           // Remueve el elemento al frente de la cola
    int frontElement() const; // Devuelve el primer elemento sin eliminarlo
    bool isEmpty() const;     // Verifica si la cola está vacía
    bool isFull() const;      // Verifica si la cola está llena
};

#endif // QUEUE_HPP
