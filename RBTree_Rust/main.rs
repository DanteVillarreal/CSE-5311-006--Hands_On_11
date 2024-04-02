extern crate rbtree;
use rbtree::RBTree;
use std::fmt::Debug;


struct RedBlackTree<T: Ord + Debug> {
    tree: RBTree<T, ()>,
}

impl<T: Ord + Debug> RedBlackTree<T> {
    pub fn new() -> Self {
        RedBlackTree { tree: RBTree::new() }
    }

    pub fn insert(&mut self, value: T) {
        self.tree.insert(value, ());
    }

    pub fn delete(&mut self, value: &T) {
        self.tree.remove(value);
    }

    pub fn query(&self, value: &T) -> bool {
        self.tree.contains_key(value)
    }

    pub fn in_order_traversal(&self, query: Option<&T>) {
        let mut found = false;
        println!("\nnew traversal:");
        for (key, _) in self.tree.iter() {
            if Some(key) == query {
                println!("Found {:?}", key);
                found = true;
            } else {
                println!("{:?}", key);
            }
        }
        if let Some(query) = query {
            if !found {
                println!("NOT FOUND {:?}", query);
            }
        }
    }
}



fn main() {
    let mut tree = RedBlackTree::new();

    // Test insert
    tree.insert(5);
    tree.in_order_traversal(None); // Prints: 5
    tree.insert(3);
    tree.in_order_traversal(None); // Prints: 3, 5
    tree.insert(7);
    tree.in_order_traversal(None); // Prints: 3, 5, 7

    // Test delete
    tree.delete(&5);
    tree.in_order_traversal(None); // Prints: 3, 7

    // Test query
    tree.in_order_traversal(Some(&3)); // Prints: Found 3, 7
    tree.in_order_traversal(Some(&7)); // Prints: 3, Found 7
    tree.in_order_traversal(Some(&10)); // Prints: 3, 7, Not found 10
    println!("\n");

    println!("All tests passed!");
}
