#pragma once
#include <mutex>
#include <queue>


template <typename T>
class SafeQueue {
public:
	SafeQueue() {}
	virtual ~SafeQueue() {}

	void enqueue(const T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(t);
	}
	
	T dequeue() {
		std::unique_lock<std::mutex> lock(m_mutex);
		T value = m_queue.front();
		m_queue.pop();
		return value;
	}
	
	bool empty() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

protected:
	std::queue<T> m_queue;
	std::mutex m_mutex;
};
