import java.util.List;
import java.util.Objects;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class DataManager {

    public static List<DataCenter> DATACENTERS = List.of(new DataCenter("Paris", 5), new DataCenter("Madrid", 3),
            new DataCenter("Rome", 2));

    /**
     * Represents a DataCenter with its name and size of the batch size it accepts
     */
    public record DataCenter(String name, int batchCapacity) {
        public DataCenter {
            Objects.requireNonNull(name);
            if (batchCapacity <= 0) {
                throw new IllegalArgumentException("Invalid batch capacity : " + batchCapacity);
            }
        }
    }

    /**
     * Represents an Image with its name and the DataCenter where it wants to be
     * archived
     */
    public record Image(String name, DataCenter dataCenter) {

        public Image {
            Objects.requireNonNull(name);
            Objects.requireNonNull(dataCenter);
        }

        private static Image random() {
            return new Image(ThreadLocalRandom.current().nextInt() + ".png",
                    DATACENTERS.get(Math.abs(ThreadLocalRandom.current().nextInt() % DATACENTERS.size())));
        }
    }

    /**
     * Represents a ZipFile with its name
     */
    public record ZipFile(String name) {

        public ZipFile {
            Objects.requireNonNull(name);
        }

        private static ZipFile random() {
            return new ZipFile(ThreadLocalRandom.current().nextInt() + ".zip");
        }
    }

    private static void waitRandomTime() throws InterruptedException {
        Thread.sleep(Math.abs(ThreadLocalRandom.current().nextInt() % 1000));
    }

    /**
     * Simulate the reception of a ZipFile from the web
     * 
     * @return
     * @throws InterruptedException
     */
    public static ZipFile retrieveFromClients() throws InterruptedException {
        waitRandomTime();
        return ZipFile.random();
    }

    /**
     * Simulate the extraction of a zip file
     * 
     * @param zipFile to be extracted
     * @return the list of files contains in the ZipFile
     * @throws InterruptedException  if interrupted
     * @throws IllegalStateException if unable to unzip the zip file
     */
    public static List<Image> unzip(ZipFile zipFile) throws InterruptedException {
        waitRandomTime();
        var hashcode = Math.abs(zipFile.name().hashCode());
        if (hashcode % 100 == 0) {
            throw new IllegalStateException();
        }
        var nbFile = hashcode % 5;
        return IntStream.range(0, nbFile).mapToObj(id -> Image.random()).collect(Collectors.toList());
    }

    /**
     * Simulate the storing of a batch of images in dataCenter The images must all
     * have the dataCenter as preferred dataCenter and the size of the batch must be
     * equal to the dataCenter batchSize
     *
     * @param images     the batch of images to be stored
     * @param dataCenter the dataCenter to store the images in
     * @throws InterruptedException
     */
    public static void archive(List<Image> images, DataCenter dataCenter) throws InterruptedException {
        if (images.stream().anyMatch(f -> !f.dataCenter.equals(dataCenter))) {
            throw new IllegalArgumentException("DataCenter can only accept file for this DataCenter");
        }
        if (images.size() != dataCenter.batchCapacity) {
            throw new IllegalArgumentException(
                    "DataCenter " + dataCenter + " accepts only batchs of size " + dataCenter.batchCapacity());
        }
        waitRandomTime();
    }
}
