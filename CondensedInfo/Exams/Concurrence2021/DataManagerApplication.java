import javax.xml.crypto.Data;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.stream.IntStream;

public class DataManagerApplication {
    public static void main(String[] args) {
        ArrayBlockingQueue<DataManager.ZipFile> zips=new ArrayBlockingQueue<>(10);
        ArrayBlockingQueue<List<DataManager.Image>> images=new ArrayBlockingQueue<>(10);
        ArrayList<Thread> threads=new ArrayList<>();

        // Récup
        IntStream.range(0,3).forEach(i->{
            var t=new Thread(()->{
                while(!Thread.currentThread().isInterrupted()) {
                    try {
                        DataManager.ZipFile zip = DataManager.retrieveFromClients();
                        zips.put(zip);
                    } catch (InterruptedException e) {
                        System.out.println(Thread.currentThread() + " was interrupted");
                        return;
                    }
                }
            });
            threads.add(t);
        });
        // Décompression
        IntStream.range(0,2).forEach(i->{
            var t=new Thread(()->{
                while(!Thread.currentThread().isInterrupted()) {
                    try{
                        var zip=zips.take();
                        images.put(DataManager.unzip(zip));
                    } catch (InterruptedException e) {
                        System.out.println(Thread.currentThread() + " was interrupted");
                        return;
                    }catch(IllegalStateException e){
                        threads.forEach(Thread::interrupt);
                        System.out.println(Thread.currentThread()+ " commit sudoku");
                        return;
                    }
                }
            });
            threads.add(t);
        });
        // Archivage
        IntStream.range(0,DataManager.DATACENTERS.size()).forEach(i->{
            var t=new Thread(()->{
                var dc=DataManager.DATACENTERS.get(i);
                ArrayList<DataManager.Image> batch=new ArrayList<>(dc.batchCapacity());
                while(!Thread.currentThread().isInterrupted()) {
                    var imgs = images.poll();
                    if (imgs == null) continue;

                    for (DataManager.Image image : imgs) {
                        if (!image.dataCenter().equals(dc)) {
                            // ignore images not meant for dataCenter
                            continue;
                        }
                        batch.add(image);
                        if (batch.size() == dc.batchCapacity()) {
                            System.out.println("Archiving images " + batch);
                            try {
                                DataManager.archive(batch, dc);
                            } catch (InterruptedException e) {
                                System.out.println(Thread.currentThread() + " was interrupted");
                                return;
                            }
                            batch.clear();
                        }
                    }
                }
            });
            threads.add(t);
        });

        for(var t : threads){
            t.start();
        }
        System.out.println("All threads started");
    }
}
