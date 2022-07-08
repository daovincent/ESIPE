import java.nio.channels.AsynchronousCloseException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.stream.IntStream;

public class BiddingCloseable {
    private final int nbParticipants;
    private final LinkedHashMap<Thread,Integer> bids=new LinkedHashMap<>();
    private final ArrayList<Thread> threads=new ArrayList<>();
    private Thread winner;
    private final Object lock=new Object();
    private boolean closed;

    public BiddingCloseable(int nbParticipants) {
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
                if(closed) throw new AsynchronousCloseException();
                lock.wait();
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
                if(closed) throw new AsynchronousCloseException();
                lock.wait();
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
        var bidding=new BiddingCloseable(8);
        IntStream.range(0,5).forEach(i->{
            new Thread(()->{
                try {
                    if(!bidding.registerAndWait()){
                        System.out.println(Thread.currentThread().getName()+ " not bidding");
                        return;
                    }
                    var bid=(int) (Math.random() * 10) +1;
                    if(bidding.bid(bid).equals(Thread.currentThread()))
                        System.out.println(Thread.currentThread().getName()+ " (bid = "+ bid + " ) won.");
                    else
                        System.out.println(Thread.currentThread().getName()+ " (bid = "+ bid + " ) lost.");
                } catch (InterruptedException e) {
                    throw new AssertionError(e);
                }catch (AsynchronousCloseException e){
                    System.out.println("Bidding was closed ...");
                }
            }).start();
        });
        Thread.sleep(2000);
        bidding.close();
    }
}
