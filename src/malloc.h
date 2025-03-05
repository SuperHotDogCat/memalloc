#ifndef MALLOC_H
#define MALLOC_H
#include <unistd.h>
typedef long long Align; // long 境界に整合させる, 格納されるオブジェクトがメモリ領域に整合するためにこうする
union header { // blockのヘッダ
    struct {
        union header *ptr; // 空きリストの上なら次のblock
        unsigned size; // このブロックの大きさ(単位はheader, 何個のn_units, headerで取られているか)
        // 例: size = 8の場合, header含めて8個　[Header][データ][データ][データ][データ][データ][データ][データ]
    } s;
    Align x; // ブロックの整合を強制, 実際には上のs部分は返されない
};
typedef union header Header;

extern Header base; // 開始時の空きリスト
extern Header *freep; // 空きリストの先頭

void *mallocx(unsigned n_bytes);
void freex(void *ap);
#endif 
