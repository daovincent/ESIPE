# Advanced Java

## PECS
Producer -> Extends / Consumer -> Super

- "Producer" is the "input", the "Data" you receive is below you or equal in the tree
  - for example a list that we are going to ONLY READ FROM. 
- "Consumer" is the "output", the "Data" you produce is above you or equal in the tree
  - for example a list that we are going to ONLY WRITE INTO.

### Example : 
```java
public class Collections { 
  public static <T> void copy(List<? super T> dest, List<? extends T> src) {
      for (int i = 0; i < src.size(); i++) 
        dest.set(i, src.get(i)); 
  } 
}
```

Source : https://github.com/khenissimehdi/PECS-JAVA


## Write your own forEach
### Case of a simple Consumer : 
```java
        public void forEach(Consumer <? super Data<T>> consumer){
            for(int i=0;i<size;i++) consumer.accept(list.get(i));
        }
```
Here, "Data<T>" represents a record, since we want the forEach to iterate over the elements of our list of Data<T>.
Consumer -> Super because PECS 

  
### Case of a BiConsumer
  ```java
  public void forEach(BiConsumer<? super T,? super U> cons ) {
        if(cons==null) throw new NullPointerException();
        data.entrySet()
                .forEach(e->e.getValue()
                        .forEach(a-> cons.accept(e.getKey(),a)));
    }
```
The data we go through is a LinkedHashMap<T, ArrayList<U>>.


BiConsumer has to be told ? super ... 2 times in order to be able to get the 2 args from a lambda 


Super because PECS
  

## Write your own Iterator 
  
First, in order to use the for ( var a : class ) , the "class" you want to iterate over has to be Iterable, so it needs to IMPLEMENT Iterable<The data you want to iterate over>.
  
  
If the structure to iterate over is simple you might be able to do "return data.iterator()", doesn't cost too much time to try...
  
  
Otherwise : 
```java
  public Iterator<Data<T>> iterator(){
      // Here you put useful outside variables accessible here that might be useful IN the iterator...
      return new Iterator<>() {
          // Here you put useful variables for your iterator ...
          // You can also put copies of your class variables, in order for the iterator to only see a snapshot of the class
  
          private int current; // often useful to know at what index you are  

          @Override
          public boolean hasNext() {
              return current<max; 
          }

          @Override
          public Data<T> next() {
              if(!hasNext()) throw new NoSuchElementException();
              var res=data.get(current);
              current++;
              return res;
          }
      };
  }
  ```
  
  
## The one and only Spliterator
  
  First, write your function with "return new Spliterator<T>();" and let your IDE show the skeletton of functions to implement.
  

  ```java
  public Spliterator<T> splirarator(int start, int end,T[] copy){
    return new Spliterator<T>() {
        // Other useful variables ...
        private int i=start; // pos in the array

        // Inside the try, you do pretty much the same as an Iterator
        @Override
        public boolean tryAdvance(Consumer<? super T> action) {
            Objects.requireNonNull(action);
            if(i<end){
                try{
                    action.accept(copy[pos++]);
                } catch (IllegalStateException e) {
                    throw new ConcurrentModificationException(e);
                }
                return true;
            }
            return false;
        }
        // This is the splitting function, here you give the instructions which to follow to separate the iterator into two instances
        // return null if you don't want your iterator to be able to split, which makes the use of a spliterator debatable...
        @Override
        public Spliterator<T> trySplit() {
             var middle = (i + end) >> 1;
                if (middle == i) {
                    return null;
                }
                var spliterator = createSpliterator(i, middle, array);
                i = middle;
                return spliterator;
        }

        // We have hasNext() at home
        @Override 
        public long estimateSize() {
            return end-i;
        }
        // Here you can specify characteristics of the spliterator 
        @Override
        public int characteristics() {
            return NONNULL | SIZED | SUBSIZED;
        }
    };
}
```

### Spliterator characteristics 
- SIZED – if it's capable of returning an exact number of elements with the estimateSize() method
- SORTED – if it's iterating through a sorted source
- SUBSIZED – if we split the instance using a trySplit() method and obtain Spliterators that are SIZED as well
- CONCURRENT – if source can be safely modified concurrently
- DISTINCT – if for each pair of encountered elements x, y, !x.equals(y)
- IMMUTABLE – if elements held by source can't be structurally modified
- NONNULL – if source holds nulls or not
- ORDERED – if iterating over an ordered sequence


Source : https://www.baeldung.com/java-spliterator


## Don't want a defensive copy for your lists ? No problem

Using a defensive copy means making a copy. It is often an unmodifiable copy but still, it's not efficient.

In order to reach "peak" efficiency, it is possible to create a class which extends AbstractList and implements  RandomAccess (in order to have constant RandomAccess)
```java
public List<U> valuesFor(Object i) { // Using object in order to check no matter the type of the key, if it's wrong it won't output anything anyways
        if ( i == null ) throw new NullPointerException();
        if(!data.containsKey((T)i)) return new ArrayList<>();
        class localView extends AbstractList<U> implements RandomAccess{
            private final List<U> list=data.get((T) i);
            private final int viewSize=list.size();
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
```
There's only 2 methods to implement and they're pretty straightforward. Since it's a view the size won't change which makes this possible.
