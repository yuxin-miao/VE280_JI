#include <iostream>
#include <string>
#include <sstream>
#include "dlist.h"

using namespace std;

class exitPro{};

class LRUCache{
private:
    int mem_size; // size of memory
    int *memory;
    struct block{
        int address; // its address in memory
        int data;
    };
    Dlist<block> cache;
    int cur_cache_size;     // current length of cache
    int max_cache_size;     // maximum length of cache
    static bool compare(const block *a, const block *b);
    // EFFECTS: returns true if two blocks have the same address
public:
    LRUCache(int cache_size, int memory_size); // constructor
    ~LRUCache(); // destructor
    int read(int address);
    // EFFECTS: returns data corresponding to address, 0 <= address < mem_size;
    // if address is out of bound, throws an exception
    void write(int address, int data);
    // EFFECTS: writes data to address, 0 <= address < mem_size
    // if address is out of bound, throws an exception
    void printCache();
    // EFFECTS: prints the cache in given format
    void printMem();
    // EFFECTS: prints the memory in given format
};

void implInstruction(const string& line, LRUCache& lruCache);
// EFFECTS: implement corresponding instruction, throw exceptions if any
void throwException();
// EFFECTS: throw exception

int main() { // cache main function
    string line;
    getline(cin, line);
    int mem_size, cache_size;
    stringstream ss;
    ss << line;
    ss >> cache_size >> mem_size; // get the first line of input
    LRUCache lruCache(cache_size, mem_size);
    while (getline(cin, line)) {
        try {
            implInstruction(line, lruCache);
        } catch (int x) { // catch the exception if any
            cout << "ERROR: Address out of bound" << endl;
        } catch (double y) {
            if (y == 10.0) cout << "ERROR: Not enough operands" << endl;
            else if (y == 3.0) cout << "ERROR: Too many operands" << endl;
            else if (y == 20.0) cout << "ERROR: Unknown instruction" << endl;
        } catch (exitPro ex) {
            return 0; // when exit, return 0
        }
    }
    return 0;
}
// constructor
LRUCache::LRUCache(int cache_size, int memory_size):
    mem_size(memory_size),  cur_cache_size(0), max_cache_size(cache_size) {
    memory = new int[memory_size];
    for (int i = 0; i < memory_size; i++) {
        memory[i] = 0;
    }
}

LRUCache::~LRUCache() {
    delete [] memory;
}

bool LRUCache::compare(const LRUCache::block *a, const LRUCache::block *b) {
    return a->address == b->address;
}

int LRUCache::read(int address) { // read
    if (address < 0 || address >= mem_size) throw 3; // out of bound
    block* new_read = new block;
    new_read->address = address;
    new_read->data = memory[address];
    block* blo_remove = cache.remove(compare, new_read); // check whether exists block in cache has the same address
    if (blo_remove) { // if hits, blo_remove has already been removed
        cache.insertFront(blo_remove);
        delete new_read;
        return blo_remove->data; // this data might be different from the data in memory
    }
    else { // if miss
        if (cur_cache_size == max_cache_size) {
            block* blo_last = cache.removeBack();
            memory[blo_last->address] = blo_last->data;
            delete blo_last;
            cache.insertFront(new_read);
        }
        else if (cur_cache_size < max_cache_size) {
            cur_cache_size++;
            cache.insertFront(new_read);
        }
        else cout << "something wrong in read!" << endl;
    }
    return memory[address];
}

void LRUCache::write(int address, int data) { // write
    if (address < 0 || address >= mem_size) throw 3; // out of bound
    block* new_write = new block;
    new_write->address = address;
    new_write->data = data;
    block* blo_remove = cache.remove(compare, new_write);
    if (blo_remove) { // if hits
        blo_remove->data = data;
        cache.insertFront(blo_remove);
        delete new_write;
    }
    else { // if miss
        if (cur_cache_size == max_cache_size) {
            block* blo_last = cache.removeBack();
            memory[blo_last->address] = blo_last->data;
            delete blo_last;
            cache.insertFront(new_write);
        }
        else if (cur_cache_size < max_cache_size) {
            cur_cache_size++;
            cache.insertFront(new_write);
        }
        else cout << "something wrong in write!" << endl;
    }
}

void LRUCache::printCache() {
    for (int i = 0; i < cur_cache_size; i++) {
        block* blo = cache.removeFront();
        cout << blo->address << " " << blo->data << endl;
        cache.insertBack(blo);
    }
}

void LRUCache::printMem() {
    for (int i = 0; i < mem_size; i++) {
        cout << memory[i] << " ";
    }
    cout << endl;
}

void implInstruction(const string& line, LRUCache& lruCache) {
    stringstream ss;
    ss << line;
    string instr;
    ss >> instr;
    string temp;
    if (instr == "READ") {
        ss >> ws; // in case the input is "READ "
        if (ss.rdbuf()->in_avail() == 0) { // no more operands could be read
            throw 10.0;
        }
        int address;
        ss >> address;
        ss >> ws;
        if (ss.rdbuf()->in_avail() != 0) throw 3.0; // still exit operands, too many
        int read_data = lruCache.read(address);
        cout << read_data << endl;
    }
    else if (instr == "WRITE") {
        ss >> ws;
        if (ss.rdbuf()->in_avail() == 0) { // no more operands could be read
            throw 10.0;
        }
        int address, data;
        ss >> address;
        ss >> ws;
        if (ss.rdbuf()->in_avail() == 0) { // no more operands could be read
            throw 10.0;
        }
        ss >> data;
        ss >> ws;
        if (ss.rdbuf()->in_avail() != 0) { // no more operands could be read
            throw 3.0;
        }
        lruCache.write(address, data);
    }
    else if (instr == "PRINTCACHE") lruCache.printCache();
    else if (instr == "PRINTMEM") lruCache.printMem();
    else if (instr == "EXIT") {
        throwException();
    }
    else throw 20.0;
}

void throwException(){
    throw exitPro();
}