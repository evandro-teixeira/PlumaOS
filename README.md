# PlumaOS - Lightweight Real-Time Operating System for Embedded Systems

PlumaOS is a **lightweight and modular real-time operating system (RTOS)** designed specifically for **embedded systems** with limited resources. Implemented in C, it provides essential primitives for synchronization and inter-process communication.

## ⚠️ Important Notice

**This is an experimental educational project.** PlumaOS is designed exclusively for learning and study purposes. **Do not use this project in production or real-world applications.** It lacks the robustness, testing, and certification required for production-grade systems. For production embedded systems, consider using well-established RTOS solutions such as FreeRTOS, Zephyr RTOS, NuttX, or others.

## 🎯 Key Features

- ✅ **Lightweight and modular** – Ideal for resource-constrained microcontrollers
- ✅ **Kernel with Scheduler** – Multi-task management with priority levels
- ✅ **Priority-based preemption** – Flexible task execution control
- ✅ **Synchronization primitives** – Semaphores, Mutex, and Events
- ✅ **Message queue** – FIFO communication between tasks
- ✅ **Critical section control** – Interrupt disabling for atomicity
- ✅ **Atomic operations** – Race condition protection

## 📦 Project Components

### 1. Kernel
- **Scheduler** (cooperative/preemptive) for task execution management
- Support for **multiple priority levels** (Idle, Low, Normal, High)
- Task state control (Ready, Blocked, Paused)
- Implementation based on **linked list** for efficient task storage

### 2. Timer
- **System tick** management via SysTick
- Functions for delay, time difference, and tick retrieval
- Based on **Cortex-M** architecture (MKL25Z4)

### 3. Synchronization and Communication
- **Semaphores** – Access control with counter mechanism
- **Mutex** – Mutual exclusion between tasks
- **Events** – Flag-based signaling
- **Message Queue** – FIFO message queue for IPC

### 4. Data Structures
- **Linked List** – Efficient task management in the kernel
- Operations: Insert, Get, Remove, Delete

## 🚀 Getting Started

### System Initialization

```c
#include "PlumaOs.h"

int main(void) {
    PlumaOS_Init();
    // Add tasks here
    PlumaOS_StartScheduler();
    return 0;
}
```

### Creating Tasks

```c
void MyTask(void) {
//    while(1) {
        // Task code
        PlumaOS_TaskDelay(100);
//    }
}

// Add task with priority
PlumaOS_TaskAdd(MyTask, PRIORITY_NORMAL, TASK_READY);
```

### Semaphores

```c
SemaphoreHandle_t semaphore;
PlumaOS_SemaphoreCreate(&semaphore, 1);

// Wait for semaphore
PlumaOS_SemaphoreWait(&semaphore);
// Protected code section
PlumaOS_SemaphorePost(&semaphore);

PlumaOS_SemaphoreDestroy(&semaphore);
```

### Mutex

```c
MutexHandle_t mutex;
PlumaOS_MutexCreate(&mutex);

PlumaOS_MutexLock(&mutex);
// Critical section
PlumaOS_MutexUnlock(&mutex);

PlumaOS_MutexDestroy(&mutex);
```

### Message Queue

```c
MsgQueueHandle_t queue;
PlumaOS_MsgQueueCreate(&queue, 10, sizeof(Message_t));

// Send message
Message_t msg = {...};
PlumaOS_MsgQueuePut(&queue, &msg);

// Receive message
Message_t rxMsg;
PlumaOS_MsgQueueGet(&queue, &rxMsg);

PlumaOS_MsgQueueDestroy(&queue);
```

### Events

```c
EventHandle_t event;
PlumaOS_EventCreate(&event, TRUE);

// Signal event
PlumaOS_EventSet(&event, 0x01);

// Wait for event
uint32_t flags;
PlumaOS_EventWait(&event, 0x01, TRUE, 1000, &flags);

PlumaOS_EventDestroy(&event);
```

## 📋 Project Structure

```
PlumaOS/
├── Kernel.c / Kernel.h          # Operating system core
├── Timer.c / Timer.h             # Time management
├── Semaphore.c / Semaphore.h     # Semaphore implementation
├── Mutex.c / Mutex.h             # Mutex implementation
├── Event.c / Event.h             # Event signaling
├── MsgQueue.c / MsgQueue.h       # Message queue
├── List.c / List.h               # Linked list data structure
├── PlumaOS_Types.h               # Data type definitions
├── PlumaOs.h                     # Main API header
└── README.md                     # This file
```

## 🔧 Requirements

- **Cortex-M Microcontroller** (MKL25Z4 or compatible)
- **C99 or newer compiler**
- **IDE**: VS Code, MCUXpresso, Keil, Embedded Studio, etc.

## 👨‍💻 Author

**Evandro Teixeira**  
Created on: December 26, 2021

## 📝 License

Creative Commons Legal Code

## 🤝 Contributing

Contributions are welcome! Please open an issue or submit a pull request.
