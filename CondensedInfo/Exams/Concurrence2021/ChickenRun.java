import java.util.stream.IntStream;

public class ChickenRun {
    public static void main(String[] args) {
        var ec=new EggCatcher();
        IntStream.range(0,5).forEach(i->{
            new Thread(()->{
                for(int j=0;j<10;j++){
                    var egg="T"+i+"-"+j;
                    try {
                        ec.dropEgg(egg);
                        if(i==4) Thread.currentThread().interrupt();
                    } catch (InterruptedException e) {
                        System.out.println("Thread "+i+" was interrupted");
                        break;
                    } catch (IllegalStateException e ){
                        System.out.println("Abort was activated");
                        break;
                    }
                }
            }).start();
        });
        var catcher=new Thread(()->{
            while(true){
                try {
                    var res=ec.catchEgg();
                    System.out.println(res);
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    System.out.println("Thread was interrupted.");
                    return;
                }
            }
        });
        catcher.setDaemon(true);
        catcher.start();
        var count=new Thread(()->{
            while(!Thread.currentThread().isInterrupted()) {
                try {
                    Thread.sleep(1000);
                    System.out.println(ec.waitingToDrop()+" threads waiting to drop their eggs");
                } catch (InterruptedException e) {
                    throw new AssertionError(e);
                }
            }

        });
        count.setDaemon(true);
        count.start();
    }
}
