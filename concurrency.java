import java.util.concurrent.*;
import java.util.concurrent.locks.*;
import java.util.*;

public class ConcurrencyReview {

    // Example 1: Implementing Runnable Interface
    public static class MyRunnable implements Runnable {
        @Override
        public void run() {
            System.out.println("Runnable running");
        }
    }

    // Example 2: Implementing Callable Interface
    public static class MyCallable implements Callable<Integer> {
        public Integer call() {
            return 123;
        }
    }

    // Example 3: Extending Thread Class
    public static class MyThread extends Thread {
        public void run() {
            System.out.println("Thread running");
        }
    }

    // Example 4: Executor Service
    public static void executorServiceExample() {
        ExecutorService executorService = Executors.newCachedThreadPool();
        for (int i = 0; i < 5; i++) {
            executorService.execute(new MyRunnable());
        }
        executorService.shutdown();
    }

    // Example 5: Daemon Thread
    public static void daemonExample() {
        Thread thread = new Thread(new MyRunnable());
        thread.setDaemon(true);
        thread.start();
    }

    // Example 6: Thread.sleep()
    public static void sleepExample() {
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // Example 7: Thread.yield()
    public static void yieldExample() {
        Thread.yield();
    }

    // Example 8: InterruptedException
    public static class InterruptExample {
        private static class MyThread1 extends Thread {
            @Override
            public void run() {
                try {
                    Thread.sleep(2000);
                    System.out.println("Thread run");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        public static void main(String[] args) throws InterruptedException {
            Thread thread1 = new MyThread1();
            thread1.start();
            thread1.interrupt();
            System.out.println("Main run");
        }
    }

    // Example 9: interrupted()
    public static class InterruptExample2 {
        private static class MyThread2 extends Thread {
            @Override
            public void run() {
                while (!interrupted()) {
                    // ...
                }
                System.out.println("Thread end");
            }
        }

        public static void main(String[] args) throws InterruptedException {
            Thread thread2 = new MyThread2();
            thread2.start();
            thread2.interrupt();
        }
    }

    // Example 10: ExecutorService shutdownNow()
    public static void executorShutdownNowExample() {
        ExecutorService executorService = Executors.newCachedThreadPool();
        executorService.execute(() -> {
            try {
                Thread.sleep(2000);
                System.out.println("Thread run");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        executorService.shutdownNow();
        System.out.println("Main run");
    }

    // Example 11: CountDownLatch
    public static class CountdownLatchExample {
        public static void main(String[] args) throws InterruptedException {
            final int totalThread = 10;
            CountDownLatch countDownLatch = new CountDownLatch(totalThread);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < totalThread; i++) {
                executorService.execute(() -> {
                    System.out.print("run..");
                    countDownLatch.countDown();
                });
            }
            countDownLatch.await();
            System.out.println("end");
            executorService.shutdown();
        }
    }

    // Example 12: CyclicBarrier
    public static class CyclicBarrierExample {
        public static void main(String[] args) {
            final int totalThread = 10;
            CyclicBarrier cyclicBarrier = new CyclicBarrier(totalThread);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < totalThread; i++) {
                executorService.execute(() -> {
                    System.out.print("before..");
                    try {
                        cyclicBarrier.await();
                    } catch (InterruptedException | BrokenBarrierException e) {
                        e.printStackTrace();
                    }
                    System.out.print("after..");
                });
            }
            executorService.shutdown();
        }
    }

    // Example 13: Semaphore
    public static class SemaphoreExample {
        public static void main(String[] args) {
            final int clientCount = 3;
            final int totalRequestCount = 10;
            Semaphore semaphore = new Semaphore(clientCount);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < totalRequestCount; i++) {
                executorService.execute(() -> {
                    try {
                        semaphore.acquire();
                        System.out.print(semaphore.availablePermits() + " ");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        semaphore.release();
                    }
                });
            }
            executorService.shutdown();
        }
    }

    // Example 14: FutureTask
    public static class FutureTaskExample {
        public static void main(String[] args) throws ExecutionException, InterruptedException {
            FutureTask<Integer> futureTask = new FutureTask<>(() -> {
                int result = 0;
                for (int i = 0; i < 100; i++) {
                    Thread.sleep(10);
                    result += i;
                }
                return result;
            });

            Thread computeThread = new Thread(futureTask);
            computeThread.start();

            Thread otherThread = new Thread(() -> {
                System.out.println("other task is running...");
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
            otherThread.start();
            System.out.println(futureTask.get());
        }
    }

    // Example 15: BlockingQueue - Producer Consumer
    public static class ProducerConsumer {
        private static BlockingQueue<String> queue = new ArrayBlockingQueue<>(5);

        private static class Producer extends Thread {
            @Override
            public void run() {
                try {
                    queue.put("product");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.print("produce..");
            }
        }

        private static class Consumer extends Thread {
            @Override
            public void run() {
                try {
                    String product = queue.take();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.print("consume..");
            }
        }

        public static void main(String[] args) {
            for (int i = 0; i < 2; i++) {
                Producer producer = new Producer();
                producer.start();
            }
            for (int i = 0; i < 5; i++) {
                Consumer consumer = new Consumer();
                consumer.start();
            }
            for (int i = 0; i < 3; i++) {
                Producer producer = new Producer();
                producer.start();
            }
        }
    }

    // Example 16: ForkJoin
    public static class ForkJoinExample extends RecursiveTask<Integer> {
        private final int threshold = 5;
        private int first;
        private int last;

        public ForkJoinExample(int first, int last) {
            this.first = first;
            this.last = last;
        }

        @Override
        protected Integer compute() {
            int result = 0;
            if (last - first <= threshold) {
                // 任务足够小则直接计算
                for (int i = first; i <= last; i++) {
                    result += i;
                }
            } else {
                // 拆分成小任务
                int middle = first + (last - first) / 2;
                ForkJoinExample leftTask = new ForkJoinExample(first, middle);
                ForkJoinExample rightTask = new ForkJoinExample(middle + 1, last);
                leftTask.fork();
                rightTask.fork();
                result = leftTask.join() + rightTask.join();
            }
            return result;
        }

        public static void main(String[] args) throws ExecutionException, InterruptedException {
            ForkJoinExample example = new ForkJoinExample(1, 10000);
            ForkJoinPool forkJoinPool = new ForkJoinPool();
            Future<Integer> result = forkJoinPool.submit(example);
            System.out.println(result.get());
        }
    }

    // Example 17: Thread Unsafe Example
    public static class ThreadUnsafeExample {
        private int cnt = 0;

        public void add() {
            cnt++;
        }

        public int get() {
            return cnt;
        }

        public static void main(String[] args) throws InterruptedException {
            final int threadSize = 1000;
            ThreadUnsafeExample example = new ThreadUnsafeExample();
            final CountDownLatch countDownLatch = new CountDownLatch(threadSize);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < threadSize; i++) {
                executorService.execute(() -> {
                    example.add();
                    countDownLatch.countDown();
                });
            }
            countDownLatch.await();
            executorService.shutdown();
            System.out.println(example.get());
        }
    }

    // Example 18: Atomic Example
    public static class AtomicExample {
        private AtomicInteger cnt = new AtomicInteger();

        public void add() {
            cnt.incrementAndGet();
        }

        public int get() {
            return cnt.get();
        }

        public static void main(String[] args) throws InterruptedException {
            final int threadSize = 1000;
            AtomicExample example = new AtomicExample();
            final CountDownLatch countDownLatch = new CountDownLatch(threadSize);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < threadSize; i++) {
                executorService.execute(() -> {
                    example.add();
                    countDownLatch.countDown();
                });
            }
            countDownLatch.await();
            executorService.shutdown();
            System.out.println(example.get());
        }
    }

    // Example 19: Atomic Synchronized Example
    public static class AtomicSynchronizedExample {
        private int cnt = 0;

        public synchronized void add() {
            cnt++;
        }

        public synchronized int get() {
            return cnt;
        }

        public static void main(String[] args) throws InterruptedException {
            final int threadSize = 1000;
            AtomicSynchronizedExample example = new AtomicSynchronizedExample();
            final CountDownLatch countDownLatch = new CountDownLatch(threadSize);
            ExecutorService executorService = Executors.newCachedThreadPool();
            for (int i = 0; i < threadSize; i++) {
                executorService.execute(() -> {
                    example.add();
                    countDownLatch.countDown();
                });
            }
            countDownLatch.await();
            executorService.shutdown();
            System.out.println(example.get());
        }
    }

    // Example 20: ThreadLocal Example
    public static class ThreadLocalExample {
        public static void main(String[] args) {
            ThreadLocal<Integer> threadLocal = new ThreadLocal<>();
            Thread thread1 = new Thread(() -> {
                threadLocal.set(1);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println(threadLocal.get());
                threadLocal.remove();
            });
            Thread thread2 = new Thread(() -> {
                threadLocal.set(2);
                threadLocal.remove();
            });
            thread1.start();
            thread2.start();
        }
    }

    // Example 21: ThreadLocal Example 1
    public static class ThreadLocalExample1 {
        public static void main(String[] args) {
            ThreadLocal<Integer> threadLocal1 = new ThreadLocal<>();
            ThreadLocal<Integer> threadLocal2 = new ThreadLocal<>();
            Thread thread1 = new Thread(() -> {
                threadLocal1.set(1);
                threadLocal2.set(1);
            });
            Thread thread2 = new Thread(() -> {
                threadLocal1.set(2);
                threadLocal2.set(2);
            });
            thread1.start();
            thread2.start();
        }
    }

    // Example 22: Stack Closed Example
    public static class StackClosedExample {
        public void add100() {
            int cnt = 0;
            for (int i = 0; i < 100; i++) {
                cnt++;
            }
            System.out.println(cnt);
        }

        public static void main(String[] args) {
            StackClosedExample example = new StackClosedExample();
            ExecutorService executorService = Executors.newCachedThreadPool();
            executorService.execute(() -> example.add100());
            executorService.execute(() -> example.add100());
            executorService.shutdown();
        }
    }

    // Example 23: Lock Example with ReentrantLock
    public static class LockExample {
        private Lock lock = new ReentrantLock();

        public void func() {
            lock.lock();
            try {
                for (int i = 0; i < 10; i++) {
                    System.out.print(i + " ");
                }
            } finally {
                lock.unlock(); // ensure that the lock is released, preventing deadlocks
            }
        }

        public static void main(String[] args) {
            LockExample lockExample = new LockExample();
            ExecutorService executorService = Executors.newCachedThreadPool();
            executorService.execute(() -> lockExample.func());
            executorService.execute(() -> lockExample.func());
        }
    }

    // Example 24: Join Example
    public static class JoinExample {
        private class A extends Thread {
            @Override
            public void run() {
                System.out.println("A");
            }
        }

        private class B extends Thread {
            private A a;

            B(A a) {
                this.a = a;
            }

            @Override
            public void run() {
                try {
                    a.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("B");
            }
        }

        public void test() {
            A a = new A();
            B b = new B(a);
            b.start();
            a.start();
        }

        public static void main(String[] args) {
            JoinExample example = new JoinExample();
            example.test();
        }
    }

    // Example 25: Wait Notify Example
    public static class WaitNotifyExample {
        public synchronized void before() {
            System.out.println("before");
            notifyAll();
        }

        public synchronized void after() {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("after");
        }

        public static void main(String[] args) {
            ExecutorService executorService = Executors.newCachedThreadPool();
            WaitNotifyExample example = new WaitNotifyExample();
            executorService.execute(() -> example.after());
            executorService.execute(() -> example.before());
        }
    }

    // Example 26: Await Signal Example
    public static class AwaitSignalExample {
        private Lock lock = new ReentrantLock();
        private Condition condition = lock.newCondition();

        public void before() {
            lock.lock();
            try {
                System.out.println("before");
                condition.signalAll();
            } finally {
                lock.unlock();
            }
        }

        public void after() {
            lock.lock();
            try {
                condition.await();
                System.out.println("after");
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }
        }

        public static void main(String[] args) {
            ExecutorService executorService = Executors.newCachedThreadPool();
            AwaitSignalExample example = new AwaitSignalExample();
            executorService.execute(() -> example.after());
            executorService.execute(() -> example.before());
        }
    }
}
