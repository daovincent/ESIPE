import java.nio.channels.AsynchronousCloseException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.stream.IntStream;

public class BiddingInterruptibly {
    private final int nbParticipants;
    private final LinkedHashMap<Thread,Integer> bids=new LinkedHashMap<>();
    private final ArrayList<Thread> threads=new ArrayList<>();
    private Thread winner;
    private final Object lock=new Object();
    private boolean closed;

    public BiddingInterruptibly(int nbParticipants) {
        this.nbParticipants = nbParticipants;
    }
    public boolean registerAndWait() throws InterruptedException, AsynchronousCloseException {
        synchronized (lock){
            if(closed) throw new IllegalStateException();
            var current=Thread.currentThread();
            if(threads.size()>=nbParticipants)
                return false;
            threads.add(current);
            if(threads.size()==nbParticipants)
                lock.notifyAll();
            while(threads.size()<nbParticipants) {
                try {
                    if (closed) throw new AsynchronousCloseException();
                    lock.wait();
                }catch (InterruptedException e){
                    threads.remove(current);
                    throw new InterruptedException();
                }
            }
            return true;
        }
    }
    public Thread bid(int value) throws InterruptedException, AsynchronousCloseException {
        synchronized (lock) {
            if(closed) throw new IllegalStateException();
            var current=Thread.currentThread();
            if (!threads.contains(current) || bids.containsKey(current))
                throw new IllegalStateException();
            bids.put(current,value);
            if(bids.size()==nbParticipants)
                lock.notifyAll();
            while(bids.size()<nbParticipants) {
                try {
                    if (closed) throw new AsynchronousCloseException();
                    lock.wait();
                }catch (InterruptedException e){
                    close();
                    throw new InterruptedException();
                }
            }
            return bids.entrySet().stream().max(Comparator.comparing(Map.Entry::getValue)).get().getKey();
        }
    }
    public void close(){
        synchronized (lock){
            closed=true;
            lock.notifyAll();
        }
    }


    public static void main(String[] args) throws InterruptedException {
        var bidding=new BiddingInterruptibly(5);
        var threads=new ArrayList<Thread>();
        IntStream.range(0,5).forEach(i->{
            var t=new Thread(()->{
                try {
                    if(!bidding.registerAndWait()){
                        System.out.println(Thread.currentThread().getName()+ " not bidding");
                        return;
                    }
                    var bid=(int) (Math.random() * 10) +1;
                    if(i==4) Thread.sleep(5000);
                    if(bidding.bid(bid).equals(Thread.currentThread()))
                        System.out.println(Thread.currentThread().getName()+ " (bid = "+ bid + " ) won.");
                    else
                        System.out.println(Thread.currentThread().getName()+ " (bid = "+ bid + " ) lost.");
                } catch (InterruptedException e) {
                    System.out.println(Thread.currentThread().getName()+" was interrupted");
                }catch (AsynchronousCloseException e){
                    System.out.println("Bidding was closed ...");
                }catch(IllegalStateException e){
                    System.out.println(Thread.currentThread().getName() + " Tried to register / bid but the bidding was already closed...");
                }
            });
            threads.add(t);
            t.start();
        });
        Thread.sleep(2000);
//        bidding.close();
        threads.get(3).interrupt();
    }
}
