import java.util.*;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class LeaderDict<T, U> {
    private final LinkedHashMap<T, ArrayList<U>> leaders;
    private final Function map;

    public LeaderDict(Function<? super U, T> map) {
        if (map == null) throw new NullPointerException();
        leaders = new LinkedHashMap<>();
        this.map = map;
    }
    @SuppressWarnings("unchecked")
    public void add(U element) {
        var lead = (T) map.apply(element);
        if (leaders.containsKey(lead))
            leaders.get(lead).add(element);
        else {
            leaders.put(lead, new ArrayList<>());
            leaders.get(lead).add(element);
        }
    }

    public int leaderCount() {
        return leaders.size();
    }

    @SuppressWarnings("unchecked")
    public List<U> valuesFor(Object i) {
        if (i == null) throw new NullPointerException();
        if (!leaders.containsKey((T) i)) return new ArrayList<>();
//        return leaders.get((T) i).stream().toList();
//        return !leaders.containsKey((T) i)?new ArrayList<>():leaders.get((T) i).stream().toList();
        class localView extends AbstractList<U> implements RandomAccess {
            private final List<U> list = leaders.get((T) i);
            private final int viewSize = list.size();

            @Override
            public U get(int index) {
                return list.get(index);
            }

            @Override
            public int size() {
                return viewSize;
            }
        }
        return new localView();
    }

    @Override
    public String toString() {
        var sb = new StringBuilder();
//        leaders.entrySet()
//                .forEach(e->e.getValue()
//                        .forEach(a->sb.append(e.getKey()).append(": ").append(a).append("\n")));
//        return sb.toString();
        forEach((manager, employee) -> {
            sb.append(manager).append(": ")
                    .append(employee).append("\n");
        });
        return sb.toString();
    }

    public void forEach(BiConsumer<? super T, ? super U> cons) {
        if (cons == null) throw new NullPointerException();
        leaders.forEach((key, value) -> value
                .forEach(a -> cons.accept(key, a)));
    }

    public void addAll(LeaderDict<? extends T, ? extends U> leaderDict2) {
        if (map.equals(leaderDict2.map())) {
            leaderDict2.leaders.forEach((key1, value1) -> {
                leaders.computeIfPresent(key1, (key, value) -> {
                    value.addAll(leaderDict2.leaders.get(key1));
                    return value;
                });
                leaders.computeIfAbsent(key1, value ->
                        new ArrayList<U>(leaderDict2.leaders.get(key1)));
            });
        } else {
            leaderDict2.leaders.values().forEach(data -> data.forEach(this::add));
        }
    }

    public Function map() {
        return map;
    }

    public Stream<U> values() {
        var list = leaders.values().stream().flatMap(Collection::stream).toList();
        return StreamSupport.stream(split(0,list.size(),list),true);
    }

    public Spliterator<U> split(int start, int end, List<U> list) {
        return new Spliterator<U>() {
            private int i = start;

            @Override
            public boolean tryAdvance(Consumer<? super U> action) {
                if(i<end){
                    try{
                        action.accept(list.get(i++));
                    } catch (IllegalStateException e) {
                        throw new ConcurrentModificationException(e);
                    }
                    return true;
                }
                return false;
            }

            @Override
            public Spliterator<U> trySplit() {
                var middle = (i + end) >> 1;
                if (middle == i) {
                    return null;
                }
                var spliterator = split(i, middle, list);
                i = middle;
                return spliterator;
            }

            @Override
            public long estimateSize() {
                return end - i;
            }

            @Override
            public int characteristics() {
                return SIZED;
            }
        };
    }
}
