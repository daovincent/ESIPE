import java.util.Map;

public class ImageCacheApplication {
    public static void main(String[] args) throws InterruptedException {
        var urls = Map.of("bird", "http://example.com/bird3.png",
                          "giraffe", "http://example.com/giraffe123.png",
                          "mouse", "http://example.com/mouse2.png");
        var cache = new ImageCache(urls); new Thread(() -> {
            try {
                System.out.println(Thread.currentThread().getName() + " : " + cache.get("giraffe").orElseThrow());
                System.out.println(Thread.currentThread().getName() + " : " + cache.get("mouse").orElseThrow());
                System.out.println(Thread.currentThread().getName() + " : " + cache.get("bird").orElseThrow());
            } catch (InterruptedException e){
                throw new AssertionError();
            }
        }).start();
        System.out.println(Thread.currentThread().getName() + " : " + cache.get("bird").orElseThrow());



    }
}