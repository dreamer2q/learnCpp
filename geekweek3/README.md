
![849589-20190306165258970-1789860540.png](https://i.loli.net/2019/11/05/irACYKgxMzevZml.png)
![849589-20180402133438219-1946132192.png](https://i.loli.net/2019/11/05/ElBFIcLVUe85xJZ.png)

# 冒泡排序(Bubble Sort)

冒泡排序是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果它们的顺序错误就把它们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。 

```python
BubbleSort(a,n)
  for i range 0 to n-1
      for j range 0 to n-i-1
          if a[j] > a[j+1]
              swap(a[j],a[j+1])
  return a
```

表现最稳定的排序算法之一，因为无论什么数据进去都是O(n^2)的时间复杂度，所以用到它的时候，数据规模越小越好。

# 桶排序(Bucket Sort)

桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。桶排序 (Bucket sort)的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

```python
BucketSort(a)
  var buckets[][]
  for value in a
      index = map(value)
      buckets[index].append(value)
      BucketSort(buckets[index])
  var ret[]
  for bucket in buckets
      for value in bucket
          ret.append(ret)
  return ret
```

桶排序最好情况下使用线性时间O(n)，桶排序的时间复杂度，取决与对各个桶之间数据进行排序的时间复杂度，因为其它部分的时间复杂度都为O(n)。很显然，桶划分的越小，各个桶之间的数据越少，排序所用的时间也会越少。但相应的空间消耗就会增大。

# 归并排序(Merge Sort)

归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为2-路归并。 

```python
MergeSort(a)
    if a.length <= 1
        return a
    mid = a.length/2
    MergeSort(Merge(a[:mid],a[mid:])
Merge(left,right)
    var ret[]
    n = getMin(left.length,right.length)
    while n > 0
        if left[0] < right[0]
            ret.append(left.shift())
        else
            ret.append(right.shift())
    if left.length > 0
        ret.append(left.shiftAll())
    if right.length > 0
        ret.append(right.shiftAll())
    return ret
```

归并排序是一种稳定的排序方法。和选择排序一样，归并排序的性能不受输入数据的影响，但表现比选择排序好的多，因为始终都是O(nlogn）的时间复杂度。代价是需要额外的内存空间。

# 快速排序(Quick Sort)

**快速排序的基本思想：** 通过一趟排序将待排记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。

快速排序使用分治法来把一个串（list）分为两个子串（sub-lists）。具体算法描述如下：

- 从数列中挑出一个元素，称为 “基准”（pivot）；
- 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
- 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。

```python
QuickSort(a,left,right)    
    if left < right
        pivot = a[left]
        l = left
        r = right
        while l < r
            while l < r and pivot < a[r]
                r--
            if l < r
                swap(a[l],a[r])
                l++
            while l < r and pivot > a[l]
                l++
            if l < r
                swap(a[l],a[r])
                r--
        a[l] = pivot
        QuickSort(a,left,i-1)
        QuickSort(a,i+1,right)
```
快速排序不稳定，时间复杂度平均O(NlogN),最坏O(N^2)

# TODO

- [x] BucketSort
- [x] BubbleSort
- [x] MergeSort
- [x] QuickSort

- [ ] 完成新排序
- [ ] 排序过程的可视化
- [ ] 排序时间复杂度的可视化
- [ ] 不同排序算法的时间比较



