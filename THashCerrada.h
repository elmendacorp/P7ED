//
// Created by Fran on 23/11/2016.
//

#ifndef P7ED_THASHCERRADA_H
#define P7ED_THASHCERRADA_H

template<typename T>
class THashCerrada {
private:
public:
    unsigned long djb2(unsigned char *str){
        unsigned long hash = 5381;
        int c;
        while(c = *str++) hash= ((hash<<5)+hash)+c;
        return hash;
    }
};


#endif //P7ED_THASHCERRADA_H
