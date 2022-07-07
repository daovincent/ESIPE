import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

public class DeliverySystem {
    public static void main(String[] args) {
        ArrayBlockingQueue<WareHouse.Order> toPrepare=new ArrayBlockingQueue<>(10);
        ArrayList<ArrayBlockingQueue<WareHouse.Order>> toDelivery=new ArrayList<>();

        for(int i = 0 ; i < WareHouse.DESTINATIONS ; i++ )
            toDelivery.add((new ArrayBlockingQueue<>(10)));

        new Thread(()->{
            // se charge de récupérer en boucle des commandes
            // en provenance de l'entrepôt en utilisant la méthode nextOrder.
            while(true){
                try {
                    var nextOrder=WareHouse.nextOrder();
                    toPrepare.put(nextOrder);
                    System.out.println("New order : "+ nextOrder);
                } catch (InterruptedException e) {
                    System.out.println("Thread interrupted : "+ Thread.currentThread());
                    return;
                }
            }
        }).start();

        IntStream.range(0, 3).forEach(j -> {
            //préparer les colis (parcels), c'est à dire d'obtenir
            // leur numéro de destination à partir des commandes récupérées,
            // en utilisant la méthode prepareParcel.
            new Thread(()->{
                while(true){
                    try{
                        var order=toPrepare.take();
                        var destOp=WareHouse.prepareParcel(order);
                        if(destOp.isEmpty()) System.out.println("Item is missing : "+order);
                        else {
                            var dest=destOp.get();
                            System.out.println("--> "+order + " for dispatch to "+ dest);
                            toDelivery.get(dest).put(order);
                        }
                    }catch (InterruptedException e){
                        System.out.println("Thread interrupted : "+ Thread.currentThread());
                        return;
                    }
                }
            }).start();
        });

        //  prépare les livraisons (delivery), c'est à dire qu'il fait des listes de 10 commandes
        //  (sans en oublier, ni en dupliquer) pour cette destination et vérifie que
        //  chaque liste est correcte en utilisant la méthode checkDelivery.
        for(int i=0;i<WareHouse.DESTINATIONS;i++){
            var orderId=i;
            new Thread(()->{
                var prep=toDelivery.get(orderId);
                ArrayList<WareHouse.Order> list = new ArrayList<>();
                while(true){
                    try{
                        list.add(prep.take());
                        if(list.size()==10){
                            WareHouse.checkDelivery(orderId,list);
                            System.out.println("Delivery to "+ orderId + " : "+ list);
                            list.clear();
                        }
                    }catch (InterruptedException e){
                        System.out.println("Thread was interrupted");
                        return;
                    }
                }
            }).start();
        }
    }


}
