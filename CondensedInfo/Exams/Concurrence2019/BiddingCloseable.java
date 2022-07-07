import java.nio.channels.AsynchronousCloseException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.stream.IntStream;

public class BiddingCloseable {
    private final int nbParcitipants;
    private final HashMap<Thread,Integer> bids=new HashMap<>();
    private final ArrayList<Thread> threads=new ArrayList<>();
    private final Object lock = new Object();
    private Thread winner;
    private boolean closed=false;

    public void close(){
        synchronized (lock){
            closed=true;
            threads.forEach(Thread::interrupt);
            lock.notifyAll();
        }
    }

    public BiddingCloseable(int nbParcitipants) {
        synchronized (lock){
            this.nbParcitipants = nbParcitipants;
        }
    }

    public boolean registerAndWait() throws AsynchronousCloseException {
        synchronized (lock){
            if(closed) throw new IllegalStateException();

            if(nbParcitipants==threads.size())
                return false;
            threads.add(Thread.currentThread());
            if(threads.size()==nbParcitipants) lock.notifyAll();

            while(threads.size() != nbParcitipants) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    throw new AsynchronousCloseException();
                }
            }
            return true;
        }
    }
    public Thread bid(int value) throws AsynchronousCloseException {
        synchronized (lock){
            if(!threads.contains(Thread.currentThread()) && bids.get(Thread.currentThread())!=null)
                throw new IllegalStateException("Illegal thread");

            bids.put(Thread.currentThread(),value);
            if (bids.size()==nbParcitipants) {
                winner = bids.entrySet().stream().max(Comparator.comparingInt(e -> e.getValue())).get().getKey();
                lock.notifyAll();
            }
            while(bids.size()!=nbParcitipants) {
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    throw new AsynchronousCloseException();
                }
            }
            return winner;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        var bidding=new BiddingCloseable(8);
        IntStream.range(0,5).forEach(j->{
            new Thread(() -> {

                try {
                    if(!bidding.registerAndWait()) {
                        System.out.println(Thread.currentThread().getName() + " not bidding");
                        return;
                    }
                } catch (AsynchronousCloseException e) {
                    System.out.println(Thread.currentThread().getName() + " registration closed");
                    return;
                }
                var bid=(int) (Math.random()*10+1);
                try {
                    if(Thread.currentThread().equals(bidding.bid(bid)))
                        System.out.println(Thread.currentThread().getName()+" bid = "+bid + " wins");
                    else System.out.println(Thread.currentThread().getName()+" bid = "+bid + " loses");
                } catch (AsynchronousCloseException e) {
                    System.out.println(Thread.currentThread().getName() + " bidding closed");
                    return;
                }

            }).start();
        });

//        Thread.sleep(500);
        bidding.close();
    }
}
