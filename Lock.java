import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;
// Synchronize is the mutex offered by JVM and ReentrantLock is the mutex offered by JDK
public class MutexSemaphoreExample {

    // Mutex (exclusive lock) implemented using ReentrantLock
    private static final ReentrantLock mutex = new ReentrantLock();

    // Semaphore with a permit count of 3 (allows up to 3 threads to access a resource simultaneously)
    private static final Semaphore semaphore = new Semaphore(3);

    public static void main(String[] args) {
        // Create and start multiple threads for both examples
        Thread[] threads = new Thread[6];

        // Mutex example
        for (int i = 0; i < 3; i++) {
            threads[i] = new Thread(() -> useResourceWithMutex());
        }

        // Semaphore example
        for (int i = 3; i < 6; i++) {
            threads[i] = new Thread(() -> useResourceWithSemaphore());
        }

        // Start all threads
        for (Thread thread : threads) {
            thread.start();
        }
    }

    // Example of using Mutex
    public static void useResourceWithMutex() {
        System.out.println(Thread.currentThread().getName() + " attempting to acquire Mutex lock.");
        mutex.lock(); // Acquiring the lock
        try {
            System.out.println(Thread.currentThread().getName() + " has acquired Mutex lock. Working...");
            Thread.sleep(1000); // Simulate work
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            System.out.println(Thread.currentThread().getName() + " releasing Mutex lock.");
            mutex.unlock(); // Releasing the lock
        }
    }

    // Example of using Semaphore
    public static void useResourceWithSemaphore() {
        System.out.println(Thread.currentThread().getName() + " attempting to acquire Semaphore permit.");
        try {
            semaphore.acquire(); // Acquiring a permit
            System.out.println(Thread.currentThread().getName() + " has acquired Semaphore permit. Working...");
            Thread.sleep(1000); // Simulate work
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            System.out.println(Thread.currentThread().getName() + " releasing Semaphore permit.");
            semaphore.release(); // Releasing the permit
        }
    }
}
