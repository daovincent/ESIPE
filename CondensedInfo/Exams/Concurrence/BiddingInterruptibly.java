import java.nio.channels.AsynchronousCloseException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.stream.IntStream;

public class BiddingInterruptibly {
    private final int nbParcitipants;
    private final HashMap<Thread,Integer> bids=new HashMap<>();
    private final ArrayList<Thread> threads=new ArrayList<>();
    private final Object lock = new Object();
    private Thread winner;
    private boolean closed=false;

    public void close(){
        synchronized (lock){
            closed=true;
            System.out.println("Bidding closed");
            threads.forEach(Thread::interrupt);
            lock.notifyAll();
        }
    }

    public BiddingInterruptibly(int nbParcitipants) {
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
            System.out.println(Thread.currentThread()+" registered ! ");
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
    public Thread bid(int value) throws InterruptedException {
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
                    close();
                    throw new InterruptedException();
                }
            }
            return winner;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        var bidding=new BiddingInterruptibly(5);
        var threads=new Thread[5];
        IntStream.range(0,5).forEach(j->{
            threads[j]=new Thread(() -> {

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
                    if(j==4) Thread.sleep(10000);
                    if(Thread.currentThread().equals(bidding.bid(bid)))
                        System.out.println(Thread.currentThread().getName()+" bid = "+bid + " wins");
                    else System.out.println(Thread.currentThread().getName()+" bid = "+bid + " loses");
                } catch (InterruptedException e) {
                    System.out.println(Thread.currentThread().getName() + " bidding closed");
                    return;
                }

            });
            threads[j].start();
        });

//        bidding.close();
        Thread.sleep(5000);
        threads[3].interrupt();
    }
}
