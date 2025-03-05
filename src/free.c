#include "malloc.h"

void freex(void* ap) {
    // apを空きリストにいれる
    Header *bp;
    Header *p;
    bp = (Header*) ap - 1; // block headerを指す, これが新しいブロックになる
    // 以下のfor文はbpを挿入すべきところを探す
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        // bp > p && bp < p->s.ptrならbp を p の次に挿入できるため ループを抜ける
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            // pが領域の始めか末尾に来ている時はそこをブロックにする
            break;
        }
    }
    if (bp + bp->s.size == p->s.ptr) {
        // bpの次がpなのでmergeする
        // この if 文は、bp の次のブロック (p->s.ptr) と連結できるか をチェックしている
        bp->s.size += p->s.ptr->s.size; // 多分一つのでかい領域になる
        bp->s.ptr = p->s.ptr->s.ptr; // pの二個先がbpの先になる
    } else {
        // もしダメならそのままリストにbpを挿入するだけ
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}
