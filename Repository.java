package videoprokat;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

/**
 * Generic класс Repository для хранения и управления объектами.
 * Требование: тип T должен быть производным от базового класса.
 * 
 * @param <T> Тип хранимых объектов
 */
public class Repository<T> {
    
    private List<T> items;
    
    /**
     * Не generic конструктор.
     */
    public Repository() {
        this.items = new ArrayList<>();
    }
    
    /**
     * Не generic метод: добавление элемента.
     */
    public void add(T item) {
        if (item != null) {
            items.add(item);
        }
    }
    
    /**
     * Не generic метод: удаление элемента по индексу.
     */
    public void remove(int index) {
        if (index >= 0 && index < items.size()) {
            items.remove(index);
        }
    }
    
    /**
     * Generic метод: поиск элемента по предикату.
     */
    public <R extends T> R findIf(Predicate<T> predicate) {
        return (R) items.stream()
                       .filter(predicate)
                       .findFirst()
                       .orElse(null);
    }
    
    /**
     * Generic метод: поиск всех элементов по предикату.
     */
    public <R extends T> List<R> findAll(Predicate<T> predicate) {
        return (List<R>) items.stream()
                             .filter(predicate)
                             .collect(Collectors.toList());
    }
    
    /**
     * Generic метод: сортировка элементов.
     */
    public <R extends T> void sort(Comparator<T> comparator) {
        items.sort(comparator);
    }
    
    /**
     * Не generic метод: сортировка по умолчанию (если T implements Comparable).
     */
    public void sortDefault() {
        if (!items.isEmpty() && items.get(0) instanceof Comparable) {
            Collections.sort((List<Comparable>) items);
        }
    }
    
    /**
     * Generic метод: удаление элементов по предикату.
     */
    public <R extends T> int removeIf(Predicate<T> predicate) {
        int originalSize = items.size();
        items.removeIf(predicate);
        return originalSize - items.size();
    }
    
    /**
     * Generic метод: применение функции ко всем элементам.
     */
    public <R> void forEach(Consumer<T> action) {
        items.forEach(action);
    }
    
    /**
     * Generic метод: преобразование элементов.
     */
    public <R> List<R> map(Function<T, R> mapper) {
        return items.stream()
                   .map(mapper)
                   .collect(Collectors.toList());
    }
    
    /**
     * Generic метод: группировка элементов.
     */
    public <K> Map<K, List<T>> groupBy(Function<T, K> classifier) {
        return items.stream()
                   .collect(Collectors.groupingBy(classifier));
    }
    
    /**
     * Не generic метод: получение всех элементов.
     */
    public List<T> getAll() {
        return new ArrayList<>(items);
    }
    
    /**
     * Не generic метод: получение элемента по индексу.
     */
    public T get(int index) {
        return (index >= 0 && index < items.size()) ? items.get(index) : null;
    }
    
    /**
     * Не generic метод: размер репозитория.
     */
    public int size() {
        return items.size();
    }
    
    /**
     * Не generic метод: проверка на пустоту.
     */
    public boolean isEmpty() {
        return items.isEmpty();
    }
    
    /**
     * Не generic метод: очистка репозитория.
     */
    public void clear() {
        items.clear();
    }
    
    /**
     * Generic метод: фильтрация с созданием нового репозитория.
     */
    public <R extends T> Repository<R> filter(Predicate<T> predicate) {
        Repository<R> result = new Repository<>();
        items.stream()
            .filter(predicate)
            .forEach(item -> result.add((R) item));
        return result;
    }
}
