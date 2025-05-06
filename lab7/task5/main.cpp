#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
   public:
    Vector() : m_size(0), m_capacity(1), m_data(new T[m_capacity]) {}
    ~Vector() { delete[] m_data; }

    Vector(std::initializer_list<T> initializer)
        : m_size(initializer.size()), m_capacity(initializer.size()), m_data(new T[m_capacity]) {
        std::copy(initializer.begin(), initializer.end(), m_data);
    }

    [[nodiscard]] size_t size() const { return m_size; }

    [[nodiscard]] bool empty() const { return m_size == 0; }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            m_capacity *= 2;
            T* new_data = new T[m_capacity];
            std::copy(m_data, m_data + m_size, new_data);
            delete[] m_data;
            m_data = new_data;
        }
        m_data[m_size++] = value;
    }

    T& operator[](size_t index) {
        if (index >= m_size) throw std::out_of_range("Out of range");
        return m_data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= m_size) throw std::out_of_range("Out of range");
        return m_data[index];
    }

    Vector operator+(const Vector& other) const {
        Vector result;
        result.m_size = m_size + other.m_size;
        result.m_capacity = result.m_size;
        result.m_data = new T[result.m_capacity];
        std::copy(m_data, m_data + m_size, result.m_data);
        std::copy(other.m_data, other.m_data + other.m_size, result.m_data + m_size);
        return result;
    }

    Vector operator-(const Vector& other) const {
        Vector result;
        for (size_t i = 0; i < m_size; ++i) {
            bool found = false;
            for (size_t j = 0; j < other.m_size; ++j) {
                if (m_data[i] == other.m_data[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result.push_back(m_data[i]);
            }
        }
        return result;
    }

    bool operator==(const Vector& other) const {
        if (m_size != other.m_size) return false;
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] != other.m_data[i]) return false;
        }
        return true;
    }

    class Iterator {
       public:
        Iterator(T* ptr) : m_ptr(ptr) {}

        T& operator*() { return *m_ptr; }

        Iterator& operator++() {
            ++m_ptr;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }

       private:
        T* m_ptr;
    };

    Iterator begin() { return Iterator(m_data); }

    Iterator end() { return Iterator(m_data + m_size); }

   private:
    size_t m_size;
    size_t m_capacity;
    T* m_data;
};

int main() {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {4, 5, 6};

    vec1.push_back(4);
    std::cout << "vec1[3]: " << vec1[3] << "\n";

    Vector<int> vec3 = vec1 + vec2;
    std::cout << "vec3: ";
    for (auto& val : vec3) std::cout << val << " ";
    std::cout << "\n";

    return 0;
}
