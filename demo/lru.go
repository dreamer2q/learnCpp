package main

import "fmt"

type dList struct {
	prev *dList
	next *dList
	k    int
	v    int
}

/**
 * lru design
 * @param operators int整型二维数组 the ops
 * @param k int整型 the k
 * @return int整型一维数组
 */
func LRU(operators [][]int, maxlen int) []int {
	// write code here
	res := make([]int, 0)
	cache := make(map[int]*dList, maxlen)
	var head *dList

	for _, test := range operators {
		op := test[0]
		k := test[1]
		node, ok := cache[k]
		if op == 1 { // set val
			val := test[2]
			if ok { // exist, fix pos
				node.v = val
				head = removeNode(head, node)
				head = insertNode(head, node)
			} else { // not exist, add new
				newNode := &dList{k: k, v: val}
				head = insertNode(head, newNode)
				cache[k] = newNode
				if len(cache) > maxlen {
					delete(cache, head.k)
					head = removeNode(head, head)
				}
			}
		} else { // get
			if ok { // exist, fix pos
				res = append(res, node.v)
				head = removeNode(head, node)
				head = insertNode(head, node)
			} else { // not exist, do nothing
				res = append(res, -1)
			}
		}
	}
	return res
}

func insertNode(pos, node *dList) *dList {
	if pos == nil {
		node.prev = node
		node.next = node
		return node
	}
	prev := pos.prev
	node.prev = prev
	node.next = pos
	prev.next = node
	pos.prev = node
	return pos
}

func removeNode(head, node *dList) *dList {
	if node.next == node { // only one node
		return nil
	}
	node.prev.next = node.next
	node.next.prev = node.prev
	if head == node {
		return head.next
	}
	return head
}

func main() {
	oprs := [][]int{
		{1, 1, 1},
		{1, 2, 2},
		{1, 3, 2},
		{2, 1},
		{1, 4, 4},
		{2, 2}}
	maxlen := 3
	res := LRU(oprs, maxlen)

	fmt.Printf("%v\n", res)
}
