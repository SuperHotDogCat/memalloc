#include <unistd.h>
#include "malloc.h"
Header base;          
Header *freep = NULL; // 初期化

#define NALLOC 1024
// morecore システムにもっとメモリを要求する
static Header *morecore(unsigned n_units) {
    char *cp;
    Header *up;
    if (n_units < NALLOC) {
        n_units = NALLOC;
    }
    cp = (char*) sbrk(n_units * sizeof(Header)); 
    if (cp == (char *) -1) {
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = n_units;
    freex((void *)(up + 1));
    return freep;
}

void *mallocx(unsigned n_bytes) {
    Header *p;
    Header *prevp;
    Header *morecore(unsigned);
    unsigned n_units; // n_unitsは確保したいメモリサイズを、Header の単位で表したもの
    n_units = (n_bytes + sizeof(Header) - 1) / sizeof(Header) + 1; // n_bytesをheaderで切り上げた数, + 1はheaderの分...?
    prevp = freep;
    if (prevp == NULL) {
        // まだ空きリストがない
        prevp = &base;
        freep = prevp;
        base.s.ptr = freep;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        // prevp = freepからスタートして
        if (p->s.size >= n_units) {
            // 十分大きいので領域をallocateして返す
            if (p->s.size == n_units) {
                prevp->s.ptr = p->s.ptr; // 今のpを割り当てて
            } else { // 後尾の部分を割り当てる
                p->s.size -= n_units;
                p += p->s.size;
                p->s.size = n_units;
            }
            freep = prevp;
            return (void *)(p + 1); // pのaddressにsizeof(Header)を加えただけ
        }
        if (p == freep) {
            // pが末尾に来たら空きリストをリング上に繋ぐ(今現在mallocが管理しているメモリ以上を要求している)
            p = morecore(n_units);
            if (p == NULL) {
                return NULL; // もうハードのリソースがない
            }
        }
    }
}
