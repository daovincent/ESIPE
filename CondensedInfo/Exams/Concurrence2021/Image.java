import java.util.Objects;

public record Image(String name, int size) {

    public Image {
        Objects.requireNonNull(name);
        if (size <= 0){
            throw new IllegalStateException();
        }
    }

    public static Image downloadImage(String url) throws InterruptedException {
        var parts = url.split("/");
        var name = parts[parts.length - 1];
        var size = Math.abs(name.hashCode()) % 1_000_000;
        System.out.println("Downloading image from " + url + " will take " + size % 10 + " seconds");
        Thread.sleep((size % 10) * 1000);
        return new Image(name, size);
    }
}
