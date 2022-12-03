package fr.uge.table;

import java.lang.reflect.RecordComponent;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Objects;
import java.util.function.Function;
import java.util.function.IntFunction;
import java.util.function.IntUnaryOperator;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

public final class IntTable {
    private final Impl storage;
    public void set(String str, int val){
        Objects.requireNonNull(str);
        storage.set(str,val);
    }
    public int size(){
        return storage.size();
    }
    public int get(String str,int def){
        Objects.requireNonNull(str);
        return storage.get(str,def);
    }
    public IntTable() {
        storage = new MapImpl();
    }
    private IntTable(Impl map){
        this.storage=map;
    }

    static HashMap<String,Integer> recordComponentIndexes(RecordComponent[] components) {
        var map = new LinkedHashMap<String,Integer>();
        int i = 0;
        for(var component : components){
            map.put(component.getName(),i++);
        }
        return map;
    }

    public static <T> IntTable from(Class<T> c) {
        Objects.requireNonNull(c);
        if(! c.isRecord()) throw new IllegalArgumentException("This must be a record");
        return new IntTable(new RecordImpl(recordComponentIndexes(c.getRecordComponents())));
    }

    public IntTable apply(IntUnaryOperator func) {
        Objects.requireNonNull(func);
        return new IntTable(storage.apply(func));

    }
    @Override
    public String toString(){
        return storage.toString();
    }
    sealed interface Impl{
        void set(String str, int val);
        int size();
        int get(String str,int def);

        Impl apply(IntUnaryOperator func);
        @Override
        String toString();
    }
    private static final class MapImpl implements Impl{
        private final LinkedHashMap<String,Integer> table= new LinkedHashMap<>();
        public void set(String str, int val){
            table.put(str,val);
        }
        public int size(){
            return table.size();
        }
        public int get(String str,int def){
            return table.getOrDefault(str,def);
        }

        public MapImpl apply(IntUnaryOperator func){
            var tmp= new MapImpl();
            table.forEach((key, value) -> tmp.set(key, func.applyAsInt(value)));
            return tmp;
        }
        @Override
        public String toString(){
            return "{"+table.entrySet().stream().map(e->e.getKey()+"="+e.getValue()).collect(Collectors.joining(", "))+"}";
        }
    }

    private static final class RecordImpl implements Impl{
        private final LinkedHashMap<String,Integer> table;

        private RecordImpl(HashMap<String, Integer> table) {
            this.table = new LinkedHashMap<>(table);
            table.keySet().forEach(k-> set(k,0));
        }

        public void set(String str, int val){
            if(!table.containsKey(str))
                throw new IllegalStateException();
            table.put(str,val);
        }
        public int size(){
            return table.size();
        }
        public int get(String str,int def){
            return table.getOrDefault(str,def);
        }
        public Impl apply(IntUnaryOperator func){
            var tmp= new RecordImpl(table);
            table.forEach((key, value) -> tmp.set(key, func.applyAsInt(value)));
            return tmp;
        }
        @Override
        public String toString(){
            return "{"+table.entrySet().stream().map(e->e.getKey()+"="+e.getValue()).collect(Collectors.joining(", "))+"}";
        }
    }

}
