import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

public class ImageCache {
    private final Map<String,String> urls;
    private enum state{ NOT,DURING,DONE};
    private final HashMap<String, Image> images = new HashMap<>();
    private final HashMap<String,state> states=new HashMap<String, state>();

    public ImageCache(Map<String,String> urls) {
        synchronized (images) {
            this.urls = Map.copyOf(urls);
            for(var url : urls.entrySet()){
                states.put(url.getKey(),state.NOT);
            }
        }
    }
    public Optional<Image> get(String name) throws InterruptedException {
        Objects.requireNonNull(name);
        synchronized (images) {
            var url = urls.get(name);
            if (url == null) {
                return Optional.empty();
            }

            if(!states.get(name).equals(state.NOT)){
                while(states.get(name)!=state.DONE)
                    images.wait();
                return Optional.of(images.get(name));
            }
        }
        // Si dans le synchronized, téléchargement simultané entre threads marche pas
        var image = Image.downloadImage(urls.get(name));
        synchronized (images){
            images.put(name, image);
            states.put(name,state.DONE);
            images.notifyAll();
            return Optional.of(image);
        }
    }
}
