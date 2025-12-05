#pragma once
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>

/**
 * Шаблонный класс Repository для хранения и управления объектами.
 * Требование: тип T должен быть производным от базового класса с виртуальными методами.
 */
template<typename T>
class Repository
{
public:
    Repository() = default;
    
    /**
     * Не шаблонный метод: добавление элемента.
     */
    void add(T* item)
    {
        if (item) {
            m_items.push_back(item);
        }
    }
    
    /**
     * Не шаблонный метод: удаление элемента по индексу.
     */
    void remove(size_t index)
    {
        if (index < m_items.size()) {
            m_items.erase(m_items.begin() + index);
        }
    }
    
    /**
     * Шаблонный метод: поиск элемента по предикату.
     */
    template<typename Predicate>
    T* findIf(Predicate pred) const
    {
        auto it = std::find_if(m_items.begin(), m_items.end(), pred);
        return (it != m_items.end()) ? *it : nullptr;
    }
    
    /**
     * Шаблонный метод: поиск всех элементов по предикату.
     */
    template<typename Predicate>
    std::vector<T*> findAll(Predicate pred) const
    {
        std::vector<T*> result;
        std::copy_if(m_items.begin(), m_items.end(), 
                     std::back_inserter(result), pred);
        return result;
    }
    
    /**
     * Шаблонный метод: сортировка элементов.
     */
    template<typename Comparator>
    void sort(Comparator comp)
    {
        std::sort(m_items.begin(), m_items.end(), comp);
    }
    
    /**
     * Не шаблонный метод: сортировка по умолчанию.
     */
    void sortDefault()
    {
        std::sort(m_items.begin(), m_items.end());
    }
    
    /**
     * Шаблонный метод: удаление элементов по предикату.
     */
    template<typename Predicate>
    size_t removeIf(Predicate pred)
    {
        auto oldSize = m_items.size();
        auto newEnd = std::remove_if(m_items.begin(), m_items.end(), pred);
        m_items.erase(newEnd, m_items.end());
        return oldSize - m_items.size();
    }
    
    /**
     * Шаблонный метод: применение функции ко всем элементам.
     */
    template<typename Function>
    void forEach(Function func) const
    {
        std::for_each(m_items.begin(), m_items.end(), func);
    }
    
    /**
     * Не шаблонный метод: получение всех элементов.
     */
    const std::vector<T*>& getAll() const
    {
        return m_items;
    }
    
    /**
     * Не шаблонный метод: получение элемента по индексу.
     */
    T* get(size_t index) const
    {
        return (index < m_items.size()) ? m_items[index] : nullptr;
    }
    
    /**
     * Не шаблонный метод: размер репозитория.
     */
    size_t size() const
    {
        return m_items.size();
    }
    
    /**
     * Не шаблонный метод: проверка на пустоту.
     */
    bool empty() const
    {
        return m_items.empty();
    }
    
    /**
     * Не шаблонный метод: очистка репозитория.
     */
    void clear()
    {
        m_items.clear();
    }

private:
    std::vector<T*> m_items;
};
