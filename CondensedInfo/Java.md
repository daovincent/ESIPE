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
