import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class EggCatcher {

    private String egg=null;
    private int waiting;
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition space = lock.newCondition();
    private final Condition drop=lock.newCondition();
    private final Condition catched=lock.newCondition();
    private boolean abort;
    public void dropEgg(String arg) throws InterruptedException {
        lock.lock();
        try{
            if(abort) {
                Thread.currentThread().interrupt();
                throw new IllegalStateException("abort state activated");
            }
            waiting++;
            while(egg!=null){
                if(abort) {
                    Thread.currentThread().interrupt();
                    throw new InterruptedException("Abort");
                }
                space.await();
            }
            this.egg=arg;
            waiting--;
            drop.signal();
            catched.await();
        }catch (InterruptedException e){
            abort=true;
            drop.signalAll();
            space.signalAll();
            catched.signalAll();
            Thread.currentThread().interrupt();
            throw new InterruptedException();
        }
        finally {
            lock.unlock();
        }
    }
    public String catchEgg() throws InterruptedException {
        lock.lock();
        try{
            while(egg==null){
                drop.await();
            }
            if(abort){
                Thread.currentThread().interrupt();
                return null;
            }
            var res=egg;
            egg=null;
            space.signal();
            catched.signal();
            return res;
        }finally {
            lock.unlock();
        }
    }
    public int waitingToDrop(){
        lock.lock();
        try{
            return waiting;
        }finally {
            lock.unlock();
        }
    }

}
