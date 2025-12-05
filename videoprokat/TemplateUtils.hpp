#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <numeric>
#include <functional>
#include <type_traits>
#include <variant>
#include <ranges>

/**
 * Шаблонная функция для вычисления среднего значения.
 * Ограничение: работает только с арифметическими типами.
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, double>::type
calculateAverage(const std::vector<T>& values)
{
    if (values.empty()) return 0.0;
    
    T sum = std::accumulate(values.begin(), values.end(), T(0));
    return static_cast<double>(sum) / values.size();
}

/**
 * Шаблонная функция для поиска минимума и максимума.
 * Ограничение: тип должен поддерживать оператор <.
 */
template<typename T>
std::pair<T, T> findMinMax(const std::vector<T>& values)
{
    static_assert(std::is_copy_constructible<T>::value, 
                  "Type must be copy constructible");
    
    if (values.empty()) {
        throw std::runtime_error("Empty container");
    }
    
    auto minIt = std::min_element(values.begin(), values.end());
    auto maxIt = std::max_element(values.begin(), values.end());
    
    return std::make_pair(*minIt, *maxIt);
}

/**
 * Шаблонная функция для фильтрации элементов.
 */
template<typename T, typename Predicate>
std::vector<T> filterElements(const std::vector<T>& source, Predicate pred)
{
    std::vector<T> result;
    std::copy_if(source.begin(), source.end(), 
                 std::back_inserter(result), pred);
    return result;
}

/**
 * Шаблонная функция для преобразования элементов.
 */
template<typename TIn, typename TOut, typename Transform>
std::vector<TOut> transformElements(const std::vector<TIn>& source, Transform func)
{
    std::vector<TOut> result;
    result.reserve(source.size());
    std::transform(source.begin(), source.end(), 
                   std::back_inserter(result), func);
    return result;
}

/**
 * Шаблонная функция для подсчета элементов, удовлетворяющих условию.
 */
template<typename T, typename Predicate>
size_t countIf(const std::vector<T>& source, Predicate pred)
{
    return std::count_if(source.begin(), source.end(), pred);
}

/**
 * Шаблонная функция проверки наличия элементов, удовлетворяющих условию.
 */
template<typename T, typename Predicate>
bool anyOf(const std::vector<T>& source, Predicate pred)
{
    return std::any_of(source.begin(), source.end(), pred);
}
