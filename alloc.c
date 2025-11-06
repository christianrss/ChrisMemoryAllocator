/* alloc.c */
#include "alloc.h"

extern heap *memspace;

header *findblock_(header *hdr, word allocation, word n) {
    bool ok;
    void *mem;
    header *hdr_;
    word n_;

    if ((n+allocation) > (Maxwords-2))
        reterr(ErrNoMem);

    ok = (!(hdr->w)) ? true : 
    (!(hdr->alloced) && (hdr->w >= allocation)) ? true :
        false;
    
    if (ok)
        return hdr;
    else {
        mem = $v hdr + (hdr->w*4) + 4;
        hdr_ = $h mem;
        n_ = n + hdr->w;

        return findblock_(hdr_, allocation, n_);
    }

    reterr(ErrUnknown);
}

void *mkalloc(word words, header *hdr) {
    void *ret, *bytesin;
    word wordsin;

    bytesin = ($v (($v hdr) - memspace));
    wordsin = (((word)bytesin)/4)+1;
    if (words > (Maxwords-wordsin))
        reterr(ErrNoMem);

    hdr->w = words;
    hdr->alloced = true;
    ret = ($v hdr)+4;

    return ret;
}

void *alloc(int32 bytes) {
    word words;
    header *hdr;
    void *mem;

    words = (!(bytes % 4)) ?
            bytes/4 :
        (bytes/4) + 1;
    
    hdr = findblock(words);
    if (!hdr)
        return $v 0;

    if (words > Maxwords)
        reterr(ErrNoMem);

    mem = mkalloc(words, hdr);
    if(!mem)
        return $v 0;

    return mem;
}

void show_(header *hdr) {
    header *p;
    void *mem;
    int32 n;
    
    for (n=1, p=hdr; p->w; mem=$v p + (p->w+1)*4, p=mem, n++)
        printf("Alloc %d = %d %s words\n", n, p->w, (p->alloced) ? "alloced" : "free");

    return;
}

int main(int argc, char *argv[]) {
    int8 *p;
    int8 *p2;
    int8 *p3;

    printf("Memspace = 0x%x\n", $i memspace);

    p = alloc(7);
    p2 = alloc(2000);
    p3 = alloc(1);
    show();

    return 0;
}