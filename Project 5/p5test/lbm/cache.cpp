#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

class Unknown{};
class No_operands{};
class Over_operands{};
class Out_of_bound{};
class Exit{};

class LRUCache{
private:
    int mem_size; // size of memory
    int *memory;
    struct block{
        int address; // its address in memory
        int data;
    };
    Dlist<block> cache;
    int cur_cache_size; // current length of `cache`
    int max_cache_size; // maximum length of `cache`

    static bool compare(const block *a, const block *b);
    // EFFECTS: returns true if two blocks have the same address

public:
    LRUCache(int cache_size, int memory_size); // constructor
    // Initialize `cur_cache_size`, `max_cache_size`, `memory`
    // Initialize all elements in `memory` to 0

    ~LRUCache(); // destructor

    int read(int address);
    // EFFECTS: returns data corresponding to address,
    // 0 <= address < mem_size;
    // if address is out of bound, throws an exception
    //
    // if hit,
    // removes this block and insert it to the front;
    // returns `data`;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    // in the `cache`;
    // writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // reads `data` of `address` from `memory`,
    // inserts the block with `address` and `data`
    // to the front of `cache`;
    // returns `data`

    void write(int address, int data);
    // EFFECTS: writes data to address, 0 <= address < mem_size
    // if address is out of bound, throws an exception
    // if hit,
    // removes this block from list,
    // writes `data` to this block,
    // and inserts this block to the front;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    //writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // inserts the block with `address` and `data`
    // to the front of `cache`

    void printCache();
    // EFFECTS: prints the cache in given format

    void printMem();
    // EFFECTS: prints the memory in given format
};

void operate(LRUCache* lru, const string &input);
    // MODIFIES: lru
    // EFFECTS: operate the input instruction

int main(){
    string input;
    int cache_size, memory_size;
    getline(cin, input);
    stringstream str;
    str << input;
    str >> cache_size >> memory_size;
    LRUCache lru(cache_size, memory_size);
    while (getline(cin, input)){
        try{
            operate(&lru, input);
        }
        catch (Unknown) {
            cout << "ERROR: Unknown instruction" << endl;
        }
        catch (No_operands) {
            cout << "ERROR: Not enough operands" << endl;
        }
        catch (Over_operands) {
            cout << "ERROR: Too many operands" << endl;
        }
        catch (Out_of_bound) {
            cout << "ERROR: Address out of bound" << endl;
        }
        catch (Exit) {
            return 0;
        }
    }
    return 0;
}

void operate(LRUCache* lru, const string &input){
    stringstream str;
    string instru;
    str << input;
    str >> instru;
    int address, data;
    char temp;
    if (instru == "READ") {
        str >> ws; // read a single white space
        if (str.eof()) throw No_operands{};
        str >> address;
        str >> ws; // read white space
        if (!str.eof()) throw Over_operands{};
        cout << lru->read(address) << endl;
    }
    else if (instru == "WRITE"){
        if (str.eof()) throw No_operands{};
        str >> address;
        str >> ws; // read a single white space
        if (str.eof()) throw No_operands{};
        str >> data;
        str >> ws; // read white space
        if (!str.eof()) throw Over_operands{};
        lru->write(address, data);
    }
    else if (instru == "PRINTCACHE"){
        lru->printCache();
    }
    else if (instru == "PRINTMEM"){
        lru->printMem();
    }
    else if (instru == "EXIT"){
        throw Exit{};
    } else {
        throw Unknown{};
    }
}

bool LRUCache::compare(const LRUCache::block *a, const LRUCache::block *b) {
    return a->address == b->address;
}

LRUCache::LRUCache(int cache_size, int memory_size) {
    mem_size = memory_size;
    memory = new int[memory_size];
    cur_cache_size = 0;
    max_cache_size = cache_size;
    for (int i = 0; i < memory_size; i ++){
        memory[i] = 0;
    }
}

LRUCache::~LRUCache() {
    delete [] memory;
}

int LRUCache::read(int address) {
    if (address < 0 || address >= mem_size) throw Out_of_bound{};
    block* read = new block;
    read->address = address;

    block* temp = cache.remove(compare, read); // try to remove the block from the cache
    if (!temp) { // mis
        read->data = memory[address];
        if (cur_cache_size < max_cache_size) {
            cache.insertFront(read);
            cur_cache_size ++;
            return memory[address];
        }
        else if (cur_cache_size == max_cache_size) {
            block *back = cache.removeBack(); // the block come out of the stack
            memory[back->address] = back->data; // change the data in the main memory
            delete back;
            cache.insertFront(read);
            return memory[address];
        }
    } else { // hit
        read->data = temp->data;
        cache.insertFront(temp);
        delete read;
        return temp->data;
    }
    return -1;
}

void LRUCache::write(int address, int data) {
    if (address < 0 || address >= mem_size) throw Out_of_bound{};
    block* read = new block;
    read->address = address;
    read->data = data;

    block* temp = cache.remove(compare, read); // try to remove the block from the cache
    if (!temp) { // mis
        if (cur_cache_size < max_cache_size) {
            cache.insertFront(read);
            cur_cache_size ++;
        }
        else if (cur_cache_size == max_cache_size) {
            block *back = cache.removeBack(); // the block come out of the stack
            memory[back->address] = back->data; // change the data in the main memory
            delete back;
            cache.insertFront(read);
        }
    } else { // hit
        cache.insertFront(read);
        delete temp;
    }
}

void LRUCache::printCache() {
    for (int i = 0; i < cur_cache_size; i ++){
        block* first = cache.removeFront();
        cout << first->address << " " << first->data << endl;
        cache.insertBack(first);
    }
}

void LRUCache::printMem() {
    for (int i = 0; i < mem_size; i ++){
        cout << memory[i] << " ";
    }
    cout << endl;
}
