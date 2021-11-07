# 关联容器

使用键值对来保存

## 类型

有序(使用关键字保存)

- map
- set
- multimap
- multiset

无序(哈希函数)

- unordered_map
- unordered_set
- unordered_multimap
- unordered_multiset

## 对关键字类型的要求

 - 必须支持比较操作，默认情况下是`<`
 
  **严格弱序**
  
 - 两个关键字不能同时"小于等于"对方
 - 传递性 a < b && b < c => a < c
 - 可等， !(a < b) && !(b < a) => a == b
 


