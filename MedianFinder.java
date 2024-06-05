import dacheng.utils.*;
import java.util.*;

class MedianFinder {

    private PriorityQueue<Integer> minHeap; // to store the upper half of the data
    private PriorityQueue<Integer> maxHeap; // to store the lower half of the data

    /** initialize your data structure here. */
    public MedianFinder() {
        // Min heap to store the minimum element at the top
        minHeap = new PriorityQueue<>();
        
        // Max heap to store the maximum element at the top
        maxHeap = new PriorityQueue<>(Collections.reverseOrder());
    }

    public void addNum(int num) {
        if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
            maxHeap.add(num);
        } else {
            minHeap.add(num);
        }

        // Balance the heaps to ensure maxHeap has equal to or one more element than minHeap
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.add(maxHeap.poll());
        } else if (maxHeap.size() < minHeap.size()) {
            maxHeap.add(minHeap.poll());
        }
    }

    public double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.peek();
        } else {
            return (maxHeap.peek() + minHeap.peek()) / 2.0;
        }
    }
}
