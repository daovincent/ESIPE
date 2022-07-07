import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;

public class Mystery {
	private final int[] tab = new int[4];
	private int index;
	private final ReentrantLock lock = new ReentrantLock();

	public void store(int value) {
		lock.lock();
		try {
			index++;
			if (index >= tab.length) {
				index = 0;
			}
			tab[index] = value;
		}finally {
			lock.unlock();
		}
	}

	@Override
	public String toString() {
		lock.lock();
		try {
			return Arrays.toString(tab);
		}finally {
			lock.unlock();
		}
	}

	public static void main(String[] args) throws InterruptedException {
		var mystery = new Mystery();

		var nbThreads = 3;
		var nbRounds = 100;


		var executorService = Executors.newFixedThreadPool(nbThreads);
		var callables=new ArrayList<Callable<String>>();

		IntStream.range(0,nbThreads*nbRounds).forEach(i-> callables.add(()->{
			mystery.store(ThreadLocalRandom.current().nextInt(10));
			return mystery.toString();
		}));
		var futures = executorService.invokeAll(callables);
		try {
			for (var future : futures){
				System.out.println(future.get());
			}
		} catch (ExecutionException e) {
			System.out.println("oops");
		}

//		IntStream.range(0, nbThreads).forEach(j -> {
//			new Thread(() -> {
//				for (int i = 0; i < nbRounds; i++) {
//					mystery.store(ThreadLocalRandom.current().nextInt(10));
//					// store peut changer de thread avant de reset la valeur à 0
//					// donc l'indice dépasse la taille du tableau et out of bounds exception
//					// store n'essaie pas d'empêcher cette situation
//					System.out.println(mystery+ " from "+Thread.currentThread());
//				}
//			}).start();
//		});
	}
}
