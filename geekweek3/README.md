
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
  var buckets[]
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

# More...



