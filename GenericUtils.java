package videoprokat;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

/**
 * Утилитный класс с generic методами.
 * Демонстрирует использование generics и ограничений на типы.
 */
public class GenericUtils {
    
    /**
     * Generic функция для вычисления среднего значения.
     * Ограничение: работает только с числовыми типами (Number).
     */
    public static <T extends Number> double calculateAverage(List<T> values) {
        if (values == null || values.isEmpty()) {
            return 0.0;
        }
        
        double sum = values.stream()
                          .mapToDouble(Number::doubleValue)
                          .sum();
        return sum / values.size();
    }
    
    /**
     * Generic функция для поиска минимума и максимума.
     * Ограничение: тип должен быть Comparable.
     */
    public static <T extends Comparable<T>> Pair<T, T> findMinMax(List<T> values) {
        if (values == null || values.isEmpty()) {
            throw new IllegalArgumentException("Empty list");
        }
        
        T min = Collections.min(values);
        T max = Collections.max(values);
        
        return new Pair<>(min, max);
    }
    
    /**
     * Generic функция для фильтрации элементов.
     */
    public static <T> List<T> filterElements(List<T> source, Predicate<T> predicate) {
        return source.stream()
                    .filter(predicate)
                    .collect(Collectors.toList());
    }
    
    /**
     * Generic функция для преобразования элементов.
     */
    public static <T, R> List<R> transformElements(List<T> source, Function<T, R> mapper) {
        return source.stream()
                    .map(mapper)
                    .collect(Collectors.toList());
    }
    
    /**
     * Generic функция для подсчета элементов, удовлетворяющих условию.
     */
    public static <T> long countIf(List<T> source, Predicate<T> predicate) {
        return source.stream()
                    .filter(predicate)
                    .count();
    }
    
    /**
     * Generic функция проверки наличия элементов, удовлетворяющих условию.
     */
    public static <T> boolean anyOf(List<T> source, Predicate<T> predicate) {
        return source.stream()
                    .anyMatch(predicate);
    }
    
    /**
     * Generic функция проверки, что все элементы удовлетворяют условию.
     */
    public static <T> boolean allOf(List<T> source, Predicate<T> predicate) {
        return source.stream()
                    .allMatch(predicate);
    }
    
    /**
     * Generic функция для удаления элементов по условию.
     */
    public static <T> int removeIf(List<T> source, Predicate<T> predicate) {
        int originalSize = source.size();
        source.removeIf(predicate);
        return originalSize - source.size();
    }
    
    /**
     * Вспомогательный класс для хранения пары значений.
     */
    public static class Pair<F, S> {
        private final F first;
        private final S second;
        
        public Pair(F first, S second) {
            this.first = first;
            this.second = second;
        }
        
        public F getFirst() { return first; }
        public S getSecond() { return second; }
        
        @Override
        public String toString() {
            return "(" + first + ", " + second + ")";
        }
    }
}
