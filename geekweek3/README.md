# 前言

排序算法经常被用到，但是如果没有深入理解算法的原理很容易就遗忘了。

这里是结合别人的文章完成的学习笔记，算是加深自己对常见的算法的理解吧。



# 算法一览
![849589-20190306165258970-1789860540.png](https://i.loli.net/2019/11/05/irACYKgxMzevZml.png)
![849589-20180402133438219-1946132192.png](https://i.loli.net/2019/11/05/ElBFIcLVUe85xJZ.png)

# 冒泡排序(Bubble Sort)

冒泡排序是一种简单的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果它们的顺序错误就把它们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端。 

```go
BubbleSort(a,n)
  for i range 0 to n-1
      for j range 0 to n-i-1
          if a[j] > a[j+1]
              swap(a[j],a[j+1])
  return a
```

表现最稳定的排序算法之一，因为无论什么数据进去都是O(n^2)的时间复杂度，所以用到它的时候，数据规模越小越好。

# 选择排序(Selection Sort)
选择排序(Selection-sort)是一种简单直观的排序算法。它的工作原理：首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。 

n个记录的直接选择排序可经过n-1趟直接选择排序得到有序结果。

**具体算法描述如下：**

- 初始状态：无序区为R[1..n]，有序区为空；
- 第i趟排序(i=1,2,3…n-1)开始时，当前有序区和无序区分别为R[1..i-1]和R(i..n）。该趟排序从当前无序区中-选出关键字最小的记录 R[k]，将它与无序区的第1个记录R交换，使R[1..i]和R[i+1..n)分别变为记录个数增加1个的新有序区和记录个数减少1个的新无序区；
- n-1趟结束，数组有序化了。
```go
SelectionSort(a)
    for i range 0 to a.length - 1
        min = i
        for j range i + 1 to a.length
            if a[min] > a[j]
                min = j
        if min != i
            swap(a[min],a[i])
```
表现最稳定的排序算法之一，因为无论什么数据进去都是O(n2)的时间复杂度，所以用到它的时候，数据规模越小越好。唯一的好处可能就是不占用额外的内存空间了吧。理论上讲，选择排序可能也是平时排序一般人想到的最多的排序方法了吧。不过数据很大的时候不推荐使用这个排序算法。

# 插入排序(Insertion Sort)
插入排序（Insertion-Sort）的算法描述是一种简单直观的排序算法。它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。

一般来说，插入排序都采用in-place在数组上实现。

**具体算法描述如下：**

- 从第一个元素开始，该元素可以认为已经被排序；
- 取出下一个元素，在已经排序的元素序列中从后向前扫描；
- 如果该元素（已排序）大于新元素，将该元素移到下一位置；
- 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置；
- 将新元素插入到该位置后；
- 重复步骤2~5。

```go
InsertSort(a)
    var ret[]
    for i range 0 to a.length
        for j range 0 to ret.length
            if a[i] < ret[j]
                break
        ret.insertAt(j,a[i])
    return ret
```
插入排序在实现上，通常采用in-place排序（即只需用到O(1)的额外空间的排序），因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。

# 希尔排序(Shell Sort)
1959年Shell发明，第一个突破O(n2)的排序算法，是简单插入排序的改进版。它与插入排序的不同之处在于，它会优先比较距离较远的元素。希尔排序又叫缩小增量排序。

先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序。

**具体算法描述：**

- 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；
- 按增量序列个数k，对序列进行k 趟排序；
- 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。
```go
ShellSort(a,n)
    for gap = n/2 ; gap > 0 ; gap /= 2 
        for i range gap to n
            j = i
            curr = a[i]
            while  j-gap >= 0 and curr < arr[j-gap]
                a[j] = a[j-gap]
                j -= gap
            a[j] = curr
```
希尔排序的核心在于间隔序列的设定。既可以提前设定好间隔序列，也可以动态的定义间隔序列。动态定义间隔序列的算法是《算法（第4版）》的合著者Robert Sedgewick提出的。

# 桶排序(Bucket Sort)

桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。桶排序 (Bucket sort)的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

```go
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

```go
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

```go
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

# 堆排序(Heap Sort)
堆排序（Heapsort）是指利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子结点的键值或索引总是小于（或者大于）它的父节点。

**算法描述**
- 将初始待排序关键字序列(R1,R2….Rn)构建成大顶堆，此堆为初始的无序区；
- 将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1,R2,……Rn-1)和新的有序区(Rn),且满足R[1,2…n-1]<=R[n]；
- 由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1,R2,……Rn-1)调整为新堆，然后再次将R[1]与无序区最后一个元素交换，得到新的无序区(R1,R2….Rn-2)和新的有序区(Rn-1,Rn)。不断重复此过程直到有序区的元素个数为n-1，则整个排序过程完成。


```go
Heapify(a,n,i)
    left    = i*2 + 1
    right   = i*2 + 2
    max     = i
    if left < n && a[left] > a[max]
        max = left
    if right < n && a[right] > a[max]
        max = right
    if max != i
        swap(a[max],a[i])
        Heapify(a,n,max)

BuildMaxHeap(a,n)
    for i range from n/2 to 0
        Heapify(a,n,i)

HeapSort(a,n)
    BuildMaxHeap(a,n)
    for i range from n - 1 to 1
        swap(a[0],a[i])
        Heapify(a,n,i)
```

# 计数排序(Counting Sort)
计数排序不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。 作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

**算法描述**

- 找出待排序的数组中最大和最小的元素；
- 统计数组中每个值为i的元素出现的次数，存入数组C的第i项；
- 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）；
- 反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1。

```go
CountingSort(a)
    var ret[]
    for v in a
        ret[v]++
    index = 0
    for i range 0 to ret.length
        while ret[i] > 0
            a[index] = i
            ret[i]--
            index++
```

计数排序是一个稳定的排序算法。当输入的元素是 n 个 0到 k 之间的整数时，时间复杂度是O(n+k)，空间复杂度也是O(n+k)，其排序速度快于任何比较排序算法。当k不是很大并且序列比较集中时，计数排序是一个很有效的排序算法。

# 基数排序(Radix Sort)
基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。

**算法描述**
- 取得数组中的最大数，并取得位数；
- arr为原始数组，从最低位开始取每个位组成radix数组；
- 对radix进行计数排序（利用计数排序适用于小范围数的特点）;

```go
RadixSort(a)
    digits = getDigits(getMax(a))
    
    for i range 0 to digits
        var buckets[]  //each time make it empty
        for v in a
            index = (v % pow(10,i+1)) / pow(10,i)
            buckets[index].push(v)
        index = 0
        for bucket in buckets
            if bucket.length > 0
                for v in bucket
                    a[index] = v
                    index++
```
基数排序基于分别排序，分别收集，所以是稳定的。但基数排序的性能比桶排序要略差，每一次关键字的桶分配都需要O(n)的时间复杂度，而且分配之后得到新的关键字序列又需要O(n)的时间复杂度。假如待排数据可以分为d个关键字，则基数排序的时间复杂度将是O(d*2n) ，当然d要远远小于n，因此基本上还是线性级别的。


# 感想

本来想加入`时间测试`但是，我发现如果实现这个功能需要重新写所有的排序算法函数，因为那些算法为了显示其过程，被我改得面目全非。
我又想了一些，这些算法的分析上面已经给出了平均情况，就没有必要进行实际测试了。所以我删去了`时间测试`功能。

写完这些算法，尽管有些地方写的不是十分理想，比如所桶排序的环节，本来应该递归调用桶排序对放入桶里面的数据进行排序，我偷懒就用写自己实现的插入排序代替了。
我也自己测试过快速排序和希尔排序的时间，也在了解到不同的算法差距实太大了。之前我认为掌握了选择排序已经足够应用日常场景了。但是对于大量的数据，选择排序还是不够快的。
学完这些算法后，我觉得最容易实现和理解的就是希尔排序了，它在数据100万的情况下和快速排序相差无几，这点已经足够了。比较目前我也接触不到需要如此巨大的排序数据。

学习算法更多的是给自己打基础，比如说在学习算法的同时学到了如何使用数组实现heap。当然数据结构远远不止这些，这些都是需要后面慢慢学的。

就写到这里吧。

