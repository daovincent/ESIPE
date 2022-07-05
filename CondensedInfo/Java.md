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
```java
        public void forEach(Consumer <? super Data<T>> consumer){
            for(int i=0;i<size;i++) consumer.accept(list.get(i));
        }
```
Here, "Data<T>" represents a record, since we want the forEach to iterate over the elements of our list of Data<T>.
Consumer -> Super because PECS 

  
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
      public Spliterator<T> splirarator(boolean onlyTagged){
        T[] copy = (T[]) new Object[size];
        System.arraycopy(elements,0,copy,0,size);
        int copyS;
        if(onlyTagged)
            copyS=sizeImportant;
        else copyS=copy.length;
        int size2=size;
        return new Spliterator<T>() {
            private int current; // actual elements returned
            private int pos; // pos in the array
            @Override
            public boolean tryAdvance(Consumer<? super T> action) {
                Objects.requireNonNull(action);
                if(current<copyS){
                    try{
                        if(onlyTagged){
                            while(pos<size2){
                                if(predicate.test(copy[pos])){
                                    action.accept(copy[pos]);
                                    current++;
                                }
                                pos++;
                            }
                        }
                        else {
                            action.accept(copy[pos++]);
                            current++;
                        }
                    } catch (IllegalStateException e) {
                        throw new ConcurrentModificationException(e);
                    }
                    return true;
                }
                return false;
            }

            @Override
            public Spliterator<T> trySplit() {
                return null;
            }

            @Override
            public long estimateSize() {
                return copyS-current;
            }

            @Override
            public int characteristics() {
                return NONNULL;
            }
        };
    }```

