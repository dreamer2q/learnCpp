# Disjoint Set 并查集

## Description

将编号分别为 1…N 的 N 个对象划分为不相交集合，
在每个集合中，选择其中某个元素代表所在集合。

## ADT

- 初始化(MakeSet)
- 合并(Merge)
- 查找(Find)

## Implementation

### Method 1

- 用编号最小的元素标记所在集合
- 定义一个数组`set[1..n]`,其中`set[i]`表示元素`i`所在的集合

```cpp
#define N 100
int set[N];
int find(int x){
    return set[x];
}
void merge(int a,int b){
    int i=a,j=b;
    if(a>b) i=b,j=a;
    for(int z=1;z<=N;z++){
        if(set[z] == j)
            set[z] = i;
    }
}
```

这里的查找操作是非常快速的，但是合并操作需要遍历所有的元素，效率不高。

### Method 2

- 每个集合用一颗`有根树`表示
- 定义数组`set[1..n]`
  - 若`set[i] == i`, 则 i 表示本集合，并是`集合`对于`树`的根
  - 若`set[i] != j` 且 `i!=j`, 则表示`j`是`i`的父节点

```cpp
#define N 100
int set[N];
int find(int x){
    int r=x;
    while(set[r] != r)
        r = set[r];
}
void merge(int a,int b){
    set[a] = b;
}
```

这里注意，虽然`合并`的操作效率很高，但是查找的最坏情况是`O(N)`

## Optimization

- 避免最坏的情况
  - 将深度小的树`合并`到深度大的树
  - 假设两个两棵树的深度分别是`h1`,`h2`,则合并后高的`h`为
    - `max(h1,h2) # h1 != h2`
    - `h1+1 # h1 == h2`
  - 包含`k`个节点的树，最大高度不超过`lgk`

```cpp
int find(int x){
    int r = x;
    while(set[r] != r)
        r = set[r];
    return r;
}
void merge(int a,int b){
    if(H(a) == H(b)){
        H(a)++;
        set[b] = a;
    }else if(H(a) < H(b)){
        set[a] = b;
    }else{
        set[b] = a;
    }
}
```

- 路径压缩
  - 每次查找的时候，如果路径较长，则修改路径信息，以便下次查找的时候速度更快
  - 找到根节点，修改查找路径上的`所有节点`,将它们都指向根节点

```cpp
int find(int x){
    int r = x;
    while(set[r]!=r) //寻找根节点
        r = set[r];

    int i = x;
    while(i != r){  //修改路径所有节点信息
        int j = set[i];
        set[i] = r;
        i = j;
    }
    return r;
}
```

## Application

- 最小生成树
