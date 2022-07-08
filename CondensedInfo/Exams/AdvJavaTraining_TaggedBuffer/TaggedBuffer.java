import java.util.*;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class TaggedBuffer<T> {
    private Predicate predicate;
    private int size;
    private int maxSize = 4;
    private int sizeImportant;
    private T[] elements;
    private int firstTag;

    public TaggedBuffer(Predicate<? super T> predicate) {
        if (predicate == null) throw new NullPointerException();
        elements = (T[]) new Object[4];
        this.predicate = predicate;
    }

    public int size(boolean onlyTagged) {
        if (onlyTagged) return sizeImportant;
        return size;
    }

    public void add(T element) {
        if (element == null) throw new NullPointerException();
        elements[size] = element;
        size++;
        if (size == maxSize) {
            maxSize *= 2;
            var newTab = (T[]) new Object[maxSize];
            for (int i = 0; i < size; i++) newTab[i] = elements[i];
            elements = newTab;
        }
        if (predicate.test(element)) {
            if (sizeImportant == 0) firstTag = size - 1;
            sizeImportant++;
        }
    }

    public Optional<T> findFirst(boolean onlyTagged) {
        if (size == 0) return Optional.empty();
        if (onlyTagged) {
            if (sizeImportant == 0) return Optional.empty();
            return Optional.of(elements[firstTag]);
        }
        return Optional.of(elements[0]);
    }

    public void forEach(boolean onlyTagged, Consumer<? super T> consumer) {
        Stream streamElements;
        if (onlyTagged) streamElements = Arrays.stream(elements).filter(e -> e != null).filter(predicate);
        else streamElements = Arrays.stream(elements).filter(e -> e != null);
        streamElements.forEach(e -> consumer.accept((T) e));
    }

    public Iterator<T> iterator(boolean onlyTagged) {
        return new Iterator<T>() {
            private int current;// elements returned
            private int pos;
            private int copySize = size;
            private int copySizeI = sizeImportant;
            private T[] copy = elements;

            @Override
            public boolean hasNext() {
                if (onlyTagged) return current < copySizeI;
                return current < copySize;
            }

            @Override
            public T next() {
                if (!hasNext()) throw new NoSuchElementException();
                T res;
                if (onlyTagged) {
                    while (true) {
                        res = copy[pos++];
                        if (predicate.test(res)) {
                            current++;
                            return res;
                        }
                    }
                }
                res = copy[pos++];
                current++;
                return res;

            }
        };
    }

    public List<T> asTaggedList() {
        return Arrays.stream(elements).filter(e -> e != null).filter(predicate).toList();
    }

    public Spliterator<T> splirarator(int start, int end, T[] copy, boolean onlyTagged) {
        return new Spliterator<T>() {
            int i = start;

            @Override
            public boolean tryAdvance(Consumer<? super T> action) {
                Objects.requireNonNull(action);
                if (i < end) {
                    try {
                        if (onlyTagged) {
                            while (i < end) {
                                if (predicate.test(copy[i])) action.accept(copy[i]);
                                i++;
                            }
                        } else action.accept(copy[i++]);

                    } catch (IllegalStateException e) {
                        throw new ConcurrentModificationException(e);
                    }
                    return true;
                }
                return false;
            }

            @Override
            public Spliterator<T> trySplit() {
                var middle = (i + end) >> 1;
                if (middle == i) {
                    return null;
                }
                var spliterator = splirarator(i, middle, copy, onlyTagged);
                i = middle;
                return spliterator;
            }

            @Override
            public long estimateSize() {
                return end - i;
            }

            @Override
            public int characteristics() {
                return NONNULL | SIZED | SUBSIZED;
            }
        };
    }

    public Stream<T> stream(boolean onlyTagged) {
        T[] copy = (T[]) new Object[size];
        System.arraycopy(elements, 0, copy, 0, size);
        return StreamSupport.stream(splirarator(0,size,copy,onlyTagged), false);
    }


}
