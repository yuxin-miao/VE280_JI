template <typename Key_type, typename Value_type> class Map {
public:
// EFFECTS: Returns whether this map is empty.
    bool empty() const;
// EFFECTS: Returns the number of key-value pairs in this map.
    size_t size() const;
// EFFECTS: Returns the value associated with the given key. If
//          the key is not in the map, inserts the key,
// associating it with a value-initialized object of type
// Value_type, and returns the newly inserted value. Value_type& operator[](const Key_type& key);
private:
// Type alias for a key-value pair.
    using Pair_type = std::pair<Key_type, Value_type>;
// Comparator that compares pairs by their key components.
    class PairLess { public:
        bool operator()(...) const; };
// Data representation.
    BinarySearchTree<Pair_type, PairLess> entries; };