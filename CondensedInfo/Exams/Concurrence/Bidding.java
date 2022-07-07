import java.util.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;

public class Bidding {
    private final int nbParcitipants;
    private final HashMap<Thread,Integer> bids=new HashMap<>();
    private final ArrayList<Thread> threads=new ArrayList<>();
    private final Object lock = new Object();
    private Thread winner;

    public Bidding(int nbParcitipants) {
        synchronized (lock){
            this.nbParcitipants = nbParcitipants;
        }
    }

    public boolean registerAndWait() throws InterruptedException {
        synchronized (lock){
            if(nbParcitipants==threads.size())
                return false;
            threads.add(Thread.currentThread());
            if(threads.size()==nbParcitipants) lock.notifyAll();

            while(threads.size() != nbParcitipants) lock.wait();
            return true;
        }
    }
    public Thread bid(int value) throws InterruptedException {
        synchronized (lock){
            if(!threads.contains(Thread.currentThread()) && bids.get(Thread.currentThread())!=null)
                throw new IllegalStateException("Illegal thread");

            bids.put(Thread.currentThread(),value);
            if (bids.size()==nbParcitipants) {
                winner = bids.entrySet().stream().max(Comparator.comparingInt(e -> e.getValue())).get().getKey();
                lock.notifyAll();
            }
            while(bids.size()!=nbParcitipants)
                lock.wait();
            return winner;
        }
    }

    public static void main(String[] args) {
        var bidding=new Bidding(3);
        IntStream.range(0,5).forEach(j->{
            new Thread(() -> {
                try{
                    if(!bidding.registerAndWait()) {
                        System.out.println(Thread.currentThread().getName() + " not bidding");
                        return;
                    }
                    var bid=(int) (Math.random()*10+1);
                    if(Thread.currentThread().equals(bidding.bid(bid)))
                        System.out.println(Thread.currentThread().getName()+" bid = "+bid + " wins");
                    else System.out.println(Thread.currentThread().getName()+" bid = "+bid + " loses");
                } catch (InterruptedException e) {
                    return;
                }
            }).start();
        });
    }
}
