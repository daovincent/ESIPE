# Concurrence 
Sources : Everything more or less comes from https://igm.univ-mlv.fr/coursconcurrence

## Synchronized
This makes the content of the block an "atomic operation". 
```java
private final Object lock=new Object();
synchronized(lock){
  // whatever data you interract with that could cause a failure somewhere
}
//useful functions to use with synchronized : 
lock.wait() // wait for someone to wake this thread, use in a while (!condition) to avoid false alerts syndrom
lock.notify/notifyAll() // wake a random thread or all sleeping threads
```
lock needs to be final.

## ReentrantLock
Pretty much the same thing as synchronized, but more flexible and easier to read thanks to "Conditions"
```java
private final ReentrantLock lock = new ReentrantLock();
private final Condition condition = lock.newCondition();
private void init() {
  lock.lock();
  try {   // ALWAYS use try finally to unlock at the end
    // Whatever you need to do
    condition.signal(); // or signalAll(), same as notify
  } finally {
    lock.unlock();
  }
}
private void someOtherFunction(){
  while (!done) {
    condition.await(); // Waits for the above function to signal
  }
}
```

## Producer/Consumer
Multiple threads that produce data, other threads that manages said data, a blocking queue to link the two sides
- ArrayBlockingQueue > Uses a circular array like ArrayDeque
- LinkedBlockingQueue > default size ain't fixed 
- SynchronousQueue > Single element at the time, doesn't stock it and we can't iterate over it

### Methods to use :
![BlockingQueueMethods](/CondensedInfo/assets/BlockingQueueFunctions.png)
In Producer/ Consumer, using methods that throw exceptions is a no-go

### Example
```java
var queue = new ArrayBlockingQueue<String>(10);
for (int i = 0; i < 3; i++) {
    new Thread(() -> {
        while (!Thread.interrupted()) {
            try {
                Thread.sleep(100);
                queue.put(Thread.currentThread().getName());
            } catch (InterruptedException e) {
                return;
            }
        }
    }).start();
}
for (int i = 0; i < 2; i++) {
  new Thread(() -> {
      while (!Thread.interrupted()) {
          try {
              Thread.sleep(500);
              System.out.println("next : " +  queue.take());
          } catch (InterruptedException e) {
              return;
          }
      }
  }).start();
}
```

## Executor Service
"I'm too lazy to write 'new Thread(()->...) so I use this instead" - Someone I know
