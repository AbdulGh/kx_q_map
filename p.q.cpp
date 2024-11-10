#include <map>
#include <iostream>
#include <stdint.h>

#include "k.h"
#define SS(x) ss(const_cast<char*>(x))

using map_t = std::map<int64_t, K>;

void destructor(K k) {
  std::cout << "here destructor" << std::endl;
  map_t* map = reinterpret_cast<map_t*>(kK(k)[1]->j);
  delete map;
}

static_assert(sizeof(uintptr_t) <= sizeof(J));

extern "C" {
  K make(K) {
    std::cout << "make" << std::endl;
    map_t* map = new map_t{};
    K foreign = knk(2, kj((J)&destructor), kj((J)map));
    foreign->t = 112;
    return foreign;
  }

  K add(K kmap, K key, K value) {
    std::cout << "add" << std::endl;
    if (key->t != -KJ) {
      return krr(SS("type"));
    }
    map_t* map = reinterpret_cast<map_t*>(kK(kmap)[1]->j);
    map->insert({key->j, value});
    r1(value);
    return key;
  }

  //returns a list, a pair of key/value
  K front(K kmap) {
    std::cout << "front" << std::endl;
    map_t* map = reinterpret_cast<map_t*>(kK(kmap)[1]->j);
    if (std::empty(*map)) {
      return krr(SS("empty"));
    }

    const auto& front = *map->begin();
    K key = kj(front.first);
    K value = front.second;

    K result = knk(2, key, value);
    return result;
  }

  K pop(K kmap) {
    std::cout << "pop" << std::endl;
    K popped = front(kmap);
    if (popped->t == -128) {
      //propogate the error (todo test this)
      return popped;
    }
    map_t* map = reinterpret_cast<map_t*>(kK(kmap)[1]->j);
    map->erase(map->begin());

    return popped;
  }

  K size(K kmap) {
    std::cout << "size" << std::endl;
    map_t* map = reinterpret_cast<map_t*>(kK(kmap)[1]->j);
    std::cout << "it was " << std::size(*map) << std::endl;
    return kj(std::size(*map));
  }
}
